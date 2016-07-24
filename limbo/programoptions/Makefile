# $Id$
# plain simple Makefile to build test

#==========================================================================
#                         Directories and names 
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ../..)
TEST_DIR = $(realpath ./test)
OBJDIR = $(LIMBO_ROOT_DIR)/obj
MKDIR = if [ ! -d $(@D) ]; then mkdir -p $(@D); fi

VPATH = . $(TEST_DIR)

#==========================================================================
#                         Compilation Flags
# ==========================================================================

# default DBG is off
DBG = 0

# include environmental configurations 
include $(LIMBO_ROOT_DIR)/Include.mk

ifeq ($(DBG), 1)
	CXXFLAGS = $(CXXFLAGS_DEBUG)
else
	CXXFLAGS = $(CXXFLAGS_RELEASE)
endif

#==========================================================================
#                         Special Library
# ==========================================================================

INCLUDE = -I $(realpath .) \
		  -I $(LIMBO_ROOT_DIR) 

# ==========================================================================
#                         Standard Setting
# ==========================================================================

SRCS = $(wildcard *.cpp) 
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
DEPS = $(OBJS:%.o=%.d) 	# one dependency file for each source

SRCS_TEST = $(wildcard $(TEST_DIR)/*.cpp)
OBJS_TEST = $(patsubst $(TEST_DIR)/%.cpp,$(TEST_DIR)/%.o,$(SRCS_TEST))
DEPS_TEST = $(OBJS_TEST:%.o=%.d)

all: libprogramoptions $(TEST_DIR)/test_ProgramOptions

# Compile dependency 

$(OBJDIR)/%.d: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $< -MM -MT $(@:%.d=%.o) >$@ $(INCLUDE)
$(TEST_DIR)/%.d: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $< -MM -MT $(@:%.d=%.o) >$@ $(INCLUDE)

-include $(DEPS)
-include $(DEPS_TEST)

# Implicit rule to compile c++ files

$(OBJDIR)/%.o: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE) 
$(TEST_DIR)/%.o: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE) 

# Link executable

$(TEST_DIR)/test_ProgramOptions: libprogramoptions $(OBJS_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_TEST) $(LIMBO_ROOT_DIR)/lib/libprogramoptions.a

libprogramoptions: $(OBJS)
	$(AR) $(ARFLAGS) libprogramoptions.a $(OBJS)
	mv libprogramoptions.a $(LIMBO_ROOT_DIR)/lib

install: libprogramoptions
	rm -f $(OBJS) $(OBJS_TEST) 

.PHONY: clean
clean: cleandep
	rm -f $(TEST_DIR)/test_ProgramOptions $(OBJS) $(OBJS_TEST)

.PHONY: cleandep
cleandep:
	rm -f $(DEPS) $(DEPS_TEST)

.PHONY: extraclean
extraclean: clean
	rm -f $(LIMBO_ROOT_DIR)/lib/libprogramoptions.a
