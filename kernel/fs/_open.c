#include <vfs.h>
#include <vfs/fd.h>

#include <debug/exec.h>

fd_t _open(char *path, unsigned int modes)
{
    vfs_node_t *node = _get_node(path);
    return node->ops.open(node, modes);
}