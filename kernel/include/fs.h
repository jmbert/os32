#ifndef _FS_H
#define _FS_H

#include <bits/defs/fs.h>

typedef enum
{
    FILE_LOCATION_INITRAMFS,
    FILE_LOCATION_DISK,
    FILE_LOCATION_VIRTUAL,
}_file_location_type_e;

typedef enum
{
    FILE_PHYSICAL,
    FILE_VIRTUAL,
}_file_type_e;

typedef unsigned int fd_t;

#define FD_UNASSIGNED 0xFFFFFFFF

typedef struct _FILE
{
    fd_t fd;
    _file_location_type_e location_type;
    _file_type_e file_type;

    unsigned char *buf;
    unsigned char *base;
    unsigned int size;
}_FILE;


typedef struct file_descriptor_table_t
{
    _FILE **_table;
    unsigned int _current_fd;
}file_descriptor_table_t;

fd_t new_virtual_file(void *buffer, unsigned int size);

fd_t _add_new_file(_FILE *file);

#define FILE_LENGTH(_file) ((_file)->buf - (_file)->base)
#define FILE_LENGTH_LEFT(_file) ((_file)->size - FILE_LENGTH(_file))

file_descriptor_table_t *get_fdtable();

#define _GET_FILE(_fd) (get_fdtable()->_table[(_fd)])

#endif