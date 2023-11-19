#include <memory.h>

#include <multiboot.h>
#include <stddef.h>
#include <info/link_info.h>
#include <debug/exec.h>

struct memrange memrange;

struct memmap memmap[MAX_MAP_ENTRIES];
uint32_t memmaplen = 0;



uint32_t _findmem(uint64_t memsize)
{
    for (size_t i = 0; i < memmaplen; i++)
    {
        struct memmap map = memmap[i];

        /* Only care about available areas with enough memory */
        if (map.type == MULTIBOOT_MEMORY_AVAILABLE && map.size >= memsize)
        {
            return map.addr;
        }
    }
    return 0;
}

uint32_t alloc_mem(uint64_t memsize, uint8_t type)
{
    uint32_t found_mem = _findmem(memsize);
    if (found_mem != 0)
    {
        _new_map(found_mem, memsize, type);
    }
    return found_mem;
}


void reserve_modules(multiboot_module_t *modules, uint32_t modules_count)
{
    for (size_t i = 0; i < modules_count; i++)
    {
        _new_map(modules->mod_start, modules->mod_end-modules->mod_start, MEMMAP_GRUB_MODULES);
    }   
}

void reserve_mmemmap(multiboot_info_t *mbinfo, uint32_t mmmap)
{
    
    if (mbinfo->mmap_addr != 0)
    {
        multiboot_memory_map_t *map = (multiboot_memory_map_t *)(mbinfo->mmap_addr + KERNEL_OFFSET);

        for (int traveled = 0; traveled < mbinfo->mmap_length; traveled+= map->size + sizeof(map->size), map = (multiboot_memory_map_t*)((char*)map + map->size +sizeof(map->size)))
        {
            struct memmap nmap = (struct memmap)
            {
                map->addr_low,
                map->len_low,
                map->type
            };

            memmap[memmaplen++] = nmap;
        }
    }
}

int _new_map(uint32_t addr, uint32_t len, uint8_t type)
{
    for (int i = 0;i < memmaplen;i++)
    {
        uint8_t maptype = memmap[i].type;

        uint32_t mapaddr = memmap[i].addr;
        uint32_t maplen = memmap[i].size;

        /* Check if the maps conflict */
        if (RANGES_CONFLICT(addr, len, mapaddr, maplen))
        {
            
            if (maptype != MEMMAP_MEM_AVAILABLE)
            {
                return 1;
            }
            /* Check the space that would be available on overwrite */
            uint32_t space = (addr + len) - mapaddr;
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

void print_mmap_type(uint32_t type)
{
    switch (type)
    {
    case MEMMAP_MEM_AVAILABLE:
        printf("AVAILABLE");
        break;
    case MEMMAP_MEM_RESERVED:
        printf("RESERVED");
        break;
    case MEMMAP_MEM_BADRAM:
        printf("BADRAM");
        break;
    case MEMMAP_GRUB_MODULES:
        printf("MODULE");
        break;
    case MEMMAP_MEM_ACPI_RECLAIMABLE:
        printf("ACPI");
        break;
    case MEMMAP_MEM_USER:
        printf("USER");
        break;
    case MEMMAP_MEM_KERNEL:
        printf("KERNEL");
        break;
    case MEMMAP_MEM_NVS:
        printf("NVS");
        break;
    case MEMMAP_MEM_PAGEFRAMES:
        printf("PAGEFRAMES");
        break;
    
    default:
        printf("UNKNOWN");
        break;
    }
}

void print_maps()
{

    printf("Memory Map:\n");

    for (int i = 0;i < memmaplen;i++)
    {
        printf("Base Address:%x,", memmap[i].addr);
        printf("Length:%x,", memmap[i].size);
        print_mmap_type(memmap[i].type);
        printf("\n");
    }
}