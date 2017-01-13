/*************************************************************************
    > File Name: test_blibapi.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 31 Oct 2014 01:57:11 PM CDT
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include "bLibPoint.h"
#include "bLibShape.h"
#include <limbo/geometry/Polygon2Rectangle.h>
#include <limbo/geometry/api/bLibApi.h>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::set;

namespace lg = limbo::geometry; 

void test1(string const& filename)
{
    std::vector<bLib::bBox> vRect; 
	lg::Polygon2Rectangle<vector<bLib::bPoint>, vector<bLib::bBox> > p2r (vRect, lg::HOR_VER_SLICING);
	assert(p2r.read(filename));
	assert(p2r());
	p2r.print("p2r1.gp");
}

void test2(string const& filename)
{
    std::vector<bLib::bBox> vRect; 
	lg::Polygon2Rectangle<list<bLib::bPoint>, vector<bLib::bBox> > p2r (vRect, lg::HOR_VER_SLICING);
	assert(p2r.read(filename));
	assert(p2r());
	p2r.print("p2r2.gp");
}

void test3(string const& filename)
{
    std::vector<bLib::bBox> vRect; 
	lg::Polygon2Rectangle<set<bLib::bPoint, lg::point_compare_type>, vector<bLib::bBox> > p2r (vRect, lg::HOR_VER_SLICING);
	assert(p2r.read(filename));
	assert(p2r());
	p2r.print("p2r3.gp");
}

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		test1(argv[1]);
		test2(argv[1]);
		test3(argv[1]);
	}
	else cout << "at least 1 argument is required" << endl;

	return 0;
}
