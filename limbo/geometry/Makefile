# $Id$
# plain simple Makefile to build test

#==========================================================================
#                         Directories and names 
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ../..)
TEST_DIR = $(realpath ./test)
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
	CXXFLAGS = $(CXXFLAGS_DEBUG)
else
	CXXFLAGS = $(CXXFLAGS_RELEASE)
endif

#==========================================================================
#                         Special Library
# ==========================================================================

INCLUDE = -I $(realpath .) \
		  -I $(LIMBO_ROOT_DIR) \
		  -I $(BLIB_DIR)/lib \
		  -I $(BOOST_DIR)/include

# ==========================================================================
#                         Standard Setting
# ==========================================================================

SRCS = $(wildcard *.cpp) 
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
DEPS = $(OBJS:%.o=%.d) 	# one dependency file for each source

SRCS_TEST = $(wildcard $(TEST_DIR)/*.cpp)
OBJS_TEST = $(patsubst $(TEST_DIR)/%.cpp,$(TEST_DIR)/%.o,$(SRCS_TEST))
DEPS_TEST = $(OBJS_TEST:%.o=%.d)

all: $(TEST_DIR)/test_p2r $(TEST_DIR)/test_blibapi $(TEST_DIR)/test_boostpolygonapi $(TEST_DIR)/libGeoBoostPolygonApi.a

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

$(TEST_DIR)/test_p2r: $(TEST_DIR)/test_p2r.o 
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_DIR)/test_p2r.o 

$(TEST_DIR)/test_blibapi: $(TEST_DIR)/test_blibapi.o
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_DIR)/test_blibapi.o 

$(TEST_DIR)/test_boostpolygonapi: $(TEST_DIR)/test_boostpolygonapi.o $(TEST_DIR)/libGeoBoostPolygonApi.a
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_DIR)/test_boostpolygonapi.o $(LIMBO_ROOT_DIR)/lib/libGeoBoostPolygonApi.a

$(TEST_DIR)/libGeoBoostPolygonApi.a: $(TEST_DIR)/GeoBoostPolygonApi.o
	$(AR) $(ARFLAGS) libGeoBoostPolygonApi.a $(TEST_DIR)/GeoBoostPolygonApi.o
	mv libGeoBoostPolygonApi.a $(LIMBO_ROOT_DIR)/lib


.PHONY: clean
clean: cleandep
	rm -f $(TEST_DIR)/test_p2r $(TEST_DIR)/test_blibapi $(TEST_DIR)/test_boostpolygonapi $(OBJS) $(OBJS_TEST)

.PHONY: cleandep
cleandep:
	rm -f $(DEPS) $(DEPS_TEST)

.PHONY: extraclean
extraclean: clean
	rm -f $(LIMBO_ROOT_DIR)/lib/libGeoBoostPolygonApi.a
