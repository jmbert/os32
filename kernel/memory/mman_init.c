
#include <memory.h>
#include <info/link_info.h>
#include <stddef.h>
#include <stdint.h>


void _reserve_modules(multiboot_module_t *modules, uint32_t modules_count)
{
    for (size_t i = 0; i < modules_count; i++)
    {
        _new_map(modules->mod_start, modules->mod_end-modules->mod_start, MEMMAP_GRUB_MODULES);
    }   
}

void _reserve_mmemmap(multiboot_info_t *mbinfo)
{
    if (mbinfo->mmap_addr != 0)
    {
        multiboot_memory_map_t *map = (multiboot_memory_map_t *)(mbinfo->mmap_addr + KERNEL_OFFSET);

        for (int traveled = 0; traveled < mbinfo->mmap_length; traveled+= map->size + sizeof(map->size), map = (multiboot_memory_map_t*)((char*)map + map->size +sizeof(map->size)))
        {
            struct memmap nmap = (struct memmap)
            {
                (((uint64_t)map->addr_high) << 32) | (map->addr_low),
                (((uint64_t)map->len_high) << 32) | (map->len_low),
                map->type
            };

            memmap[memmaplen++] = nmap;
        }
    }
}

void reserve_mem(multiboot_info_t *mbinfo)
{
    _reserve_mmemmap(mbinfo);
    _reserve_modules((multiboot_module_t *)(mbinfo->mods_addr + KERNEL_OFFSET), mbinfo->mods_count);
}



void mman_init(multiboot_info_t *mbinfo)
{
    reserve_mem(mbinfo);
    NEWKERNELMAP(KERNEL_PHYS_START, KERNEL_SIZE);
}