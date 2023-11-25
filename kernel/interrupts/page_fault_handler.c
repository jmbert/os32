#include <interrupts.h>

#include <stdio.h>

[[gnu::interrupt, noreturn]]
void page_fault_handler(int_stackframe_t *sf, unsigned int err_code)
{
    TSS_INTERRUPT_PRELUDE

    unsigned int violation;
    asm("mov %%cr2, %%eax;mov %%eax, %0" : "=m"(violation));

    printf("Fatal Interrupt: Page Fault with code 0x%x\n", err_code);
    printf("\tFrom: 0x%x\n", sf->eip);
    printf("\tWhile Acessing: 0x%x\n", violation);
    printf("\tFlags: 0x%x\n", sf->eflags);
    printf("\tCode Selector: 0x%x\n", sf->cs_padded);
    asm("hlt");
    for (;;);
}