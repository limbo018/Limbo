# $Id$
# plain simple Makefile to build test

#==========================================================================
#                         Directories and names 
# ==========================================================================

PARSER_PREFIX = Gds
LIB_PREFIX = gds
DEBUG_PREFIX = $(shell echo $(PARSER_PREFIX) | tr a-z A-Z) # lower case to upper case 
LIMBO_ROOT_DIR = $(realpath ../../../..)
TEST_DIR = $(realpath ../test)
OBJDIR = $(LIMBO_ROOT_DIR)/obj
MKDIR = if [ ! -d $(@D) ]; then mkdir -p $(@D); fi

VPATH = . $(TEST_DIR)

#==========================================================================
#                         Compilation Flags
# ==========================================================================

# default DBG is off
DBG = 0

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	-include $(LIMBO_ROOT_DIR)/Unix.mk
endif 
ifeq ($(UNAME_S), Darwin)
	-include $(LIMBO_ROOT_DIR)/Darwin.mk
endif 

ifeq ($(DBG), 1)
	CXXFLAGS = $(CXXFLAGS_DEBUG) -DDEBUG_GDSREADER -DDEBUG_GDSWRITER
else
	CXXFLAGS = $(CXXFLAGS_RELEASE)
endif

#==========================================================================
#                         Special Library
# ==========================================================================

INCLUDE = -I $(LIMBO_ROOT_DIR) 

# ==========================================================================
#                         Standard Setting
# ==========================================================================

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
DEPS = $(OBJS:%.o=%.d) 	# one dependency file for each source

SRCS_TEST = $(wildcard $(TEST_DIR)/*.cpp)
OBJS_TEST = $(patsubst $(TEST_DIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS_TEST))
DEPS_TEST = $(OBJS_TEST:%.o=%.d)

all: lib$(LIB_PREFIX)parser $(TEST_DIR)/test_reader 
	#$(TEST_DIR)/test_writer $(TEST_DIR)/test_driver

# Compile dependency 

$(OBJDIR)/%.d: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $< -MM -MT $(@:%.d=%.o) >$@ $(INCLUDE)

-include $(DEPS)

# Implicit rule to compile c++ files

$(OBJDIR)/%.o: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

$(TEST_DIR)/test_reader: lib$(LIB_PREFIX)parser $(TEST_DIR)/test_reader.o
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_DIR)/test_reader.o $(LIMBO_ROOT_DIR)/lib/lib$(LIB_PREFIX)parser.a

$(TEST_DIR)/test_writer: lib$(LIB_PREFIX)parser $(TEST_DIR)/test_writer.o
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_DIR)/test_writer.o $(LIMBO_ROOT_DIR)/lib/lib$(LIB_PREFIX)parser.a

$(TEST_DIR)/test_driver: lib$(LIB_PREFIX)parser $(TEST_DIR)/test_driver.o
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_driver.o $(LIMBO_ROOT_DIR)/lib/lib$(LIB_PREFIX)parser.a

lib$(LIB_PREFIX)parser: $(OBJS)
	$(AR) $(ARFLAGS) lib$(LIB_PREFIX)parser.a $(OBJS)
	mv lib$(LIB_PREFIX)parser.a $(LIMBO_ROOT_DIR)/lib

install: lib$(LIB_PREFIX)parser
	rm -f *.o

.PHONY: clean
clean: cleandep
	rm -f $(TEST_DIR)/test_reader $(TEST_DIR)/test_writer $(TEST_DIR)/test_driver $(OBJS) $(OBJS_TEST)

.PHONY: cleandep
cleandep:
	rm -f $(DEPS) $(DEPS_TEST)

.PHONY: extraclean
extraclean: clean
	rm -f $(LIMBO_ROOT_DIR)/lib/lib$(LIB_PREFIX)parser.a
