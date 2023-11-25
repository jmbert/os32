#include <string.h>


unsigned int strlen(char *str)
{
    unsigned int i = 0;
    for (;*str!='\0';str++, i++);
    return i;
}