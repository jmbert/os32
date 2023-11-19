
#include <arch-specific/info.h>

#if (TARGET==IA32)

#include <arch-specific/paging.h>

#else
#error "Unknown Target"
#endif


int mmap(vaddr to, size_t size);