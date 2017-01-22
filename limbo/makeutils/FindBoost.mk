#########################################################################
# File Name: FindBoost.mk
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Wed 18 Jan 2017 11:18:47 AM CST
#########################################################################

## find Boost library given BOOST_DIR, set BOOST_LINK_FLAG to either STATIC_LINK_FLAG or DYNAMIC_LINK_FLAG
BOOST_LINK_FLAG :=
# use libboost_system.a to test whether boost has static library
ifeq ($(wildcard $(BOOST_DIR)/lib/libboost_system.a),) 
	BOOST_LINK_FLAG = -Wl,-rpath,$(BOOST_DIR)/lib $(DYNAMIC_LINK_FLAG)
else 
	BOOST_LINK_FLAG = $(STATIC_LINK_FLAG)
endif 
