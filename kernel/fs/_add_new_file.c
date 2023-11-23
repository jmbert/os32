#include <fs.h>

fd_t _add_new_file(_FILE *file)
{
    file->fd = _global_fd_table._current_fd;
    _global_fd_table._table[_global_fd_table._current_fd] = file;
    _global_fd_table._current_fd++;
    return file->fd;
}