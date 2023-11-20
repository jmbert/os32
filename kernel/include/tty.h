#ifndef _TTY_H
#define _TTY_H

#include <stddef.h>
#include <stdint.h>

extern uint8_t *font;

#define CHAR_HEIGHT 14
#define CHAR_WIDTH 8

struct virtualterm
{
    char *stdout;
    char *stdin;
    char *stderr;

    uint32_t *swap; 

    size_t cursor;

    size_t size;

    uint32_t default_col_bg;
    uint32_t default_col_fg;
};

struct framebuffer
{
    uint32_t rmask_position;
    uint32_t rmask_width;
    uint32_t gmask_position;
    uint32_t gmask_width;
    uint32_t bmask_position;
    uint32_t bmask_width;

    uint32_t pwidth;
    uint32_t pitch;

    uint32_t width;
    uint32_t height;
};

#define INDEX(x, y) ((x) + (y)*framebuffer.width)

extern struct framebuffer framebuffer;


extern struct virtualterm current_term;

extern uint32_t current_colour_fg;
extern uint32_t current_colour_bg;

int tty_put_char(char c);

void tty_set_term(struct virtualterm buf);

int tty_write_buffer();

int tty_swap();


#endif