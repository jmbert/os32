#ifndef _MEM_H
#define _MEM_H

#include <stdint.h>
#include <multiboot.h>

struct memrange
{
    uint64_t lower;
    uint64_t higher;
};
struct memmap
{
    uint64_t addr;
    uint64_t size;

    uint64_t type;
};

#define MAX_MAP_ENTRIES 0x10000

#define RANGES_CONFLICT(addr1, len1, addr2, len2)   (((addr1 > addr2) && addr1 < (addr2 + len2)) ||\
                                                    ((addr2 > addr1) && addr2 < (addr1 + len1)) ||\
                                                    ((addr2 == addr1)))

extern struct memrange memrange;

extern struct memmap memmap[MAX_MAP_ENTRIES];
extern uint64_t memmaplen;

#define INSERT_MAP(map, position)\
    memmaplen++;\
    for (int __index = (memmaplen) - 1; __index >= position; __index--)\
    {\
        memmap[__index] = memmap[__index - 1];\
    }\
    memmap[position] = map\

#define MOVE_DOWN(index)\
    for (int __index = index; __index < memmaplen-1; __index++)\
    {\
        memmap[__index] = memmap[__index+1];\
    }\
    memmaplen--;\

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

#define NEWUSERMAP(addr, len) _new_map(addr, len, MEMMAP_MEM_USER);
#define NEWPAGINGMAP(addr, len) _new_map(addr, len, MEMMAP_MEM_PAGEFRAMES);
#define NEWKERNELMAP(addr, len) _new_map(addr, len, MEMMAP_MEM_KERNEL);

int _new_map(uint64_t addr, uint64_t len, uint8_t type);

void reserve_mem(multiboot_info_t *mbinfo);

uint64_t alloc_mem(uint64_t memsize, uint8_t type, uint64_t align);


void print_maps();

#endif