/*************************************************************************
    > File Name: test_bison.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Sun 14 Dec 2014 10:27:31 AM CST
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

#include <limbo/parsers/lef/bison/LefDriver.h>

using std::cout;
using std::endl;

/// this is an recommended API for LefParser, which also matches to potential bison version in the future
/// actually spirit version of parser is based on template, so user does not necessarily need to inherit LefDataBase
class DataBase : public LefParser::LefDataBase
{
	public:
		typedef LefParser::LefDataBase base_type;

		DataBase() : base_type()
		{
			cout << "constructing DataBase" << endl;
		}
};

void test1(std::string const& filename)
{
	cout << "////////////// test1 ////////////////" << endl;
	DataBase db;
	if (LefParser::read(db, filename))
		cout << "read successfully" << endl;
	else cout << "read failed" << endl;
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

