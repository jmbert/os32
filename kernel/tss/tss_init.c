#include <tss.h>
#include <paging.h>
#include <gdt.h>
#include <bits/defs/proc.h>

tss_entry_t tss;

void tss_init()
{
    tss.ss0 = GDT_KERNEL_DATA;
    mmap(_KERNEL_STACK_POSITION - _STACK_SIZE, _STACK_SIZE);
    tss.esp0 = _KERNEL_STACK_POSITION;
    tss.iomap_base = sizeof(tss);

    new_segment_descriptor((unsigned int)&tss, sizeof(tss), 0x0, 0x89, 5);
}