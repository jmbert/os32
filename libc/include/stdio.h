#ifndef _LIBC_STDIO_H
#define _LIBC_STDIO_H

#include <sys/cdefs.h>
#include <stdarg.h>
#include <bits/io/stdpipes.h>


#ifdef _IN_KERNEL
#include <vfs/fd.h>
#include <terminal.h>
#define WRITE_SWAP() terminal_write_swap() 

#endif

#define EOF -1

#define MAX_PRINTF_LIMIT 0x1000

typedef _OPEN_FILE FILE;

int putchar(char c);

int putc(FILE *stream, char c);

int puts(const char *str);

int sprintf(char *str, const char *fmt, ...);
int printf(const char *fmt, ...);

int vsprintf(char *str, const char *fmt, va_list args);
int vprintf(const char *fmt, va_list args);

int fputs(FILE *stream, const char *str);
int fprintf(FILE *stream, const char *fmt, ...);
int vfprintf(FILE *stream, const char *fmt, va_list args);


#endif