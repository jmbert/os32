
#include <tty.h>

#include <vmem.h>

int vmem_clear()
{
    for (size_t i = 0; i < VMEM_SIZE; i++)
    {
        VMEM[i] = '\0';
    }
}