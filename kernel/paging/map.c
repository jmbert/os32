#include <paging.h>
#include <page_alloc.h>

#include <debug/mem.h>
#include <debug/exec.h>


int _map_table(vaddr addr, paddr from, unsigned short flags)
{
    vaddr aligned_addr = PALIGN_ADDR(addr);

    size_t tIndex = (aligned_addr / PAGE_SIZE / TABLE_LENGTH);

    SET_PDE(tIndex, (from | flags | 0x1));

    return 0;
}

int map_page(vaddr addr, paddr from, unsigned short flags)
{
    vaddr aligned_addr = PALIGN_ADDR(addr);

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
        if (_map_table(tIndex*TABLE_COVERAGE, alloc, flags) == -1)
        {
            return -1;
        }
    }


    ptable table = (ptable)(PALIGN_ADDR(GET_PDE(tIndex)) + KERNEL_OFFSET);

    size_t relPIndex = pIndex % TABLE_LENGTH;

    table[relPIndex] = (from | flags | 0x1);

    INVLPG(aligned_addr);

    return 0;
}


int map_pages(vaddr to, paddr from, size_t length, unsigned short flags)
{
    vaddr page_addr = PALIGN_ADDR(to);

    if (length != PALIGN_ADDR(length))
    {
        length = PALIGN_ADDR(length) + PAGE_SIZE;
    }
    
    vaddr end_page_addr = page_addr + length;

    for (;page_addr < end_page_addr;page_addr += PAGE_SIZE, from += PAGE_SIZE) 
    {
        if (map_page(page_addr, from, flags) == -1)
        {
            return -1;
        }
    }

    return 0;
}
