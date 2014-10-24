# $Id$
# plain simple Makefile to build test

CXX = g++
CXXFLAGS = -W -Wall -Wextra -ansi -g #-DDEBUG_GDSREADER

INCLUDE = #-I$(LIBRARIES_DIR)/boost_1_55_0

HEADERS = GdsReader.h GdsWriter.h

all: test_reader test_writer libgdsparser

# Implicit rule to compile c++ files

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

test_reader: test_reader.o GdsReader.o 
	$(CXX) $(LDFLAGS) -o $@ test_reader.o GdsReader.o 

test_writer: test_writer.o GdsWriter.o
	$(CXX) $(LDFLAGS) -o $@ test_writer.o GdsWriter.o

libgdsparser: GdsReader.o GdsWriter.o
	ar rvs libgdsparser.a GdsReader.o GdsWriter.o

clean:
	rm -f test_reader test_writer *.o 

extraclean: clean
	rm -f *.a
