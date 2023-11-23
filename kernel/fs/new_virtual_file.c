#include <fs.h>

#include <stdlib.h>

fd_t new_virtual_file(void *buffer, unsigned int size)
{  

    _FILE *new_file = (_FILE *)malloc(sizeof(_FILE));
    *new_file = (_FILE)
    {
        .fd = FD_UNASSIGNED,
        .location_type = FILE_LOCATION_VIRTUAL,
        .file_type = FILE_VIRTUAL,
        .buf = buffer,
        .base = buffer,
        .size = size,
    };
    
    return _add_new_file(new_file);
}