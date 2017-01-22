#########################################################################
# File Name: FindLemon.mk
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Wed 18 Jan 2017 11:18:47 AM CST
#########################################################################

## find Lemon library given LEMON_DIR, set LEMON_LINK_FLAG to either STATIC_LINK_FLAG or DYNAMIC_LINK_FLAG
LEMON_LINK_FLAG :=
# use libemon.a to test whether lemon has static library
ifeq ($(wildcard $(LEMON_DIR)/lib/libemon.a),) 
	LEMON_LINK_FLAG = -Wl,-rpath,$(LEMON_DIR)/lib $(DYNAMIC_LINK_FLAG)
else 
	LEMON_LINK_FLAG = $(STATIC_LINK_FLAG)
endif 
