#include <gdt.h>

segdesc_t gdt[256];

static void new_segment_descriptor(unsigned int base, unsigned int limit, unsigned char flags, unsigned char access, unsigned int index)
{
    segdesc_t desc;

    desc.base_low = base;
    desc.base_medium = base >> 16;
    desc.base_high = base >> 24;

    desc.limit_low = limit;
    desc.limit_high_flags = ((limit >> 16) & 0xF) | ((flags & 0xF) << 4);
    desc.access = access;

    gdt[index] = desc;
}

extern void reloadSegments();

void gdt_init()
{
    new_segment_descriptor(0, 0, 0, 0, 0);
    new_segment_descriptor(0, 0xFFFFF, 0xC, 0x9A, 1);
    new_segment_descriptor(0, 0xFFFFF, 0xC, 0x92, 2);
    new_segment_descriptor(0, 0xFFFFF, 0xC, 0xFA, 3);
    new_segment_descriptor(0, 0xFFFFF, 0xC, 0xF2, 4);

    unsigned int gdt_off = (unsigned int)(&gdt);

    gdtr_t gdtr;
    gdtr._ptr = gdt_off;
    gdtr.size = sizeof(segdesc_t)*5;

    asm("lgdt %0" :: "m"(gdtr));
    reloadSegments();
}