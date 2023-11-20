#include <tty.h>
#include <ttycol.h>
#include <vmem.h>

#include <math.h>
#include <string.h>
#include <debug/exec.h>

int clear_flag = 0;

struct framebuffer framebuffer;

uint32_t current_colour_fg;
uint32_t current_colour_bg;

uint8_t *font = NULL;


void write_char(uint32_t x, uint32_t y, char c)
{
    uint8_t *charmap = font + ((uint32_t)c)*CHAR_HEIGHT;

    x *= CHAR_WIDTH;
    y *= CHAR_HEIGHT;

    for (int cx = 0; cx < CHAR_WIDTH; cx++)
    { 
        for (int cy = 0; cy < CHAR_HEIGHT; cy++)
        {
            uint8_t is_fg = charmap[cy] & 1 << ((CHAR_WIDTH-1)-cx);


            (current_term.swap)[INDEX(x+cx, y+cy)] = is_fg ? current_colour_fg : current_colour_bg;
        }
    }

}

int tty_write_buffer()
{
    static int line_offset = 0;
    int y = 0;
    int x = 0;

    int printed = 0;
    
    for (int i = 0;(x+y*framebuffer.width) < VMEM_SIZE;i++)
    {
        char c = current_term.stdout[i + line_offset*framebuffer.height/CHAR_HEIGHT];

        if (c == '\0')
        {
            break;
        }

        switch (c)
        {
        case '\n':
            x = 0;
            y++;
            break;
        case '\t':
            int toAlign = 4 - (x % 4);
            x += toAlign;
            break;
        default:
            write_char(x, y, c);
            printed++;
            x++;
            break;
        }

        if (x%framebuffer.width == 0 && x != 0)
        {
            x = 0;
            y++;
        }
    }


    if (y >= framebuffer.height/CHAR_HEIGHT)
    {
        line_offset++;
    }

    if (printed > 0)
    {
        tty_swap();
    }


    return 0;
}

int tty_swap()
{
    memcpy(VMEM, current_term.swap, VMEM_SIZE);
}