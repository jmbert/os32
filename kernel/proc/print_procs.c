#include <proc.h>

#include <stdio.h>

static void print_process(_process_t p)
{
    printf("\tPID: %d\n\tParent: %d\n\tPrivilege: %s\n\n", p.pid, p.parent, (p.privilege == PROC_MODE_KERNEL) ? "KERNEL" : "USER");
}


void print_processes()
{
    printf("Processes:\n");
    for (pid_t i = 0; i < next_pid; i++)
    {
        _process_t *p = _proclookup(i);
        print_process(*p);
    }
    
}