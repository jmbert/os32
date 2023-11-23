#ifndef _PALLOC_H
#define _PALLOC_H

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