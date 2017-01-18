#########################################################################
# File Name: FindClangxx.mk
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Wed 18 Jan 2017 02:03:20 PM CST
#########################################################################

## find clang++, determine CXX
ifneq ($(shell which clang++),)
	CXX = clang++
else 
	CXX = g++
endif
