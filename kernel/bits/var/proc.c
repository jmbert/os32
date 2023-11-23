#include <proc.h>

_process_t *proc_table[MAX_PROCESSES];
pid_t current_process;
pid_t next_pid = 0;