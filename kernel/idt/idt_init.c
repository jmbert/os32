#include <idt.h>

interrupt_gate_t idt[256];

void idt_init()
{
    idtr_t idtr;
    idtr.size = sizeof(idt);
    idtr._ptr = (unsigned int)(idt);

    asm("lidt %0" :: "m"(idtr));
}