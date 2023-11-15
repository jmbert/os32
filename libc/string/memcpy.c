#include <string.h>

void *memcpy(void *destination, const void *source, size_t num)
{
#ifdef _IN_KERNEL

    int i;
	char* d = destination;
	char* s = source;
	for (i = 0; i < num; i++) {
		d[i] = s[i];
	}
	return destination;

#else


#endif
}