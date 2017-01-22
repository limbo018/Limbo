#########################################################################
# File Name: FindGurobi.mk
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Wed 18 Jan 2017 11:18:47 AM CST
#########################################################################

## find Gurobi library given GUROBI_HOME, set GUROBI_VERSION and GUROBI_LINK_LIB
GUROBI_VERSION = $(subst .so,,$(subst libgurobi,,$(notdir $(wildcard $(GUROBI_HOME)/lib/libgurobi*.so))))
GUROBI_LINK_LIB = -Wl,-rpath,$(GUROBI_HOME)/lib -L $(GUROBI_HOME)/lib -lgurobi_c++ -lgurobi$(GUROBI_VERSION)

# $(info Gurobi: GUROBI_VERSION = $(GUROBI_VERSION))
