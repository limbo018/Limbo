/**
 * @file   Math.h
 * @brief  mathematical utilities such as abs 
 * @author Yibo Lin
 * @date   Dec 2014
 */

#ifndef _LIMBO_MATH_MATH
#define _LIMBO_MATH_MATH

#include <iterator>

namespace for Limbo
namespace limbo 
{

/// @brief generalized api can handle both integer and floating points 
/// @return absolute value of a number 
template <typename T>
inline T abs(T const& t)
{
	return (t > 0)? t : -t;
}
/// @brief get summation of an array 
/// @param first begin iterator 
/// @param last end iterator 
/// @return sum value of an array
/// @tparam Iterator iterator type 
template <typename Iterator>
inline typename std::iterator_traits<Iterator>::value_type sum(Iterator first, Iterator last)
{
	typename std::iterator_traits<Iterator>::value_type v = 0;
	for (; first != last; ++first)
		v += *first;
	return v;
}
/// @brief get average of an array 
/// @param first begin iterator 
/// @param last end iterator 
/// @return average value of an array
/// @tparam Iterator iterator type 
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
/// @brief get max of an array 
/// @param first begin iterator 
/// @param last end iterator 
/// @return max value of an array
/// @tparam Iterator iterator type 
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
/// @brief get min of an array 
/// @param first begin iterator 
/// @param last end iterator 
/// @return min value of an array
/// @tparam Iterator iterator type 
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
