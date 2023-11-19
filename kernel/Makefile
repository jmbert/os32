MKFILE_PATH = $(firstword $(MAKEFILE_LIST))
KERNELROOT = $(shell dirname $(MKFILE_PATH))

KERNELINCLUDE = $(KERNELROOT)/include
KERNELARCH = $(KERNELROOT)/arch

LIBCINCLUDE=$(KERNELROOT)/../libc/include

ASSETS = $(KERNELROOT)/assets

SYSROOT=$(KERNELROOT)/../sysroot
SYSROOTINCLUDE=$(SYSROOT)/include
SYSROOTARCHINCLUDE=$(SYSROOT)/include/arch-specific
SYSROOTLIBCINCLUDE=$(SYSROOT)/include/libc
SYSROOTLIB=$(SYSROOT)/lib
SYSROOTASSETS=$(SYSROOT)/assets

ARCHROOT = $(KERNELARCH)/$(TARGET)
ARCHINCLUDE = $(ARCHROOT)/include

CC = $(TARGETTOOL)-gcc
LD = $(TARGETTOOL)-ld
AS = $(TARGETTOOL)-as

CFLAGS += -Wall -Wpedantic
CPPFLAGS += -MD -I$(SYSROOTINCLUDE)  -I$(SYSROOTLIBCINCLUDE) -ffreestanding -nostdlib -m32 -fno-asynchronous-unwind-tables

include $(ARCHROOT)/arch.make

LDSCRIPT=linker.ld

LDFLAGS = -T$(LDSCRIPT) -nostdlib -melf_i386
LDPFLAGS = -L$(SYSROOTLIB) -l:libc.a

SRCS +=\
kernel_init.c\
tty/put_char.c\
tty/set_term.c\
tty/write_buffer.c\
tty/clear.c\
addr/conversion.c\
multiboot/helpers.c\
elf/helpers.c\
memory/memory.c\
fs/tar/lookup.c\
fs/tar/helpers.c\

SRCS += $(ARCH_SRCS)

OBJS = $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SRCS)))


KERNELBIN=kernel.bin


ERRLOG=/dev/null
MSG_COL=1;32


kernel-all: create-sysroot compile link install-initramfs iso


install-libc: 

%.o: %.c
	@printf "\e[$(MSG_COL)mCompiling $@ from $<\e[m\n"
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)
	@printf "\e[$(MSG_COL)mCompiled $@\e[m\n"

%.o: %.S
	@printf "\e[$(MSG_COL)mCompiling $@ from $<\e[m\n"
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)
	@printf "\e[$(MSG_COL)mCompiled $@\e[m\n"

$(KERNELBIN): $(OBJS)
	@printf "\e[$(MSG_COL)mLinking $@ from $^\e[m\n"
	$(LD) $(LDFLAGS) -o $@ $^ $(LDPFLAGS)
	@printf "\e[$(MSG_COL)mLinked $@\e[m\n"


create-sysroot:
	-mkdir  $(SYSROOT)
	rsync -r $(KERNELINCLUDE) $(SYSROOT)/
	cp -Lrp $(ARCHINCLUDE)/ $(SYSROOTARCHINCLUDE)
	cp -Lrp $(LIBCINCLUDE)/ $(SYSROOTLIBCINCLUDE)/
	-mkdir $(SYSROOT)/boot 
	-mkdir $(SYSROOTLIB)

compile: $(OBJS)

link: $(KERNELBIN) $(LDSCRIPT)

iso: link
	@printf "\e[$(MSG_COL)mCreating ISO\e[m\n"
	@cp $(KERNELBIN) $(KERNELROOT)/isodir/boot/
	@cp grub.cfg $(KERNELROOT)/isodir/boot/grub/
	@grub-mkrescue -o $(KERNELROOT)/kernel $(KERNELROOT)/isodir
	@printf "\e[$(MSG_COL)mCreated ISO\e[m\n"

install-kernel:
	@cp kernel $(SYSROOT)/boot/kernel

clean:
	-rm $(OBJS)
	-rm $(DEPS)
	-rm -rf $(SYSROOT) 
	-rm $(KERNELINCLUDE)/arch-specific
	-rm $(KERNELBIN)
	-rm -rf $(KERNELROOT)/isodir
	-rm $(KERNELROOT)/kernel
	-rm -rf $(KERNELROOT)/initramfs
	-rm $(KERNELROOT)/initramfs.img

install-initramfs:
	-mkdir initramfs
	-mkdir -p isodir/boot/grub
	rsync -r $(ASSETS) $(KERNELROOT)/initramfs/ 
	-tar -cH ustar  $(KERNELROOT)/initramfs -f $(KERNELROOT)/initramfs.img
	-cp -Lp $(KERNELROOT)/initramfs.img $(KERNELROOT)/isodir/boot/
	-cp -Lp $(KERNELROOT)/initramfs.img $(KERNELROOT)/../sysroot/boot/
	

DEPS = $(OBJS:.o=.d)

-include $(DEPS)