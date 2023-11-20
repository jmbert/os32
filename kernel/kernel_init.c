
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
	framebuffer.height = mbinfo->framebuffer_height;
	framebuffer.width = mbinfo->framebuffer_width;
	framebuffer.pitch = mbinfo->framebuffer_pitch;
	framebuffer.pwidth = mbinfo->framebuffer_bpp/8;
	framebuffer.rmask_position = mbinfo->framebuffer_red_field_position;
	framebuffer.rmask_width = mbinfo->framebuffer_red_mask_size;
	framebuffer.gmask_position = mbinfo->framebuffer_green_field_position;
	framebuffer.gmask_width = mbinfo->framebuffer_green_field_position;
	framebuffer.bmask_position = mbinfo->framebuffer_blue_field_position;
	framebuffer.bmask_width = mbinfo->framebuffer_blue_field_position;

	mmap(ARENA_START, ARENA_SIZE);
	map_pages(VMEM_START, mbinfo->framebuffer_addr, VMEM_SIZE);


	multiboot_module_t initramfs;

	for (size_t i = 0; i < mbinfo->mods_count; i++)
	{
		multiboot_module_t mod = ((multiboot_module_t*)(mbinfo->mods_addr + KERNEL_OFFSET))[i];
		if (strcmp((char*)(mod.cmdline + KERNEL_OFFSET), "initramfs") == 0)
		{
			initramfs = mod;
		}
	}
	
	struct tar_header *font_file = tar_lookup(initramfs.mod_start + KERNEL_OFFSET, "./initramfs/fonts/font.bin");
	font = (uint64_t*)DATA_FROM_HEADER(font_file);


	tty_set_term((struct virtualterm)
	{
		(char*)malloc(sizeof(char)*framebuffer.width*framebuffer.height*2),
		(char*)malloc(sizeof(char)*framebuffer.width*framebuffer.height*2),
		(char*)malloc(sizeof(char)*framebuffer.width*framebuffer.height*2),
		(uint32_t*)malloc(VMEM_SIZE),
		0,
		framebuffer.width*framebuffer.height*2,
		COLRGB(0, 30, 127),
		COLRGB(0, 255, 50),
	});

	print_mbinfo(mbinfo, MULTIBOOT_INFO_FRAMEBUFFER_INFO);

	return;
}
