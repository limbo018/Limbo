# $Id$
# plain simple Makefile to build test

CXX = g++

LIMBO_ROOT_DIR = $(realpath ../../..)
TEST_DIR = $(realpath ../test)
VPATH = . $(TEST_DIR)

# -stdlib=libstdc++ is necessary to compile under osx 10.9 
#  because there are two stl implementation under osx 10.9, libc++ and libstdc++
CXXFLAGS = -W -Wall -Wextra -Wreturn-type -ansi -pthread -fmax-errors=1 -DDEBUG_LPCOLORING -DASSERT_LPCOLORING -DDEBUG_ODDCYCLE -DDEBUG_GRAPHSIMPLIFICATION -g #-O2 
LDFLAGS = #-stdlib=libstdc++ 

# internal dependency is lp parser 
# external dependency is boost and lemon 
INCLUDE = -I $(LIMBO_ROOT_DIR) \
		  -I $(BOOST_DIR)/include \
		  -I $(GUROBI_HOME)/include \
		  -I $(LIBRARIES_DIR)/boost_1_55_0
LINK = -L $(GUROBI_HOME)/lib -lgurobi_c++ -lgurobi60 \
	   -L -Wl,rpath-link,$(BOOST_DIR)/lib -lboost_graph -lboost_unit_test_framework \
	   -lm 
#	   -lrt

all: $(TEST_DIR)/test_ChromaticNumber $(TEST_DIR)/test_LPColoring $(TEST_DIR)/test_GraphSimplification

# Implicit rule to compile c++ files

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE) 

# Link executable

$(TEST_DIR)/test_ChromaticNumber: $(TEST_DIR)/test_ChromaticNumber.o 
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_ChromaticNumber.o $(LINK) 
$(TEST_DIR)/test_LPColoring: $(TEST_DIR)/test_LPColoring.o 
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_LPColoring.o $(LDFLAGS) $(LINK)
$(TEST_DIR)/test_GraphSimplification: $(TEST_DIR)/test_GraphSimplification.o 
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_GraphSimplification.o $(LDFLAGS) $(LINK)


clean:
	rm -f $(TEST_DIR)/*.o 
	rm -f $(TEST_DIR)/test_ChromaticNumber
	rm -f $(TEST_DIR)/test_LPColoring
	rm -f $(TEST_DIR)/test_GraphSimplification
