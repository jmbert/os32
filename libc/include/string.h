#ifndef _LIBC_STRING_H
#define _LIBC_STRING_H

#include <sys/cdefs.h>

#include <stddef.h>


void *memset(void *str, int c, size_t n);

void *memcpy(void *destination, void *source, size_t num);

int memcmp(const void *s1, const void *s2, size_t n);

int strcmp(char *str1, char *str2);

unsigned int strlen(char *str);


char* strtok(char* s, char* delm);

#endif