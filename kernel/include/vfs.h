#ifndef _VFS_H
#define _VFS_H


typedef enum
{
    VFS_NODE_FILE,
    VFS_NODE_DIRECTORY,
    VFS_NODE_MOUNT_POINT,
}_vfs_node_types_e;

typedef enum
{
    VFS_USTAR,
}_vfs_type_e;

typedef struct
{
    _vfs_type_e type;
    union
    {
        /* Convert to tar_header_t * */
        void *ustar_header;
    };
}__FILE;


typedef int (*vfs_node_read_t)(struct _vfs_node *_node, void *buffer, unsigned int size);
typedef int (*vfs_node_write_t)(struct _vfs_node *_node, void *buffer, unsigned int size, unsigned int offset);
typedef int (*vfs_node_open_t)(struct _vfs_node *_node);
typedef int (*vfs_node_close_t)(struct _vfs_node *_node);

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
            __FILE *_base;
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
    _vfs_type_e type;
}vfs_t;

extern vfs_t file_system;

#endif