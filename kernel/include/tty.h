#ifndef _TTY_H
#define _TTY_H

#include <stddef.h>
#include <stdint.h>

struct textbuffer 
{
    char *buffer;

    size_t size;

    size_t cursor;
};

extern struct textbuffer current_buffer;

int tty_put_char(char c, uint8_t colour);

void tty_set_buffer(struct textbuffer buf);

#endif