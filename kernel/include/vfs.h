#ifndef _VFS_H
#define _VFS_H

typedef void (*vfs_node_read_t)(void *buffer, unsigned int size);
typedef void (*vfs_node_write_t)(void *buffer, unsigned int size);
typedef void (*vfs_node_open_t)();
typedef void (*vfs_node_close_t)();

typedef enum
{
    VFS_NODE_FILE,
    VFS_NODE_DIRECTORY,
    VFS_NODE_MOUNT_POINT,
}_vfs_node_types_e;

typedef struct _vfs_node
{
    char *nameseg;

    struct _vfs_node *parent;

    _vfs_node_types_e type;

    vfs_node_open_t open;
    vfs_node_close_t close;


    /* Type-specific information */
    union
    {
        struct
        {
            vfs_node_read_t read;
            vfs_node_write_t write;
        };

        struct 
        {
            struct _vfs_node **children;
            unsigned int children_len;
        };

        struct _vfs *mount_source;
    };
    
}vfs_node_t;

typedef struct _vfs
{
    vfs_node_t *root;
}vfs_t;

extern vfs_t file_system;

#endif