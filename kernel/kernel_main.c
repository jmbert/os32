
#include <memory.h>

#include <debug/exec.h>
#include <stdio.h>
#include <string.h>
#include <terminal.h>
#include <multiboot.h>
#include <multiboot_helpers.h>
#include <fs/tar.h>
#include <info/link_info.h>

#include <proc.h>

void kernel_main(multiboot_info_t *mbinfo, terminal_t term, font_t font)
{
    HALT();
}