#include <syscalls.h>

#include <vfs/fd.h>

int syscall_write(int fd, void *buffer, unsigned int size, unsigned int offset)
{
    return _write(fd, buffer, size, offset);
}