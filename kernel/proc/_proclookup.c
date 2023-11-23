#include <proc.h>

_process_t *_proclookup(pid_t proc)
{
    return proc_table[proc];
}