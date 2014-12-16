# $Id$
# plain simple Makefile to build test

#CXX = /usr/local/bin/g++-4.9
CXX = g++
LEX = flex
YACC = bison

PARSER_PREFIX = Lef
LIB_PREFIX = lef
DEBUG_PREFIX = $(shell echo $(PARSER_PREFIX) | tr a-z A-Z) # lower case to upper case 
LIMBO_ROOT_DIR = $(realpath ../../../..)
TEST_DIR = $(realpath ../test)

#CXXFLAGS = -W -Wall -Wextra -ansi -O2 -fmax-errors=5 #-g #-DDEBUG_$(DEBUG_PREFIX)PARSER
CXXFLAGS = -W -Wall -Wextra -Wuninitialized -ansi -fmax-errors=1 -g #-DDEBUG_$(DEBUG_PREFIX)PARSER
LDFLAGS = 

INCLUDE = -I . -I $(LIMBO_ROOT_DIR) #-I$(LIBRARIES_DIR)/boost_1_55_0

#HEADERS = $(PARSER_PREFIX)Driver.h $(PARSER_PREFIX)Parser.h $(PARSER_PREFIX)Scanner.h $(PARSER_PREFIX)DataBase.h \
    y.tab.h FlexLexer.h location.hh position.hh stack.hh
HEADERS = $(wildcard *.hpp) \
		  $(PARSER_PREFIX)Driver.h $(PARSER_PREFIX)Parser.h $(PARSER_PREFIX)Scanner.h $(PARSER_PREFIX)DataBase.h \
		  y.tab.h FlexLexer.h location.hh position.hh stack.hh
SRCS = $(wildcard lef*.cc)  $(PARSER_PREFIX)Driver.cc $(PARSER_PREFIX)Parser.cc $(PARSER_PREFIX)Scanner.cc $(PARSER_PREFIX)DataBase.cc
OBJS = $(patsubst %.cc, %.o, $(SRCS))

all: $(PARSER_PREFIX)Scanner.cc $(PARSER_PREFIX)Parser.cc lib$(LIB_PREFIX)parser $(TEST_DIR)/test_bison

# Generate scanner and parser

$(PARSER_PREFIX)Parser.cc: $(PARSER_PREFIX)Parser.yy
	$(YACC) -o $(PARSER_PREFIX)Parser.cc --defines=$(PARSER_PREFIX)Parser.h $(PARSER_PREFIX)Parser.yy

$(PARSER_PREFIX)Scanner.cc: $(PARSER_PREFIX)Scanner.ll
	$(LEX) -o $(PARSER_PREFIX)Scanner.cc $(PARSER_PREFIX)Scanner.ll

# Implicit rule to compile c++ files

%.o: %.cc 
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE) 

$(TEST_DIR)/test_bison.o: $(TEST_DIR)/test_bison.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE) 

# Link executable

$(TEST_DIR)/test_bison: $(TEST_DIR)/test_bison.o lib$(LIB_PREFIX)parser
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_bison.o -L $(LIMBO_ROOT_DIR)/lib -l$(LIB_PREFIX)parser 

#lib$(LIB_PREFIX)parser: $(PARSER_PREFIX)Parser.o $(PARSER_PREFIX)Scanner.o $(PARSER_PREFIX)Driver.o 
lib$(LIB_PREFIX)parser: $(OBJS)
	ar rvs lib$(LIB_PREFIX)parser.a $(OBJS)
	mv lib$(LIB_PREFIX)parser.a $(LIMBO_ROOT_DIR)/lib

install: lib$(LIB_PREFIX)parser
	rm -f $(PARSER_PREFIX)Parser.cc $(PARSER_PREFIX)Parser.h $(PARSER_PREFIX)Scanner.cc 
	rm -f *.o $(TEST_DIR)/*.o

clean:
	rm -f $(TEST_DIR)/test_bison *.o $(TEST_DIR)/*.o

extraclean: clean
	rm -f $(PARSER_PREFIX)Parser.cc $(PARSER_PREFIX)Parser.h $(PARSER_PREFIX)Scanner.cc 
	rm -f *.a $(LIMBO_ROOT_DIR)/lib/lib$(LIB_PREFIX)parser.a
	rm -f location.hh position.hh stack.hh
