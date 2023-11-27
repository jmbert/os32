#include <syscalls.h>

#include <vfs/fd.h>

int syscall_stat(int fd, stat_t *statbuffer)
{
    return _stat(fd, statbuffer);
}