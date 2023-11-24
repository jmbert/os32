#include <interrupts.h>

#include <stdio.h>

[[gnu::interrupt, noreturn]]
void double_fault_handler_trap(int_stackframe_t *sf, unsigned int err_code)
{
    TSS_INTERRUPT_PRELUDE
    printf("Fatal Interrupt: Double Fault\n");
    asm("hlt");
    for (;;);
}