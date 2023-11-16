MKFILE_PATH = $(firstword $(MAKEFILE_LIST))
LIBROOT = $(shell dirname $(MKFILE_PATH))
KERNELROOT = $(LIBROOT)/../kernel

LIBINCLUDE = $(LIBROOT)/include
KERNELINCLUDE = $(KERNELROOT)/include

SYSROOT=$(LIBROOT)/../sysroot

CC = $(TARGETTOOL)-gcc
LD = $(TARGETTOOL)-ld
AS = $(TARGETTOOL)-as
AR = $(TARGETTOOL)-ar

CFLAGS += -Wall -Wpedantic
CPPFLAGS += -I$(LIBINCLUDE) -I$(KERNELINCLUDE) -MD -ffreestanding -nostdlib -m32 -fno-asynchronous-unwind-tables


ARFLAGS = 

SRCS +=\
stdlib/malloc.c\
stdio/putchar.c\
string/memset.c\
string/memcpy.c\
math/comp.c\

OBJS = $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SRCS)))

LIBC=libc.a


ERRLOG=/dev/null
MSG_COL=1;32

libc-all: compile link

install-libc:
	cp $(LIBC) $(SYSROOT)/lib/$(LIBC)

%.o: %.c
	@printf "\e[$(MSG_COL)mCompiling $@ from $<\e[m\n"
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)
	@printf "\e[$(MSG_COL)mCompiled $@\e[m\n"

%.o: %.S
	@printf "\e[$(MSG_COL)mCompiling $@ from $<\e[m\n"
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)
	@printf "\e[$(MSG_COL)mCompiled $@\e[m\n"

$(LIBC): $(OBJS)
	@printf "\e[$(MSG_COL)mLinking $@ from $^\e[m\n"
	$(AR) rcs $(ARFLAGS) -o $@ $^
	@printf "\e[$(MSG_COL)mLinked $@\e[m\n"

compile: $(OBJS)

link: $(LIBC) $(LDSCRIPT)

clean:
	-rm $(OBJS) 2> $(ERRLOG)
	-rm $(DEPS) 2> $(ERRLOG)
	-rm $(LIBC)

DEPS = $(OBJS:.o=.d)

-include $(DEPS);