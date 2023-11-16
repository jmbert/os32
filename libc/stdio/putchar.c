#include <stdio.h>

#ifdef _IN_KERNEL

#include <tty.h>
#include <ttycol.h>

#endif


int putchar(char c)
{
#ifdef _IN_KERNEL
    return tty_put_char(c, COL16(GREEN16, BLACK16)); 
#else

#endif

}