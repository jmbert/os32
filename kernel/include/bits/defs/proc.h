#ifndef MAX_PROCESSES
#define MAX_PROCESSES 0x1000
#endif

#ifndef _STACK_OFFSET
#define _STACK_OFFSET 0x100000
#endif

#ifndef _STACK_POSITION
#define _STACK_POSITION (KERNEL_OFFSET - _STACK_OFFSET)
#endif


#ifndef _STACK_SIZE
#define _STACK_SIZE 0x4000
#endif