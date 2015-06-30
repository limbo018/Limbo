
#include <iostream>
#include <fstream>

#include <limbo/parsers/verilog/bison/VerilogDriver.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class DataBase : public VerilogParser::VerilogDataBase
{
	public:
		DataBase()
		{
			cout << "DataBase::" << __func__ << endl;
		}
		//////////////////// required callbacks from abstract VerilogParser::VerilogDataBase ///////////////////
        virtual void verilog_instance_cbk(std::string const& macro_name, std::string inst_name, std::vector<VerilogParser::NetPin> const& vNetPin)
        {
			cout << __func__ << " => " << macro_name << ", " << inst_name << ", ";
            for (std::vector<VerilogParser::NetPin>::const_iterator it = vNetPin.begin(); it != vNetPin.end(); ++it)
                cout << it->pin << "(" << it->net << ") ";
            cout << endl;
        }
        virtual void verilog_net_declare_cbk(std::string const& net_name, VerilogParser::Range const& range)
		{
			cout << __func__ << " => " << net_name << " (" << range.low << ", " << range.high << ")" << endl;
		}
};

void test1(string const& filename)
{
	cout << "////////////// test1 ////////////////" << endl;
	DataBase db;
	VerilogParser::read(db, filename);
}

void test2(string const& filename)
{
	cout << "////////////// test2 ////////////////" << endl;
	DataBase db;
	VerilogParser::Driver driver (db);
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
