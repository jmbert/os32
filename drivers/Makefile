MKFILE_PATH = $(firstword $(MAKEFILE_LIST))
DRIVERROOT = $(shell dirname $(MKFILE_PATH))
DRIVERINSTALL= $(DRIVERROOT)/../kernel/initramfs/drivers

DRIVERS=\
cat

.PHONY: build_drivers $(DRIVERS)


build_drivers: $(DRIVERS)

install_drivers: $(DRIVERS)
	cp -rv $^ $(DRIVERINSTALL)/

clean: 
	-rm `tree --noreport -fi | grep \.o`
	-rm $(DRIVERS)

cat:
	$(MAKE) -C cat_src build