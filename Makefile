.PHONY: clean sysroot kernel drivers libc all

CFLAGS +=  -m32 -fno-asynchronous-unwind-tables -Wall -Wpedantic -std=gnu23
CPPFLAGS += -MD 

export CFLAGS CPPFLAGS

all: libc drivers kernel

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C libc clean
	$(MAKE) -C drivers clean
	-rm initramfs.img
	-rm os.iso

drivers:
	$(MAKE) -C drivers build_drivers
	$(MAKE) -C drivers install_drivers

kernel: sysroot
	$(MAKE) -C kernel kernel-all
	$(MAKE) -C kernel install-kernel

libc: sysroot
	$(MAKE) -C libc libc-all
	$(MAKE) -C libc install-libc

sysroot:
	$(MAKE) -C kernel create-sysroot