#########################################################################
# File Name: GCCVersion.mk
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Sat 01 Aug 2015 01:05:15 PM CDT
#########################################################################

## calculate gcc version without . and save to GCCVERSION
empty:=
space:= $(empty) $(empty)
GCCVERSIONSTRING := $(shell expr `$(CXX) -dumpversion`)
#Create version number without "."
GCCVERSION := $(shell expr `echo $(GCCVERSIONSTRING)` | cut -f1 -d.)
GCCVERSION += $(shell expr `echo $(GCCVERSIONSTRING)` | cut -f2 -d.)
GCCVERSION += $(shell expr `echo $(GCCVERSIONSTRING)` | cut -f3 -d.)
# Make sure the version number has at least 3 decimals
GCCVERSION += 00
# Remove spaces from the version number
GCCVERSION := $(subst $(space),$(empty),$(GCCVERSION))
# Crop the version number to 3 decimals.
GCCVERSION := $(shell expr `echo $(GCCVERSION)` | cut -b1-3)
