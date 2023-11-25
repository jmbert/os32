#ifndef _PAGING_H
#define _PAGING_H

#include <addr.h>
#include <stddef.h>

typedef paddr *ptable;

extern vaddr paging_start;

#define MAX_FRAMES 0x100

#define PAGE_SIZE 0x1000
#define TABLE_LENGTH 0x400
#define PAGE_MASK 0xfffff000
#define PALIGN_ADDR(addr) ((paddr)addr & PAGE_MASK)

#define PAGING_RESERVED_START paging_start

#define PAGING_RESERVED_SPACE MAX_FRAMES*TABLE_LENGTH*4
#define PAGING_RESERVED_END (PAGING_RESERVED_START + PAGING_RESERVED_SPACE)
#define TABLE_COVERAGE TABLE_LENGTH * PAGE_SIZE

#define INVLPG(addr) _invlpg(addr)
#define SET_PDIR(addr) asm("mov %0, %%eax;mov %%eax, %%cr3" :: "m"(addr)) 
#define GET_PDIR() ((ptable)0xFFFFF000)
#define SET_PDE(index, value) (GET_PDIR())[index] = value
#define GET_PDE(index) (GET_PDIR()[index])

#define GET_PDIR_PHYS() (PALIGN_ADDR(GET_PDE(0x3ff)))

typedef enum
{
    PAGE_PRESENT = 1 << 0,
    PAGE_WRITABLE = 1 << 1,
    PAGE_USER = 1 << 2,
    PAGE_WRITETHROUGH = 1 << 3,
    PAGE_CACHE_DISABLE = 1 << 4,
}_page_flags_e;

extern void _invlpg(paddr addr);

void paging_init();

int map_page(vaddr to, paddr from, unsigned short flags);

int map_pages(vaddr to, paddr from, size_t length, unsigned short flags);

int mmap(vaddr to, size_t size, unsigned short flags);

#endif