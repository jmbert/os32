
#include <memory.h>

#include <debug/exec.h>
#include <stdio.h>
#include <string.h>
#include <terminal.h>
#include <multiboot.h>
#include <multiboot_helpers.h>
#include <fs/tar.h>
#include <info/link_info.h>
#include <stdlib.h>

#include <proc.h>

void test()
{
    exit();
}

void kernel_main()
{

    char *stdoutBuf = (char*)malloc(sizeof(char)*0x1000);
    char *stdinBuf = (char*)malloc(sizeof(char)*0x1000);
    char *stderrBuf = (char*)malloc(sizeof(char)*0x1000);

    _file_from_buffer(stdinBuf, 0x1000);
    _file_from_buffer(stdoutBuf, 0x1000);
    _file_from_buffer(stderrBuf, 0x1000);

    graphics_swap_buffer_t swap = {
        .offset = 0,
        .size = GRAPHICS_SIZE,
        .buffer = (unsigned char *)malloc(sizeof(unsigned char)*GRAPHICS_SIZE),
    };

    HALT();
}