
#include <paging.h>
#include <memory.h>
#include <string.h>
#include <page_alloc.h> 

void paging_init()
{
    paging_start = alloc_mem(PAGING_RESERVED_SPACE, MEMMAP_MEM_PAGEFRAMES, PAGE_SIZE) + KERNEL_OFFSET;

    ptable pdir = (ptable)pframe_alloc();
    ((ptable)((paddr)pdir + KERNEL_OFFSET))[0x3ff] = PALIGN_ADDR((paddr)pdir) | 0x3;
    paddr ktable = pframe_alloc();
    ((ptable)((paddr)pdir + KERNEL_OFFSET))[0x300] = ktable | 0x3;

    paddr newTable = ktable + KERNEL_OFFSET;
    paddr oldTable = ((paddr)GET_PDE(0x300)) + KERNEL_OFFSET;

    memcpy((void *)PALIGN_ADDR(newTable), (void *)PALIGN_ADDR(oldTable), 4096);
    SET_PDIR(pdir);
}