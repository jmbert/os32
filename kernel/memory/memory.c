#include <memory.h>

#include <stdio.h>

#include <multiboot.h>
#include <stddef.h>
#include <info/link_info.h>
#include <debug/exec.h>

struct memrange memrange;

struct memmap memmap[MAX_MAP_ENTRIES];
uint64_t memmaplen = 0;

int _new_map(uint64_t addr, uint64_t len, uint8_t type)
{
    
    for (int i = 0;i < memmaplen;i++)
    {
        uint8_t maptype = memmap[i].type;

        uint64_t mapaddr = memmap[i].addr;
        uint64_t maplen = memmap[i].size;

        /* Check if the maps conflict */
        if (RANGES_CONFLICT(addr, len, mapaddr, maplen))
        {
            
            if (maptype != MEMMAP_MEM_AVAILABLE)
            {
                return 1;
            }
            /* Check the space that would be available on overwrite */
            uint64_t space = (addr + len) - mapaddr;
            if (space <= 0)
            {
                continue;
            }
            if (space < len)
            {
                continue;
            }
            struct memmap newmap;
            newmap.addr = addr;
            newmap.size = len;
            newmap.type = type;

            struct memmap premap;
            premap.addr = mapaddr;
            premap.size = addr - mapaddr;
            premap.type = maptype;

            struct memmap postmap;
            postmap.addr = addr+len;
            postmap.size = (mapaddr + maplen) - (addr + len);
            postmap.type = maptype;

            int maps_pushed = 0;

            if (premap.size > 0)
            {
                memmap[i] = premap;
                maps_pushed++;
                INSERT_MAP(newmap, i+(maps_pushed));
                maps_pushed++;
            } else
            {
                memmap[i] = newmap;
                maps_pushed++;
            }


            if (postmap.size > 0)
            {
                
                INSERT_MAP(postmap, i+maps_pushed);
            }


            return 0;
        }
    }
    return 1;
}



uint64_t _findmem(uint64_t memsize, uint64_t align)
{
    for (size_t i = 0; i < memmaplen; i++)
    {
        struct memmap map = memmap[i];

        /* 0 is our failure address, do not allocate there */
        if (map.addr == 0)
        {
            continue;
        }

        uint64_t toAlign = align - (map.addr % align);
        if (toAlign != align)
        {
            map.addr += toAlign;
        }

        /* Only care about available areas with enough memory */
        if (map.type == MULTIBOOT_MEMORY_AVAILABLE && map.size >= memsize)
        {
            return map.addr;
        }
    }
    return 0;
}

uint64_t alloc_mem(uint64_t memsize, uint8_t type, uint64_t align)
{
    uint64_t found_mem = _findmem(memsize, align);
    if (found_mem != 0)
    {
        _new_map(found_mem, memsize, type);
    }
    return found_mem;
}