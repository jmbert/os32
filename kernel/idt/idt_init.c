#include <idt.h>

interrupt_gate_t idt[256];

void idt_init()
{
    unsigned int idt_off = (unsigned int)(&idt);

    idtr_t idtr;
    idtr._ptr = idt_off;
    idtr.size = sizeof(idt);

    asm("lidt %0" :: "m"(idtr));
}