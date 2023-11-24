#ifndef _GDT_H
#define _GDT_H


typedef struct [[gnu::packed]]
{
    unsigned short size;
    unsigned int _ptr;
}gdtr_t;

typedef struct [[gnu::packed]]
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_medium;
    unsigned char access;
    unsigned char limit_high_flags;
    unsigned char base_high;
}segdesc_t;

typedef enum
{
    GDT_KERNEL_CODE = 0x8,
    GDT_KERNEL_DATA = 0x10,
    GDT_USER_CODE = 0x18,
    GDT_USER_DATA = 0x20,
    GDT_TSS = 0x28,
}_gdt_segment_selectors_e;

void gdt_init();
void new_segment_descriptor(unsigned int base, unsigned int limit, unsigned char flags, unsigned char access, unsigned int index);

extern segdesc_t gdt[256];

#endif