/*************************************************************************
    > File Name: ConversionHelpers.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 15 Jul 2015 04:46:25 PM CDT
 ************************************************************************/

#ifdef _LIMBO_PROGRAMOPTIONS_CONVERSIONHELPERS_H
#define _LIMBO_PROGRAMOPTIONS_CONVERSIONHELPERS_H

namespace limbo { namespace programoptions {

template <typename T>
void parse_helper(T& target, const char* value);

template <typename T>
void print_helper(std::ostream& os, T const& target);

template <typename T>
void assign_helper(T& target, T const& source);

}} // namespace limbo // programoptions

#endif
