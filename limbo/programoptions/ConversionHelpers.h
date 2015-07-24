/*************************************************************************
    > File Name: ConversionHelpers.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 15 Jul 2015 04:46:25 PM CDT
 ************************************************************************/

#ifndef _LIMBO_PROGRAMOPTIONS_CONVERSIONHELPERS_H
#define _LIMBO_PROGRAMOPTIONS_CONVERSIONHELPERS_H

#include <iostream>
#include <vector>
#include <set>
#include <limbo/string/String.h>

namespace limbo { namespace programoptions {

/// template function objects to parse, print and assign values 
/// template specialization is needed if default operators are not defined 
template <typename T>
struct parse_helper 
{
    inline bool operator()(T& target, const char* value) const
    {
        target = value;
        return true;
    }
};

template <typename T>
struct print_helper
{
    inline void operator()(std::ostream& os, T const& target) const
    {
        os << target;
    }
};

template <typename T>
struct assign_helper
{
    inline void operator()(T& target, T const& source) const
    {
        target = source;
    }
};

/////////////////// specialization for parse_helper /////////////////
template <>
struct parse_helper<bool>
{
    inline bool operator()(bool& target, const char* value) const
    {
        if (limbo::iequals(value, "true") || limbo::iequals(value, "1"))
            target = true;
        else if (limbo::iequals(value, "false") || limbo::iequals(value, "0"))
            target = false;
        else return false;
        return true;
    }
};
template <>
struct parse_helper<char>
{
    inline bool operator()(char& target, const char* value) const
    {
        target = *value;
        return true;
    }
};
template <>
struct parse_helper<unsigned char>
{
    inline bool operator()(unsigned char& target, const char* value) const
    {
        target = *value;
        return true;
    }
};
template <>
struct parse_helper<int>
{
    inline bool operator()(int& target, const char* value) const
    {
        target = atoi(value);
        return true;
    }
};
template <>
struct parse_helper<unsigned int>
{
    inline bool operator()(unsigned int& target, const char* value) const
    {
        target = atoi(value);
        return true;
    }
};
template <>
struct parse_helper<long>
{
    inline bool operator()(long& target, const char* value) const
    {
        target = atol(value);
        return true;
    }
};
template <>
struct parse_helper<unsigned long>
{
    inline bool operator()(unsigned long& target, const char* value) const
    {
        target = atol(value);
        return true;
    }
};
template <>
struct parse_helper<float>
{
    inline bool operator()(float& target, const char* value) const
    {
        target = atof(value);
        return true;
    }
};
template <>
struct parse_helper<double>
{
    inline bool operator()(double& target, const char* value) const
    {
        target = atof(value);
        return true;
    }
};
template <typename T>
struct parse_helper<std::vector<T> >
{
    inline bool operator()(std::vector<T>& target, const char* value) const
    {
        T v;
        parse_helper<T>()(v, value);
        target.push_back(v);
        return true;
    }
};
template <typename T>
struct parse_helper<std::set<T> >
{
    inline bool operator()(std::set<T>& target, const char* value) const
    {
        T v;
        parse_helper<T>()(v, value);
        target.insert(v);
        return true;
    }
};

/////////////////// specialization for print_helper /////////////////
template <>
struct print_helper<bool>
{
    inline void operator()(std::ostream& os, bool const& target) const 
    {
        os << ((target)? "true" : "false");
    }
};
template <typename T>
struct print_helper<std::vector<T> >
{
    inline void operator()(std::ostream& os, std::vector<T> const& target) const
    {
        const char* prefix = "";
        for (typename std::vector<T>::const_iterator it = target.begin(); it != target.end(); ++it)
        {
            os << prefix;
            print_helper<T>()(os, *it);
            prefix = ",";
        }
    }
};
template <typename T>
struct print_helper<std::set<T> >
{
    inline void operator()(std::ostream& os, std::set<T> const& target) const
    {
        const char* prefix = "";
        for (typename std::set<T>::const_iterator it = target.begin(); it != target.end(); ++it)
        {
            os << prefix;
            print_helper<T>()(os, *it);
            prefix = ",";
        }
    }
};

/////////////////// specialization for assign_helper /////////////////

}} // namespace limbo // programoptions

#endif
