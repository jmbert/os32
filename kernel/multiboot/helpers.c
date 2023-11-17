
#include <multiboot_helpers.h>
#include <elf_helpers.h>

#include <info/link_info.h>

void print_mbinfo(struct multiboot_info *mbinfo, uint32_t view_flags)
{
    uint32_t flags = mbinfo->flags & view_flags;

    if (flags & MULTIBOOT_INFO_MEMORY)
    {
        printf("Lower memory: 0x%x\n", mbinfo->mem_lower);
        printf("Upper memory: 0x%x\n\n", mbinfo->mem_upper);
    } else if (view_flags & MULTIBOOT_INFO_MEMORY) {
        printf("Memory Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_BOOTDEV)
    {
        uint8_t bootdevicedriven = (mbinfo->boot_device >> 24) & 0xFF;
        uint8_t bootdevicep1 = (mbinfo->boot_device >> 16) & 0xFF;
        uint8_t bootdevicep2 = (mbinfo->boot_device >> 8) & 0xFF;
        uint8_t bootdevicep3 = (mbinfo->boot_device) & 0xFF;

        printf("Boot Device Drive Number: 0x%x\n", bootdevicedriven);
        if (bootdevicep1 != 0xff)
        {  
            printf("\tBoot Device Drive Parition: 0x%x\n", bootdevicep1);
            if (bootdevicep2 != 0xff)
            {  
                printf("\t\tBoot Device Drive Sub-Parition: 0x%x\n", bootdevicep2);
                if (bootdevicep3 != 0xff)
                {  
                    printf("\t\t\tBoot Device Drive Sub-Parition: 0x%x\n", bootdevicep3);
                }
        }
        }
    } else if (view_flags & MULTIBOOT_INFO_BOOTDEV) {
        printf("Boot Device Drive Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_CMDLINE)
    {
        printf("Command line: \"%s\"\n\n", mbinfo->cmdline + KERNEL_OFFSET);
    } else if (view_flags & MULTIBOOT_INFO_CMDLINE)  {
        printf("Command Line Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_MODS)
    {
        printf("Number of modules: %d\n", mbinfo->mods_count);
        if (mbinfo->mods_addr != 0)
        {
            multiboot_module_t *mods = (multiboot_module_t *)(mbinfo->mods_addr + KERNEL_OFFSET);

            for (int i = 0; i < mbinfo->mods_count; i++)
            {
                printf("\tModule start: 0x%x\n", mods[i].mod_start);
                printf("\tModule end: 0x%x", mods[i].mod_end);
                printf("\tModule cmdline: \"%s\"\n", mods[i].cmdline + KERNEL_OFFSET);
            }
            printf("\n");
        }
    } else if (view_flags & MULTIBOOT_INFO_MODS)  {
        printf("Module Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_AOUT_SYMS)
    {
        printf("AOUT not supported\n\n");
    } else if (view_flags & MULTIBOOT_INFO_AOUT_SYMS)
    {
        printf("AOUT Information not available\n\n");
    }
    if (flags & MULTIBOOT_INFO_ELF_SHDR)
    {
        multiboot_elf_section_header_table_t eheader = mbinfo->u.elf_sec;
        Elf32_Shdr *sections = (Elf32_Shdr*)(eheader.addr + KERNEL_OFFSET);
        printf("Elf Section Entry Count: %d\n", eheader.num);
        printf("Elf Section Entry Size: 0x%x\n", eheader.size);
        print_secHeaders(sections, eheader.num, "\t", KERNEL_OFFSET, (char*)(sections[eheader.shndx].sh_addr + KERNEL_OFFSET));
        printf("\n");
    } else if (view_flags & MULTIBOOT_INFO_ELF_SHDR) {
        printf("ELF Section Header Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_MEM_MAP)
    {
        printf("Memory Map:\n");
        if (mbinfo->mmap_addr != 0)
        {
            multiboot_memory_map_t *map = (multiboot_memory_map_t *)(mbinfo->mmap_addr + KERNEL_OFFSET);

            for (int traveled = 0; traveled < mbinfo->mmap_length; traveled+= map->size, map = (multiboot_memory_map_t*)((char*)map + map->size))
            {
                printf("\tMap Entry Base Address: 0x%x\n", map->addr);
                printf("\tMap Entry Length: 0x%x\n", map->len);
                printf("\tMap Entry Type: 0x%x\n\n", map->type);
            }
            printf("\n");
        }
    } else if (view_flags & MULTIBOOT_INFO_MEM_MAP) {
        printf("Memory Map Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_DRIVE_INFO)
    {
        printf("Drives Buffer Size: 0x%x\n", mbinfo->drives_length);
        if (mbinfo->mmap_addr != 0)
        {
            multiboot_drive_info_t *drive = (multiboot_drive_info_t *)(mbinfo->drives_addr + KERNEL_OFFSET);

            for (int traveled = 0; traveled < mbinfo->drives_length; traveled+= drive->size, drive = (multiboot_drive_info_t*)((char*)drive + drive->size))
            {
                printf("\tDrive Number: 0x%x\n", drive->drive_number);
                printf("\tDrive Mode: 0x%x\n", drive->drive_mode);
                printf("\tDrive Cylinders: 0x%x\n", drive->drive_cylinders);
                printf("\tDrive Heads: 0x%x\n", drive->drive_heads);
                printf("\tDrive Sectors: 0x%x\n", drive->drive_sectors);
            }
            printf("\n");
        }
    } else if (view_flags & MULTIBOOT_INFO_DRIVE_INFO) {
        printf("Drive Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_CONFIG_TABLE)
    {
        printf("ROM Config Table: 0x%x\n\n", mbinfo->config_table);
    } else if (view_flags & MULTIBOOT_INFO_CONFIG_TABLE) {
        printf("ROM Config Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_BOOT_LOADER_NAME)
    {
        printf("Bootloader Name: \"%s\"\n\n", mbinfo->boot_loader_name + KERNEL_OFFSET);
    } else if (view_flags & MULTIBOOT_INFO_BOOT_LOADER_NAME) {
        printf("Bootloader Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_APM_TABLE)
    {
        printf("APM Table Address: 0x%x", mbinfo->apm_table);
    } else if (view_flags & MULTIBOOT_INFO_APM_TABLE) {
        printf("APM Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_VBE_INFO)
    {
        printf("VBE Mode: 0x%x\n", mbinfo->vbe_mode);
        printf("VBE Mode Info: 0x%x\n", mbinfo->vbe_mode_info);
        printf("VBE Control Info: 0x%x\n\n", mbinfo->vbe_control_info);
    } else if (view_flags & MULTIBOOT_INFO_VBE_INFO) {
        printf("VBE Info Unavailable\n\n");
    }
    if (flags & MULTIBOOT_INFO_FRAMEBUFFER_INFO)
    {
        printf("Framebuffer Address: 0x%x\n", mbinfo->framebuffer_addr);
        printf("Framebuffer Type: 0x%x\n", mbinfo->framebuffer_type);
        printf("Framebuffer Palette: 0x%x\n", mbinfo->framebuffer_palette_addr);
        printf("Framebuffer Width: 0x%x\n", mbinfo->framebuffer_width);
        printf("Framebuffer Height: 0x%x\n", mbinfo->framebuffer_height);
        printf("Framebuffer Bits Per Pixel: 0x%x\n", mbinfo->framebuffer_bpp);
    } else if (view_flags & MULTIBOOT_INFO_FRAMEBUFFER_INFO) {
        printf("Framebuffer Info Unavailable\n\n");
    }
}