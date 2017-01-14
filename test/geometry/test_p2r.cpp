/*************************************************************************
    > File Name: test_p2r.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Mon 27 Oct 2014 11:44:57 PM CDT
 ************************************************************************/

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <limbo/geometry/Polygon2Rectangle.h>
using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::set;
using namespace limbo::geometry; 

struct Point
{
	typedef int value_type;
	value_type m_x;
	value_type m_y;
	value_type const& x() const {return m_x;}
	value_type const& y() const {return m_y;}
	void x(value_type v) {m_x = v;}
	void y(value_type v) {m_y = v;}

	//bool operator==(Point const& rhs) {return x() == rhs.x() && y() == rhs.y();}
};

/// \brief if your point class setting is different from that in the default point_traits
/// please create a specialization
namespace limbo { namespace geometry {

template <>
struct point_traits<Point>
{
	typedef Point point_type;
	typedef int coordinate_type;

	static coordinate_type get(const point_type& point, orientation_2d orient) 
	{
		if (orient == HORIZONTAL) return point.x();
		else if (orient == VERTICAL) return point.y();
		else assert(0);
	}
	static void set(point_type& point, orientation_2d orient, coordinate_type value) 
	{
		if (orient == HORIZONTAL) return point.x(value);
		else if (orient == VERTICAL) return point.y(value);
		else assert(0);
	}
	static point_type construct(coordinate_type x, coordinate_type y) 
	{
		point_type p; 
		p.x(x); p.y(y);
		return p;
	}
};

}}

struct Rectangle 
{
	typedef int value_type;

	value_type m_xl;
	value_type m_yl;
	value_type m_xh;
	value_type m_yh;

	value_type const& xl() const {return m_xl;}
	value_type const& yl() const {return m_yl;}
	value_type const& xh() const {return m_xh;}
	value_type const& yh() const {return m_yh;}
	void xl(value_type v) {m_xl = v;}
	void yl(value_type v) {m_yl = v;}
	void xh(value_type v) {m_xh = v;}
	void yh(value_type v) {m_yh = v;}
};

/// \brief if your rectangle class setting is different from that in the default point_traits
/// please create a specialization
namespace limbo { namespace geometry {

template <>
struct rectangle_traits<Rectangle>
{
	typedef Rectangle rectangle_type;
	typedef int coordinate_type;

	static coordinate_type get(const rectangle_type& rect, direction_2d dir) 
	{
		switch (dir)
		{
			case LEFT: return rect.xl();
			case BOTTOM: return rect.yl();
			case RIGHT: return rect.xh();
			case TOP: return rect.yh();
			default: assert(0);
		}
	}
	static void set(rectangle_type& rect, direction_2d dir, coordinate_type value) 
	{
		switch (dir)
		{
			case LEFT: rect.xl(value); break;
			case BOTTOM: rect.yl(value); break;
			case RIGHT: rect.xh(value); break;
			case TOP: rect.yh(value); break;
			default: assert(0);
		}
	}
	static rectangle_type construct(coordinate_type xl, coordinate_type yl, coordinate_type xh, coordinate_type yh) 
	{
		rectangle_type rect; 
		rect.xl(xl); rect.yl(yl);
		rect.xh(xh); rect.yh(yh);
		return rect;
	}
};

}}

void test1(string const& filename)
{
    vector<Rectangle> vRect; 
	Polygon2Rectangle<vector<Point>, vector<Rectangle> > p2r (vRect, HOR_VER_SLICING);
	assert(p2r.read(filename));
	assert(p2r());
	p2r.print("p2r1.gp");
}

void test2(string const& filename)
{
    vector<Rectangle> vRect; 
	Polygon2Rectangle<list<Point>, vector<Rectangle> > p2r (vRect, HOR_VER_SLICING);
	assert(p2r.read(filename));
	assert(p2r());
	p2r.print("p2r2.gp");
}

void test3(string const& filename)
{
    vector<Rectangle> vRect; 
	Polygon2Rectangle<set<Point, point_compare_type>, vector<Rectangle> > p2r (vRect, HOR_VER_SLICING);
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
