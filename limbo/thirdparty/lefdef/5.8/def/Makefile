#  $Source: /usr1/mfg/3.4C/solaris_bld/group/util/makefiles/RCS/dir.mk,v $
#
#  $Author: wanda $
#  $Revision: #3 $
#  $Date: 2004/09/29 $
#  $State: Exp $
#

.PHONY: all
all: install release

LIMBO_ROOT_DIR = $(realpath ../../../../..)
BUILD_ORDER	= \
			def \
			cdef \
			cdefzlib \
			defzlib \
			defrw \
			defwrite \
			defdiff

## HP-UX 9.0.X
OS_TYPE := $(shell uname)
ifeq ($(OS_TYPE),HP-UX)
OPTIMIZE_FLAG = +O2
else
OS_VER := $(shell uname -r)
ifeq ($(findstring 4.1,$(OS_VER)),4.1)
OPTIMIZE_FLAG = -O
else
OPTIMIZE_FLAG = -O
endif
endif

install:
	@$(MAKE) $(MFLAGS) installhdrs installlib installbin

release:
	@$(MAKE) "DEBUG=$(OPTIMIZE_FLAG)" install
	mv lib/libcdef.a $(LIMBO_ROOT_DIR)/lib
	mv lib/libcdefzlib.a $(LIMBO_ROOT_DIR)/lib
	mv lib/libdef.a $(LIMBO_ROOT_DIR)/lib
	mv lib/libdefzlib.a $(LIMBO_ROOT_DIR)/lib

myinstall: 
	mkdir -p $(PREFIX)/include/limbo/thirdparty/lefdef/5.8/def/include
	cp $(wildcard include/*.h) $(PREFIX)/include/limbo/thirdparty/lefdef/5.8/def/include
	cp $(wildcard include/*.hpp) $(PREFIX)/include/limbo/thirdparty/lefdef/5.8/def/include
	cp $(LIMBO_ROOT_DIR)/lib/libcdef.a $(PREFIX)/lib
	cp $(LIMBO_ROOT_DIR)/lib/libcdefzlib.a $(PREFIX)/lib
	cp $(LIMBO_ROOT_DIR)/lib/libdef.a $(PREFIX)/lib
	cp $(LIMBO_ROOT_DIR)/lib/libdefzlib.a $(PREFIX)/lib

test:
	@$(MAKE) "BUILD_ORDER=TEST" dotest

.PHONY: clean
clean:
	@$(MAKE) "BUILD_ORDER += TEST" doclean;
	echo $(BUILD_ORDER);
	@$(MAKE) doclean;

.DEFAULT:
	@for i in $(BUILD_ORDER) ;do \
		echo $(MAKE) $@ in $$i ; \
		cd $$i ; \
		$(MAKE) $(MFLAGS) $@ || exit ; \
		cd .. ; \
	done

.DELETE_ON_ERROR:
