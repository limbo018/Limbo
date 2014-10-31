/*************************************************************************
    > File Name: bLibApi.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 31 Oct 2014 01:12:59 PM CDT
 ************************************************************************/

#ifndef _LIMBO_GEOMETRY_API_BLIBAPI_H
#define _LIMBO_GEOMETRY_API_BLIBAPI_H

/// ===================================================================
///    class          : bLibApi
///
///  Geometry traits for bLib, include this file when bLib is available  
///
/// ===================================================================

#include <limbo/geometry/Geometry.h>

/// \brief if your point class setting is different from that in the default point_traits
/// please create a specialization
namespace limbo { namespace geometry {

/// \brief specialization for bLib::bPoint 
template <>
struct point_traits<bLib::bPoint>
{
	typedef bLib::bPoint point_type;
	typedef int coordinate_type;

	static coordinate_type get(const point_type& point, orientation_2d const& orient) 
	{
		if (orient == HORIZONTAL) return point.x();
		else if (orient == VERTICAL) return point.y();
		else assert(0);
	}
	static void set(point_type& point, orientation_2d const& orient, coordinate_type const& value) 
	{
		if (orient == HORIZONTAL) return point.set(value, point.y());
		else if (orient == VERTICAL) return point.set(point.x(), value);
		else assert(0);
	}
	static point_type construct(coordinate_type const& x, coordinate_type const& y) 
	{
		return point_type(x, y);
	}
};

/// \brief specialization for bLib::bBox 
template <>
struct rectangle_traits<bLib::bBox>
{
	typedef bLib::bBox rectangle_type;
	typedef int coordinate_type;

	static coordinate_type get(const rectangle_type& rect, direction_2d const& dir) 
	{
		switch (dir)
		{
			case LEFT: return rect.x1();
			case BOTTOM: return rect.y1();
			case RIGHT: return rect.x2();
			case TOP: return rect.y2();
			default: assert(0);
		}
	}
	static void set(rectangle_type& rect, direction_2d const& dir, coordinate_type const& value) 
	{
		switch (dir)
		{
			case LEFT: rect.set(value, rect.y1(), rect.x2(), rect.y2()); break;
			case BOTTOM: rect.set(rect.x1(), value, rect.x2(), rect.y2()); break;
			case RIGHT: rect.set(rect.x1(), rect.y1(), value, rect.y2()); break;
			case TOP: rect.set(rect.x1(), rect.y1(), rect.x2(), value); break;
			default: assert(0);
		}
	}
	static rectangle_type construct(coordinate_type const& xl, coordinate_type const& yl, 
			coordinate_type const& xh, coordinate_type const& yh) 
	{
		return rectangle_type(xl, yl, xh, yh); 
	}
};

}}// namespace limbo // namespace geometry

#endif 
