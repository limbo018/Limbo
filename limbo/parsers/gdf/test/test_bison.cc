
#include <iostream>
#include <fstream>

#include <limbo/parsers/gdf/bison/GdfDriver.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class DataBase : public GdfParser::GdfDataBase
{
	public:
		DataBase()
		{
			cout << "DataBase::" << __func__ << endl;
		}
		//////////////////// required callbacks from abstract GdfParser::GdfDataBase ///////////////////
        virtual void add_gdf_cell(GdfParser::Cell& cell) 
        {
            cout << cell << endl;
        }
};

void test1(string const& filename)
{
	cout << "////////////// test1 ////////////////" << endl;
	DataBase db;
	GdfParser::read(db, filename);
}

void test2(string const& filename)
{
	cout << "////////////// test2 ////////////////" << endl;
	DataBase db;
	GdfParser::Driver driver (db);
	//driver.trace_scanning = true;
	//driver.trace_parsing = true;

	driver.parse_file(filename);
}

int main(int argc, char** argv)
{

	if (argc > 1)
	{
		test1(argv[1]);
		//test2(argv[1]);
	}
	else 
		cout << "at least 1 argument is required" << endl;

	return 0;
}
