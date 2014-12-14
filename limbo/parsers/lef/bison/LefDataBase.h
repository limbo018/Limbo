/*************************************************************************
    > File Name: LefDataBase.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 10 Oct 2014 11:49:28 PM CDT
 ************************************************************************/

#ifndef LEFPARSER_DATABASE_H
#define LEFPARSER_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "lefiUser.hpp"
#include "lefiDefs.hpp"
#include "lefiUtil.hpp"

namespace LefParser {

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
class IntegerArray : public vector<int>
{
	public: 
		typedef vector<int> base_type;
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

// temporary data structures to hold parsed data 
struct Item 
{
	virtual void print(ostringstream&) const {};
	friend std::ostream& operator<<(std::ostream& os, Item const& rhs)
	{
		std::ostringstream ss;
		rhs.print(ss);
		os << ss.str();
		return os;
	}
	friend ostringstream& operator<<(ostringstream& ss, Item const& rhs)
	{
		rhs.print(ss);
		return ss;
	}
};
// forward declaration
// base class for DataBase 
// only pure virtual functions are defined 
// user needs to heritate this class 
class LefDataBase
{
	public:
		LefDataBase();
		double current_version() const;
		void current_version(double);
	protected:
		double m_current_version; /* default current lef version, use static variable to mimic definitions */
};

} // namespace LefParser

namespace LefParser {

enum lefiConstantEnum
{
	C_EQ = 0,
	C_NE = 1,
	C_LT = 2,
	C_LE = 3,
	C_GT = 4,
	C_GE = 5
};

/***************** custom help functions here ******************/
// copy from lex.h and lex.cpph
void* lefMalloc(int lef_size);
void* lefRealloc(void *name, int lef_size);
void lefFree(void *name);

} // namespace LefParser

#endif
