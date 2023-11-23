#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// A utility function to reverse a string
void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

char* iota(uint64_t num, char* str, uint64_t base)
{
    uint64_t i = 0;
 
    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // Process individual digits
    while (num != 0) {
        uint64_t rem = num % base;
        if (rem > 9)
        {
            str[i++] = 'a' + (rem - 10);
        } else
        {
            str[i++] = '0' + rem;
        }
        num /= base;
    }
 

    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

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
        int longint = 0;
        if (*fmt == 'l')
        {
            longint = 1;
            fmt++;
        }
        switch (*fmt)
        {
        case 's':;
            char *s = va_arg(args, char*);
            for (;*s != '\0';s++,str++)
            {
                *str = *s;
            }
            str--;
            break;

        case 'c':;
            char c = va_arg(args, int);
            *str = c;
            break;
        case 'd':;
            uint64_t d = 0;
            if (longint)
            {   
                d = va_arg(args, uint64_t);
            } else 
            {
                d = va_arg(args, uint32_t);
            }
            char *ds = iota(d, str, 10);
            for (;*ds != '\0';ds++,str++)
            {
                *str = *ds;
            }
            str--;
            break;
        case 'x':;
            uint64_t x = 0;
            if (longint)
            {   
                x = va_arg(args, uint64_t);
            } else 
            {
                x = va_arg(args, uint32_t);
            }
            char *xs = iota(x, str, 16);
            for (;*xs != '\0';xs++,str++)
            {
                *str = *xs;
            }
            str--;
            break;

        default: //
            fmt--;
            *str = *fmt;
            break;
        }
    }
    return 0;
}

int sprintf(char *str, const char *fmt, ...)
{

    va_list args;

    va_start(args, fmt);

    return  vsprintf(str, fmt, args);

}


int vfprintf(FILE *stream, const char *fmt, va_list args)
{
    char *str = (char*)malloc(sizeof(char)*MAX_PRINTF_LIMIT);

    if (str == NULL)
    {
        return 1;
    }
    int err = vsprintf(str, fmt, args);
    if (err)
    {
        free(str);
        return err;
    }


    err = fputs(stream, str);
    free(str);
    return err;
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
        free(str);
        return err;
    }


    err = puts(str);
    free(str);
    return err;
}

int fprintf(FILE *stream, const char *fmt, ...)
{
    
    va_list args;

    va_start(args, fmt);

    return vfprintf(stream, fmt, args);
}

int printf(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    return vprintf(fmt, args);
}
