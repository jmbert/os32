#include <stdlib.h>


#ifdef _IN_KERNEL

#include <kmalloc.h>

#endif

void *malloc(size_t len)
{

#ifdef _IN_KERNEL

    static void *arena_current = (void*)ARENA_START;
    static size_t size_left = ARENA_SIZE;
    if (size_left < len)
    {
        return NULL;
    }

    struct allocheader alloc_header = (struct allocheader)
    {
        MALLOC_KERNEL,
        len,
    };


    *(struct allocheader*)arena_current = alloc_header;
    size_left -= sizeof(struct allocheader);
    arena_current = (void*)(((char*)arena_current) + sizeof(struct allocheader));
    void *_ptr = arena_current;
    arena_current = (void*)(((char*)arena_current) + len);
    size_left -= len;

    char *_ptr2 = (char*)_ptr;
    for (int i = 0;i < len; i++, _ptr2++)
    {
        *_ptr2 = 0;
    }


    return _ptr;

#else

#endif

}


void free(void *_ptr)
{

    #ifdef _IN_KERNEL

    struct allocheader *current_header = (struct allocheader*)_ptr;

    if (current_header->tag != MALLOC_EMPTY)
    {
        current_header->tag = MALLOC_EMPTY;
    }

#else

#endif

}