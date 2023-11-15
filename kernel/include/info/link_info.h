#ifndef _LINK_INFO_H
#define _LINK_INFO_H

#include <addr.h>

extern uint32_t _LD_KERNEL_OFFSET;
extern uint32_t _LD_KERNEL_START;
extern uint32_t _LD_KERNEL_END;
extern uint32_t _LD_KERNEL_SIZE;
extern uint32_t _LD_KERNEL_PHYS_START;
extern uint32_t _LD_PAGING_RESERVED_START;

#define _LINKCAST(id, t) ((t)id)

#define KERNEL_OFFSET _LINKCAST(&_LD_KERNEL_OFFSET, vaddr)
#define KERNEL_START _LINKCAST(&_LD_KERNEL_START, vaddr)
#define KERNEL_END _LINKCAST(&_LD_KERNEL_END, vaddr)
#define KERNEL_SIZE _LINKCAST(&_LD_KERNEL_SIZE, vaddr)
#define KERNEL_PHYS_START _LINKCAST(&_LD_KERNEL_PHYS_START, vaddr)
#define PAGING_RESERVED_START _LINKCAST(&_LD_PAGING_RESERVED_START, vaddr)


#endif