# $Id$
# plain simple Makefile to build test

CXX = g++
LEX = flex
YACC = bison

CXXFLAGS = -W -Wall -Wextra -ansi -g #-DDEBUG_EBEAMPARSER
LDFLAGS = 

INCLUDE = #-I$(LIBRARIES_DIR)/boost_1_55_0

HEADERS = EbeamDriver.h EbeamParser.h EbeamScanner.h EbeamDataBase.h \
    y.tab.h FlexLexer.h location.hh position.hh stack.hh

all: test libebeamparser

# Generate scanner and parser

EbeamParser.cc: EbeamParser.yy
	$(YACC) -o EbeamParser.cc --defines=EbeamParser.h EbeamParser.yy

EbeamScanner.cc: EbeamScanner.ll
	$(LEX) -o EbeamScanner.cc EbeamScanner.ll

# Implicit rule to compile c++ files

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

test: test.o EbeamParser.o EbeamScanner.o EbeamDriver.o
	$(CXX) $(LDFLAGS) -o $@ test.o EbeamParser.o EbeamScanner.o EbeamDriver.o

libebeamparser: EbeamParser.o EbeamScanner.o EbeamDriver.o 
	ar rvs libebeamparser.a EbeamParser.o EbeamScanner.o EbeamDriver.o 

clean:
	rm -f test *.o 

extraclean: clean
	rm -f EbeamParser.cc EbeamParser.h EbeamScanner.cc *.a
