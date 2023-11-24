#include <idt.h>
#include <gdt.h>

void register_interrupt(void *_ptr, unsigned int index, unsigned char flags)
{
    interrupt_gate_t gate;
    gate._ptr_low = (unsigned int)_ptr;
    gate._ptr_high = ((unsigned int)_ptr) >> 16;
    gate.flags = flags | IDT_GATE_PRESENT;
    gate.segment_selector = GDT_KERNEL_CODE;
    
    idt[index] = gate;
}