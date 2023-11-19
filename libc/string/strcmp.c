#include <string.h>


int strcmp(char *src1, char *src2)
{
    int i=0;
    while((*src1!='\0') || (*src2!='\0'))
    {
        if(*src1 > *src2)
            return 1;
        if(*src1 < *src2)
            return -1;
        src1++;
        src2++;
    }
    return 0;
}

int memcmp(const void *str1, const void *str2, size_t n)
{
    const unsigned char *s1 = (const unsigned char*)str1;
    const unsigned char *s2 = (const unsigned char*)str2;
    
    while (n-- > 0)
      {
        if (*s1++ != *s2++)
    	  return s1[-1] < s2[-1] ? -1 : 1;
      }
    return 0;
}