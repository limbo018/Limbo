
#include <iostream>
#include <fstream>

#include <limbo/parsers/lp/bison/LpDriver.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class DataBase : public LpParser::LpDataBase
{
	public:
		typedef LpParser::int64_t int64_t;
		DataBase()
		{
			cout << "constructing DataBase" << endl;
		}
		void add_variable(string const& vname, int64_t const& l, int64_t const& r) 
		{
			cout << l << " <= " << vname << " <= " << r << endl;
		}
		void add_constraint(string const& vname1, string const& vname2, int64_t const& constant) 
		{
			cout << vname1 << " - " << vname2 << " >= " << constant << endl;
		}
		void add_objective(string const& vname, int64_t const& coef) 
		{
			cout << " + " << coef << "*" << vname << endl;
		}
};

void test1(string const& filename)
{
	cout << "////////////// test1 ////////////////" << endl;
	DataBase db;
	LpParser::read(db, filename);
}

void test2(string const& filename)
{
	cout << "////////////// test2 ////////////////" << endl;
	DataBase db;
	LpParser::Driver driver (db);
	//driver.trace_scanning = true;
	//driver.trace_parsing = true;

	driver.parse_file(filename);
}

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
