# $Id$
# plain simple Makefile to build test

CXX = g++

LIMBO_ROOT_DIR = $(realpath ../../..)
TEST_DIR = $(realpath ../test)
VPATH = . $(TEST_DIR)

CXXFLAGS = -W -Wall -Wextra -Wreturn-type -ansi -pthread -fmax-errors=1 -DDEBUG_LPCOLORING -DASSERT_LPCOLORING -DDEBUG_ODDCYCLE -g #-O2 
LDFLAGS =

# internal dependency is lp parser 
# external dependency is boost and lemon 
INCLUDE = -I $(LIMBO_ROOT_DIR) \
		  -I $(BOOST_DIR)/include \
		  -I $(GUROBI_HOME)/include \
		  -I $(LIBRARIES_DIR)/boost_1_55_0
LINK = -L $(GUROBI_HOME)/lib -lgurobi_c++ -lgurobi60 -lrt -lboost_graph

all: $(TEST_DIR)/test_ChromaticNumber $(TEST_DIR)/test_LPColoring

# Implicit rule to compile c++ files

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

$(TEST_DIR)/test_ChromaticNumber: $(TEST_DIR)/test_ChromaticNumber.o 
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_ChromaticNumber.o $(LINK) 
$(TEST_DIR)/test_LPColoring: $(TEST_DIR)/test_LPColoring.o 
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_LPColoring.o $(LINK)


clean:
	rm -f $(TEST_DIR)/*.o 
	rm -f $(TEST_DIR)/test_ChromaticNumber
	rm -f $(TEST_DIR)/test_LPColoring
