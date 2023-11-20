#include <stdint.h>

#define VMEM_START 0xcf000000
#define VMEM ((uint32_t*)VMEM_START)
#define VMEM_SIZE framebuffer.pitch*framebuffer.height