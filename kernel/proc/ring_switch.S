#include <gdt.h>

.globl ring_switch
ring_switch:
    pop %edx /* Data segment */
    pop %ecx /* Code segment */
    pop %ebx /* Return Address */
    
    
    mov %dx, %ds
    mov %dx, %es
    mov %dx, %gs
    mov %dx, %fs

    push %edx
    push %esp
    pushf
    push %ecx
    push %ebx
    
    iret