#==========================================================================
#                    Configuration under darwin environment
# ==========================================================================

# detect compiler 
ifneq ($(shell which clang++),)
	CXX = clang++
	CC = clang
	AR = ar
else
	CXX = g++
	CC = gcc
	AR = ar
endif

CXXFLAGS_BASIC = -ferror-limit=1 -W -Wall -Wextra -Wreturn-type -m64 -Wno-deprecated -stdlib=libstdc++ -Wno-unused-parameter -Wno-unused-local-typedef
CXXFLAGS_DEBUG = -g -DDEBUG $(CXXFLAGS_BASIC) 
CXXFLAGS_RELEASE = -O3 $(CXXFLAGS_BASIC) 

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
