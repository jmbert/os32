#include <stdio.h>


int fputs(FILE *stream, const char *str)
{
    stream->node->ops.write(stream->node, (void*)str, strlen(str), 0);

    return 0;
}

int puts(const char *str)
{
    fputs(_GET_STDOUT(), str);

    terminal_write_swap();
    return 0;
}