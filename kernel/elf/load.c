#include <elf_loader.h>
#include <elf_helpers.h>
#include <stdio.h>
#include <debug/exec.h>

static unsigned short pflags(Elf32_Word phflags, _process_type_e privilege)
{
    unsigned short flags;

    if (privilege == PROC_MODE_USER)
    {
        flags |= PAGE_USER;
    }

    if (phflags & PF_W)
    {
        flags |= PAGE_WRITABLE;
    }

    return flags; 
}

static void load_phdr(Elf32_Ehdr *elf_file, Elf32_Phdr header, _process_type_e privilege)
{
    mmap(header.p_vaddr, header.p_memsz, pflags(header.p_flags, privilege));
    void *phcontent = ELF_OFFSET(elf_file, header.p_offset);
    memcpy(header.p_vaddr, phcontent, header.p_filesz);
}

unsigned int load_elf(Elf32_Ehdr *elf_file, _process_type_e privilege)
{
    unsigned int entry = elf_file->e_entry;
    unsigned int phlen = elf_file->e_phnum;
    Elf32_Phdr *phs = (Elf32_Phdr*)ELF_OFFSET(elf_file, elf_file->e_phoff);

    for (unsigned int i = 0; i < phlen; i++)
    {
        if (phs[i].p_type & PT_LOAD)
        {
            load_phdr(elf_file, phs[i], privilege);
        }
    }
    
    return entry;
}