/*************************************************************************
    > File Name: ToString.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Sat 04 Apr 2015 03:35:21 PM CDT
 ************************************************************************/

#ifndef _LIMBO_STRING_TOSTRING
#define _LIMBO_STRING_TOSTRING

/// ===================================================================
///    File          : ToString
///    Function      : convert metadata type to string 
///
/// ===================================================================

#include <string>
#include <cstdio>
#include <limits>

namespace limbo {

using std::string;

inline string to_string(int val)
{
	char a[sizeof(int)<<2]; 
	sprintf(a, "%d", val);
	return string(a);
}
inline string to_string(long val)
{
	char a[sizeof(long)<<2]; 
	sprintf(a, "%ld", val);
	return string(a);
}
inline string to_string(long long val)
{
	char a[sizeof(long long)<<2]; 
	sprintf(a, "%lld", val);
	return string(a);
}
inline string to_string(unsigned int val)
{
	char a[sizeof(unsigned int)<<2]; 
	sprintf(a, "%u", val);
	return string(a);
}
inline string to_string(unsigned long val)
{
	char a[sizeof(unsigned long)<<2]; 
	sprintf(a, "%lu", val);
	return string(a);
}
inline string to_string(unsigned long long val)
{
	char a[sizeof(unsigned long long)<<2]; 
	sprintf(a, "%llu", val);
	return string(a);
}
inline string to_string(float val)
{
	if (val != val) return string("nan");
	char a[std::numeric_limits<float>::max_exponent10+20]; 
	sprintf(a, "%g", val);
	return string(a);
}
inline string to_string(double val)
{
	if (val != val) return string("nan");
	char a[std::numeric_limits<double>::max_exponent10+20]; 
	sprintf(a, "%g", val);
	return string(a);
}
inline string to_string(long double val)
{
	if (val != val) return string("nan");
	char a[std::numeric_limits<long double>::max_exponent10+20]; 
	sprintf(a, "%Lf", val);
	return string(a);
}

} // namespace limbo 

#endif
