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
/// return sum value of an array
template <typename Iterator>
inline typename std::iterator_traits<Iterator>::value_type sum(Iterator first, Iterator last)
{
	typename std::iterator_traits<Iterator>::value_type v = 0;
	for (; first != last; ++first)
		v += *first;
	return v;
}
/// return average value of an array 
template <typename Iterator>
inline typename std::iterator_traits<Iterator>::value_type average(Iterator first, Iterator last)
{
	typename std::iterator_traits<Iterator>::value_type v = 0;
	size_t cnt = 0;
	for (; first != last; ++first)
	{
		v += *first;
		cnt += 1;
	}
	return v/cnt;
}
/// return max value of an array 
template <typename Iterator>
inline typename std::iterator_traits<Iterator>::value_type max(Iterator first, Iterator last)
{
	typename std::iterator_traits<Iterator>::value_type v = *first;
	for (; first != last; ++first)
	{
		if (v < *first)
			v = *first;
	}
	return v;
}
/// return min value of an array 
template <typename Iterator>
inline typename std::iterator_traits<Iterator>::value_type min(Iterator first, Iterator last)
{
	typename std::iterator_traits<Iterator>::value_type v = *first;
	for (; first != last; ++first)
	{
		if (v > *first)
			v = *first;
	}
	return v;
}

} // namespace limbo 

#endif 
