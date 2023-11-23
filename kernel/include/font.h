#ifndef _FONT_H
#define _FONT_H

typedef struct font_t
{
    unsigned int c_width;
    unsigned int c_height;

    unsigned char *chardata;


}font_t;

#define GET_GLYPH(_char, _font) (((_font).chardata)+((_char)*(_font).c_height))
#define GET_GLYPH_STATE(_row, _column, _glyph, _font) ((_glyph)[(_row)] & (1 << (((_font).c_width - 1) - (_column))))

#endif