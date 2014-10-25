# $Id$
# plain simple Makefile to build test

CXX = g++
CXXFLAGS = -W -Wall -Wextra -ansi -g #-DDEBUG_DEFPARSER
LDFLAGS = 

INCLUDE = -I$(LIBRARIES_DIR)/boost_1_55_0

HEADERS = DefParser.h ErrorHandler.h

all: test

# Implicit rule to compile c++ files

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

test: test.o 
	$(CXX) $(LDFLAGS) -o $@ test.o

clean:
	rm -f test *.o 
