#include <gdt.h>

.globl ring_switch
ring_switch:
    pop %ecx /* Data segment */
    pop %edx /* Code segment */
    pop %ebx /* Return Address */
    
    mov %cx, %ds
    mov %cx, %es
    mov %cx, %gs
    mov %cx, %fs

    pushf
    push %edx
    push %ebx
    iret