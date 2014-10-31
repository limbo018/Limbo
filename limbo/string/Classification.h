/*************************************************************************
    > File Name: Classification.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Tue 28 Oct 2014 11:24:15 AM CDT
 ************************************************************************/

#ifndef _LIMBO_STRING_CLASSIFICATION
#define _LIMBO_STRING_CLASSIFICATION

/// ===================================================================
///    File          : Classification
///    Function      : Check string is integer, floating point, number...
///
/// ===================================================================

#include <iostream>
#include <string>
#include <cctype>
using std::cout;
using std::endl;
using std::string;

namespace limbo { 

/// check whether string represents an integer 
inline bool is_integer(string const& s)
{
	if (s.empty()) return false;
	for (string::const_iterator it = s.begin(); it != s.end(); ++it)
	{
		if (!isdigit(*it)) return false;
	}
	return true;
}

/// check whether string represents a floating point 
inline bool is_float(string const& s)
{
	if (s.empty()) return false;
	short dp_cnt = 0; // count how many times the decimal point appears 
					// if it appears more than 1, then s is not a floating point number 
	for (string::const_iterator it = s.begin(); it != s.end(); ++it)
	{
		if (!isdigit(*it))
		{
			if (*it == '.' && dp_cnt < 1) // dp_cnt should be <= 1 
				++dp_cnt;
			else return false;
		}
	}
	// for floating point we assume decimal point should be there 
	return dp_cnt == 1;
}

/// check whether string represents a number, either an integer or a floating point 
inline bool is_number(string const& s)
{
	if (s.empty()) return false;
	short dp_cnt = 0; // count how many times the decimal point appears 
					// if it appears more than 1, then s is not a floating point number 
	for (string::const_iterator it = s.begin(); it != s.end(); ++it)
	{
		if (!isdigit(*it))
		{
			if (*it == '.' && dp_cnt < 1) // dp_cnt should be <= 1 
				++dp_cnt;
			else return false;
		}
	}
	// no requirement for floating point here 
	return true;
}

} // namespace limbo 

#endif 
