#include <tty.h>
#include <ttycol.h>
#include <vmem.h>

#include <math.h>
#include <string.h>
#include <debug/exec.h>

int clear_flag = 0;

uint8_t current_colour_fg;
uint8_t current_colour_bg;

uint32_t framebuffer_width;
uint32_t framebuffer_height;


int tty_write_buffer(struct virtualterm buf)
{
    static int line_offset = 0;
    int y = 0;
    int x = 0;
    
    for (int i = 0;(x+y*framebuffer_width) < VMEM_SIZE;i++)
    {
        char c = buf.stdout[i + line_offset*framebuffer_width];

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
            x += 8;
            break;
        default:
            VMEM[x + y * framebuffer_width*2] = c;
            VMEM[x + y * framebuffer_width*2 + 1] = COL16(current_colour_fg, current_colour_bg);
            x += 2;
            break;
        }

        if (x%framebuffer_width*2 == 0 && x != 0)
        {
            x = 0;
            y++;
        }
    }


    if ((x + y * framebuffer_width)*2 >= framebuffer_width*framebuffer_height*2)
    {
        line_offset++;
    }

    return 0;
}