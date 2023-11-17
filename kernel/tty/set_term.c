
#include <tty.h>

struct virtualterm current_term;

void tty_set_term(struct virtualterm buf)
{
    current_term = buf;
}