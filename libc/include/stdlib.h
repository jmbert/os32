#ifndef _LIBC_STDLIB_H
#define _LIBC_STDLIB_H

#include <sys/cdefs.h>

#include <stddef.h>
#include <stdint.h>

enum
{
    MALLOC_EMPTY = 0xbead,
    MALLOC_KERNEL = 0xdead,
    MALLOC_USER = 0xbeef,
};

struct allocheader
{
    unsigned int tag;
    unsigned int alloc_length;
};

void *malloc(size_t len);

void free(void *_ptr);

#endif