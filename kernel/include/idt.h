#ifndef _IDT_H
#define _IDT_H

typedef struct 
{
    unsigned short size;
    unsigned int _ptr;
}idtr_t;


typedef struct
{
    unsigned short _ptr_low;
    unsigned short segment_selector;
    unsigned char reserved;
    unsigned char flags;
    unsigned short _ptr_high;
}interrupt_gate_t;

typedef enum
{
    IDT_GATE_PRESENT,
    IDT_GATE_TYPE_TASK,
    IDT_GATE_TYPE_INT16,
    IDT_GATE_TYPE_TRAP16,
    
    IDT_GATE_TYPE_INT32,
    IDT_GATE_TYPE_TRAP32,

    IDT_GATE_PRIVILEGE_KERNEL = 0,
    IDT_GATE_PRIVILEGE_USER = 3,

}_interrupt_flags_e;


extern interrupt_gate_t idt[256];

void idt_init();

void register_interrupt(unsigned int _ptr, unsigned int index, unsigned char flags);

#endif