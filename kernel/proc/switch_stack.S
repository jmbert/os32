
#include <bits/defs/reg.h>

.extern ring_switch
.globl switch_stack
switch_stack:

    pushl $0 /* Reserve space for segments */
    pushl $0 /* Reserve space for segments */
    push %esp
    pusha /* Store registers */

    mov (_REGISTERS_SIZE+0x10)(%esp), %eax /* New Page directory */ 
    mov (_REGISTERS_SIZE+0x14)(%esp), %ebx /* Pointer to store old ESP */
    mov (_REGISTERS_SIZE+0x18)(%esp), %ecx /* New ESP */
    mov (_REGISTERS_SIZE+0x1c)(%esp), %edi /* New Code Segment */ 
    mov (_REGISTERS_SIZE+0x20)(%esp), %edx /* New Data Segment */ 

    mov %esp, (%ebx)

    mov %eax, %cr3

    mov %ecx, %esp

    mov %edx, (_REGISTERS_SIZE+0x4)(%esp)
    mov %edi, (_REGISTERS_SIZE+0x8)(%esp)

    popa
    pop %esp

    jmp ring_switch
