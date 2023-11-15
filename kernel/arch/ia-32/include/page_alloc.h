#ifndef _IA32_P_ALLOC_H
#define _IA32_P_ALLOC_H

#include <addr.h>

#include <info/link_info.h>

#include "paging.h"

#define MAX_FRAMES 0x100

enum {
    PAGE_FRAME_UNUSED,
    PAGE_FRAME_USED,
};

vaddr pframe_alloc();
int pframe_free(paddr frame);

#endif