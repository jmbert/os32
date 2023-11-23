#include <proc.h>

#include <bits/defs/paging.h>

#include <memory.h>

#include <stdlib.h>

#include <debug/exec.h>

#include <paging.h>
#include <page_alloc.h>


ptable _initialise_pdir()
{
    paddr pdir_phys = pframe_alloc();
    ptable pdir = (ptable)(pdir_phys + KERNEL_OFFSET);

    /* Copy over all kernel page directories (over index 0xc00) */
    for ( unsigned int i = _KERNEL_PAGETABLES_START / sizeof(uword_t); i < TABLE_LENGTH; i++)
    {
        pdir[i] = GET_PDE(i);
    }


    /* Finally, we recursively map the page directory */
    pdir[TABLE_LENGTH-1] = (paddr)pdir_phys | 0x3;

    return (ptable)pdir_phys;
}