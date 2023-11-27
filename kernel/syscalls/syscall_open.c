#include <syscalls.h>

#include <vfs/fd.h>

#include <debug/exec.h>

int syscall_open(char *path, unsigned int modes)
{
    return _open(path, modes);
}