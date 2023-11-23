#include <stdio.h>


int fputs(FILE *stream, const char *str)
{
    for (;*str!='\0';str++)
    {
        int err = putc(stream, *str);
        if (err) {return err;}
    }

    return 0;
}

int puts(const char *str)
{
    for (;*str!='\0';str++)
    {
        int err = putchar(*str);
        if (err) {return err;}
    }

    return 0;
}