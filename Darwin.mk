#==========================================================================
#                    Configuration under darwin environment
# ==========================================================================

# detect compiler 
ifneq ($(shell which clang++),)
	CXX = clang++
	AR = ar
else
	CXX = g++
	AR = ar
endif

CXXFLAGS_BASIC = -ferror-limit=1 -W -Wall -Wextra -Wreturn-type -m64 -Wno-deprecated -stdlib=libstdc++ -Wno-unused-parameter
CXXFLAGS_DEBUG = -g -DDEBUG $(CXXFLAGS_BASIC) 
CXXFLAGS_RELEASE = -O3 $(CXXFLAGS_BASIC) 

ARFLAGS = rvs

LEX = flex
YACC = bison
