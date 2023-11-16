#include <stdio.h>


int puts(const char *str)
{
#ifdef _IN_KERNEL

    for (;*str!='\0';str++)
    {
        int err = putchar(*str);
        if (err) {return err;}
    }

    return 0;

#else

#endif
}