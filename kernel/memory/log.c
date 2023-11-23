#include <memory.h>
#include <stdio.h>

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
        printf("\t0x%lx-0x%lx (0x%lx) : ", memmap[i].addr, memmap[i].addr + memmap[i].size, memmap[i].size);
        print_mmap_type(memmap[i].type);
        printf("\n\n");
    }
}