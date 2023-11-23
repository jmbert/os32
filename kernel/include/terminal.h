#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <graphics.h>
#include <fs.h>
#include <font.h>

typedef struct terminal_t
{
    fd_t stdin;
    fd_t stdout;
    fd_t stderr;

    graphics_swap_buffer_t swap;

    unsigned int xPosition;
    unsigned int yPosition;
}terminal_t;

terminal_t create_terminal(unsigned int xPosition, unsigned int yPosition, unsigned int buffer_length);

void terminal_write_swap(terminal_t terminal, font_t font);

#endif