
#include <tty.h>

#include <stdint.h>

int tty_put_char(char c, uint8_t colour) 
{
    if (current_buffer.buffer == NULL)
    {
        return 1;
    }

    if (current_buffer.cursor >= current_buffer.size || current_buffer.cursor < 0) 
    {
        return 1;
    }

	current_buffer.buffer[current_buffer.cursor*2] = c;
    current_buffer.buffer[current_buffer.cursor*2 + 1] = colour;
    current_buffer.cursor++;
    return 0;
}