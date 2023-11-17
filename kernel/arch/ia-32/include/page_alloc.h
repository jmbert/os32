#ifndef _IA32_P_ALLOC_H
#define _IA32_P_ALLOC_H

#include <addr.h>

#include <info/link_info.h>

#include "paging.h"


enum {
    PAGE_FRAME_UNUSED,
    PAGE_FRAME_USED,
};

paddr pframe_alloc();
int pframe_free(paddr frame);

#endif