#include <fs.h>
#include <proc.h>

file_descriptor_table_t *get_fdtable()
{
    /* Find the current process, and get its fd table */
    _process_t *current = _proclookup(getpid());
    if (current == NULL)
    {
        return NULL;
    } else
    {
        return &(current->fd_lookup_table);
    }
}