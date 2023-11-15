#include <string.h>

void *memset(void *str, int c, size_t n)
{
#ifdef _IN_KERNEL

    for (char *inbuf = (char*)str;inbuf-(char*)str < n;*inbuf=c, inbuf++);

    return str;
#else


#endif
}