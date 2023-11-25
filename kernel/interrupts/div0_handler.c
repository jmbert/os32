#include <interrupts.h>
#include <stdio.h>

[[gnu::interrupt, noreturn]]
void div0_handler(int_stackframe_t *sf)
{
    TSS_INTERRUPT_PRELUDE
    printf("Fatal Interrupt: Division by 0\n");
    asm("hlt");
    for (;;);
}