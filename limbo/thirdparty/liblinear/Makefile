#==========================================================================
#                         Directories and names 
# ==========================================================================

#CXX ?= g++
#CC ?= gcc
#LIBS = blas/blas.a
SHVER = 3
OS = $(shell uname)

LIMBO_ROOT_DIR = $(realpath ../../..)
LIBDIR = $(LIMBO_ROOT_DIR)/lib

#==========================================================================
#                         Compilation Flags
# ==========================================================================

DBG = 0

# include environmental configurations 
include $(LIMBO_ROOT_DIR)/Include.mk

ifeq ($(DBG), 1)
	CXXFLAGS = $(CXXFLAGS_DEBUG) -Wconversion 
	CFLAGS = $(CFLAGS_DEBUG) -Wconversion 
else
	CXXFLAGS = $(CXXFLAGS_RELEASE) -Wconversion 
	CFLAGS = $(CFLAGS_RELEASE) -Wconversion
endif

#LIBS = -lblas
LIBS = $(LINK_FLAG) -L$(LIMBO_ROOT_DIR)/lib -lopenblas-st
ifeq ($(UNAME_S), Linux)
	LIBS += -lrt -lgfortran
endif 

# ==========================================================================
#                         Standard Setting
# ==========================================================================

all: train predict static_lib

lib: linear.o tron.o blas/blas.a
	if [ "$(OS)" = "Darwin" ]; then \
		SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,liblinear.so.$(SHVER)"; \
	else \
		SHARED_LIB_FLAG="-shared -Wl,-soname,liblinear.so.$(SHVER)"; \
	fi; \
	$(CXX) $${SHARED_LIB_FLAG} linear.o tron.o blas/blas.a -o liblinear.so.$(SHVER)

static_lib: linear.o tron.o blas/blas.a
	$(AR) $(ARFLAGS) liblinear.a linear.o tron.o

train: tron.o linear.o train.c blas/blas.a
	$(CXX) $(CXXFLAGS) -o train train.c tron.o linear.o $(LIBS)

predict: tron.o linear.o predict.c blas/blas.a
	$(CXX) $(CXXFLAGS) -o predict predict.c tron.o linear.o $(LIBS)

tron.o: tron.cpp tron.h
	$(CXX) $(CXXFLAGS) -c -o tron.o tron.cpp

linear.o: linear.cpp linear.h
	$(CXX) $(CXXFLAGS) -c -o linear.o linear.cpp

blas/blas.a: blas/*.c blas/*.h
	make -C blas OPTFLAGS='$(CFLAGS)' CC='$(CC)';

.PHONY: install 
install: 
	cmp -s $(PREFIX)/lib/liblinear.a $(LIBDIR)/liblinear.a; \
	RETVAL=$$?; \
	if [ $$RETVAL -ne 0 ]; then \
		mkdir -p $(PREFIX)/lib; \
		cp $(LIBDIR)/liblinear.* $(PREFIX)/lib; \
		mkdir -p $(PREFIX)/bin; \
		cp $(LIMBO_ROOT_DIR)/bin/liblinear-* $(PREFIX)/bin; \
	fi
	mkdir -p $(PREFIX)/include/limbo/thirdparty/liblinear
	cp $(wildcard *.h) $(PREFIX)/include/limbo/thirdparty/liblinear

clean:
	make -C blas clean
	make -C matlab clean
	rm -f *~ tron.o linear.o train predict liblinear.so.$(SHVER)
