/*************************************************************************
    > File Name: DefDataBase.cc
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Thu 11 Dec 2014 04:28:14 PM CST
 ************************************************************************/

#include "DefDataBase.h"
#include <cstring>
#include <cstdlib>

namespace DefParser {

void DefDataBase::resize_def_blockage(int) 
{
	def_user_cbk_reminder(__func__);
}
void DefDataBase::add_def_placement_blockage(int, int, int, int)
{
	def_user_cbk_reminder(__func__);
}
void DefDataBase::add_def_routing_blockage(int, int, int, int)
{
	def_user_cbk_reminder(__func__);
}
void DefDataBase::def_user_cbk_reminder(const char* str) const 
{
	cout << "A corresponding user-defined callback is necessary: " << str << endl;
	exit(0);
}

}
