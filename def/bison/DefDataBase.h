/*************************************************************************
    > File Name: DefDataBase.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 10 Oct 2014 11:49:28 PM CDT
 ************************************************************************/

#ifndef DEFPARSER_DATABASE_H
#define DEFPARSER_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

namespace DefParser {

	using std::cout;
	using std::endl;
	using std::cerr;
	using std::string; 
	using std::vector;
	using std::pair;
	using std::make_pair;
	using std::ostringstream;
	typedef short int int8_t;
	typedef int int32_t;
	typedef unsigned int uint32_t;
	typedef long int64_t;
	typedef unsigned short int uint8_t;

// temporary data structures to hold parsed data 
struct Item 
{
	virtual void print(ostringstream&) const {};
	friend std::ostream& operator<<(std::ostream& os, Item const& rhs)
	{
		std::ostringstream ss;
		rhs.print(ss);
		os << ss.str();
		return os;
	}
	friend ostringstream& operator<<(ostringstream& ss, Item const& rhs)
	{
		rhs.print(ss);
		return ss;
	}
};
struct Row : public Item
{
	string row_name;
	string macro_name;
	int32_t origin[2]; // x, y
	string orient;
	int32_t repeat[2]; // do x by y  
	int32_t step[2]; // x, y
	void reset()
	{
		row_name = macro_name = orient = "";
		origin[0] = origin[1]  = -1;
		repeat[0] = repeat[1] = -1;
		step[0] = step[1] = -1;
	}
	virtual void print(ostringstream& ss) const
	{
		ss << "//////// Row ////////" << endl
			<< "row_name = " << row_name << endl 
			<< "macro_name = " << macro_name << endl 
			<< "origin = " << origin[0] << " " << origin[1] << endl 
			<< "orient = " << orient << endl 
			<< "repeat = " << repeat[0] << " " << repeat[1] << endl 
			<< "step = " << step[0] << " " << step[1] << endl; 
	}
};
struct Component : public Item
{
	string comp_name;
	string macro_name;
	string status;
	int32_t origin[2];
	string orient;
	void reset()
	{
		comp_name = macro_name = status = orient = "";
		origin[0] = origin[1] = -1;
	}
	virtual void print(ostringstream& ss) const
	{
		ss << "//////// Component ////////" << endl
			<< "comp_name = " << comp_name << endl 
			<< "macro_name = " << macro_name << endl 
			<< "status = " << status << endl 
			<< "origin = " << origin[0] << " " << origin[1] << endl 
			<< "orient = " << orient << endl; 
	}
};
struct Pin : public Item
{
	string pin_name;
	string net_name;
	string direct;
	string status; 
	int32_t origin[2];
	string orient; 
	string layer_name;
	int32_t bbox[4];
	void reset()
	{
		pin_name = net_name = direct = status = orient = layer_name = "";
		origin[0] = origin[1] = -1;
		bbox[0] = bbox[1] = bbox[2] = bbox[3] = -1;
	}
	virtual void print(ostringstream& ss) const
	{
		ss << "//////// Pin ////////" << endl
			<< "pin_name = " << pin_name << endl 
			<< "net_name = " << net_name << endl 
			<< "direct = " << direct << endl 
			<< "status = " << status << endl 
			<< "origin = " << origin[0] << " " << origin[1] << endl 
			<< "orient = " << orient << endl
			<< "layer_name = " << layer_name << endl 
			<< "bbox = " << bbox[0] << " " << bbox[1] << " " << bbox[2] << " " << bbox[3] << endl;
	}
};
struct Net : public Item
{
	string net_name;
	vector< std::pair<string, string> > vNetPin;
	void reset()
	{
		net_name = "";
		vNetPin.clear();
	}
	virtual void print(ostringstream& ss) const
	{
		ss << "//////// Net ////////" << endl
			<< "net_name = " << net_name << endl; 
		for (uint32_t i = 0; i < vNetPin.size(); ++i)
			ss << "(" << vNetPin[i].first << ", " << vNetPin[i].second << ") ";
		ss << endl;
	}
};
// forward declaration
// base class for DataBase 
// only pure virtual functions are defined 
// user needs to heritate this class 
class DefDataBase
{
	public:
		virtual void set_def_dividerchar(string const&) = 0;
		virtual void set_def_busbitchars(string const&) = 0;
		virtual void set_def_version(string const&) = 0;
		virtual void set_def_design(string const&) = 0;
		virtual void set_def_unit(int) = 0;
		virtual void set_def_diearea(int, int, int, int) = 0;
		virtual void add_def_row(Row const&) = 0;
		virtual void add_def_component(Component const&) = 0;
		virtual void resize_def_component(int) = 0;
		virtual void add_def_pin(Pin const&) = 0;
		virtual void resize_def_pin(int)  = 0;
		virtual void add_def_net(Net const&) = 0;
		virtual void resize_def_net(int) = 0;
};

} // namespace DefParser

#endif
