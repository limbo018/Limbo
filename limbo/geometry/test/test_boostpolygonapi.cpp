/*************************************************************************
    > File Name: test_boostpolygonapi.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 31 Oct 2014 02:53:46 PM CDT
 ************************************************************************/

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <boost/polygon/polygon.hpp>
#include <limbo/geometry/Polygon2Rectangle.h>
#include <limbo/geometry/api/BoostPolygonApi.h>
using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::set;

namespace gtl = boost::polygon;
namespace lg = limbo::geometry; 

void test1(string const& filename)
{
	lg::Polygon2Rectangle<vector<gtl::point_data<int> >, vector<gtl::rectangle_data<int> > > p2r (lg::HOR_VER_SLICING);
	assert(p2r.read(filename));
	assert(p2r());
	p2r.print("p2r1.gp");
}

void test2(string const& filename)
{
	lg::Polygon2Rectangle<list<gtl::point_data<int> >, vector<gtl::rectangle_data<int> > > p2r (lg::HOR_VER_SLICING);
	assert(p2r.read(filename));
	assert(p2r());
	p2r.print("p2r2.gp");
}

void test3(string const& filename)
{
	lg::Polygon2Rectangle<set<gtl::point_data<int> , lg::point_compare_type>, vector<gtl::rectangle_data<int> > > p2r (lg::HOR_VER_SLICING);
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
