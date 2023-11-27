MKFILE_PATH = $(firstword $(MAKEFILE_LIST))
KERNELROOT = $(shell dirname $(MKFILE_PATH))

KERNELINCLUDE = $(KERNELROOT)/include
KERNELARCH = $(KERNELROOT)/arch

LIBCINCLUDE=$(KERNELROOT)/../libc/include

BUILD=$(KERNELROOT)/build

SYSROOT=$(KERNELROOT)/../sysroot
SYSROOTINCLUDE=$(SYSROOT)/include
SYSROOTLIBCINCLUDE=$(SYSROOT)/include/libkernel
SYSROOTLIB=$(SYSROOT)/lib
SYSROOTASSETS=$(SYSROOT)/assets

TARGETTOOL?=i686-elf

CC = $(TARGETTOOL)-gcc
LD = $(TARGETTOOL)-ld
AS = $(TARGETTOOL)-as

CFLAGS += -fno-stack-protector -ffreestanding -nostdlib -mgeneral-regs-only
CPPFLAGS+=-I$(SYSROOTINCLUDE)  -I$(SYSROOTLIBCINCLUDE)

LDSCRIPT=linker.ld

LDFLAGS = -T$(LDSCRIPT) -nostdlib -melf_i386 --sysroot=$(SYSROOT)
LDPFLAGS = -lkernel -lgcc 

SRCS +=\
kernel_init.c\
kernel_main.c\
addr/conversion.c\
multiboot/helpers.c\
elf/helpers.c\
memory/memory.c\
memory/mman_init.c\
memory/log.c\
fs/_add_new_file.c\
fs/new_virtual_file.c\
fs/tar/lookup.c\
fs/tar/helpers.c\
fs/tar/to_vfs.c\
paging/mmap.c\
paging/map.c\
paging/pfalloc.c\
paging/helpers.S\
paging/paging_init.c\
boot/boot.S\
graphics/_graphics_info.c\
graphics/graphics_swap.c\
terminal/terminal_write_swap.c\
bits/var/fs.c\
colours/_convert_colour.c\
proc/new_process.c\
proc/_initialise_pdir.c\
proc/switch_process.c\
bits/var/proc.c\
proc/getpid.c\
proc/_proclookup.c\
proc/exit.c\
proc/fork.c\
proc/print_procs.c\
fs/get_fdtable.c\
bits/var/terminal.c\
gdt/gdt.c\
gdt/load_gdt.S\
idt/idt_init.c\
idt/register_interrupt.c\
interrupts/div0_handler.c\
interrupts/double_fault_handler.c\
interrupts/page_fault_handler.c\
interrupts/gpf_handler.c\
tss/tss_init.c\
tss/load_tss.S\
proc/ring_switch.S\
proc/switch_stack.S\
fs/open.c\
fs/tar/vfs_ops.c\
streams/init_streams.c\
char_dev/new_char_device.c\
fs/_add_node.c\
fs/_get_node.c\
fs/_open.c\
fs/_rw.c\
elf/load.c\
proc/process_from_elf.c\
syscalls/syscall.S\
syscalls/syscall_read.c\
syscalls/syscall_open.c\
syscalls/syscall_close.c\
syscalls/syscall_stat.c\
syscalls/syscall_write.c\
fs/_close_file.c\

OBJS = $(patsubst %.S,$(BUILD)/%.o,$(patsubst %.c,$(BUILD)/%.o,$(SRCS)))


KERNELBIN=kernel.bin


ERRLOG=/dev/null
MSG_COL=1;32

SUBDIRS = $(patsubst %,$(BUILD)/%,$(shell tree -dfi -I build --noreport --gitfile=$(KERNELROOT)/../.gitignore $(KERNELROOT)))


kernel-all: compile link install-initramfs iso


$(BUILD)/%.o: %.c
	@printf "\e[$(MSG_COL)mCompiling $@ from $<\e[m\n"
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)

$(BUILD)/%.o: %.S
	@printf "\e[$(MSG_COL)mCompiling $@ from $<\e[m\n"
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)

$(KERNELBIN): $(OBJS)
	@printf "\e[$(MSG_COL)mLinking $@ from $^\e[m\n"
	$(LD) $(LDFLAGS) -o $@ $^ $(LDPFLAGS)


create-sysroot:
	@-mkdir $(BUILD)
	@-mkdir $(SUBDIRS)
	@-mkdir  $(SYSROOT)
	@cp -Lrp $(KERNELINCLUDE) $(SYSROOT)/
	@cp -Lrp $(LIBCINCLUDE)/ $(SYSROOTLIBCINCLUDE)/
	@-mkdir $(SYSROOT)/boot 
	@-mkdir $(SYSROOTLIB)

compile: $(OBJS)

link: $(KERNELBIN) $(LDSCRIPT)

iso: link
	@printf "\e[$(MSG_COL)mCreating ISO\e[m\n"
	@cp $(KERNELBIN) $(KERNELROOT)/isodir/boot/
	@cp grub.cfg $(KERNELROOT)/isodir/boot/grub/
	@grub-mkrescue -quiet -o $(KERNELROOT)/kernel $(KERNELROOT)/isodir
	@printf "\e[$(MSG_COL)mCreated ISO\e[m\n"

install-kernel:
	@cp kernel $(SYSROOT)/boot/kernel

clean:
	@-rm -rf $(BUILD)
	@-rm -rf $(SYSROOT)
	@-rm $(KERNELBIN)
	@-rm -rf $(KERNELROOT)/isodir
	@-rm $(KERNELROOT)/kernel
	@-rm $(KERNELROOT)/initramfs.img

install-initramfs:
	@-mkdir initramfs
	@-mkdir -p isodir/boot/grub
	@-tar -cH ustar -C $(KERNELROOT)/initramfs . -f $(KERNELROOT)/initramfs.img
	@-cp -Lp $(KERNELROOT)/initramfs.img $(KERNELROOT)/isodir/boot/
	@-cp -Lp $(KERNELROOT)/initramfs.img $(KERNELROOT)/../sysroot/boot/
	

DEPS = $(OBJS:.o=.d)

-include $(DEPS)