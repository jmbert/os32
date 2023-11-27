#ifndef _FS_H
#define _FS_H

#include <bits/defs/fs.h>
#include <vfs.h>

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

typedef enum
{
    O_WRONLY,
    O_APPEND,
    O_RDONLY,
}_open_file_mode_e;

typedef struct _OPEN_FILE
{
    fd_t fd;
    
    vfs_node_t *node;

    unsigned int mode;
}_OPEN_FILE;

typedef struct file_descriptor_table_t
{
    _OPEN_FILE **_table;
    unsigned int _current_fd;
}file_descriptor_table_t;

fd_t _add_new_file(_OPEN_FILE *file);
fd_t _open(char *path, unsigned int modes);
int _read(fd_t file, void *buffer, unsigned int size);
int _write(fd_t file, void *buffer, unsigned int size, unsigned int offset);
int _stat(fd_t file, stat_t *statbuffer);
int _close_file(fd_t file);

file_descriptor_table_t *get_fdtable();

#define _GET_FILE(_fd) (get_fdtable()->_table[(_fd)])

#endif