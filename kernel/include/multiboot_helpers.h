#include <multiboot.h>

#include <stdio.h>

struct multiboot_drive_info
{
    multiboot_uint32_t size;
    multiboot_uint8_t drive_number;
    multiboot_uint8_t drive_mode;
    multiboot_uint16_t drive_cylinders;
    multiboot_uint8_t drive_heads;
    multiboot_uint16_t drive_sectors;
    multiboot_uint16_t drive_ports[];
};

typedef struct multiboot_drive_info multiboot_drive_info_t;

void print_mbinfo(struct multiboot_info *mbinfo, unsigned int view_flags);