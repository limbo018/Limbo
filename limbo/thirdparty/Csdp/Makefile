#
# This Makefile can be used to automatically build the entire package.  
#
# If you make changes in the "Makefile" under any subdirectory, you can
# rebuild the system with "make clean" followed by "make all".
#
#
# Generic. On most systems, this should handle everything.
#

#==========================================================================
#                         Directories and names 
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ../../..)

#==========================================================================
#                         Compilation Flags
# ==========================================================================

# include environmental configurations 
include $(LIMBO_ROOT_DIR)/Include.mk

all:
	make -C lib CC=$(CC) libsdp.a
	make -C solver CC=$(CC) csdp
	make -C theta CC=$(CC) all 
	make -C example CC=$(CC) all 

#
# Perform a unitTest
#

unitTest:
	make -C test CC=$(CC) all

#
# Install the executables in /usr/local/bin.
#

install:
	cp -f solver/csdp /usr/local/bin
	cp -f theta/theta /usr/local/bin
	cp -f theta/graphtoprob /usr/local/bin
	cp -f theta/complement /usr/local/bin
	cp -f theta/rand_graph /usr/local/bin

#
# Clean out all of the directories.
# 

clean:
	make -C lib clean 
	make -C solver clean 
	make -C theta clean 
	make -C test clean 
	make -C example clean

