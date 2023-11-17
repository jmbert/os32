#include <elf.h>
#include <stdio.h>

void print_flags(Elf32_Word flags, char *off)
{
    printf("%sFlags: ", off);
    if (flags & SHF_WRITE)
    {
        printf("W");
    }
    if (flags & SHF_ALLOC)
    {
        printf("A");
    }
    if (flags & SHF_EXECINSTR)
    {
        printf("X");
    }
    if (flags & SHF_MERGE)
    {
        printf("M");
    }
    if (flags & SHF_STRINGS)
    {
        printf("S");
    }
    if (flags & SHF_INFO_LINK)
    {
        printf("I");
    }
    if (flags & SHF_LINK_ORDER)
    {
        printf("L");
    }
    if (flags & SHF_OS_NONCONFORMING)
    {
        printf("O");
    }
    if (flags & SHF_GROUP)
    {
        printf("G");
    }
    if (flags & SHF_TLS)
    {
        printf("T");
    }
    printf("\n");
}

void print_secHeaders(Elf32_Shdr *headers, Elf32_Word num, char *off, Elf32_Word addr_off, char *name_index)
{
    if (headers != 0 && num != 0)
    {
        printf("Elf Section Headers:\n");
        for (int i = 0; i < num; i++, headers++)
        {

            printf("%sSection Name: \"%s\"\n", off, name_index+headers->sh_name);
            printf("%sSection Type: 0x%x\n", off, headers->sh_type);
            printf("%sSection Address: 0x%x\n", off, headers->sh_addr);
            printf("%sSection Offset: 0x%x\n", off, headers->sh_offset);
            print_flags(headers->sh_flags, off);
            printf("%sSection Info: 0x%x\n\n", off, headers->sh_info);
        }
    }
}
