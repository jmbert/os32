#ifndef _TSS_H
#define _TSS_H

typedef struct [[gnu::packed]] {
	unsigned int prev_tss; // The previous TSS - with hardware task switching these form a kind of backward linked list.
	unsigned int esp0;     // The stack pointer to load when changing to kernel mode.
	unsigned int ss0;      // The stack segment to load when changing to kernel mode.
	// Everything below here is unused.
	unsigned int esp1; // esp and ss 1 and 2 would be used when switching to rings 1 or 2.
	unsigned int ss1;
	unsigned int esp2;
	unsigned int ss2;
	unsigned int cr3;
	unsigned int eip;
	unsigned int eflags;
	unsigned int eax;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebx;
	unsigned int esp;
	unsigned int ebp;
	unsigned int esi;
	unsigned int edi;
	unsigned int es;
	unsigned int cs;
	unsigned int ss;
	unsigned int ds;
	unsigned int fs;
	unsigned int gs;
	unsigned int ldt;
	unsigned short trap;
	unsigned short iomap_base;
}tss_entry_t;

extern tss_entry_t tss;

#define _SET_KERNEL_STACK_INTERRUPT(_stack) (tss.esp0 = (_stack))

#define TSS_INTERRUPT_PRELUDE \
    if (sf->cs_padded & GDT_USER_CODE)\
    {\
        unsigned int sp;\
        asm("mov %%esp, %0" : "=m"(sp));\
        _SET_KERNEL_STACK_INTERRUPT(sp);\
    }\
    


void tss_init();
void load_tss();

#endif