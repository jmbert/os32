.PHONY: clean sysroot kernel libc all

all: libc kernel

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C libc clean


kernel: sysroot
	$(MAKE) -C kernel kernel-all
	$(MAKE) -C kernel install-kernel

libc: sysroot
	$(MAKE) -C libc libc-all
	$(MAKE) -C libc install-libc

sysroot:
	$(MAKE) -C kernel create-sysroot