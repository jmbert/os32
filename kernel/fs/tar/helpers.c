#include <fs/tar.h>
#include <stdio.h>
#include <string.h>

int decodeOctal(char *str, int size) 
{
    int n = 0;
    unsigned char *c = str;
    while (size-- > 0) 
    {
        n *= 8;
        n += *c - '0';
        c++;
    }
    return n;
}

void print_tar_file(struct tar_header *file)
{
    printf("\"%s\":\n", file->name);
    printf("\tFile Mode: %s\n", file->mode);
    printf("\tFile Size: 0x%x\n", decodeOctal(file->sizeOct, 11));
    printf("\tFile Data: 0x%x\n", ((uint32_t)file)+512);
}

int validate_header(tar_header_t *header)
{
    if (memcmp(header->indicator, "ustar", 5) != 0)
    {
        return 0;
    }
    return 1;
}