# $Id$
# plain simple Makefile to build test

#==========================================================================
#                         Directories and names 
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ../../..)
TEST_DIR = $(realpath ../test)
OBJDIR = $(LIMBO_ROOT_DIR)/obj
MKDIR = if [ ! -d $(@D) ]; then mkdir -p $(@D); fi

VPATH = . $(TEST_DIR)

#==========================================================================
#                         Compilation Flags
# ==========================================================================

# default DBG is off
DBG = 0

# include environmental configurations 
include $(LIMBO_ROOT_DIR)/Include.mk

ifeq ($(DBG), 1)
	CXXFLAGS = $(CXXFLAGS_DEBUG) -DDEBUG_LPCOLORING -DASSERT_LPCOLORING -DDEBUG_GRAPHSIMPLIFICATION -DDEBUG_ILPCOLORING -DDEBUG_SDPCOLORING
else
	CXXFLAGS = $(CXXFLAGS_RELEASE)
endif

# moved to SDPColoringCsdp.h
#CXXFLAGS += -DNOSHORTS

#==========================================================================
#                         Special Library
# ==========================================================================

# internal dependency is lp parser 
# external dependency is boost
INCLUDE = -I $(LIMBO_ROOT_DIR) \
		  -I $(BOOST_DIR)/include 
LIBS = \
	   $(BOOST_DIR)/lib/libboost_graph.a \
	   $(BOOST_DIR)/lib/libboost_regex.a \
	   $(BOOST_DIR)/lib/libboost_unit_test_framework.a \
	   -lm

# ==== boost chrono links to to librt.a under Linux
ifeq ($(UNAME_S), Linux)
LIBS += $(STATIC_LINK_FLAG) -lrt 
endif 

# ==== GUROBI 
INCLUDE += -I $(GUROBI_HOME)/include
LIBS += -L $(GUROBI_HOME)/lib \
		$(STATIC_LINK_FLAG) -lgurobi_c++ \
		$(DYNAMIC_LINK_FLAG) -lgurobi60 \
		$(DYNAMIC_LINK_FLAG) -lpthread 
# ==== Csdp api (OpenBLAS and Fortran library are necessary)
# it looks like pthead must be linked dynamically when GUROBI is also on 
LIBS += -L $(LIMBO_DIR)/lib $(STATIC_LINK_FLAG) -lsdp \
	   -L $(LIMBO_DIR)/lib $(STATIC_LINK_FLAG) -lopenblas-st -lm 
# ==== Csdp links to Fortran under Linux 
ifeq ($(UNAME_S), Linux)
LIBS += -lgfortran 
endif

# ==========================================================================
#                         Standard Setting
# ==========================================================================

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
DEPS = $(OBJS:%.o=%.d) 	# one dependency file for each source

SRCS_TEST = $(wildcard $(TEST_DIR)/*.cpp)
OBJS_TEST = $(patsubst $(TEST_DIR)/%.cpp,$(TEST_DIR)/%.o,$(SRCS_TEST))
DEPS_TEST = $(OBJS_TEST:%.o=%.d)

all: $(TEST_DIR)/test_ChromaticNumber $(TEST_DIR)/test_LPColoring $(TEST_DIR)/test_GraphSimplification $(TEST_DIR)/test_ILPColoring  $(TEST_DIR)/test_SDPColoring

# Compile dependency 

$(OBJDIR)/%.d: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $< -MM -MT $(@:%.d=%.o) >$@ $(INCLUDE)
$(TEST_DIR)/%.d: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $< -MM -MT $(@:%.d=%.o) >$@ $(INCLUDE)

-include $(DEPS)
-include $(DEPS_TEST)

# Implicit rule to compile c++ files

$(OBJDIR)/%.o: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)
$(TEST_DIR)/%.o: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

$(TEST_DIR)/test_ChromaticNumber: $(TEST_DIR)/test_ChromaticNumber.o 
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_DIR)/test_ChromaticNumber.o $(LIBS) 
$(TEST_DIR)/test_LPColoring: $(TEST_DIR)/test_LPColoring.o 
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_DIR)/test_LPColoring.o $(CXXFLAGS) $(LIBS)
$(TEST_DIR)/test_GraphSimplification: $(TEST_DIR)/test_GraphSimplification.o 
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_DIR)/test_GraphSimplification.o $(CXXFLAGS) $(LIBS)
$(TEST_DIR)/test_ILPColoring: $(TEST_DIR)/test_ILPColoring.o 
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_DIR)/test_ILPColoring.o $(CXXFLAGS) $(LIBS)
$(TEST_DIR)/test_SDPColoring: $(TEST_DIR)/test_SDPColoring.o 
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_DIR)/test_SDPColoring.o $(CXXFLAGS) $(LIBS)

.PHONY: clean
clean: cleandep
	rm -f $(TEST_DIR)/test_ChromaticNumber $(TEST_DIR)/test_LPColoring $(TEST_DIR)/test_GraphSimplification $(TEST_DIR)/test_ILPColoring $(TEST_DIR)/test_SDPColoring $(OBJS) $(OBJS_TEST)

.PHONY: cleandep
cleandep:
	rm -f $(DEPS) $(DEPS_TEST)

