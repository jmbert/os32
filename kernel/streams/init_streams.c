#include <vfs/streams.h>
#include <vfs/char_dev.h>
#include <string.h>
#include <vfs/fd.h>
#include <stdlib.h>

#include <terminal.h>

#include <debug/exec.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

char *stdoutbuf;
char *stdoutbase;
unsigned int stdoutlen;

char *stderrbuf;
char *stderrbase;
unsigned int stderrlen;

char *stdinbuf;
char *stdinbase;
unsigned int stdinlen;


int _write_stdout(void *_, char *buffer, unsigned int size)
{
    if (size > stdoutlen)
    {
        return -1;
    }
    memcpy(stdoutbuf, buffer, size);
    stdoutbuf += size;
    stdoutlen -= size;

    terminal_write_swap();
    return 0;
}

int _stat_stdout(void *_, stat_t *statbuffer)
{
    statbuffer->size = stdoutbuf-stdoutbase;
}

int _write_stderr(void *_, char *buffer, unsigned int size)
{
    if (size > stdoutlen)
    {
        return -1;
    }
    memcpy(stderrbuf, buffer, size);
    stderrbuf += size;
    stderrlen -= size;
    return 0;
}


int _stat_stderr(void *_, stat_t *statbuffer)
{
    statbuffer->size = stderrbuf-stderrbase;
}

void init_stdin(char *buffer, unsigned int bufferlen)
{
    file_ops_t stdinops;
    stdinops.open = vfs_open;


    stdinbase = buffer;
    stdinbuf = stdinbase;
    stdinlen = bufferlen;

    new_char_device("/dev", "stdin", stdinops);
    _open("/dev/stdin", 0);
}

void init_stdout(char *buffer, unsigned int bufferlen)
{
    file_ops_t stdoutops;
    stdoutops.write = _write_stdout;
    stdoutops.stat = _stat_stdout;
    stdoutops.open = vfs_open;

    stdoutbase = buffer;
    stdoutbuf = stdoutbase;
    stdoutlen = bufferlen;

    new_char_device("/dev", "stdout", stdoutops);
    _open("/dev/stdout", 0);
}

void init_stderr(char *buffer, unsigned int bufferlen)
{

    file_ops_t stderrops;
    stderrops.write = _write_stderr;
    stderrops.stat = _stat_stderr;
    stderrops.open = vfs_open;

    stderrbase = buffer;
    stderrbuf = stderrbase;
    stderrlen = bufferlen;

    new_char_device("/dev", "stderr", stderrops);
    _open("/dev/stderr", 0);
}