#ifndef _VFS_H
#define _VFS_H

#include <vfs/file_ops.h>

typedef enum
{
    VFS_NODE_FILE,
    VFS_NODE_DIRECTORY,
    VFS_NODE_MOUNT_POINT,
}_vfs_node_types_e;

typedef enum
{
    VFS_USTAR,
    VFS_NODE_CHAR,
}_vfs_type_e;

int vfs_open(void *_node);
int vfs_close(void *_node);

typedef struct _vfs_node
{
    char *nameseg;

    struct _vfs_node *parent;

    _vfs_node_types_e type;

    file_ops_t ops;

    /* Type-specific information */
    union
    {
        struct
        {
            _vfs_type_e format;
            union
            {
                /* Convert to tar_header_t * */
                void *ustar_header;
            };
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

void _add_node(char *path, vfs_node_t *node);
vfs_node_t *_get_node(char *path);


extern vfs_t file_system;

#endif