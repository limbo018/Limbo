
#include <iostream>
#include <fstream>

#include <limbo/parsers/bookshelf/bison/BookshelfDriver.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class DataBase : public BookshelfParser::BookshelfDataBase
{
	public:
		DataBase()
		{
			cout << "DataBase::" << __func__ << endl;
		}
		//////////////////// required callbacks from abstract BookshelfParser::BookshelfDataBase ///////////////////
        virtual void resize_bookshelf_node_terminals(int nn, int nt) 
        {
            cout << __func__ << " => " << nn << ", " << nt << endl;
        }
        virtual void resize_bookshelf_net(int n)
        {
            cout << __func__ << " => " << n << endl;
        }
        virtual void resize_bookshelf_pin(int n)
        {
            cout << __func__ << " => " << n << endl;
        }
        virtual void resize_bookshelf_row(int n)
        {
            cout << __func__ << " => " << n << endl;
        }
        virtual void add_bookshelf_terminal(string& name, int w, int h)
        {
            cout << __func__ << " => " << name << ", " << w << ", " << h << endl;
        }
        virtual void add_bookshelf_node(string& name, int w, int h)
        {
            cout << __func__ << " => " << name << ", " << w << ", " << h << endl;
        }
        virtual void add_bookshelf_net(BookshelfParser::Net const& net)
        {
            net.print(cout);
        }
        virtual void add_bookshelf_row(BookshelfParser::Row const& row)
        {
            row.print(cout);
        }
        virtual void set_bookshelf_node_position(string const& name, double x, double y, string const& orient, string const& status)
        {
            cout << __func__ << " => " << name << ", " << x << ", " << y << ", " << orient << ", " << status << endl;
        }
        virtual void set_bookshelf_design(string& name)
        {
            cout << __func__ << " => " << name << endl;
        }
};

void test1(string const& filename)
{
	cout << "////////////// test1 ////////////////" << endl;
	DataBase db;
	BookshelfParser::read(db, filename);
}

void test2(string const& filename)
{
	cout << "////////////// test2 ////////////////" << endl;
	DataBase db;
	BookshelfParser::Driver driver (db);
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
