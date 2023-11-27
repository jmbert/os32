#include <syscalls.h>

#include <vfs/fd.h>

#include <debug/exec.h>

int syscall_read(int fd, void *buffer, unsigned int size)
{
    return _read(fd, buffer, size);
}