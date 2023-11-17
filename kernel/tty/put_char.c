
#include <tty.h>

#include <stdint.h>

#include <debug/exec.h>

int tty_put_char(char c, uint8_t colour) 
{
    if (current_term.stdout == NULL)
    {
        return 1;
    }

    if (current_term.cursor >= current_term.size || current_term.cursor < 0) 
    {
        return 1;
    }

	current_term.stdout[current_term.cursor*2] = c;
    current_term.stdout[current_term.cursor*2 + 1] = colour;
    current_term.cursor++;

    if (c == '\n')
    {
        vmem_clear();
        tty_write_buffer(current_term);
    }

    return 0;
}