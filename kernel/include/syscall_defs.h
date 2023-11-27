#ifndef _SYSCALL_DEFS_H
#define _SYSCALL_DEFS_H


#define SYSCALL_read 1
#define SYSCALL_write 2
#define SYSCALL_open 3
#define SYSCALL_close 4
#define SYSCALL_stat 5

#define SYSCALL1(_name)    .extern syscall_ ## _name;\
                            cmp $SYSCALL_ ## _name, %eax;\
                            jne .syscall_ ## _name ## _end;\
                            push %ebx;\
                            call syscall_ ## _name;\
                            pop %ebx;\
                            jmp .exit_syscall;\
                            .syscall_ ## _name ## _end:;
                                

#define SYSCALL2(_name)    .extern syscall_ ## _name; \
                            cmp $SYSCALL_ ## _name, %eax;\
                            jne .syscall_ ## _name ## _end;\
                            push %ecx;\
                            push %ebx;\
                            call syscall_ ## _name;\
                            pop %ebx;\
                            pop %ecx;\
                            jmp .exit_syscall;\
                            .syscall_ ## _name ## _end:;

#define SYSCALL3(_name)    .extern syscall_ ## _name;\
                            cmp $SYSCALL_ ## _name, %eax;\
                            jne .syscall_ ## _name ## _end;\
                            push %edx;\
                            push %ecx;\
                            push %ebx;\
                            call syscall_ ## _name;\
                            pop %ebx;\
                            pop %ecx;\
                            pop %edx;\
                            jmp .exit_syscall;\
                            .syscall_ ## _name ## _end:;

#define SYSCALL4(_name)    .extern syscall_ ## _name;\
                            cmp $SYSCALL_ ## _name, %eax;\
                            jne .syscall_ ## _name ## _end;\
                            push %edi;\
                            push %edx;\
                            push %ecx;\
                            push %ebx;\
                            call syscall_ ## _name;\
                            pop %ebx;\
                            pop %ecx;\
                            pop %edx;\
                            pop %edi;\
                            jmp .exit_syscall;\
                            .syscall_ ## _name ## _end:;

#endif