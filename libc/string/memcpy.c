#include <string.h>

void *memcpy(void *destination, void *source, size_t num)
{
#ifdef _IN_KERNEL

	char* d = destination;
	char* s = source;
	for (int i = 0; i < num; i++) {
		d[i] = s[i];
	}
	return destination;

#else


#endif
}