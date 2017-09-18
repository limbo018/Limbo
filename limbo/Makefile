#==========================================================================
#                         Directories and names 
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ..)

#==========================================================================
#                         Compilation Flags
# ==========================================================================

# include environmental configurations 
include $(LIMBO_ROOT_DIR)/Include.mk

# ==========================================================================
#                         Standard Setting
# ==========================================================================

all: parsers thirdparty
.PHONY: parsers thirdparty

geometry:
	$(MAKE) -C geometry

parsers: thirdparty
	$(MAKE) -C parsers

programoptions:
	$(MAKE) -C programoptions

thirdparty:
	$(MAKE) -C thirdparty

.PHONY: install
install:
	$(MAKE) install -C parsers
	$(MAKE) install -C thirdparty
	
.PHONY: clean
clean:
	$(MAKE) clean -C parsers
	$(MAKE) clean -C thirdparty

.PHONY: extraclean
extraclean:
	$(MAKE) extraclean -C parsers
	$(MAKE) extraclean -C thirdparty
