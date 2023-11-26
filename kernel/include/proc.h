#ifndef _PROC_H
#define _PROC_H

#include <bits/types/state.h>
#include <bits/defs/proc.h>

#include <paging.h>
#include <string.h>
#include <vfs/fd.h>
#include <graphics.h>

typedef unsigned long pid_t;

typedef enum
{
    PROC_MODE_KERNEL,
    PROC_MODE_USER,
}_process_type_e;

typedef struct
{
    pid_t pid;
    pid_t parent;

    _sstate_t stack_state;
    
    ptable page_directory;

    _process_type_e privilege;

    file_descriptor_table_t fd_lookup_table;

    graphics_swap_buffer_t swap_buf;
}_process_t;

extern _process_t *proc_table[MAX_PROCESSES];
extern pid_t current_process;
extern pid_t next_pid;
extern ptable kernel_pdir;

#define _LOAD_STACK(_process_ptr) __asm__ ("mov %0, %%esp\n" :: "m"((_process_ptr)->stack_state._esp))

#define _SAVE_STACK(_process_ptr) __asm__ ("mov %%esp, %0\n" : "=m"((_process_ptr)->stack_state._esp))

#define _SAVE_REGISTERS() __asm__ ("pusha");
#define _LOAD_REGISTERS() __asm__ ("popa");


pid_t fork();

void exit();

ptable _initialise_pdir();
ptable _initialise_pdir_fork();

pid_t getpid();

_process_t *_proclookup(pid_t proc);

int switch_process_nosave(pid_t proc);
int switch_process(pid_t proc);

pid_t new_process(uword_t start_eip, _process_type_e privilege);

void print_processes();

extern void ring_switch(unsigned int _code_segment, unsigned int _data_segment, unsigned int _ret);
extern void switch_stack(unsigned int _new_pdir, unsigned int _old_esp_ptr, unsigned int _new_esp, unsigned int _code_segment, unsigned int _data_segment);

#endif