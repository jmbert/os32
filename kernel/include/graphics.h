#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <bits/defs/framebuffer.h>

#include <multiboot.h>

typedef struct
{
    unsigned int bit_depth;
     
    unsigned int width;
    unsigned int height;
}_graphics_info_t;


typedef struct 
{
    unsigned char *buffer;
    unsigned long size;
    unsigned long offset;
}graphics_swap_buffer_t;

extern _graphics_info_t _graphics_info;

#define GRAPHICS_BITDEPTH (_graphics_info.bit_depth)
#define GRAPHICS_PIXELWIDTH ((GRAPHICS_BITDEPTH/8) + ((GRAPHICS_BITDEPTH % 8 == 0) ? 0 : 1))
#define GRAPHICS_WIDTH (_graphics_info.width)
#define GRAPHICS_PITCH (GRAPHICS_WIDTH * GRAPHICS_PIXELWIDTH)
#define GRAPHICS_HEIGHT (_graphics_info.height)
#define GRAPHICS_SIZE (GRAPHICS_PITCH*GRAPHICS_HEIGHT)

#define _GRAPHICS_PIXEL_BUFFER ((unsigned char*)FRAMEBUFFER_ADDRESS)

#define GRAPHICS_GET_PIXEL_OFFSET(_x, _y) ((_x) * GRAPHICS_PIXELWIDTH + (_y) * GRAPHICS_PITCH)

void graphics_swap(graphics_swap_buffer_t buffer);

void initialise_graphics_info(multiboot_info_t *mbinfo);

#endif