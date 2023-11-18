#include <memory.h>

#include <multiboot.h>
#include <stddef.h>

#include <debug/exec.h>

struct memrange memrange;

struct kernelmmap kernelmap[1024];
uint32_t kernelmaplen = 0;

multiboot_memory_map_t *memmap;
uint32_t memmap_len;


uint32_t _findmem(uint64_t memsize)
{
    for (size_t i = 0; i < memmap_len; i++)
    {
        multiboot_memory_map_t map = memmap[i];


        uint64_t addr = (map.addr_high << 32) | map.addr_low;
        uint64_t len =  (map.len_high << 32) | map.len_low;


        /* Only care about available areas with enough memory */
        if (map.type != MULTIBOOT_MEMORY_AVAILABLE || len < memsize)
        {
            continue;
        }
        
        for (size_t i = 0; i < kernelmaplen; i++)
        {
            /* If this memory area possibly intersects with the kernelmap area */
            if (addr + len > kernelmap[i].addr)
            {
                /* Find out difference between area starts */
                uint64_t diff = addr - kernelmap[i].addr; 
                if (diff < 0)
                {
                    /* If the area start comes before the kernel start, we may be able to fit the memory in before the kernel map */
                    if (-diff < memsize)
                    {
                        /* We can! Memory before kernel area */
                        return addr;
                    } else
                    {
                        /* No chance on this kernel area */
                        break;
                    }
                } else  /* Check if we can fit the memory in after the kernel map */
                {
                    
                    int64_t size_diff = (addr + len) - (kernelmap[i].addr + kernelmap[i].size);
                    if (size_diff > memsize) /* Find out if theres enough space after the kernel map*/
                    {
                        /* Memory comes right after the kernel */
                        return kernelmap[i].addr + kernelmap[i].size; 
                    } else 
                    {
                        /* No chance here either*/
                        break;
                    }
                }
            }
        }
    }
    
    return 0;
}

uint32_t alloc_mem(uint64_t memsize)
{
    uint32_t found_mem = _findmem(memsize);
    if (found_mem != 0)
    {
        NEWKERNELMAP(found_mem, memsize);
    }
    return found_mem;
}


uint32_t reserve_modules(multiboot_module_t *modules, uint32_t modules_count)
{
    for (size_t i = 0; i < modules_count; i++)
    {
        NEWKERNELMAP(modules->mod_start, modules->mod_end-modules->mod_start);
    }   
}