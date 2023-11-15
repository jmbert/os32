#include <info/link_info.h>

#include <arch-specific/paging.h>
#include <arch-specific/page_alloc.h>

#include <debug/exec.h>

#include <string.h>

void arch_init()
{
    paddr pdir = pframe_alloc();
    ((paddr*)(pdir + KERNEL_OFFSET))[0x3ff] = ALIGN_ADDR(pdir) | 0x3;
    paddr ktable = pframe_alloc(); 
    ((paddr*)(pdir + KERNEL_OFFSET))[0x300] = ktable | 0x3;
    
    paddr newTable = ktable + KERNEL_OFFSET;
    paddr oldTable = ((paddr)GET_PDE(0x300)) + KERNEL_OFFSET;
    

    memcpy(ALIGN_ADDR(newTable), ALIGN_ADDR(oldTable), 4096);
    SET_PDIR(pdir);
}