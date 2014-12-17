/*************************************************************************
    > File Name: Math.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 17 Dec 2014 12:53:24 PM CST
 ************************************************************************/

#ifndef _LIMBO_MATH_MATH
#define _LIMBO_MATH_MATH

/// ===================================================================
///    File          : Math
///    Function      : mathematical utilities such as abs 
///
/// ===================================================================

namespace limbo {

/// return absolute value of a number 
/// generalized api can handle both integer and floating points 
template <typename T>
inline T abs(T const& t)
{
	return (t > 0)? t : -t;
}

} // namespace limbo 

#endif 
