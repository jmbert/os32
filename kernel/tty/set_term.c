
#include <tty.h>

struct virtualterm current_term;

void tty_set_term(struct virtualterm buf)
{
    current_term = buf;
    vmem_clear();
    current_colour_fg = current_term.default_col_fg;
    current_colour_bg = current_term.default_col_bg;
    tty_write_buffer(current_term);
}