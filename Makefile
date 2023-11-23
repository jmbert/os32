.PHONY: clean sysroot kernel libc all

CFLAGS += -fno-stack-protector -ffreestanding -nostdlib -m32 -fno-asynchronous-unwind-tables -Wall -Wpedantic -std=gnu23
CPPFLAGS += -MD 

export CFLAGS CPPFLAGS

all: libc kernel

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C libc clean
	-rm initramfs.img
	-rm os.iso


kernel: sysroot
	$(MAKE) -C kernel kernel-all
	$(MAKE) -C kernel install-kernel

libc: sysroot
	$(MAKE) -C libc libc-all
	$(MAKE) -C libc install-libc

sysroot:
	$(MAKE) -C kernel create-sysroot