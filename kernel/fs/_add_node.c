#include <vfs.h>
#include <string.h>
#include <stdlib.h>

#include <debug/exec.h>

void _add_node(char *path, vfs_node_t *node)
{
    vfs_node_t *parent = _get_node(path);
    parent->children[parent->children_len] = node;
    parent->children_len++;
}