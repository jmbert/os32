#include <addr.h>
#include <stddef.h>

#include <paging.h>

#include <debug/exec.h>

paddr vaddrtopaddr(vaddr addr) 
{
    paddr pdindex = (paddr)addr >> 22;
    paddr ptindex = (paddr)addr >> 12 & 0x03FF;

    ptable pt = ((ptable)0xFFC00000) + (TABLE_LENGTH * pdindex);
    if (!(*pt & 0x1))
    {
        return 0;
    }
 
    paddr phys = (paddr)((pt[ptindex] & ~0xFFF) + ((paddr)addr & 0xFFF));
    return phys;
}