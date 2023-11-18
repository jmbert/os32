#include <info/link_info.h>

#include <arch-specific/paging.h>
#include <arch-specific/page_alloc.h>

#include <debug/exec.h>

#include <string.h>
#include <multiboot.h>

#include <memory.h>

#include <arch-specific/gdt.h>
#include <arch-specific/idt.h>

vaddr paging_start;

void arch_init(struct multiboot_info *mbinfo)
{
    memmap = (multiboot_memory_map_t*)(mbinfo->mmap_addr + KERNEL_OFFSET);
    memmap_len = mbinfo->mmap_length;

    reserve_modules((multiboot_module_t*)(mbinfo->mods_addr + KERNEL_OFFSET), mbinfo->mods_count);

    NEWKERNELMAP(KERNEL_PHYS_START, KERNEL_SIZE);

    paging_start = alloc_mem(PAGING_RESERVED_SPACE) + KERNEL_OFFSET;
    

    init_gdt();
    init_idt();

    ptable pdir = (ptable)pframe_alloc();
    ((ptable)((paddr)pdir + KERNEL_OFFSET))[0x3ff] = ALIGN_ADDR((paddr)pdir) | 0x3;
    paddr ktable = pframe_alloc(); 
    ((ptable)((paddr)pdir + KERNEL_OFFSET))[0x300] = ktable | 0x3;
    
    paddr newTable = ktable + KERNEL_OFFSET;
    paddr oldTable = ((paddr)GET_PDE(0x300)) + KERNEL_OFFSET;
    

    memcpy((void*)ALIGN_ADDR(newTable), (void*)ALIGN_ADDR(oldTable), 4096);
    SET_PDIR(pdir);
}