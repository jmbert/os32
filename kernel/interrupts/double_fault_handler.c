#include <interrupts.h>

#include <stdio.h>

[[gnu::interrupt, noreturn]]
void double_fault_handler_trap(int_stackframe_t *sf, unsigned int err_code)
{
    printf("Fatal Interrupt: Double Fault\n");
    for (;;);
}