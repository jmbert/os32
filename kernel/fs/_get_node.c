#include <vfs.h>
#include <string.h>

#include <debug/exec.h>

vfs_node_t *_get_node(char *path)
{
    path++;
    char *pathseg = strtok(path, "/");
    vfs_node_t *current_node = file_system.root;
    for (int j = 0;pathseg != NULL && current_node != NULL;pathseg = strtok(NULL, "/"),j++)
    {
        if (current_node->type != VFS_NODE_DIRECTORY)
        {
            break;
        }
        for (unsigned int i = 0; i < current_node->children_len; i++)
        {
            if (strcmp(current_node->children[i]->nameseg, pathseg) == 0)
            {
                current_node = current_node->children[i];
                break;
            }
        }
    }
    return current_node;
}