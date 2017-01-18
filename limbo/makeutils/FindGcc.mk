#########################################################################
# File Name: FindGcc.mk
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Wed 18 Jan 2017 02:01:01 PM CST
#########################################################################

## find gcc, determine CC
ifneq ($(shell which gcc48),)
	CC = gcc48
else
ifneq ($(shell which gcc-4.8),)
	CC = gcc-4.8
else
ifneq ($(shell which gcc47),)
	CC = gcc47
else
ifneq ($(shell which gcc-4.7),)
	CC = gcc-4.7
else 
ifneq ($(shell which gcc44),)
	CC = gcc44
else
ifneq ($(shell which gcc-4.4),)
	CC = gcc-4.4
else 
	CC = gcc
endif
endif
endif
endif
endif
endif 
