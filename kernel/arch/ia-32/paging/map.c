#include <arch-specific/paging.h>
#include <arch-specific/page_alloc.h>

#include <debug/mem.h>
#include <debug/exec.h>


int _map_table(vaddr addr, paddr from)
{
    vaddr aligned_addr = ALIGN_ADDR(addr);

    size_t tIndex = (aligned_addr / PAGE_SIZE / TABLE_LENGTH);

    SET_PDE(tIndex, (from | 0x3));

    return 0;
}

int _map_page(vaddr addr, paddr from)
{
    vaddr aligned_addr = ALIGN_ADDR(addr);

    size_t pIndex = aligned_addr / PAGE_SIZE;

    size_t tIndex = (pIndex / TABLE_LENGTH);

    
    paddr tableEntry = GET_PDE(tIndex);
    
    if (!(tableEntry & 1) )
    {
        paddr alloc = pframe_alloc();
        if (alloc == 0)
        {
            pframe_free(alloc);
            return -1;
        }
        if (_map_table(tIndex*TABLE_COVERAGE, alloc) == -1)
        {
            return -1;
        }
    }


    paddr *table = ALIGN_ADDR((paddr*)GET_PDE(tIndex)) + KERNEL_OFFSET;

    size_t relPIndex = pIndex % TABLE_LENGTH;

    table[relPIndex] = (from | 0x3);

    INVLPG(aligned_addr);

    return 0;
}


int map_pages(vaddr to, paddr from, size_t length)
{
    vaddr page_addr = ALIGN_ADDR(to);
    
    vaddr end_page_addr = page_addr + ALIGN_ADDR(length) + 1;

    for (;page_addr < end_page_addr;page_addr += PAGE_SIZE, from += PAGE_SIZE) 
    {
        if (_map_page(page_addr, from) == -1)
        {
            return -1;
        }
    }

    return 0;
}
