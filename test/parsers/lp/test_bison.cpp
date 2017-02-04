/**
 * @file   lp/test_bison.cpp
 * @brief  test lp parser, see @ref LpParser::Driver and @ref LpParser::LpDataBase
 * @author Yibo Lin
 * @date   Oct 2014
 */

#include <iostream>
#include <fstream>

#include <limbo/parsers/lp/bison/LpDriver.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/// @brief Custom class that inheritates @ref LpParser::LpDataBase 
/// with all the required callbacks defined. 
class LpDataBase : public LpParser::LpDataBase
{
	public:
        /// @brief use int64_t in base type 
		typedef LpParser::int64_t int64_t;
        /// @brief constructor 
		LpDataBase()
		{
			cout << "constructing LpDataBase" << endl;
		}
        /// @brief add variable that \a l <= \a vname <= \a r. 
        /// @param vname variable name 
        /// @param l lower bound 
        /// @param r upper bound 
		void add_variable(string const& vname, int64_t const& l, int64_t const& r) 
		{
			cout << l << " <= " << vname << " <= " << r << endl;
		}
        /// @brief add constraint that \a vname1 - \a vname2 >= \a constant. 
        /// @param vname1 first variable 
        /// @param vname2 second variable 
        /// @param constant constant value 
		void add_constraint(string const& vname1, string const& vname2, int64_t const& constant) 
		{
			cout << vname1 << " - " << vname2 << " >= " << constant << endl;
		}
        /// @brief add object terms that \a coef * \a vname 
        /// @param vname variable name 
        /// @param coef coefficient 
		void add_objective(string const& vname, int64_t const& coef) 
		{
			cout << " + " << coef << "*" << vname << endl;
		}
};

/// @brief test 1: use function wrapper @ref LpParser::read  
void test1(string const& filename)
{
	cout << "////////////// test1 ////////////////" << endl;
	LpDataBase db;
	LpParser::read(db, filename);
}

/// @brief test 2: use class wrapper @ref LpParser::Driver 
void test2(string const& filename)
{
	cout << "////////////// test2 ////////////////" << endl;
	LpDataBase db;
	LpParser::Driver driver (db);
	//driver.trace_scanning = true;
	//driver.trace_parsing = true;

	driver.parse_file(filename);
}

/// @brief main function 
/// @param argc number of arguments 
/// @param argv values of arguments 
/// @return 0 
int main(int argc, char** argv)
{
	if (argc > 1)
	{
		test1(argv[1]);
		test2(argv[1]);
	}
	else 
		cout << "at least 1 argument is required" << endl;

	return 0;
}
