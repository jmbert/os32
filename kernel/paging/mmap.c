#include <paging.h>
#include <memory.h>

int mmap(vaddr to, size_t size)
{
    uint64_t n_pages = size / PAGE_SIZE;
    uint64_t start_page = to / PAGE_SIZE;

    for (size_t i = 0; i < n_pages; i++, to += PAGE_SIZE)
    {
        uint64_t alloc = alloc_mem(PAGE_SIZE, MEMMAP_MEM_KERNEL);
        if (alloc == 0)
        {
            return 1;
        }

        if (map_page(to, alloc) == -1)
        {
            return 1;
        }
    }
    
    return 0;
}