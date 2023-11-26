#include <vfs.h>
#include <vfs/fd.h>

#include <stdlib.h>

int vfs_open(void *_node)
{
    vfs_node_t *node = (vfs_node_t*)_node;
    _OPEN_FILE *file = malloc(sizeof(_OPEN_FILE));
    file->node = node;

    return _add_new_file(file);
}