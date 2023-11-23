
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

vaddr paging_start;

extern void kernel_main(multiboot_info_t *mbinfo);

void kernel_init(multiboot_info_t *mbinfo)
{
	mman_init(mbinfo);

	paging_init();

	mmap(ARENA_START, ARENA_SIZE);

	initialise_graphics_info(mbinfo);

	map_pages(FRAMEBUFFER_ADDRESS, mbinfo->framebuffer_addr, GRAPHICS_SIZE);

	kernel_main(mbinfo);
}
