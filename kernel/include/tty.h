#ifndef _TTY_H
#define _TTY_H

#include <stddef.h>
#include <stdint.h>

extern int framebuffer_width;
extern int framebuffer_height;

struct virtualterm
{
    char *stdout;
    char *stdin;
    char *stderr;

    size_t cursor;

    size_t size;
};

extern struct virtualterm current_term;

int tty_put_char(char c, uint8_t colour);

void tty_set_term(struct virtualterm buf);

int tty_write_buffer(struct virtualterm buf);

int vmem_clear();

#endif