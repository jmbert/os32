#ifndef _DEBUG_MEM_H
#define _DEBUG_MEM_H

#define WRITE(val, addr, type) *(type*)(addr) = val
#define READ(val, addr, type) val = *(type*)(addr);

#endif