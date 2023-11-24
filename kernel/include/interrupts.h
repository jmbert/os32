#ifndef _INT_H
#define _INT_H

typedef struct
{
    unsigned int eflags;
    unsigned int cs_padded;
    unsigned int eip;
}int_stackframe_t;

#endif