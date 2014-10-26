/*************************************************************************
    > File Name: test_spirit.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Sun 26 Oct 2014 02:49:27 AM CDT
 ************************************************************************/

#include <iostream>
#include <string>

#include <limbo/parsers/tf/spirit/TfParser.h>

using std::cout;
using std::endl;
using std::string;

struct DataBase : public TfParser::TfDataBase
{
	void add_tf_layer_id(string const& s1, int32_t const& s2, string const& s3)
	{
		cout << __func__ << endl; 
		cout << s1 << ", " << s2 << ", " << s3 << endl;
	}
};

void test1(string const& filename)
{
	cout << "////////////// test1 ////////////////" << endl;
	DataBase db;
	TfParser::read(db, filename);
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
