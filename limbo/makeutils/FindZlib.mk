## @file   FindZlib.mk
## @brief  find Zlib library given ZLIB_DIR, set ZLIB_LINK_FLAG to either STATIC_LINK_FLAG or DYNAMIC_LINK_FLAG
##
## It check whether Zlib library is installed as static library. If so, link to static library; otherwise, link to shared library. 
## Use following command in the Makefile to view the results 
## 
##     $(info Zlib: ZLIB_LINK_FLAG = $(ZLIB_LINK_FLAG))
##
## @author Yibo Lin
## @date   Jan 2017
##
## @param  ZLIB_DIR given path to Zlib library 
## @param  ZLIB_LINK_FLAG set linking flag to Zlib

## @cond 

ZLIB_LINK_FLAG =

# use libz.a to test whether Zlib has static library
ifeq ($(wildcard $(ZLIB_DIR)/libz.a),) 
	ZLIB_LINK_FLAG = -Wl,-rpath,$(ZLIB_DIR) $(DYNAMIC_LINK_FLAG)
else 
	ZLIB_LINK_FLAG = $(STATIC_LINK_FLAG)
endif 

## @endcond
