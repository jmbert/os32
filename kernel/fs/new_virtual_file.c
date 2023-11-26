#include <vfs/fd.h>

#include <stdlib.h>

fd_t new_virtual_file(void *buffer, unsigned int size)
{  

    _OPEN_FILE *new_file = (_OPEN_FILE *)malloc(sizeof(_OPEN_FILE));
    *new_file = (_OPEN_FILE)
    {
        .fd = FD_UNASSIGNED,
        .node = NULL,
    };
    
    return _add_new_file(new_file);
}