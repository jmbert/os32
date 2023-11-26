#ifndef _FS_TAR_H
#define _FS_TAR_H

#include <stdint.h>
#include <vfs.h>

#define MAX_DIR_ITEMS 0x200

#define DATA_FROM_HEADER(addr) ((uint32_t)(addr) + 512)

typedef struct tar_header
{
    char name[100];
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
    char owner[32];
    char gowner[32];
    uint8_t devMajor[8];
    uint8_t devMinor[8];

    char namePrefix[32];
}tar_header_t;

struct tar_file
{
    tar_header_t *header;
    void *data;
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

int decodeOctal(char *str, int size);

tar_header_t *tar_lookup(uint32_t archive, char *fileName);
char **tar_list_files(uint32_t archive);

vfs_t convert_to_vfs(unsigned int archive);

int validate_header(tar_header_t *header);

#endif