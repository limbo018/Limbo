/*************************************************************************
    > File Name: test_gdsdb.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Tue 17 Jan 2017 10:12:44 PM CST
 ************************************************************************/

#include <iostream>
#include <limbo/parsers/gdsii/gdsdb/GdsIO.h>
#include <limbo/preprocessor/Msg.h>

int main(int argc, char** argv)
{
	if (argc > 2)
    {
        limbo::GdsParser::GdsDB db; 
        limbo::GdsParser::GdsReader reader (db); 
        limboAssert(reader(argv[1]));

        limbo::GdsParser::GdsWriter gw (db); 
        gw(argv[2]);
    }
	else std::cout << "at least 2 argument is required: input gds, output gds" << std::endl;

	return 0;
}
