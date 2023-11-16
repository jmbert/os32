#ifndef _LIBC_STDIO_H
#define _LIBC_STDIO_H

#include <sys/cdefs.h>
#include <stdarg.h>

#define MAX_PRINTF_LIMIT 0x100

#ifdef _IN_KERNEL

#include <tty.h>

#define MAX_PRINTF_LIMIT (current_buffer.size)

#endif

int putchar(char c);
int puts(const char *str);

int sprintf(char *str, const char *fmt, ...);
int printf(const char *fmt, ...);

int vsprintf(char *str, const char *fmt, va_list args);
int vprintf(const char *fmt, va_list args);

#endif