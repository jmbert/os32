#ifndef _MEM_H
#define _MEM_H

#include <stdint.h>
#include <multiboot.h>

struct memrange
{
    uint32_t lower;
    uint32_t higher;
};
struct memmap
{
    uint32_t addr;
    uint32_t size;

    uint32_t type;
};

#define MAX_MAP_ENTRIES 0x1000

#define RANGES_CONFLICT(addr1, len1, addr2, len2)   (((addr1 > addr2) && addr1 < (addr2 + len2)) ||\
                                                    ((addr2 > addr1) && addr2 < (addr1 + len1)) ||\
                                                    ((addr2 == addr1)))

extern struct memrange memrange;

extern struct memmap memmap[MAX_MAP_ENTRIES];
extern uint32_t memmaplen;

#define INSERT_MAP(map, position)\
    memmaplen++;\
    for (int __index = (memmaplen) - 1; __index >= position; __index--)\
    {\
        memmap[__index] = memmap[__index - 1];\
    }\
    memmap[position] = map\

enum
{
    MEMMAP_MEM_AVAILABLE = 1,
    MEMMAP_MEM_RESERVED,
    MEMMAP_MEM_ACPI_RECLAIMABLE,
    MEMMAP_MEM_NVS,
    MEMMAP_MEM_BADRAM,

    MEMMAP_MEM_KERNEL,
    MEMMAP_MEM_PAGEFRAMES,
    MEMMAP_MEM_USER,

    MEMMAP_GRUB_MODULES,
};

#define NEWUSERMAP(addr, len) _new_map(addr, len, MEMMAP_MEM_USER) == NULL);
#define NEWPAGINGMAP(addr, len) _new_map(addr, len, MEMMAP_MEM_PAGEFRAMES);
#define NEWKERNELMAP(addr, len) _new_map(addr, len, MEMMAP_MEM_KERNEL);

int _new_map(uint32_t addr, uint32_t len, uint8_t type);

void reserve_modules(multiboot_module_t *modules, uint32_t modules_count);
void reserve_mmemmap(multiboot_info_t *mbinfo, uint32_t mmmap);

uint32_t alloc_mem(uint64_t memsize, uint8_t type);

#endif