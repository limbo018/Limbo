/*************************************************************************
    > File Name: ../test/test_driver.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 12 Nov 2014 03:01:03 PM CST
 ************************************************************************/

#include <iostream>
#include <limbo/parsers/gdsii/stream/GdsDriver.h>
using std::cout;
using std::endl;

struct DataBase : public GdsParser::GdsDriverDataBase
{
	DataBase()
	{
		cout << "constructing DataBase" << endl;
	}
	///////////////////// required callbacks /////////////////////
	virtual void add_gds_lib(GdsParser::GdsLib const& lib) 
	{
		cout << "library name = " << lib.lib_name << endl;
		cout << "library unit = " << lib.unit[0] << ", " << lib.unit[1] << endl;
		cout << "# CELL = " << lib.vCell.size() << endl;
		if (!lib.vCell.empty())
		{
			cout << "# BOUNDARY = " << lib.vCell.front().vBoundary.size() << endl;
			cout << "cell name = " << lib.vCell.front().cell_name << endl;
			for (unsigned int i = 0; i < lib.vCell.front().vBoundary.size(); ++i)
			{
				vector<GdsParser::GdsBoundary> const& vBoundary = lib.vCell.front().vBoundary;
				cout << "XY: ";
				for (unsigned int j = 0; j < vBoundary[i].vPoint.size(); ++j)
				{
					cout << vBoundary[i].vPoint[j][0] << ", " << vBoundary[i].vPoint[j][1] << endl;
				}
			}
			cout << "# TEXT = " << lib.vCell.front().vText.size() << endl;
		}
	}
};

int main(int argc, char** argv)
{
	DataBase db;
	if (argc > 1)
		cout << GdsParser::read(db, argv[1]) << endl;
	else cout << "at least 1 argument is required" << endl;

	return 0;
}
