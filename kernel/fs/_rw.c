#include <vfs.h>
#include <vfs/fd.h>

#include <debug/exec.h>

int _read(fd_t file, void *buffer, unsigned int size)
{
    vfs_node_t *node = _GET_FILE(file)->node;
    return node->ops.read(node, buffer, size);
}

int _write(fd_t file, void *buffer, unsigned int size, unsigned int offset)
{
    vfs_node_t *node = _GET_FILE(file)->node;
    return node->ops.write(node, buffer, size, offset);
}

int _stat(fd_t file, stat_t *statbuffer)
{

    vfs_node_t *node = _GET_FILE(file)->node;
    return node->ops.stat(node, statbuffer);
}