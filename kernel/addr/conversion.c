#include <addr.h>
#include <stddef.h>

#include <paging.h>

#include <debug/exec.h>

paddr vaddrtopaddr(vaddr addr) 
{
    unsigned long pdindex = (unsigned long)addr >> 22;
    unsigned long ptindex = (unsigned long)addr >> 12 & 0x03FF;
 
    unsigned long *pd = (unsigned long *)0xFFFFF000;
    // Here you need to check whether the PD entry is present.
 
    unsigned long *pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    // Here you need to check whether the PT entry is present.
 
    paddr phys = (paddr)((pt[ptindex] & ~0xFFF) + ((unsigned long)addr & 0xFFF));
    return phys;
}