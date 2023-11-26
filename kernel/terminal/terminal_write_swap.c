#include <terminal.h>
#include <stdio.h>
#include <font.h>
#include <stdlib.h>
#include <colour.h>
#include <debug/exec.h>
#include <proc.h>

static void set_colour(unsigned int x, unsigned int y, colour_t colour, unsigned char *swapbuffer)
{
    unsigned char *buf = _convert_colour(colour, GRAPHICS_PIXELWIDTH);

    for (unsigned int i = 0; i < GRAPHICS_PIXELWIDTH; i++)
    {
        swapbuffer[GRAPHICS_GET_PIXEL_OFFSET(x+i, y)] = buf[i];
    }

    free(buf);
}

static void write_char(unsigned char c, unsigned int sx, unsigned int sy, font_t font, unsigned char *swapbuffer, colour_t fg, colour_t bg)
{
    sx *= font.c_width;
    sy *= font.c_height;
    unsigned char *glyph = GET_GLYPH(c, font);
    for (unsigned int y = 0; y < font.c_height; y++)
    {
        for (unsigned int x = 0; x < font.c_width; x++)
        {
            unsigned long col = (GET_GLYPH_STATE(y, x, glyph, font)) ? fg : bg;
            set_colour(sx+x, sy+y, col, swapbuffer);
        }
    }
}

extern char *stdoutbase;
extern char *stdoutbuf;

void terminal_write_swap()
{

    graphics_swap_buffer_t swap = _proclookup(getpid())->swap_buf;

    unsigned int x = 0;
    unsigned int y = 0;

    unsigned char draw = 0;
    unsigned int printed = 0;

    for (unsigned int i = 0; i < stdoutbuf-stdoutbase; i++ )
    {
        unsigned char c = stdoutbase[i];

        switch (c)
        {
        case '\0':
            return;
            break;
        case '\n':
            x = 0;
            y++;
            draw = 1;
            break;
        case '\t':
            unsigned int toAlign = 4 - (x % 4);
            x += toAlign;
            break;
        default:
            write_char(c, x, y, term_font, swap.buffer, -1, 0);
            x++;
            printed++;
            break;
        }
    }

    graphics_swap(swap);
    
}