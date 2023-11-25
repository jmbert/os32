#include <fs/tar.h>
#include <stdio.h>
#include <stdlib.h>
#include <debug/exec.h>
#include <string.h>

static char *basename(char *path) {

    char *p = (char*)malloc(sizeof(char)*strlen(path));
    unsigned int length = (path[strlen(path)-1] == '/') ? strlen(path)-1 : strlen(path);
    memcpy(p, path, length);
    char *base = strrchr(p, '/');

    if (base != NULL)
    {
        if (base[0] == '/')
        {
            base++;
        }
    }
    
    return (base == NULL) ? p : base;
}

static vfs_node_t *convert_to_node(tar_header_t *file)
{
    vfs_node_t *node = malloc(sizeof(vfs_node_t));

    
    char *bname = basename(file->name);
    node->nameseg = bname;
    

    switch (file->type)
    {
    case TAR_NORMAL_FILE:
        node->type = VFS_NODE_FILE;
        break;
    case TAR_DIR:
        node->type = VFS_NODE_DIRECTORY;
        node->children = (vfs_node_t**)malloc(sizeof(vfs_node_t*)*MAX_DIR_ITEMS);
        node->children_len = 0;
        break;
    default:
        node->type = VFS_NODE_FILE;
        break;
    }


    return node;
}

vfs_t convert_to_vfs(unsigned int archive)
{
    vfs_t filesys;

    vfs_node_t *root_node;
    vfs_node_t *current_parent = NULL;
    vfs_node_t *current_node = NULL;
    tar_header_t *dir = (tar_header_t*)archive;
    int i = 0;
    int depth = 0;
    char *last_dir = NULL;
    archive = (uint32_t)dir;
    for (;memcmp(dir->indicator, "ustar", 5) == 0 && i < MAX_DIR_ITEMS;i++)
    {
        if (last_dir != NULL)
        {
            if (memcmp(last_dir, dir->name, strlen(last_dir)) != 0)
            {
                if (depth > 0)
                {
                    depth--;
                    current_parent = current_parent->parent;
                }
            }
        }
        current_node = convert_to_node(dir);
        current_node->parent = current_parent;
        if (current_parent != NULL)
        {
            current_parent->children[current_parent->children_len] = current_node;
            current_parent->children_len++;
        } else
        {
            root_node = current_node;
        }
        if (current_node->type == VFS_NODE_DIRECTORY)
        {
            depth++;
            last_dir = dir->name;
            current_parent = current_node;
        }

        uint64_t filesize = decodeOctal(dir->sizeOct, 11);
        archive += (((filesize + 511) / 512) + 1) * 512;
        dir = (tar_header_t*)archive;
    }

    filesys.root = root_node;
    return filesys;
}