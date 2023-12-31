#include <paging.h>
#include <memory.h>

#include <debug/exec.h>

int mmap(vaddr to, size_t size, unsigned short flags)
{
    uint64_t alloc = alloc_mem(size, MEMMAP_MEM_KERNEL, PAGE_SIZE);

    map_pages(to, alloc, size, flags);
    
    return 0;
}