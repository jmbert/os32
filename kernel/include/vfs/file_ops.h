#ifndef _VFS_FOPS_H
#define _VFS_FOPS_H

typedef struct
{
    unsigned int size;
}stat_t;

typedef struct 
{
    int (*read)(void *_node, void *buffer, unsigned int size);
    int (*write)(void *_node, void *buffer, unsigned int size, unsigned int offset);
    int (*open)(void *_node, unsigned int modes);
    int (*stat)(void *_node, stat_t *statbuffer);
}file_ops_t;

#endif