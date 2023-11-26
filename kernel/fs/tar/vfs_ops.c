#include <fs/tar.h>
#include <vfs.h>
#include <string.h>


static int _read_tar_header(tar_header_t *hdr, void *buffer, unsigned int size)
{
    if (!validate_header(hdr))
    {
        return -1;
    }
    if (decodeOctal(hdr->sizeOct, 12) < size)
    {
        return -2;
    }
    memcpy(buffer, (void*)(DATA_FROM_HEADER(hdr)), size);
    return 0;
}

int vfs_read_tar(void *_node, void *buffer, unsigned int size)
{
    vfs_node_t *node = (vfs_node_t*)_node;
    if (node->format != VFS_USTAR)
    {
        return -1;
    }
    tar_header_t *file = node->ustar_header;

    return _read_tar_header(file, buffer, size);
}

static int _write_tar_header(tar_header_t *hdr, void *buffer, unsigned int size, unsigned int offset)
{
    if (!validate_header(hdr))
    {
        return -1;
    }
    if (decodeOctal(hdr->sizeOct, 12) < size)
    {
        return -2;
    }
    memcpy((void*)(DATA_FROM_HEADER(hdr) + offset), buffer, size);
    return 0;
}

int vfs_write_tar(void *_node, void *buffer, unsigned int size, unsigned int offset)
{
    vfs_node_t *node = (vfs_node_t*)_node;
    if (node->format != VFS_USTAR)
    {
        return -1;
    }
    tar_header_t *file = node->ustar_header;

    return _write_tar_header(file, buffer, size, offset);
}

int vfs_stat_tar(void *_node, stat_t *statbuffer)
{
    vfs_node_t *node = (vfs_node_t*)_node;
    if (node->format != VFS_USTAR)
    {
        return -1;
    }
    tar_header_t *file = node->ustar_header;

    statbuffer->size = decodeOctal(file->sizeOct, 12);
}