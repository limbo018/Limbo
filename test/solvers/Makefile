#==========================================================================
#                         Directories and names 
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ../..)
OBJDIR = obj
MKDIR = if [ ! -d $(@D) ]; then mkdir -p $(@D); fi

VPATH = .

#==========================================================================
#                         Compilation Flags
# ==========================================================================

# default DBG is off
DBG = 0

# include environmental configurations 
include $(LIMBO_ROOT_DIR)/Include.mk

ifeq ($(DBG), 1)
	CXXFLAGS = $(CXXFLAGS_DEBUG) 
else
	CXXFLAGS = $(CXXFLAGS_RELEASE)
endif

#==========================================================================
#                         Special Library
# ==========================================================================

# internal dependency is lp parser 
# external dependency is boost
INCLUDE = -I $(LIMBO_ROOT_DIR) \
		  -I $(LEMON_DIR)/include
LIBS = -L $(LIMBO_ROOT_DIR)/lib -llpparser -lsolvers \
	   -L $(LEMON_DIR)/lib -lemon

# ==========================================================================
#                         Standard Setting
# ==========================================================================

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
DEPS = $(OBJS:%.o=%.d) 	# one dependency file for each source

all: lpmcf test_solvers test_MultiKnapsackLagRelax test_DualMinCostFlow
.PHONY: lpmcf

lpmcf:
	$(MAKE) -C lpmcf

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

test_solvers: $(OBJDIR)/test_solvers.o 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJDIR)/test_solvers.o $(LIBS) 

test_MultiKnapsackLagRelax: $(OBJDIR)/test_MultiKnapsackLagRelax.o $(LIMBO_ROOT_DIR)/lib/libsolvers.a
	$(CXX) $(CXXFLAGS) -o $@ $(OBJDIR)/test_MultiKnapsackLagRelax.o $(LIBS) 

test_DualMinCostFlow: $(OBJDIR)/test_DualMinCostFlow.o $(LIMBO_ROOT_DIR)/lib/libsolvers.a
	$(CXX) $(CXXFLAGS) -o $@ $(OBJDIR)/test_DualMinCostFlow.o $(LIBS) 

.PHONY: clean
clean: cleandep
	$(MAKE) clean -C lpmcf
	rm -f test_solvers
	rm -f test_MultiKnapsackLagRelax
	rm -f test_DualMinCostFlow
	rm -f $(OBJS) 

.PHONY: cleandep
cleandep:
	rm -f $(DEPS)

.PHONY: extraclean
extraclean: clean
	$(MAKE) extraclean -C lpmcf
	rm -rf $(OBJDIR)
