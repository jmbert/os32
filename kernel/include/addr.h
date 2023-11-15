#ifndef _ADDR_H
#define _ADDR_H

#include <stdint.h>

#include <info/link_info.h>

typedef uint32_t vaddr;

typedef uint32_t paddr;

paddr vaddrtopaddr(vaddr virtualaddr);

#endif