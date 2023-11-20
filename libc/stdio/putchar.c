#include <stdio.h>

#ifdef _IN_KERNEL

#include <tty.h>

#endif


int putchar(char c)
{
#ifdef _IN_KERNEL
    return tty_put_char(c); 
#else

#endif

}