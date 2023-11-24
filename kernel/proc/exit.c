#include <proc.h>

void exit()
{
    pid_t parent = _proclookup(getpid())->parent;

    switch_process_nosave(parent);
}