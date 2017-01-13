#==========================================================================
#                         Directories and names 
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ../..)
TEST_DIR = $(realpath .)
OBJDIR = $(TEST_DIR)/obj
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
	CXXFLAGS = $(CXXFLAGS_DEBUG) -DDEBUG_LPCOLORING -DASSERT_LPCOLORING -DDEBUG_GRAPHSIMPLIFICATION -DDEBUG_ILPCOLORING -DDEBUG_SDPCOLORING -DDEBUG_FM
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
LIBS = -L $(BOOST_DIR)/lib -lboost_graph -lboost_regex -lboost_unit_test_framework 

# ==== boost chrono links to to librt.a under Linux
ifeq ($(UNAME_S), Linux)
LIBS += -lrt 
endif 

# ==== GUROBI 
INCLUDE += -I $(GUROBI_HOME)/include
LIBS += -L $(GUROBI_HOME)/lib -lgurobi_c++ -lgurobi60 \
		-lpthread 
# ==== Csdp api (OpenBLAS and Fortran library are necessary)
# it looks like pthead must be linked dynamically when GUROBI is also on 
LIBS += -L $(LIMBO_ROOT_DIR)/lib -lsdp -lopenblas-st -lm 
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

all: $(TEST_DIR)/test_ChromaticNumber $(TEST_DIR)/test_LPColoring $(TEST_DIR)/test_GraphSimplification $(TEST_DIR)/test_ILPColoring  $(TEST_DIR)/test_SDPColoring $(TEST_DIR)/test_FM

# Compile dependency 

$(OBJDIR)/%.d: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $< -MM -MT $(@:%.d=%.o) >$@ $(INCLUDE)

-include $(DEPS)

# Implicit rule to compile c++ files

$(OBJDIR)/%.o: %.cpp
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDE)

# Link executable

$(TEST_DIR)/test_ChromaticNumber: $(OBJDIR)/test_ChromaticNumber.o 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJDIR)/test_ChromaticNumber.o $(LIBS) 

$(TEST_DIR)/test_LPColoring: $(OBJDIR)/test_LPColoring.o 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJDIR)/test_LPColoring.o $(CXXFLAGS) $(LIBS)

$(TEST_DIR)/test_GraphSimplification: $(OBJDIR)/test_GraphSimplification.o 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJDIR)/test_GraphSimplification.o $(CXXFLAGS) $(LIBS)

$(TEST_DIR)/test_ILPColoring: $(OBJDIR)/test_ILPColoring.o 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJDIR)/test_ILPColoring.o $(CXXFLAGS) $(LIBS)

$(TEST_DIR)/test_SDPColoring: $(OBJDIR)/test_SDPColoring.o $(LIMBO_ROOT_DIR)/lib/libsdp.a $(LIMBO_ROOT_DIR)/lib/libopenblas-st.a
	$(CXX) $(CXXFLAGS) -o $@ $(OBJDIR)/test_SDPColoring.o $(CXXFLAGS) $(LIBS)

$(TEST_DIR)/test_FM: $(OBJDIR)/test_FM.o 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJDIR)/test_FM.o $(LIBS) 

.PHONY: clean
clean: cleandep
	rm -f $(TEST_DIR)/test_ChromaticNumber 
	rm -f $(TEST_DIR)/test_LPColoring 
	rm -f $(TEST_DIR)/test_GraphSimplification 
	rm -f $(TEST_DIR)/test_ILPColoring 
	rm -f $(TEST_DIR)/test_SDPColoring 
	rm -f $(TEST_DIR)/test_FM
	rm -f $(OBJS)

.PHONY: cleandep
cleandep:
	rm -f $(DEPS)
