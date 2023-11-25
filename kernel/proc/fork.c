#include <proc.h>

#include <stdlib.h>

#include <memory.h>

#include <bits/defs/reg.h>

#include <debug/exec.h>


pid_t fork()
{
    _sstate_t sstate;

    ptable pdir = _initialise_pdir_fork();

    _process_t *parent = _proclookup(getpid());

    _process_t proc = (_process_t)
    {
        .page_directory = pdir,
        .pid = next_pid,
        .parent = parent->pid,
        .privilege = parent->privilege,
        .stack_state = parent->stack_state,
        .fd_lookup_table = parent->fd_lookup_table,
        .swap_buf = parent->swap_buf,
    };

    next_pid++;

    _process_t *entry = (_process_t*)malloc(sizeof(_process_t));
    *entry = proc;
    proc_table[proc.pid] = entry;

    return proc.pid;
}