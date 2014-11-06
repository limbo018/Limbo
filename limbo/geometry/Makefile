# $Id$
# plain simple Makefile to build test

CXX = g++

LIMBO_ROOT_DIR = $(realpath ../..)
TEST_DIR = $(realpath ./test)
VPATH = . $(TEST_DIR)

CXXFLAGS = -W -Wall -Wextra -ansi -pthread -fmax-errors=1 -g -O2 #-DDEBUG
LDFLAGS = 

# internal dependency is lp parser 
# external dependency is boost and lemon 
INCLUDE = -I $(LIMBO_ROOT_DIR) \
		  -I $(BLIB_DIR)/lib \
		  -I $(LIBRARIES_DIR)/boost_1_55_0

all: $(TEST_DIR)/test_p2r $(TEST_DIR)/test_blibapi $(TEST_DIR)/test_boostpolygonapi

# Implicit rule to compile c++ files

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

$(TEST_DIR)/test_p2r: $(TEST_DIR)/test_p2r.o 
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_p2r.o 

$(TEST_DIR)/test_blibapi: $(TEST_DIR)/test_blibapi.o
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_blibapi.o 

$(TEST_DIR)/test_boostpolygonapi: $(TEST_DIR)/test_boostpolygonapi.o
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_boostpolygonapi.o

clean:
	rm -f $(TEST_DIR)/*.o 
	rm -f $(TEST_DIR)/test_p2r
	rm -f $(TEST_DIR)/test_blibapi
	rm -f $(TEST_DIR)/test_boostpolygonapi
