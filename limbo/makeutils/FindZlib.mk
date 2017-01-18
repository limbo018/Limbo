#########################################################################
# File Name: FindZLib.mk
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Wed 18 Jan 2017 11:39:44 AM CST
#########################################################################

## find Zlib library given ZLIB_DIR, set ZLIB_LINK_FLAG to either STATIC_LINK_FLAG or DYNAMIC_LINK_FLAG
ZLIB_LINK_FLAG =
# use libz.a to test whether Zlib has static library
ifeq ($(wildcard $(ZLIB_DIR)/libz.a),) 
	ZLIB_LINK_FLAG = -Wl,-rpath=$(ZLIB_DIR) $(DYNAMIC_LINK_FLAG)
else 
	ZLIB_LINK_FLAG = $(STATIC_LINK_FLAG)
endif 
