#include <graphics.h>

#include <string.h>

void graphics_swap(graphics_swap_buffer_t buffer)
{
    memcpy((void*)(FRAMEBUFFER_ADDRESS + buffer.offset), buffer.buffer, buffer.size);
}