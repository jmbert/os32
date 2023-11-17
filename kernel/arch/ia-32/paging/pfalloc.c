#include <arch-specific/page_alloc.h>

#include <info/link_info.h>
#include <stdint.h>
#include <stddef.h>

#include <string.h>

#include <debug/exec.h>
#include <debug/mem.h>

uint8_t framemap[MAX_FRAMES] = {PAGE_FRAME_UNUSED};

paddr pframe_alloc()
{
    vaddr frame = 0;


    for (size_t i = 0; i < MAX_FRAMES; i++) 
    {
        if (framemap[i] == PAGE_FRAME_UNUSED) 
        {
            frame = (vaddr)((i * PAGE_SIZE) + PAGING_RESERVED_START);
            framemap[i] = PAGE_FRAME_USED;
            break;
        }
    }

    if (frame == 0)
    {
        return 0;
    }

    memset((void*)frame, 0, PAGE_SIZE);

    paddr fpaddr = vaddrtopaddr(frame);

    return fpaddr;
}

int pframe_free(paddr frame)
{

    // TODO: Implement

    return 0;
}