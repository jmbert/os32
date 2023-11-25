
#include <stdint.h>

#include <paging.h>
#include <page_alloc.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kmalloc.h>

#include <debug/exec.h>

#include <multiboot.h>
#include <multiboot_helpers.h>

#include <memory.h>
#include <fs/tar.h>

#include <terminal.h>
#include <proc.h>
#include <font.h>
#include <gdt.h>
#include <idt.h>
#include <interrupts.h>

vaddr paging_start;

extern void kernel_main();


void kernel_init(multiboot_info_t *mbinfo)
{
    gdt_init();
    idt_init();

	mman_init(mbinfo);

	paging_init();

	mmap(ARENA_START, ARENA_SIZE, PAGE_WRITABLE);

	initialise_graphics_info(mbinfo);

	map_pages(FRAMEBUFFER_ADDRESS, mbinfo->framebuffer_addr, GRAPHICS_SIZE, PAGE_WRITABLE);


    multiboot_module_t initramfs;
    for (unsigned int i = 0; i < mbinfo->mods_count; i++)
    {
        multiboot_module_t mod = ((multiboot_module_t *)(mbinfo->mods_addr + KERNEL_OFFSET))[i];

        if (strcmp((char*)(mod.cmdline + KERNEL_OFFSET), "initramfs") == 0)
        {
            initramfs = mod;
            break;
        }
    }

    unsigned int initramfsroot = initramfs.mod_start + KERNEL_OFFSET;
    file_system = convert_to_vfs(initramfsroot);
    unsigned char *fontdata = (unsigned char *)DATA_FROM_HEADER(tar_lookup(initramfsroot, "./fonts/font.bin"));

    term_font = (font_t)
    {
        .c_height = 14,
        .c_width = 8,
        .chardata = fontdata,
    };

    register_interrupt(div0_handler, EXCEPTION_DIV0, IDT_GATE_TYPE_TRAP32 | IDT_GATE_PRIVILEGE_KERNEL);
    register_interrupt(double_fault_handler, EXCEPTION_DOUBLE_FAULT, IDT_GATE_TYPE_TRAP32 | IDT_GATE_PRIVILEGE_KERNEL);
    register_interrupt(page_fault_handler, EXCEPTION_PAGE_FAULT, IDT_GATE_TYPE_TRAP32 | IDT_GATE_PRIVILEGE_KERNEL);
    register_interrupt(gpf_handler, EXCEPTION_GENERAL_PROTECTION_FAULT, IDT_GATE_TYPE_TRAP32 | IDT_GATE_PRIVILEGE_KERNEL);

    kernel_pdir = (ptable)GET_PDIR_PHYS();

    pid_t kmain = new_process((uword_t)kernel_main, PROC_MODE_KERNEL);
    pid_t umain = new_process((uword_t)0, PROC_MODE_USER);
    switch_process_nosave(kmain);
}
