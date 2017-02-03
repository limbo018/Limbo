/**
 * @file   LpDataBase.h
 * @brief  Database for Lp parser 
 * @author Yibo Lin
 * @date   Oct 2014
 */

#ifndef LPPARSER_DATABASE_H
#define LPPARSER_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <limits>

/// namespace for LpParser
namespace LpParser {

/// @nowarn
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
/// @endnowarn

/// @brief bison does not support vector very well, 
/// so here create a dummy class for integer array. 
class IntegerArray : public vector<int64_t>
{
	public: 
        /// @nowarn 
		typedef vector<int64_t> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;
        /// @endnowarn

        /// @brief constructor 
        /// @param alloc memory allocator 
		IntegerArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
        /// @brief constructor 
        /// @param n number of values 
        /// @param val data value
        /// @param alloc memory allocator 
		IntegerArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
			: base_type(n, val, alloc) {}
};

/// @brief bison does not support vector very well, 
/// so here create a dummy class for string array. 
class StringArray : public vector<string>
{
	public: 
        /// @nowarn 
		typedef vector<string> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;
        /// @endnowarn

        /// @brief constructor 
        /// @param alloc memory allocator 
		StringArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
        /// @brief constructor 
        /// @param n number of values 
        /// @param val data value
        /// @param alloc memory allocator 
		StringArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
			: base_type(n, val, alloc) {}
};

/// @brief a term denotes coefficient times a variable 
struct Term 
{
	int64_t coef; ///< coefficient 
	string var; ///< variable 

    /// @brief constructor 
    /// @param c coefficient 
    /// @param v variable 
	Term(int64_t c, string const& v) : coef(c), var(v) {}
};

// temporary data structures to hold parsed data 

// forward declaration
/// @class LpParser::LpDataBase
/// @brief Base class for lp database. 
/// Only pure virtual functions are defined.  
/// User needs to inheritate this class and derive a custom database type with all callback functions defined.  
class LpDataBase
{
	public:
        /// @brief add variable that \a l <= \a vname <= \a r. 
        /// @param vname variable name 
        /// @param l lower bound 
        /// @param r upper bound 
		virtual void add_variable(string const& vname, 
				int64_t const& l = std::numeric_limits<int64_t>::min(), 
				int64_t const& r = std::numeric_limits<int64_t>::max()) = 0;
        /// @brief add constraint that \a vname1 - \a vname2 >= \a constant. 
        /// @param vname1 first variable 
        /// @param vname2 second variable 
        /// @param constant constant value 
		virtual void add_constraint(string const& vname1, string const& vname2, int64_t const& constant) = 0;
        /// @brief add object terms that \a coef * \a vname 
        /// @param vname variable name 
        /// @param coef coefficient 
		virtual void add_objective(string const& vname, int64_t const& coef) = 0;
};

} // namespace DefParser

#endif
