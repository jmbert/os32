MKFILE_PATH = $(firstword $(MAKEFILE_LIST))
CATROOT = $(shell dirname $(MKFILE_PATH))
CATEXEC = $(CATROOT)/../cat

TARGETTOOL?=i686-elf

CC = $(TARGETTOOL)-gcc
LD = $(TARGETTOOL)-ld
AS = $(TARGETTOOL)-as

CFLAGS += 
CPPFLAGS+=

LDFLAGS = -nostdlib -melf_i386
LDPFLAGS =

SRCS+=\
main.c

OBJS = $(patsubst %.c,%.o,$(SRCS))


%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)

$(CATEXEC): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LDPFLAGS)

build: $(OBJS) $(CATEXEC)

clean:
	rm $(OBJS)