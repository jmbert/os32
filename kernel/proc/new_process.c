#include <proc.h>

#include <stdlib.h>

#include <memory.h>

#include <bits/defs/reg.h>

#include <debug/exec.h>

pid_t new_process(uword_t start_eip, _process_type_e privilige)
{
    _sstate_t sstate;


    ptable pdir = _initialise_pdir();

    ptable kernel_pdir = GET_PDIR_PHYS();

    /* Easier to work inside the process page directory */
    SET_PDIR(pdir);

    uword_t proc_esp = _STACK_POSITION;
    mmap(proc_esp-_STACK_SIZE, _STACK_SIZE);

    /* Set up stack for return to the process */
    proc_esp -= _REGISTER_SIZE; /* For EIP */
    *(uword_t*)proc_esp = start_eip;
    proc_esp -= _REGISTER_SIZE; /* For ESP */
    *(uword_t*)proc_esp = proc_esp+_REGISTER_SIZE;
    uword_t proc_ebp = proc_esp;
    proc_esp -= _REGISTERS_SIZE; /* For all registers */
    proc_esp += _REGISTER_SIZE * 2; /* Go back to ebp */
    *(uword_t*)proc_esp = proc_ebp;
    proc_esp -= _REGISTER_SIZE * 2; /* Go back to top */


    /* Get our old pages back */
    SET_PDIR(kernel_pdir);

    sstate._esp = proc_esp;

    _process_t proc = 
    {
        .page_directory = pdir,
        .pid = next_pid,
        .privilige = privilige,
        .stack_state = sstate
    };


    next_pid++;

    _process_t *entry = (_process_t*)malloc(sizeof(_process_t));
    *entry = proc;
    proc_table[proc.pid] = entry;

    return proc.pid;
}