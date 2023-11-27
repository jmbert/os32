#include <syscalls.h>

#include <vfs/fd.h>

int syscall_close(int fd)
{
    return _close_file(fd);
}