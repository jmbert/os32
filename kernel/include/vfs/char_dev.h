#ifndef _CDEV_H
#define _CDEV_H

#include <vfs/file_ops.h>

void new_char_device(char *path, char *name, file_ops_t fops);

#endif