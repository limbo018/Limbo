/*************************************************************************
    > File Name: GeoBoostPolygonApi.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Thu 10 Sep 2015 08:15:51 PM CDT
 ************************************************************************/

#ifndef LIMBO_GEOMETRY_GEOBOOSTPOLYGONAPI_H
#define LIMBO_GEOMETRY_GEOBOOSTPOLYGONAPI_H

#include <boost/polygon/polygon.hpp>

/// ==========================================================================
/// this file extracts polygon-to-rectangle conversion for Boost.Polygon API. 
/// ==========================================================================

namespace limbo { namespace geometry {

namespace gtl = boost::polygon;

/// this function takes a set of points describing a rectilinear polygon and decomposes it into rectangles 
/// \param vPoint, a set of points as input 
/// \param vRectangle, a set of rectangles as output 
/// \return true if succeeded 
bool polygon2RectangleBoost(std::vector<gtl::point_data<int> > const& vPoint, std::vector<gtl::rectangle_data<int> >& vRectangle);
/// this function takes a rectilinear polygon and decomposes it into rectangles 
/// \param polygon, rectilinear polygon as input 
/// \param vRectangle, a set of rectangles as output 
/// \return true if succeeded 
bool polygon2RectangleBoost(gtl::polygon_90_data<int> const& polygon, std::vector<gtl::rectangle_data<int> >& vRectangle);

}} // namespace limbo // namespace geometry

#endif
