#ifndef _FS_TAR_H
#define _FS_TAR_H

#include <stdint.h>

#define MAX_DIR_ITEMS 0x200

#define DATA_FROM_HEADER(addr) ((uint32_t)(addr) + 512)

struct tar_header
{
    uint8_t name[100];
    uint8_t mode[8];
    uint8_t uid[8];
    uint8_t guid[8];
    uint8_t sizeOct[12];
    uint8_t mTime[12];
    uint8_t checkSum[8];
    uint8_t type;
    uint8_t linkName[100];
    uint8_t indicator[6];
    uint8_t ver[2];
    uint8_t owner[32];
    uint8_t gowner[32];
    uint8_t devMajor[8];
    uint8_t devMinor[8];

    uint8_t namePrefix[32];
};

enum
{
    TAR_NORMAL_FILE = '0',
    TAR_HLINK,
    TAR_SLINK,
    TAR_CDEV,
    TAR_BDEV,
    TAR_DIR,
    TAR_PIPE,
};

int decodeOctal(unsigned char *str, int size);

struct tar_header *tar_lookup(uint32_t archive, uint8_t *fileName);

char **tar_list_subdirs(uint32_t archive, uint8_t *fileName);

void print_tar_file(struct tar_header *file);

#endif