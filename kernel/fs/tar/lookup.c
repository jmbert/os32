#include <fs/tar.h>
#include <string.h>
#include <stdlib.h>

#include <debug/exec.h>

tar_header_t *tar_lookup(uint32_t archive, char *fileName)
{
    tar_header_t *file = (tar_header_t*)archive;
    for (;memcmp(file->indicator, "ustar", 5) == 0;)
    {
        if (strcmp(file->name, fileName) == 0)
        {
            return file;
        }

        uint64_t filesize = decodeOctal(file->sizeOct, 11);
        archive += (((filesize + 511) / 512) + 1) * 512;
        file = (tar_header_t*)archive;
    }
    return NULL;
}

char **tar_list_files(uint32_t archive)
{
    tar_header_t *dir = (tar_header_t*)archive;
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
        dir = (tar_header_t*)archive;
    }
    names[i] = NULL;

    return names;
}