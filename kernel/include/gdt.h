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

void gdt_init();

extern segdesc_t gdt[256];

#endif