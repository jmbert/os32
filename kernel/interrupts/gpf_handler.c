#include <interrupts.h>

#include <stdio.h>

[[gnu::interrupt, noreturn]]
void gpf_handler(int_stackframe_t *sf, unsigned int err_code)
{
    TSS_INTERRUPT_PRELUDE
    printf("Fatal Interrupt: General Protection Fault with code 0x%x\n", err_code);
    printf("\tFrom: 0x%x\n", sf->eip);
    printf("\tFlags: 0x%x\n", sf->eflags);
    printf("\tCode Selector: 0x%x\n", sf->cs_padded);
    asm("hlt");
    for (;;);
}