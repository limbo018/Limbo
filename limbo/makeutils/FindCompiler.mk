#########################################################################
# File Name: FindCompiler.mk
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Wed 18 Jan 2017 12:55:16 PM CST
#########################################################################

## find compiler under various platform, determine CXX, CC, FC, AR 

# detect platform
UNAME_S = $(shell uname -s)

# ==== search compilers under Linux
ifeq ($(UNAME_S), Linux)
#FOUNDCC = $(shell find ${PATH//:/ } -maxdepth 1 -executable -name gcc* -exec basename {} \;)

include $(LIMBO_ROOT_DIR)/limbo/makeutils/FindGcc.mk
include $(LIMBO_ROOT_DIR)/limbo/makeutils/FindGxx.mk
include $(LIMBO_ROOT_DIR)/limbo/makeutils/FindGfortran.mk
include $(LIMBO_ROOT_DIR)/limbo/makeutils/FindAR.mk

endif 

# ==== search for compilers under Darwin
ifeq ($(UNAME_S), Darwin)

include $(LIMBO_ROOT_DIR)/limbo/makeutils/FindClang.mk
include $(LIMBO_ROOT_DIR)/limbo/makeutils/FindClangxx.mk
include $(LIMBO_ROOT_DIR)/limbo/makeutils/FindGfortran.mk
include $(LIMBO_ROOT_DIR)/limbo/makeutils/FindAR.mk

endif 

$(info Compilers: CC = $(CC), CXX = $(CXX), FC = $(FC), AR = $(AR))
