#include <vfs/fd.h>

fd_t _add_new_file(_OPEN_FILE *file)
{
    file_descriptor_table_t *fdtable = get_fdtable();

    file->fd = fdtable->_current_fd;
    fdtable->_table[fdtable->_current_fd] = file;
    fdtable->_current_fd++;
    return file->fd;
}