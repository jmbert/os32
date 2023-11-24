#include <fs/tar.h>
#include <string.h>
#include <stdlib.h>

#include <debug/exec.h>

struct tar_header *tar_lookup(uint32_t archive, unsigned char *fileName)
{
    struct tar_header *file = (struct tar_header*)archive;
    for (;memcmp(file->indicator, "ustar", 5) == 0;)
    {
        if (strcmp(file->name, fileName) == 0)
        {
            return file;
        }

        uint64_t filesize = decodeOctal(file->sizeOct, 11);
        archive += (((filesize + 511) / 512) + 1) * 512;
        file = (struct tar_header*)archive;
    }
    return NULL;
}

char **tar_list_subdirs(uint32_t archive, uint8_t *fileName)
{
    struct tar_header *dir = tar_lookup(archive, fileName);
    if (dir == NULL)
    {
        return NULL;
    }

    if (dir->type != TAR_DIR)
    {
        return NULL;
    }

    char **names = (char**)malloc(sizeof(char*)*(MAX_DIR_ITEMS));
    if (names == NULL)
    {
        return NULL;
    }
    int i = 0;
    archive = (uint32_t)dir;
    for (;memcmp(dir->indicator, "ustar", 5) == 0 && i < MAX_DIR_ITEMS;i++)
    {
        names[i] = dir->name;

        uint64_t filesize = decodeOctal(dir->sizeOct, 11);
        archive += (((filesize + 511) / 512) + 1) * 512;
        dir = (struct tar_header*)archive;
    }
    names[i] = NULL;

    return names;
}