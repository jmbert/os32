
#include <stdint.h>

#include <tty.h>
#include <ttycol.h>

#include <paging.h>

#include <stdio.h>
#include <stdlib.h>
#include <kmalloc.h>

#include <debug/exec.h>

#include <multiboot.h>
#include <multiboot_helpers.h>

#include <vmem.h>

void kernel_init(struct multiboot_info *mbinfo)
{
	map_pages(VMEM_START, mbinfo->framebuffer_addr, VMEM_SIZE);

	framebuffer_width = mbinfo->framebuffer_width;
	framebuffer_height = mbinfo->framebuffer_height;

	map_pages(ARENA_START, PAGING_RESERVED_END-KERNEL_OFFSET, ARENA_SIZE);

	tty_set_term((struct virtualterm)
	{
		(char*)malloc(sizeof(char)*1024),
		(char*)malloc(sizeof(char)*1024),
		(char*)malloc(sizeof(char)*1024),
		0,
		1024,	
	});

	print_mbinfo(mbinfo, MULTIBOOT_INFO_MEM_MAP);

	return;
}
