.PHONY: all

all: deb 

###############################################################################
ARCH ?= intel
BASE_DIR ?= $(shell pwd)
OUT_DIR ?= $(BASE_DIR)/bin/$(ARCH)
SCRIPT_PATH ?= $(BASE_DIR)/scripts
FPA_RELEASE    =`cat version.txt | grep fpa_release    | awk {'print $$2'}`
FPA_VERSION    =`cat version.txt | grep fpa_version    | awk {'print $$2'}`
###############################################################################
FPA_PATH ?= $(BASE_DIR)
FPA_LIB_PATH := $(FPA_PATH)/bin/$(ARCH)/lib
###############################################################################


$(FPA_LIB_PATH)/libfpa.so:
	@ $(ECHO) "FPA lib does not exist !!!"

lib: $(FPA_LIB_PATH)/libfpa.so
	
deb: lib
	@ $(SCRIPT_PATH)/make_deb.sh $(OUT_DIR) $(FPA_VERSION) $(FPA_RELEASE)

