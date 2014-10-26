/*************************************************************************
    > File Name: LpDataBase.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 10 Oct 2014 11:49:28 PM CDT
 ************************************************************************/

#ifndef LPPARSER_DATABASE_H
#define LPPARSER_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <limits>

namespace LpParser {

	using std::cout;
	using std::endl;
	using std::cerr;
	using std::string; 
	using std::vector;
	using std::pair;
	using std::make_pair;
	using std::ostringstream;
	typedef int int32_t;
	typedef unsigned int uint32_t;
	typedef long int64_t;

// bison does not support vector very well 
// so here create a dummy class 
class IntegerArray : public vector<int64_t>
{
	public: 
		typedef vector<int64_t> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;

		IntegerArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
		IntegerArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
			: base_type(n, val, alloc) {}
};

class StringArray : public vector<string>
{
	public: 
		typedef vector<string> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;

		StringArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
		StringArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
			: base_type(n, val, alloc) {}
};

struct Term 
{
	int64_t coef;
	string var;

	Term(int64_t c, string const& v) : coef(c), var(v) {}
};

// temporary data structures to hold parsed data 

// forward declaration
// base class for DataBase 
// only pure virtual functions are defined 
// user needs to heritate this class 
class LpDataBase
{
	public:
		virtual void add_variable(string const&, 
				int64_t const& l = std::numeric_limits<int64_t>::min(), 
				int64_t const& r = std::numeric_limits<int64_t>::max()) = 0;
		virtual void add_constraint(string const&, string const&, int64_t const&) = 0;
		virtual void add_objective(string const&, int64_t const&) = 0;
};

} // namespace DefParser

#endif
