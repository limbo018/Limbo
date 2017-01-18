#########################################################################
# File Name: FindClang.mk
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Wed 18 Jan 2017 02:02:57 PM CST
#########################################################################

## find clang, determine CC
ifneq ($(shell which clang),)
	CC = clang
else 
	CC = gcc
endif
