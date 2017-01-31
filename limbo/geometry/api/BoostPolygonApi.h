/**
 * @file   BoostPolygonApi.h
 * @author Yibo Lin
 * @date   Oct 2014
 */

#ifndef _LIMBO_GEOMETRY_API_BOOSTPOLYGONAPI_H
#define _LIMBO_GEOMETRY_API_BOOSTPOLYGONAPI_H

/// ===================================================================
///    class          : BoostPolygonApi
///
///  Geometry traits for Boost.Polygon, include this file when you use Boost.Polygon 
///  geometric types 
///
/// ===================================================================

#include <limbo/geometry/Geometry.h>

/// \brief if your point class setting is different from that in the default point_traits
/// please create a specialization
namespace limbo { namespace geometry {

/// \brief specialization for boost::polygon::point_data
template <typename T>
struct point_traits<boost::polygon::point_data<T> >
{
	typedef T coordinate_type;
	typedef boost::polygon::point_data<T> point_type;

	static coordinate_type get(const point_type& point, orientation_2d const& orient) 
	{
		if (orient == HORIZONTAL) return point.x();
		else if (orient == VERTICAL) return point.y();
		else assert(0);
	}
	static void set(point_type& point, orientation_2d const& orient, coordinate_type const& value) 
	{
		if (orient == HORIZONTAL) return point.set(boost::polygon::HORIZONTAL, value);
		else if (orient == VERTICAL) return point.set(boost::polygon::VERTICAL, value);
		else assert(0);
	}
	static point_type construct(coordinate_type const& x, coordinate_type const& y) 
	{
		return point_type(x, y);
	}
};

/// \brief specialization for boost::polygon::rectangle_data
template <typename T>
struct rectangle_traits<boost::polygon::rectangle_data<T> >
{
	typedef T coordinate_type;
	typedef boost::polygon::rectangle_data<T> rectangle_type;

	static coordinate_type get(const rectangle_type& rect, direction_2d const& dir) 
	{
		switch (dir)
		{
			case LEFT: return boost::polygon::xl(rect);
			case BOTTOM: return boost::polygon::yl(rect);
			case RIGHT: return boost::polygon::xh(rect);
			case TOP: return boost::polygon::yh(rect);
			default: assert(0);
		}
	}
	static void set(rectangle_type& rect, direction_2d const& dir, coordinate_type const& value) 
	{
		switch (dir)
		{
			case LEFT: boost::polygon::xl(rect, value); break;
			case BOTTOM: boost::polygon::yl(rect, value); break;
			case RIGHT: boost::polygon::xh(rect, value); break;
			case TOP: boost::polygon::yh(rect, value); break;
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
