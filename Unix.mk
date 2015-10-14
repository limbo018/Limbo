#==========================================================================
#                    Configuration under unix environment
# ==========================================================================

# detect compiler 
ifneq ($(shell which g++48),)
	CXX = g++48
	CC = gcc48
	AR = ar
else
ifneq ($(shell which g++47),)
	CXX = g++47
	CC = gcc47
	AR = ar
else 
ifneq ($(shell which g++44),)
	CXX = g++44
	CC = gcc44
	AR = ar
else
	CXX = g++
	CC = gcc
	AR = ar
endif
endif
endif

CXXFLAGS_BASIC = -fmax-errors=1 -W -Wall -Wextra -Wreturn-type -ansi -m64 -Wno-deprecated -Wno-unused-local-typedefs
CXXFLAGS_DEBUG = -g $(CXXFLAGS_BASIC) 
CXXFLAGS_RELEASE = -O3 -fopenmp $(CXXFLAGS_BASIC) 

ARFLAGS = rvs

LEX = flex
YACC = bison
