# $Id$
# plain simple Makefile to build test

CXX = g++

PARSER_PREFIX = Lef
DEBUG_PREFIX = $(shell echo $(PARSER_PREFIX) | tr a-z A-Z) # lower case to upper case 
LIMBO_ROOT_DIR = $(realpath ../../../..)
TEST_DIR = $(realpath ../test)

CXXFLAGS = -W -Wall -Wextra -ansi -g -fmax-errors=1 #-DDEBUG_$(DEBUG_PREFIX)PARSER
LDFLAGS = 

INCLUDE = -I $(LIMBO_ROOT_DIR) \
		  -I $(LIBRARIES_DIR)/boost_1_55_0

HEADERS = $(PARSER_PREFIX)Parser.h ErrorHandler.h

all: $(TEST_DIR)/test_spirit

# Implicit rule to compile c++ files

$(TEST_DIR)/test_spirit.o: $(TEST_DIR)/test_spirit.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

$(TEST_DIR)/test_spirit: $(TEST_DIR)/test_spirit.o 
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_spirit.o

clean:
	rm -f $(TEST_DIR)/test_spirit $(TEST_DIR)/*.o 
