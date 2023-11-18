#ifndef _IA32_PAGING_H
#define _IA32_PAGING_H

#include <addr.h>
#include <stddef.h>

typedef paddr *ptable;

extern vaddr paging_start;

#define MAX_FRAMES 0x100

#define PAGE_SIZE 0x1000
#define TABLE_LENGTH 0x400
#define PAGE_MASK 0xfffff000

#define PAGING_RESERVED_START paging_start

#define PAGING_RESERVED_SPACE MAX_FRAMES*TABLE_LENGTH*4
#define PAGING_RESERVED_END (PAGING_RESERVED_START + PAGING_RESERVED_SPACE)
#define TABLE_COVERAGE TABLE_LENGTH * PAGE_SIZE

#define ALIGN_ADDR(addr) ((paddr)addr & PAGE_MASK)

extern void _invlpg(paddr addr);
#define INVLPG(addr) _invlpg(addr)

#define SET_PDIR(addr) asm("mov %0, %%eax;mov %%eax, %%cr3" :: "m"(addr)) 
#define GET_PDIR() ((paddr*)0xFFFFF000)

#define SET_PDE(index, value) (GET_PDIR())[index] = value
#define GET_PDE(index) (GET_PDIR()[index])

int map_pages(vaddr to, paddr from, size_t length);

#endif