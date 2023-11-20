
#include <tty.h>

struct virtualterm current_term;

void tty_set_term(struct virtualterm buf)
{
    current_term = buf;
    current_colour_fg = current_term.default_col_fg;
    current_colour_bg = current_term.default_col_bg;
    fill(current_colour_bg);
    tty_write_buffer(current_term);
    tty_swap();
}

void fill(uint32_t col)
{
    for (size_t i = 0; i < framebuffer.pitch * framebuffer.height; i++)
    {
        (current_term.swap)[i] = col;
    }
    
}