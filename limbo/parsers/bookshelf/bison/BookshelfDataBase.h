/*************************************************************************
    > File Name: BookshelfDataBase.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 10 Oct 2014 11:49:28 PM CDT
 ************************************************************************/

#ifndef BOOKSHELFPARSER_DATABASE_H
#define BOOKSHELFPARSER_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

namespace BookshelfParser {

	using std::cout;
	using std::endl;
	using std::cerr;
	using std::string; 
	using std::vector;
	using std::pair;
	using std::make_pair;
	using std::ostream;
	typedef int int32_t;
	typedef unsigned int uint32_t;
	typedef long int64_t;

// bison does not support vector very well 
// so here create a dummy class 
class IntegerArray : public vector<int>
{
	public: 
		typedef vector<int> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;

		IntegerArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
		IntegerArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
			: base_type(n, val, alloc) {}
};

class StringArray : public vector<string>
{
	public: 
		typedef vector<string> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;

		StringArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
		StringArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
			: base_type(n, val, alloc) {}
};

// temporary data structures to hold parsed data 
struct Item 
{
	virtual void print(ostream&) const {};
	friend ostream& operator<<(ostream& ss, Item const& rhs)
	{
		rhs.print(ss);
		return ss;
	}
};
struct Row : public Item
{
	int32_t origin[2]; // x, y
	string orient;
    int32_t height;
	int32_t site_num; 
	int32_t site_width; 
    int32_t site_spacing;
    int32_t site_orient;
    int32_t site_symmetry;
    Row()
    {
        reset();
    }
	void reset()
	{
		orient = "";
		origin[0] = origin[1]  = -1;
        height = 0;
        site_num = 0;
        site_width = site_spacing = site_orient = site_symmetry = 0;
	}
	virtual void print(ostream& ss) const
	{
		ss << "//////// Row ////////" << endl
			<< "origin = " << origin[0] << " " << origin[1] << endl 
			<< "orient = " << orient << endl 
            << "site width = " << site_width << endl 
            << "site_spacing = " << site_spacing << endl 
            << "site_orient = " << site_orient << endl 
            << "site_symmetry = " << site_symmetry << endl;
	}
};
struct NetPin : public Item 
{
    string node_name; 
    string pin_name; 
    char direct; 
    double offset[2]; 
    double size[2];

    NetPin(string& nn, char d, double x, double y, double w, double h, string& pn)
    {
        node_name.swap(nn);
        direct = d;
        offset[0] = x;
        offset[1] = y;
        size[0] = w;
        size[1] = h;
        pin_name.swap(pn);
    }
    NetPin(string& nn, char d, double x, double y, double w, double h)
    {
        node_name.swap(nn);
        direct = d;
        offset[0] = x;
        offset[1] = y;
        size[0] = w;
        size[1] = h;
        pin_name.clear();
    }
    void reset()
    {
        node_name = "";
        pin_name = "";
        direct = 'I';
        offset[0] = offset[1] = 0;
        size[0] = size[1] = 0;
    }
};
struct Net : public Item
{
	string net_name;
	vector<NetPin> vNetPin;
	void reset()
	{
		net_name = "";
		vNetPin.clear();
	}
	virtual void print(ostream& ss) const
	{
		ss << "//////// Net ////////" << endl
			<< "net_name = " << net_name << endl; 
		for (uint32_t i = 0; i < vNetPin.size(); ++i)
			ss << "(" << vNetPin[i].node_name << ", " << vNetPin[i].pin_name << ") " 
                << vNetPin[i].direct << " @(" << vNetPin[i].offset[0] << ", " << vNetPin[i].offset[1] << ")";
		ss << endl;
	}
};
// forward declaration
// base class for DataBase 
// only pure virtual functions are defined 
// user needs to heritate this class 
class BookshelfDataBase
{
	public:
        virtual void resize_bookshelf_node_terminals(int, int) = 0;
        virtual void resize_bookshelf_net(int) = 0;
        virtual void resize_bookshelf_pin(int) = 0;
        virtual void resize_bookshelf_row(int) = 0;
        virtual void add_bookshelf_terminal(string&, int, int) = 0;
        virtual void add_bookshelf_node(string&, int, int) = 0;
        virtual void add_bookshelf_net(Net const&) = 0;
        virtual void add_bookshelf_row(Row const&) = 0;
        virtual void set_bookshelf_node_position(string const&, double, double, string const&, string const&) = 0;
        virtual void set_bookshelf_design(string&) = 0;
};

} // namespace BookshelfParser

#endif
