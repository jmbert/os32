
#include <colour.h>
#include <stdlib.h>

#include <debug/exec.h>

unsigned char *_convert_colour(colour_t col, unsigned int pixelWidth)
{
    unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char)*pixelWidth);

    for (unsigned int i = 0; i < pixelWidth; i++)
    {
        buf[i] = (col >> (8 * i)) & 0xFF;
    }
    return buf;
}
