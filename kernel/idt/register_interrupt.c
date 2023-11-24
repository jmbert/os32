#include <idt.h>


void register_interrupt(unsigned int _ptr, unsigned int index, unsigned char flags)
{
    interrupt_gate_t gate;
    gate._ptr_low = _ptr;
    gate._ptr_high = _ptr >> 16;
    gate.flags = flags | IDT_GATE_PRESENT;
    
    idt[index] = gate;
}