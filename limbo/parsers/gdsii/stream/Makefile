# $Id$
# plain simple Makefile to build test

CXX = g++

PARSER_PREFIX = Gds
LIB_PREFIX = gds
DEBUG_PREFIX = $(shell echo $(PARSER_PREFIX) | tr a-z A-Z) # lower case to upper case 
LIMBO_ROOT_DIR = $(realpath ../../../..)
TEST_DIR = $(realpath ../test)

VPATH = . $(TEST_DIR)

CXXFLAGS = -W -Wall -Wextra -ansi -g #-DDEBUG_GDSREADER

INCLUDE = $(LIMBO_ROOT_DIR) #-I$(LIBRARIES_DIR)/boost_1_55_0

HEADERS = $(PARSER_PREFIX)Reader.h $(PARSER_PREFIX)Writer.h

all: lib$(LIB_PREFIX)parser $(TEST_DIR)/test_reader $(TEST_DIR)/test_writer

# Implicit rule to compile c++ files

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I $(INCLUDE)

# Link executable

$(TEST_DIR)/test_reader: $(TEST_DIR)/test_reader.o
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_reader.o -L $(LIMBO_ROOT_DIR)/lib -l$(LIB_PREFIX)parser

$(TEST_DIR)/test_writer: $(TEST_DIR)/test_writer.o 
	$(CXX) $(LDFLAGS) -o $@ $(TEST_DIR)/test_writer.o -L $(LIMBO_ROOT_DIR)/lib -l$(LIB_PREFIX)parser

lib$(LIB_PREFIX)parser: $(PARSER_PREFIX)Reader.o $(PARSER_PREFIX)Writer.o
	ar rvs lib$(LIB_PREFIX)parser.a $(PARSER_PREFIX)Reader.o $(PARSER_PREFIX)Writer.o
	mv lib$(LIB_PREFIX)parser.a $(LIMBO_ROOT_DIR)/lib

install: lib$(LIB_PREFIX)parser
	rm -f *.o

clean:
	rm -f $(TEST_DIR)/test_reader $(TEST_DIR)/test_writer *.o $(TEST_DIR)/*.o

extraclean: clean
	rm -f $(LIMBO_ROOT_DIR)/lib/lib$(LIB_PREFIX)parser.a
