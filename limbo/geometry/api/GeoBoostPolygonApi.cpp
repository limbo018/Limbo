/*************************************************************************
    > File Name: GeoBoostPolygonApi.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Thu 10 Sep 2015 08:23:49 PM CDT
 ************************************************************************/

// for better potability 
// I do not include from limbo dir 
//#include <limbo/geometry/api/GeoBoostPolygonApi.h>
#include "GeoBoostPolygonApi.h"
#include <limbo/geometry/Polygon2Rectangle.h>
#include <limbo/geometry/api/BoostPolygonApi.h>

namespace limbo { namespace geometry {

namespace gtl = boost::polygon;

bool polygon2RectangleBoost(std::vector<gtl::point_data<int> > const& vPoint, std::vector<gtl::rectangle_data<int> >& vRectangle)
{
    typedef gtl::point_data<int> point_type;

    return limbo::geometry::polygon2rectangle(
                vPoint.begin(), vPoint.end(), 
                //set<yLib::Point, limbo::geometry::point_compare_type>(), 
                vector<point_type>(), 
                //list<yLib::Point>(), 
                vRectangle, 
                HOR_VER_SLICING);
}

bool polygon2RectangleBoost(gtl::polygon_90_data<int> const& polygon, std::vector<gtl::rectangle_data<int> >& vRectangle)
{
    typedef gtl::point_data<int> point_type;

    // after experiment, I found use vector as container is fastest
    // for s.gds, set takes 22s, vector takes 2.5s, and list takes 16s
    return limbo::geometry::polygon2rectangle(
                polygon.begin(), polygon.end(), 
                //set<yLib::Point, limbo::geometry::point_compare_type>(), 
                vector<point_type>(), 
                //list<yLib::Point>(), 
                vRectangle, 
                HOR_VER_SLICING);
}

}} // namespace limbo // namespace geometry

