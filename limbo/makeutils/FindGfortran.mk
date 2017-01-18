#########################################################################
# File Name: FindGfortran.mk
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Wed 18 Jan 2017 02:02:07 PM CST
#########################################################################

## find gfortran, determine FC
ifneq ($(shell which gfortran48),)
	FC = gfortran48
else
ifneq ($(shell which gfortran-4.8),)
	FC = gfortran-4.8
else
ifneq ($(shell which gfortran47),)
	FC = gfortran47
else
ifneq ($(shell which gfortran-4.7),)
	FC = gfortran-4.7
else 
ifneq ($(shell which gfortran44),)
	FC = gfortran44
else
ifneq ($(shell which gfortran-4.4),)
	FC = gfortran-4.4
else 
	FC = gfortran
endif
endif
endif
endif
endif
endif 
