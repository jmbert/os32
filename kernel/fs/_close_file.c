#include <vfs/fd.h>
#include <stdlib.h>

void _close_file(fd_t file)
{
    get_fdtable()->_table[file] = NULL;
}