#ifndef _MEM_H
#define _MEM_H

#include <stdint.h>
#include <multiboot.h>

struct memrange
{
    uint32_t lower;
    uint32_t higher;
};

extern struct memrange memrange;

struct kernelmmap
{
    uint32_t addr;
    uint32_t size;
};

extern struct kernelmmap kernelmap[1024];
extern uint32_t kernelmaplen;

extern multiboot_memory_map_t *memmap;
extern uint32_t memmap_len;

#define NEWKERNELMAP(addr, len) kernelmap[kernelmaplen++] = (struct kernelmmap){\
    addr,\
    len\
};

uint32_t reserve_modules(multiboot_module_t *modules, uint32_t modules_count);

uint32_t alloc_mem(uint64_t memsize);

#endif