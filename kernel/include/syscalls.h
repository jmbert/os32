#ifndef _SYSCALL_H
#define _SYSCALL_H

#define SYSCALL_INT 0x80

#include <vfs.h>
#include <interrupts.h>

typedef enum
{
    SYSCALL_READ,
    SYSCALL_WRITE,
    SYSCALL_OPEN,
    SYSCALL_CLOSE,
    SYSCALL_STAT, 
}_syscalls_e;

extern int syscall(int_stackframe_t *sf);

int syscall_open(char *path, unsigned int modes);
int syscall_close(int fd);
int syscall_read(int fd, void *buffer, unsigned int size);
int syscall_write(int fd, void *buffer, unsigned int size, unsigned int offset);
int syscall_stat(int fd, stat_t *statbuffer);

#endif