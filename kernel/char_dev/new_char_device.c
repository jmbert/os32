#include <vfs/char_dev.h>
#include <vfs.h>
#include <stdlib.h>

#include <debug/exec.h>

void new_char_device(char *path, char *name, file_ops_t fops)
{
    vfs_node_t *node = (vfs_node_t*)malloc(sizeof(vfs_node_t));

    node->nameseg = name;

    node->type = VFS_NODE_FILE;

    node->format = VFS_NODE_CHAR;

    node->ops = fops;


    _add_node(path, node);
}