#include <tty.h>
#include <vmem.h>

#include <math.h>
#include <string.h>

#include <debug/exec.h>

int framebuffer_width;
int framebuffer_height;

int clear_flag = 0;

int tty_write_buffer(struct virtualterm buf)
{
    static int line_offset = 0;
    int y = 0;
    int x = 0;
    
    for (int i = 0;(x+y*framebuffer_width)*2 < VMEM_SIZE;x++, i++)
    {
        char c = buf.stdout[i + line_offset*framebuffer_width*2];
        char col = buf.stdout[i+1 + line_offset*framebuffer_width*2];

        if (c == '\0')
        {
            break;
        }

        switch (c)
        {
        case '\n':
            x = -2;
            y++;
            break;
        case '\t':
            x += 6;
            break;
        default:
            VMEM[x+y*framebuffer_width*2] = c;
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