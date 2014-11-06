# $Id$
# plain simple Makefile to build test

CXX = g++

LIMBO_ROOT_DIR = $(realpath ../../..)
TEST_DIR = $(realpath ./test)
VPATH = . $(TEST_DIR)

CXXFLAGS = -W -Wall -Wextra -ansi -pthread -g -DDEBUG
LDFLAGS = 

# internal dependency is lp parser 
# external dependency is boost and lemon 
INCLUDE = -I $(LIMBO_ROOT_DIR) \
		  -I $(LIBRARIES_DIR)/boost_1_55_0 \
		  -I $(LIBRARIES_DIR)/lemon/include

HEADERS = Lgf.h LpDualMcf.h

all: $(TEST_DIR)/test

# Implicit rule to compile c++ files

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

$(TEST_DIR)/test: $(TEST_DIR)/test.o 
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test.o \
		-L $(LIBRARIES_DIR)/lemon/lib -lemon \
		-L $(LIMBO_ROOT_DIR)/lib -llpparser

clean:
	rm -f $(TEST_DIR)/test $(TEST_DIR)/*.o 
