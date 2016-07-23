# ==========================================================================
# general file for inclusion in sub-makefiles 
# make sure required variables are already set before including this file 

# ==========================================================================
#                         Compilation Platform
# ==========================================================================

# detect platform
# determine linking flags 
UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LINK_FLAG = -static # overall linking flag, maybe changed later 
	STATIC_LINK_FLAG = -Wl,-Bstatic # ld under Linux has fine control 
	DYNAMIC_LINK_FLAG = -Wl,-Bdynamic # ld under Linux has fine control 
endif 
ifeq ($(UNAME_S), Darwin)
	LINK_FLAG = # overall linking flag, set to empty
	STATIC_LINK_FLAG = # dummy flags for linker
	DYNAMIC_LINK_FLAG = # dummy flags for linker
endif 

# ==========================================================================
#                                Compilers
# ==========================================================================

# ==== search compilers under Linux
ifeq ($(UNAME_S), Linux)
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
endif 
# ==== search for compilers under Darwin
ifeq ($(UNAME_S), Darwin)
ifneq ($(shell which clang++),)
	CXX = clang++
	CC = clang
	AR = ar
else
	CXX = g++ 
	CC = gcc
	AR = ar
endif
endif 

# ==========================================================================
#                                Compilation Flags
# ==========================================================================

ifneq ($(findstring clang, $(CXX)), ) # CXX contains clang 
	include $(LIMBO_ROOT_DIR)/Makefile.clang 
else 
	include $(LIMBO_ROOT_DIR)/Makefile.gcc
endif 

# ==========================================================================
#                                 Lex/Yacc
# ==========================================================================

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

