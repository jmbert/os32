#include <stdio.h>
#include <string.h>

int vsprintf(char *str, const char *fmt, va_list args)
{
    for (;*fmt != '\0';str++,fmt++)
    {
        if (*fmt != '%')
        {
            *str = *fmt;
            continue;
        }
        fmt++;
        switch (*fmt)
        {
        case 's':
            char *s = va_arg(args, char*);
            for (;*s != '\0';s++,str++)
            {
                *str = *s;
            }
            str--;
            break;

        case 'c':
            char c = va_arg(args, char);
            *str = c;
            break;
        default:
            fmt--;
            *str = *fmt;
            break;
        }
    }
    
}

int sprintf(char *str, const char *fmt, ...)
{

    va_list args;

    va_start(args, fmt);

    int err = vsprintf(str, fmt, args);
    if (err)
    {
        return err;
    }

    return str;

}

int vprintf(const char *fmt, va_list args)
{
    char *str = (char*)malloc(sizeof(char)*MAX_PRINTF_LIMIT);

    if (str == NULL)
    {
        return 1;
    }
    int err = vsprintf(str, fmt, args);
    if (err)
    {
        return err;
    }

    return puts(str);
}

int printf(const char *fmt, ...)
{
    char *str = (char*)malloc(sizeof(char)*MAX_PRINTF_LIMIT);

    if (str == NULL)
    {
        return 1;
    }

    va_list args;

    va_start(args, fmt);

    return vprintf(fmt, args);
}