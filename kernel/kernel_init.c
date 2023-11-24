
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

vaddr paging_start;

extern void kernel_main();

void kernel_init(multiboot_info_t *mbinfo)
{
	mman_init(mbinfo);

	paging_init();

	mmap(ARENA_START, ARENA_SIZE);

	initialise_graphics_info(mbinfo);

	map_pages(FRAMEBUFFER_ADDRESS, mbinfo->framebuffer_addr, GRAPHICS_SIZE);


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

    _new_fs_from_mem((void*)(initramfs.mod_start + KERNEL_OFFSET));
    HALT();

    kernel_pdir = (ptable)GET_PDIR_PHYS();

    pid_t kmain = new_process((uword_t)kernel_main, PROC_MODE_KERNEL);
    switch_process_nosave(kmain);
}
