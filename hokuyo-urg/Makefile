all: hokuyo-urg

TARBALL     = build/urg-0.8.13.zip
TARBALL_URL = http://www.hokuyo-aut.jp/02sensor/07scanner/download/urg_programs_en/urg-0.8.13.zip
UNPACK_CMD  = unzip -o
SOURCE_DIR  = build/urg-0.8.13
#TARBALL_PATCH = matrix.patch
MD5SUM_FILE = urg-0.8.13.zip.md5sum

include $(shell rospack find mk)/download_unpack_build.mk

INSTALL_DIR = install


hokuyo-urg: $(INSTALL_DIR)/installed

$(INSTALL_DIR)/installed: $(SOURCE_DIR)/unpacked
	mkdir -p $(INSTALL_DIR)
	cd $(SOURCE_DIR); ./configure --prefix=$(shell pwd)/$(INSTALL_DIR);
	cd $(SOURCE_DIR); make;
	cd $(SOURCE_DIR); make install;
	touch $(INSTALL_DIR)/installed

clean:
	rm -rf $(SOURCE_DIR) $(INSTALL_DIR)

wipe: clean
	rm -rf build
