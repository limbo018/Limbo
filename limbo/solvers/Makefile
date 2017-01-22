#==========================================================================
#                         Directories and names 
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ../..)

#==========================================================================
#                         Compilation Flags
# ==========================================================================

# include environmental configurations 
include $(LIMBO_ROOT_DIR)/Include.mk

# ==========================================================================
#                         Standard Setting
# ==========================================================================

.PHONY: install
install:
	mkdir -p $(PREFIX)/include/limbo/solvers/api
	cp $(wildcard api/*.h) $(PREFIX)/include/limbo/solvers/api
	mkdir -p $(PREFIX)/include/limbo/solvers/lpmcf
	cp $(wildcard lpmcf/*.h) $(PREFIX)/include/limbo/solvers/lpmcf
