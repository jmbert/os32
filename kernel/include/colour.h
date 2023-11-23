#ifndef _COLOURS_H
#define _COLOURS_H

typedef unsigned long long colour_t;

typedef struct
{
    unsigned int rmask;
    unsigned int gmask;
    unsigned int bmask;
}colour_info_t;

unsigned char *_convert_colour(colour_t col, unsigned int pixelWidth);

#endif