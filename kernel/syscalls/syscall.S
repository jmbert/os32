#include <syscall_defs.h>

.global syscall
syscall:
    SYSCALL3(read)
    SYSCALL4(write)
    SYSCALL2(open)
    SYSCALL1(close)
    SYSCALL2(stat)
.exit_syscall:
    iret