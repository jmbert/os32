


int open(char *path, unsigned int modes)
{
    asm("mov $3, %%eax\n"
        "mov %0, %%ebx\n"
        "mov %1, %%ecx\n"
        "int $0x80"
        :: "m"(path), "m"(modes));
}

void read(unsigned int fd, char *buffer, unsigned int length)
{
    asm("mov $1, %%eax\n"
        "mov %0, %%ebx\n"
        "mov %1, %%ecx\n"
        "mov %2, %%edx\n"
        "int $0x80"
        :: "m"(fd), "m"(buffer), "m"(length));
}

void write(unsigned int fd, char *buffer, unsigned int length, unsigned int offset)
{
    asm("mov $2, %%eax\n"
        "mov %0, %%ebx\n"
        "mov %1, %%ecx\n"
        "mov %2, %%edx\n"
        "mov %3, %%edi\n"
        "int $0x80"
        :: "m"(fd), "m"(buffer), "m"(length), "m"(offset));
}

int _start(int argc, char **argv)
{
    int fd = open("/INFO", 0);
    char buffer[100];
    read(fd, buffer, 100);
    write(1, buffer, 100, 0);
    for (;;);
}