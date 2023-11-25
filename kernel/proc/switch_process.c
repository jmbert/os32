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

    /* Swap page directory */
    SET_PDIR(process->page_directory);

    /* Get new stack, with registers off of it */
    _LOAD_STACK(process);
    _LOAD_REGISTERS();

    current_process = getpid();
    /* Now in new process */

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

    /* Save stack and registers */
    _SAVE_REGISTERS();
    _SAVE_STACK(current);

    /* Swap page directory */
    SET_PDIR(process->page_directory);

    /* Get new stack, with registers off of it */
    _LOAD_STACK(process);
    _LOAD_REGISTERS();

    current_process = getpid();

    unsigned int new_code = (process->privilege == PROC_MODE_KERNEL) ? GDT_USER_CODE : GDT_KERNEL_CODE;
    unsigned int new_data = (process->privilege == PROC_MODE_KERNEL) ? GDT_USER_DATA : GDT_KERNEL_DATA;

    /* Now to change to ring 3 */
    unsigned int ret = __builtin_return_address(0);

    ring_switch(new_code, new_data, ret);

    return 0;
}