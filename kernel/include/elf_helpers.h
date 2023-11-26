#include <elf.h>

void print_secHeaders(Elf32_Shdr *headers, Elf32_Word num, char *off, Elf32_Word addr_off, char *name_index);
int validate_elf(Elf32_Ehdr *elf);