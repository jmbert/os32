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

extern unsigned int initramfs_fs;

void print_fs(vfs_node_t fs, unsigned int depth)
{

    for (size_t i = 0; i < depth; i++)
    {
        printf("\t");
    }
    
    
    printf("%s\n", fs.nameseg);

    if (fs.type == VFS_NODE_DIRECTORY)
    {
        for (size_t i = 0; i < fs.children_len; i++)
        {
            print_fs(*fs.children[i], depth + 1);
        }
    }
    
}

void kernel_main()
{

    
    print_fs(*file_system.root, 0);

    HALT();
}