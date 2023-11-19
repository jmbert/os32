
#include <stdint.h>

#include <tty.h>
#include <ttycol.h>

#include <paging.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kmalloc.h>

#include <debug/exec.h>

#include <multiboot.h>
#include <multiboot_helpers.h>

#include <vmem.h>
#include <memory.h>
#include <fs/tar.h>

void kernel_init(struct multiboot_info *mbinfo)
{
	map_pages(ARENA_START, PAGING_RESERVED_END-KERNEL_OFFSET, ARENA_SIZE);
	map_pages(VMEM_START, mbinfo->framebuffer_addr, VMEM_SIZE);

	framebuffer_height = mbinfo->framebuffer_height;
	framebuffer_width = mbinfo->framebuffer_width;


	tty_set_term((struct virtualterm)
	{
		(char*)malloc(sizeof(char)*framebuffer_width*framebuffer_height*2),
		(char*)malloc(sizeof(char)*framebuffer_width*framebuffer_height*2),
		(char*)malloc(sizeof(char)*framebuffer_width*framebuffer_height*2),
		0,
		framebuffer_width*framebuffer_height*2,
		BLACK16,
		LIGHTGREEN16,
	});

	print_maps();


	return;
}
