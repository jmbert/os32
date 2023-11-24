#include <interrupts.h>

#include <stdio.h>

[[gnu::interrupt, noreturn]]
void div0_handler_trap(int_stackframe_t *sf, unsigned int err_code)
{
    printf("Fatal Interrupt: Division by 0\n");
    for (;;);
}