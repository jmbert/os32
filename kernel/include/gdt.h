#ifndef _GDT_H
#define _GDT_H


struct _gdtr
{
    unsigned short size;
    unsigned int _ptr;
}__attribute__((packed));

typedef struct _gdtr gdtr_t;

struct _segdesc
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_medium;
    unsigned char access;
    unsigned char limit_high_flags;
    unsigned char base_high;
}__attribute__((packed));

typedef struct _segdesc segdesc_t;

void gdt_init();

extern segdesc_t gdt[256];

#endif