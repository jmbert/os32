#ifndef _LIBC_STDIO_H
#define _LIBC_STDIO_H

#include <sys/cdefs.h>

#ifdef _IN_KERNEL

#include <tty.h>

#endif


int putchar(char c);


#endif