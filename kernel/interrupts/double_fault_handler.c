#include <interrupts.h>

#include <stdio.h>

[[gnu::interrupt, noreturn]]
void double_fault_handler(int_stackframe_t *sf, unsigned int err_code)
{
    TSS_INTERRUPT_PRELUDE
    printf("Fatal Interrupt: Double Fault\n");
    printf("\tFrom: 0x%x\n", sf->eip);
    printf("\tFlags: 0x%x\n", sf->eflags);
    printf("\tCode Selector: 0x%x\n", sf->cs_padded);
    asm("hlt");
    for (;;);
}