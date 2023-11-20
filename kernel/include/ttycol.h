#ifndef _TTYCOL_H
#define _TTYCOL_H

#include <tty.h>

#define COL16(fg, bg) _MIX(fg, bg)

#define COL16BLINK(fg, bg, blink) _MIX(fg, (((blink & 0x1) << 7) | bg))


#define _MIX(fg, bg)     ((bg & 0x0f) << 4) | \
                        ((fg & 0x0f))

#define COLRGB(r, g, b)     ((((uint32_t)r) << framebuffer.rmask_position) | \
                            (((uint32_t)g) << framebuffer.gmask_position) | \
                            (((uint32_t)b) << framebuffer.bmask_position))

enum {
    BLACK16,
    BLUE16,
    GREEN16,
    CYAN16,
    RED16,
    MAGENTA16,
    BROWN16,
    WHITE16,
    GRAY16,
    LIGHTBLUE16,
    LIGHTGREEN16,
    LIGHTCYAN16,
    LIGHTRED16,
    LIGHTMAGENTA16,
    YELLOW16,
    BRIGHTWHITE16,
};

#endif