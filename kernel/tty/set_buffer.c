
#include <tty.h>

struct textbuffer current_buffer;

void tty_set_buffer(struct textbuffer buf)
{
    current_buffer = buf;
}