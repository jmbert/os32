#include <proc.h>

#include <stdlib.h>

#include <memory.h>

#include <bits/defs/reg.h>

#include <debug/exec.h>

#include <vfs/streams.h>

pid_t new_process(uword_t start_eip, _process_type_e privilege)
{
    _sstate_t sstate;

    ptable pdir = _initialise_pdir();

    ptable old_pdir = GET_PDIR_PHYS();
    /* Easier to work inside the process page directory */
    SET_PDIR(pdir);

    uword_t proc_esp = _STACK_POSITION;
    mmap(proc_esp-_STACK_SIZE, _STACK_SIZE, PAGE_WRITABLE | ((privilege == PROC_MODE_KERNEL) ? 0 : PAGE_USER));

    /* Set up stack for return to the process */
    
    proc_esp -= _REGISTER_SIZE; /* For EIP */
    *(uword_t*)proc_esp = start_eip;
    proc_esp -= _REGISTER_SIZE*2; /* For segments */
    proc_esp -= _REGISTER_SIZE; /* For ESP */
    *(uword_t*)proc_esp = proc_esp+_REGISTER_SIZE;
    uword_t proc_ebp = proc_esp;
    proc_esp -= _REGISTERS_SIZE; /* For all registers */
    proc_esp += _REGISTER_SIZE * 2; /* Go back to ebp */
    *(uword_t*)proc_esp = proc_ebp;
    proc_esp -= _REGISTER_SIZE * 2; /* Go back to top */

    /* Get our old pages back */
    SET_PDIR(old_pdir);

    sstate._esp = proc_esp;

    file_descriptor_table_t fdtab;
    fdtab._current_fd = 0;
    fdtab._table = (_OPEN_FILE**)malloc(sizeof(_OPEN_FILE*)*MAX_FILE_DESCRIPTORS);

    _process_t proc = 
    {
        .page_directory = pdir,
        .pid = next_pid,
        .parent = getpid(),
        .privilege = privilege,
        .stack_state = sstate,
        .fd_lookup_table = fdtab,
    };

    next_pid++;

    _process_t *entry = (_process_t*)malloc(sizeof(_process_t));
    *entry = proc;

    proc_table[proc.pid] = entry;


    char *stdoutBuf = (char*)malloc(sizeof(char)*STD_STREAM_SIZE);
    char *stdinBuf = (char*)malloc(sizeof(char)*STD_STREAM_SIZE);
    char *stderrBuf = (char*)malloc(sizeof(char)*STD_STREAM_SIZE);

    /* Setup std streams */

    pid_t old_process = current_process;
    current_process = proc.pid;


    init_stdin(stdinBuf, STD_STREAM_SIZE);
    init_stdout(stdoutBuf, STD_STREAM_SIZE);
    init_stderr(stderrBuf, STD_STREAM_SIZE);

    /* Set up swap buffer */
    _proclookup(getpid())->swap_buf = (graphics_swap_buffer_t)
    {
        .offset = 0,
        .size = GRAPHICS_SIZE,
        .buffer = (unsigned char*)malloc(sizeof(unsigned char)*GRAPHICS_SIZE),
    };

    current_process = old_process;

    return proc.pid;
}