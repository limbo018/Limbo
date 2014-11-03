# $Id$
# plain simple Makefile to build test

CXX = g++
LEX = flex
YACC = bison

PARSER_PREFIX = Def
LIB_PREFIX = def
DEBUG_PREFIX = $(shell echo $(PARSER_PREFIX) | tr a-z A-Z) # lower case to upper case 
LIMBO_ROOT_DIR = $(realpath ../../../..)
TEST_DIR = $(realpath ../test)

CXXFLAGS = -W -Wall -Wextra -ansi -g #-DDEBUG_$(DEBUG_PREFIX)PARSER
LDFLAGS = 

INCLUDE = $(LIMBO_ROOT_DIR) #-I$(LIBRARIES_DIR)/boost_1_55_0

HEADERS = $(PARSER_PREFIX)Driver.h $(PARSER_PREFIX)Parser.h $(PARSER_PREFIX)Scanner.h $(PARSER_PREFIX)DataBase.h \
    y.tab.h FlexLexer.h location.hh position.hh stack.hh

all: lib$(LIB_PREFIX)parser $(TEST_DIR)/test_bison

# Generate scanner and parser

$(PARSER_PREFIX)Parser.cc: $(PARSER_PREFIX)Parser.yy
	$(YACC) -o $(PARSER_PREFIX)Parser.cc --defines=$(PARSER_PREFIX)Parser.h $(PARSER_PREFIX)Parser.yy

$(PARSER_PREFIX)Scanner.cc: $(PARSER_PREFIX)Scanner.ll
	$(LEX) -o $(PARSER_PREFIX)Scanner.cc $(PARSER_PREFIX)Scanner.ll

# Implicit rule to compile c++ files

$(TEST_DIR)/test_bison.o: $(TEST_DIR)/test_bison.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I $(INCLUDE) 

# Link executable

$(TEST_DIR)/test_bison: $(TEST_DIR)/test_bison.o 
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_bison.o -L $(LIMBO_ROOT_DIR)/lib -l$(LIB_PREFIX)parser 

lib$(LIB_PREFIX)parser: $(PARSER_PREFIX)Parser.o $(PARSER_PREFIX)Scanner.o $(PARSER_PREFIX)Driver.o 
	ar rvs lib$(LIB_PREFIX)parser.a $(PARSER_PREFIX)Parser.o $(PARSER_PREFIX)Scanner.o $(PARSER_PREFIX)Driver.o 
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
