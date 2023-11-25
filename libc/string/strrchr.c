#include <stdlib.h>

char *strrchr (char *s, char c)
{
    char *rtnval = NULL;

    for (;*s != '\0';s++) {
        if (*s == c)
        {
            rtnval = s;
        }
    };

    return rtnval;
}