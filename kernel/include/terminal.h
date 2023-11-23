#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <graphics.h>
#include <fs.h>
#include <font.h>

extern font_t term_font;

void terminal_write_swap(graphics_swap_buffer_t swap);

#endif