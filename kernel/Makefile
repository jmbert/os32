MKFILE_PATH = $(firstword $(MAKEFILE_LIST))
KERNELROOT = $(shell dirname $(MKFILE_PATH))

KERNELINCLUDE = $(KERNELROOT)/include
KERNELARCH = $(KERNELROOT)/arch

LIBCINCLUDE=$(KERNELROOT)/../libc/include

SYSROOT=$(KERNELROOT)/../sysroot
SYSROOTINCLUDE=$(SYSROOT)/include
SYSROOTARCHINCLUDE=$(SYSROOT)/include/arch-specific
SYSROOTLIBCINCLUDE=$(SYSROOT)/include/libc
SYSROOTLIB=$(SYSROOT)/lib

ARCHROOT = $(KERNELARCH)/$(TARGET)
ARCHINCLUDE = $(ARCHROOT)/include

CC = $(TARGETTOOL)-gcc
LD = $(TARGETTOOL)-ld
AS = $(TARGETTOOL)-as

CFLAGS += -Wall -Wpedantic
CPPFLAGS += -I$(SYSROOTINCLUDE)  -I$(SYSROOTLIBCINCLUDE) -ffreestanding -nostdlib -m32 -fno-asynchronous-unwind-tables

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

SRCS += $(ARCH_SRCS)

OBJS = $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SRCS)))


KERNELBIN=kernel.bin


ERRLOG=/dev/null
MSG_COL=1;32


kernel-all: create-sysroot compile link iso


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
	@printf "\e[$(MSG_COL)mCreating Sysroot\e[m\n"
	@-mkdir  $(SYSROOT) 2> $(ERRLOG)
	@cp -Lr $(KERNELINCLUDE)/ $(SYSROOT)/ 2> $(ERRLOG)
	@cp -Lr $(ARCHINCLUDE)/ $(SYSROOTARCHINCLUDE)/ 2> $(ERRLOG)
	@cp -Lr $(LIBCINCLUDE)/ $(SYSROOTLIBCINCLUDE)/ 2> $(ERRLOG)
	@-mkdir $(SYSROOT)/boot 2> $(ERRLOG)
	@-mkdir $(SYSROOTLIB) 2> $(ERRLOG)
	@printf "\e[$(MSG_COL)mCreated Sysroot\e[m\n"

compile: $(OBJS)

link: $(KERNELBIN) $(LDSCRIPT)

iso: link
	@printf "\e[$(MSG_COL)mCreating ISO\e[m\n"
	@-mkdir -p isodir/boot/grub 2> $(ERRLOG)
	@cp $(KERNELBIN) isodir/boot/ 2> $(ERRLOG)
	@cp grub.cfg isodir/boot/grub/ 2> $(ERRLOG)
	@grub-mkrescue -o kernel isodir 2> $(ERRLOG)
	@printf "\e[$(MSG_COL)mCreated ISO\e[m\n"

install-kernel:
	@cp kernel $(SYSROOT)/boot/kernel

clean:
	-rm $(OBJS) 2> $(ERRLOG)
	-rm $(DEPS) 2> $(ERRLOG)
	-rm -rf $(SYSROOT) 2> $(ERRLOG) 
	-rm $(KERNELINCLUDE)/arch-specific 2> $(ERRLOG)
	-rm $(KERNELBIN)
	-rm -rf isodir
	-rm kernel

DEPS = $(OBJS:.o=.d)