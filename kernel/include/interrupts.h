#ifndef _INT_H
#define _INT_H

#include <tss.h>
#include <gdt.h>

typedef struct
{
    unsigned int eflags;
    unsigned int cs_padded;
    unsigned int eip;
}int_stackframe_t;

typedef enum
{
    EXCEPTION_DIV0,
    EXCEPTION_DEBUG,
    EXCEPTION_NMI,
    EXCEPTION_BREAKPOINT,
    EXCEPTION_OVERFLOW,
    EXCEPTION_BOUND_RANGE_EXCEEDED,
    EXCEPTION_INVALID_OPCODE,
    EXCEPTION_DEVICE_NOT_AVAILABLE,
    EXCEPTION_DOUBLE_FAULT,
    EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN [[deprecated("No more coprocessor")]],
    EXCEPTION_INVALID_TSS,
    EXCEPTION_SEGMENT_NOT_PRESENT,
    EXCEPTION_STACK_SEGMENT_FAULT,
    EXCEPTION_GENERAL_PROTECTION_FAULT,
    EXCEPTION_PAGE_FAULT,
    EXCEPTION_x87_FLOATING = 0x10,
    EXCEPTION_ALIGNMENT_CHECK,
    EXCEPTION_MACHINE_CHECK,
    EXCEPTION_SIMD_FLOATING,
    EXCEPTION_VIRTUALISATION,
    EXCEPTION_CONTROL_PROTECTION,
    EXCEPTION_HYPERVISOR_INJECTION = 0x28,
    EXCEPTION_VMM_COMMUNICATION,
    EXCEPTION_SECURITY,
}_int_exceptions_e;

void div0_handler_trap(int_stackframe_t *sf, unsigned int err_code);
void double_fault_handler_trap(int_stackframe_t *sf, unsigned int err_code);

#endif