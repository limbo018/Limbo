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

CXXFLAGS_BASIC = -fmax-errors=1 -fPIC -W -Wall -Wextra -Wreturn-type -ansi -m64 -Wno-deprecated -Wno-unused-local-typedefs
CXXFLAGS_DEBUG = -g $(CXXFLAGS_BASIC) 
CXXFLAGS_RELEASE = -O3 -fopenmp $(CXXFLAGS_BASIC) 

ARFLAGS = rvs

LEX = flex
YACC = bison

# detect flex version for FlexLexer.h
# a backup for version 2.5.37 is available in the library to be compatible with previous releases of limbo 
# for other versions, user need to specify FLEX_DIR environment variable 
ifneq ($(findstring 2.5.37,$(shell $(LEX) --version)),)
	LEX_INCLUDE_DIR = $(LIMBO_ROOT_DIR)/limbo/thirdparty/flex/2.5.37
else 
# LEX_INCLUDE_DIR is not set as environment variable, so that user has more flexibility to set either FLEX_DIR or LEX_INCLUDE_DIR 
ifeq ($(LEX_INCLUDE_DIR),) 
	LEX_INCLUDE_DIR = $(FLEX_DIR)/include # the path to FlexLexer.h 
endif 
endif 
