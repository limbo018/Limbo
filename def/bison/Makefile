# $Id$
# plain simple Makefile to build test

CXX = g++
LEX = flex
YACC = bison

CXXFLAGS = -W -Wall -Wextra -ansi -g #-DDEBUG_DEFPARSER
LDFLAGS = 

INCLUDE = #-I$(LIBRARIES_DIR)/boost_1_55_0

HEADERS = DefDriver.h DefParser.h DefScanner.h DefDataBase.h \
    y.tab.h FlexLexer.h location.hh position.hh stack.hh

all: test libdefparser

# Generate scanner and parser

DefParser.cc: DefParser.yy
	$(YACC) -o DefParser.cc --defines=DefParser.h DefParser.yy

DefScanner.cc: DefScanner.ll
	$(LEX) -o DefScanner.cc DefScanner.ll

# Implicit rule to compile c++ files

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

test: test.o DefParser.o DefScanner.o DefDriver.o
	$(CXX) $(LDFLAGS) -o $@ test.o DefParser.o DefScanner.o DefDriver.o

libdefparser: DefParser.o DefScanner.o DefDriver.o 
	ar rvs libdefparser.a DefParser.o DefScanner.o DefDriver.o 

clean:
	rm -f test *.o 

extraclean: clean
	rm -f DefParser.cc DefParser.h DefScanner.cc *.a
