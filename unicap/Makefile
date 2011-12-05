all: unicap

TARBALL     = build/libunicap-0.9.8.tar.gz
TARBALL_URL = http://unicap-imaging.org/downloads/libunicap-0.9.8.tar.gz
UNPACK_CMD  = tar -xf
SOURCE_DIR  = build/libunicap-0.9.8
#TARBALL_PATCH = matrix.patch
MD5SUM_FILE = libunicap-0.9.8.tar.gz.md5sum

include $(shell rospack find mk)/download_unpack_build.mk

INSTALL_DIR = install


unicap: $(INSTALL_DIR)/installed

$(INSTALL_DIR)/installed: $(SOURCE_DIR)/unpacked
	mkdir -p $(INSTALL_DIR)
#	patch $(SOURCE_DIR)/include/unicap.h -i ./patches_v0.9.8/patch-ab
#	patch $(SOURCE_DIR)/src/unicap.c -i ./patches_v0.9.8/patch-ac
	cd $(SOURCE_DIR); ./configure --prefix=$(shell pwd)/$(INSTALL_DIR);
	cd $(SOURCE_DIR); make;
	touch $(INSTALL_DIR)/installed
	cd $(SOURCE_DIR); make install;

clean:
	rm -rf $(SOURCE_DIR) $(INSTALL_DIR)

wipe: clean
	rm -rf build
