#include <stdio.h>
#include <stddef.h>

int putc(FILE *stream, char c)
{
    if (stream == NULL)
    {
        return -2;
    }
    if (FILE_LENGTH_LEFT(stream) > 0)
    {
        *(stream->buf) = c;
        (stream->buf)++;
        return 0;
    } else
    {
        return EOF;
    }
}

int putchar(char c)
{
    return putc(_GET_STDOUT(), c);
}