#==========================================================================
#                         Directories and names 
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ..)
DOCDIR = $(LIMBO_ROOT_DIR)/doc
#SRCSDIR = $(LIMBO_ROOT_DIR)/limbo
SRCSDIR = $(LIMBO_ROOT_DIR)/Readme.md \
		  $(DOCDIR)/algorithms \
		  $(DOCDIR)/bibtex \
		  $(DOCDIR)/containers \
		  $(DOCDIR)/geometry \
		  $(DOCDIR)/makeutils \
		  $(DOCDIR)/math \
		  $(DOCDIR)/parsers \
		  $(DOCDIR)/preprocessor \
		  $(DOCDIR)/programoptions \
		  $(DOCDIR)/solvers \
		  $(DOCDIR)/string \
		  $(DOCDIR)/thirdparty \
		  $(wildcard $(LIMBO_ROOT_DIR)/limbo/bibtex/*.py) \
		  $(wildcard $(LIMBO_ROOT_DIR)/limbo/containers/*.h) \
		  $(wildcard $(LIMBO_ROOT_DIR)/limbo/makeutils/*.mk) \
		  $(wildcard $(LIMBO_ROOT_DIR)/limbo/math/*.h) \
		  $(wildcard $(LIMBO_ROOT_DIR)/test/geometry/*.cpp) \
		  $(wildcard $(LIMBO_ROOT_DIR)/limbo/geometry/*.h) \
		  $(wildcard $(LIMBO_ROOT_DIR)/limbo/geometry/api/*.h) \
		  $(wildcard $(LIMBO_ROOT_DIR)/limbo/preprocessor/*.h) \
		  $(wildcard $(LIMBO_ROOT_DIR)/test/programoptions/*.cpp) \
		  $(wildcard $(LIMBO_ROOT_DIR)/limbo/programoptions/*.h) \
		  $(wildcard $(LIMBO_ROOT_DIR)/test/string/*.cpp) \
		  $(wildcard $(LIMBO_ROOT_DIR)/limbo/string/*.h) 


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
	echo INCLUDE_PATH           = $(LIMBO_ROOT_DIR) > $(DOCDIR)/Doxyfile
	echo EXAMPLE_PATH           = $(LIMBO_ROOT_DIR) >> $(DOCDIR)/Doxyfile
	echo IMAGE_PATH             = $(LIMBO_ROOT_DIR)/doc/geometry >> $(DOCDIR)/Doxyfile
	echo INPUT                  = $(SRCSDIR) >> $(DOCDIR)/Doxyfile
	echo OUTPUT_DIRECTORY       = $(DOCDIR) >> $(DOCDIR)/Doxyfile
	echo FILE_PATTERNS          = *.c *.cc *.cpp *.md *.py *.mk >> $(DOCDIR)/Doxyfile
	echo INCLUDE_FILE_PATTERNS  = *.h *.hpp >> $(DOCDIR)/Doxyfile
	echo ALIASES               += nowarn=\"\\{\" endnowarn=\"\\}\" >> $(DOCDIR)/Doxyfile
	echo FILTER_PATTERNS = *.mk=$(LIMBO_ROOT_DIR)/doc/MKFilter.sh >> $(DOCDIR)/Doxyfile

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
	#rm -rf $(DOCDIR)/latex
	rm -f $(DOCDIR)/Doxyfile

.PHONY: extraclean
extraclean: clean
