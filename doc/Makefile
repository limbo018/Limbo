#==========================================================================
#                         Directories and names 
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ..)
#SRCSDIR = $(LIMBO_ROOT_DIR)/limbo
SRCSDIR = $(LIMBO_ROOT_DIR)/Readme.md
DOCDIR = $(LIMBO_ROOT_DIR)/doc


#==========================================================================
#                         Compilation Flags
# ==========================================================================

# include environmental configurations 
include $(LIMBO_ROOT_DIR)/Include.mk

# ==========================================================================
#                         Standard Setting
# ==========================================================================

all: doc

Doxyfile: $(DOCDIR)/Doxyfile.in $(DOCDIR)/Makefile
	echo INPUT                  = $(SRCSDIR) > $(DOCDIR)/Doxyfile
	echo OUTPUT_DIRECTORY       = $(DOCDIR) >> $(DOCDIR)/Doxyfile
	echo FILE_PATTERNS          = *.c *.cc *.cpp *.md >> $(DOCDIR)/Doxyfile
	echo INCLUDE_FILE_PATTERNS  = *.h *.hpp >> $(DOCDIR)/Doxyfile

doc: Doxyfile $(SRCS)
	$(DOXYGEN) $(DOCDIR)/Doxyfile.in

.PHONY: install
install: 
	mkdir -p $(PREFIX)/doc
	cp -r $(DOCDIR)/html $(PREFIX)/doc
	#cp -r $(DOCDIR)/latex $(PREFIX)/doc

.PHONY: clean
clean: 
	rm -rf $(DOCDIR)/html
	rm -rf $(DOCDIR)/latex
	rm -f $(DOCDIR)/Doxyfile

.PHONY: extraclean
extraclean: clean
