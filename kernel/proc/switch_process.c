#include <proc.h>

#include <stddef.h>
#include <gdt.h>
#include <debug/exec.h>

int switch_process_nosave(pid_t proc)
{
    _process_t *process = proc_table[proc];

    if (process == NULL)
    {
        return -1;
    }


    current_process = process->pid;
    unsigned int _random_valid_ptr;

    unsigned int new_code = (process->privilege == PROC_MODE_KERNEL) ? GDT_KERNEL_CODE : GDT_USER_CODE ;
    unsigned int new_data = (process->privilege == PROC_MODE_KERNEL) ? GDT_KERNEL_DATA : GDT_USER_DATA ;

    switch_stack((unsigned int)(process->page_directory), (unsigned int)&_random_valid_ptr, (unsigned int)(process->stack_state._esp), new_code, new_data);

    return 0;
}

int switch_process(pid_t proc)
{
    _process_t *process = proc_table[proc];

    _process_t *current = proc_table[current_process];

    if (current == NULL || process == NULL)
    {
        return -1;
    }

    current_process = process->pid;
    unsigned int new_code = (process->privilege == PROC_MODE_KERNEL) ? GDT_KERNEL_CODE : GDT_USER_CODE ;
    unsigned int new_data = (process->privilege == PROC_MODE_KERNEL) ? GDT_KERNEL_DATA : GDT_USER_DATA ;

    switch_stack((unsigned int)(process->page_directory), (unsigned int)&(current->stack_state._esp), (unsigned int)(process->stack_state._esp), new_code, new_data);

    return 0;
}