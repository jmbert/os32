#ifndef _LIBC_STDLIB_H
#define _LIBC_STDLIB_H

#include <sys/cdefs.h>

#include <stddef.h>
#include <stdint.h>

enum
{
    MALLOC_KERNEL = 0xdead,
    MALLOC_USER = 0xbeef,
};

struct allocheader
{
    uint16_t malloc_type;
    size_t alloc_length;
};

void *malloc(size_t len);

#endif