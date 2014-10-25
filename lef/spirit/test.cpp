
#include <iostream>
#include <fstream>

#include "LefParser.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class DataBase : public LefParser::LefDataBase
{
	public:
		DataBase()
		{
			cout << "constructing DataBase" << endl;
		}
		///////////////// required callback ////////////////
		virtual void set_ebeam_unit(int token) 
		{
			cout << __func__ << " => " << token << endl;
		}
		virtual void set_ebeam_boundary(EbeamParser::EbeamBoundary const&) 
		{
			cout << __func__ << endl;
		}
		virtual void add_ebeam_macro(EbeamParser::Macro const&) 
		{
			cout << __func__ << endl;
		}
};

void test1(string const& filename)
{
	cout << "////////////// test1 ////////////////" << endl;
	DataBase db;
	LefParser::read(db, filename);
}

int main(int argc, char** argv)
{

	if (argc > 1)
	{
		test1(argv[1]);
	}
	else 
		cout << "at least 1 argument is required" << endl;

	return 0;
}
