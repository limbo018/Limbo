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

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	-include $(LIMBO_ROOT_DIR)/Unix.mk
endif 
ifeq ($(UNAME_S), Darwin)
	-include $(LIMBO_ROOT_DIR)/Darwin.mk
endif 

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
		  -I $(BOOST_DIR)/include \
		  -I $(GUROBI_HOME)/include \
		  -I $(CSDP_DIR)/include
LIBS = \
	   $(BOOST_DIR)/lib/libboost_graph.a \
	   $(BOOST_DIR)/lib/libboost_regex.a \
	   $(BOOST_DIR)/lib/libboost_unit_test_framework.a \
	   -lm \
	   -L $(GUROBI_HOME)/lib -lgurobi_c++ -lgurobi60 \
	   -L$(CSDP_DIR)/lib -lsdp \
	   -L$(OPENBLAS_DIR)/lib -lopenblas \
	   -lgfortran -lm -lrt -lpthread

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

