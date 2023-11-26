#ifndef _ELF_LDR_H
#define _ELF_LDR_H

#include <elf.h>
#include <proc.h>
#include <paging.h>

#define ELF_OFFSET(_elf_start, _offset) ((unsigned int)(_elf_start) + _offset)

unsigned int load_elf(Elf32_Ehdr *elf_file, _process_type_e privilege);

#endif