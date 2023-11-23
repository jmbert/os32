#include <graphics.h>

#include <stdio.h>

_graphics_info_t _graphics_info;

void initialise_graphics_info(multiboot_info_t *mbinfo)
{
    _graphics_info.bit_depth = mbinfo->framebuffer_bpp;
    _graphics_info.height = mbinfo->framebuffer_height;
    _graphics_info.width = mbinfo->framebuffer_width;
}