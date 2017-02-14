/**
 * @file   LpDriver.cc
 * @author Yibo Lin
 * @date   Oct 2014
 * @brief  Implementation of @ref LpParser::Driver
 */

#include <limits>
#include "LpDriver.h"
#include "LpScanner.h"

namespace LpParser {

Driver::Driver(LpDataBase& db)
    : trace_scanning(false),
      trace_parsing(false),
      m_db(db)
{
}

bool Driver::parse_stream(std::istream& in, const std::string& sname)
{
    streamname = sname;

    Scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    Parser parser(*this);
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool Driver::parse_file(const std::string &filename)
{
    std::ifstream in(filename.c_str());
    if (!in.good()) return false;
    return parse_stream(in, filename);
}

bool Driver::parse_string(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::error(const class location& l,
		   const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void Driver::error(const std::string& m)
{
    std::cerr << m << std::endl;
}

// coef*var 
void Driver::obj_cbk(int64_t coef, string const& var)
{
	m_db.add_variable(var);
	m_db.add_objective(var, coef);
}
// coef1*var1 + coef2*var2 >= constant 
void Driver::constraint_cbk(int64_t coef1, string const& var1, int64_t coef2, string const& var2, int64_t constant)
{
	assert(coef1 == -coef2 && coef1 != 0);
	m_db.add_variable(var1);
	m_db.add_variable(var2);

	if (coef1 > 0)
		m_db.add_constraint(var1, var2, constant/coef1);
	else 
		m_db.add_constraint(var2, var1, constant/coef2);
}
// var compare_op constant 
void Driver::bound_cbk(string const& var, int64_t compare, int64_t constant)
{
	if (compare > 0)
		m_db.add_variable(var, constant, std::numeric_limits<int64_t>::max());
	else 
		m_db.add_variable(var, std::numeric_limits<int64_t>::min(), constant);
}
// generals type (integer)
void Driver::generals_cbk(StringArray const&)
{}
// binary type  
void Driver::binary_cbk(StringArray const&)
{}

bool read(LpDataBase& db, const string& lpFile)
{
	Driver driver (db);
	//driver.trace_scanning = true;
	//driver.trace_parsing = true;

	return driver.parse_file(lpFile);
}

} // namespace example
