
#include <memory.h>

#include <debug/exec.h>
#include <stdio.h>
#include <string.h>
#include <terminal.h>
#include <multiboot.h>
#include <multiboot_helpers.h>
#include <fs/tar.h>
#include <info/link_info.h>

void kernel_main(multiboot_info_t *mbinfo)
{
    terminal_t term = create_terminal(0, 0, 0x1000);

    multiboot_module_t initramfs;
    for (unsigned int i = 0; i < mbinfo->mods_count; i++)
    {
        multiboot_module_t mod = ((multiboot_module_t *)(mbinfo->mods_addr + KERNEL_OFFSET))[i];
        if (strcmp((char*)(mod.cmdline + KERNEL_OFFSET), "initramfs") == 0)
        {
            initramfs = mod;
            break;
        }
    }

    struct tar_header *f_header = tar_lookup(initramfs.mod_start+KERNEL_OFFSET, "./initramfs/fonts/font.bin");
    unsigned char *fontdat = (unsigned char *)DATA_FROM_HEADER(f_header);

    font_t font = (font_t)
    {
        .c_height = 14,
        .c_width = 8,
        .chardata = fontdat,
    };

    print_mbinfo(mbinfo, MULTIBOOT_INFO_FRAMEBUFFER_INFO);
    terminal_write_swap(term, font);
    graphics_swap(term.swap);
}