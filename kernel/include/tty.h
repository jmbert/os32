#ifndef _TTY_H
#define _TTY_H

#include <stddef.h>
#include <stdint.h>

struct virtualterm
{
    char *stdout;
    char *stdin;
    char *stderr;

    size_t cursor;

    size_t size;

    uint8_t default_col_bg;
    uint8_t default_col_fg;
};

extern struct virtualterm current_term;

extern uint8_t current_colour_fg;
extern uint8_t current_colour_bg;

extern uint32_t framebuffer_width;
extern uint32_t framebuffer_height;

int tty_put_char(char c);

void tty_set_term(struct virtualterm buf);

int tty_write_buffer(struct virtualterm buf);

int vmem_clear();

#endif