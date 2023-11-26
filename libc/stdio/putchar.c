#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int putc(FILE *stream, char c)
{
    if (stream == NULL)
    {
        return -2;
    }

    void *cbuffer = malloc(sizeof(char));
    stream->node->ops.write(stream->node, cbuffer, 1, 0);
    return 0;

}

int putchar(char c)
{
    return putc(_GET_STDOUT(), c);
}