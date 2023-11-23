
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

extern void kernel_main(multiboot_info_t *mbinfo, terminal_t term, font_t font);

void kernel_init(multiboot_info_t *mbinfo)
{
	mman_init(mbinfo);

	paging_init();

	mmap(ARENA_START, ARENA_SIZE);

	initialise_graphics_info(mbinfo);

	map_pages(FRAMEBUFFER_ADDRESS, mbinfo->framebuffer_addr, GRAPHICS_SIZE);

	terminal_t term = create_terminal(0, 0, 0x1000);

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

    struct tar_header *f_header = tar_lookup(initramfs.mod_start+KERNEL_OFFSET, "./initramfs/fonts/font.bin");
    unsigned char *fontdat = (unsigned char *)DATA_FROM_HEADER(f_header);

    font_t font = (font_t)
    {
        .c_height = 14,
        .c_width = 8,
        .chardata = fontdat,
    };


    pid_t kmain = new_process((uword_t)kernel_main, PROC_MODE_KERNEL);
    switch_process_nosave(kmain);
}
