MKFILE_PATH = $(firstword $(MAKEFILE_LIST))
LIBROOT = $(shell dirname $(MKFILE_PATH))
KERNELROOT = $(LIBROOT)/../kernel

LIBINCLUDE = $(LIBROOT)/include
KERNELINCLUDE = $(KERNELROOT)/include

SYSROOT=$(LIBROOT)/../sysroot

TARGETTOOL?=i686-elf

CC = $(TARGETTOOL)-gcc
LD = $(TARGETTOOL)-ld
AS = $(TARGETTOOL)-as
AR = $(TARGETTOOL)-ar 

CFLAGS += 
CPPFLAGS += -I$(LIBINCLUDE) -I$(KERNELINCLUDE)


ARFLAGS =

SRCS +=\
stdlib/malloc.c\
stdio/putchar.c\
stdio/puts.c\
stdio/printf.c\
string/memset.c\
string/memcpy.c\
string/strcmp.c\
string/strlen.c\
string/strtok.c\
string/strrchr.c\
math/comp.c

OBJS = $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SRCS)))

LIBC=libkernel.a


ERRLOG=/dev/null
MSG_COL=1;32

libc-all: compile link

install-libc:
	cp $(LIBC) $(SYSROOT)/lib/$(LIBC)
	cp $(LIBGCC) $(SYSROOT)/lib/

%.o: %.c
	@printf "\e[$(MSG_COL)mCompiling $@ from $<\e[m\n"
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)

%.o: %.S
	@printf "\e[$(MSG_COL)mCompiling $@ from $<\e[m\n"
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)

$(LIBC): $(OBJS)
	@printf "\e[$(MSG_COL)mLinking $@ from $^\e[m\n"
	$(AR) rcs $(ARFLAGS) -o $@ $^

compile: $(OBJS)

link: $(LIBC) $(LDSCRIPT)

clean:
	-rm $(OBJS) 2> $(ERRLOG)
	-rm $(DEPS) 2> $(ERRLOG)
	-rm $(LIBC)

DEPS = $(OBJS:.o=.d)

-include $(DEPS);