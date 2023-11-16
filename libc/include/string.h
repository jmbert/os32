#ifndef _LIBC_STRING_H
#define _LIBC_STRING_H

#include <sys/cdefs.h>

#include <stddef.h>


void *memset(void *str, int c, size_t n);

void *memcpy(void *destination, const void *source, size_t num);


#endif