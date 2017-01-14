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
using std::string;

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
		virtual void lef_version_cbk(string const& v)
		{
			cout << "lef version = " << v << endl;
		}
		virtual void lef_version_cbk(double v) 
		{
			cout << "lef version = " << v << endl;
		}
		virtual void lef_dividerchar_cbk(string const& v)
		{
			cout << "lef dividechar = " << v << endl;
		}
		virtual void lef_units_cbk(LefParser::lefiUnits const& v)
		{
			v.print(stdout);
		}
		virtual void lef_manufacturing_cbk(double v)
		{
			cout << "lef manufacturing = " << v << endl;
		}
		virtual void lef_busbitchars_cbk(string const& v)
		{
			cout << "lef busbitchars = " << v << endl;
		}
		virtual void lef_layer_cbk(LefParser::lefiLayer const& v)
		{
			v.print(stdout);
		}
		virtual void lef_via_cbk(LefParser::lefiVia const& v)
		{
			v.print(stdout);
		}
		virtual void lef_viarule_cbk(LefParser::lefiViaRule const& v)
		{
			v.print(stdout);
		}
		virtual void lef_spacing_cbk(LefParser::lefiSpacing const& v)
		{
			v.print(stdout);
		}
		virtual void lef_site_cbk(LefParser::lefiSite const& v)
		{
			v.print(stdout);
		}
		virtual void lef_macro_cbk(LefParser::lefiMacro const& v)
		{
			v.print(stdout);
		}
		virtual void lef_prop_cbk(LefParser::lefiProp const& v)
        {
            v.print(stdout);
        }
		virtual void lef_maxstackvia_cbk(LefParser::lefiMaxStackVia const& v)
        {
            v.print(stdout);
        }
#if 0
        // deprecated 
		virtual void lef_obstruction_cbk(LefParser::lefiObstruction const& v)
		{
			v.print(stdout);
		}
#endif
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
		for (int i = 1; i < argc; ++i)
			test1(argv[i]);
	}
	else 
		cout << "at least 1 argument is required" << endl;

	return 0;
}

