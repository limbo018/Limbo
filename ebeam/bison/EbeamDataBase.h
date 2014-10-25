/*************************************************************************
    > File Name: EbeamDataBase.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 10 Oct 2014 11:49:28 PM CDT
 ************************************************************************/

#ifndef EBEAMPARSER_DATABASE_H
#define EBEAMPARSER_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

namespace EbeamParser {

	using std::cout;
	using std::endl;
	using std::cerr;
	using std::string; 
	using std::vector;
	using std::pair;
	using std::make_pair;
	using std::ostringstream;
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
struct EbeamBoundary : public Item
{
	double offset;
	double width;
	double step;
	vector<int32_t> vLayerId;
	vector<string> vLayer;
	EbeamBoundary() {reset();}
	void reset()
	{
		offset = 0;
		width = 0;
		step = 0;
		vLayerId.clear();
		vLayer.clear();
	}
	virtual void print(ostringstream& ss) const
	{
		ss << "//////// EbeamBoundary ////////" << endl
			<< "offset = " << offset << endl 
			<< "width = " << width << endl 
			<< "step = " << step << endl
			<< "vLayerId = ";
		for (vector<int32_t>::const_iterator it = vLayerId.begin(); it != vLayerId.end(); ++it)
			ss << *it << "\t";
		ss << endl;
		ss << "vLayer = ";
		for (vector<string>::const_iterator it = vLayer.begin(); it != vLayer.end(); ++it)
			ss << *it << "\t";
	}
};
struct ConfSite : public Item
{
	string confsite_name;
	int32_t layer_id;
	string layer;
	vector<int32_t> vSiteCnt;
	ConfSite() {reset();}
	void reset()
	{
		confsite_name = "";
		layer_id = -1;
		layer = "";
		vSiteCnt.clear();
	}
	virtual void print(ostringstream& ss) const
	{
		ss << "//////// ConfSite ////////" << endl;
		ss << "confsite_name = " << confsite_name << endl;
		ss << "layer_id = " << layer_id << endl;
		ss << "layer = " << layer << endl;
		ss << "vSiteCnt = ";
		for (vector<int32_t>::const_iterator it = vSiteCnt.begin(); it != vSiteCnt.end(); ++it)
			ss << *it << "\t";
		ss << endl;
	}
};
struct Macro : public Item 
{
	string macro_name;
	vector<ConfSite> vConfSite;
	void reset()
	{
		macro_name = "";
		vConfSite.clear();
	}
	virtual void print(ostringstream& ss) const
	{
		ss << "//////// Macro ////////" << endl;
		ss << "macro_name = " << macro_name << endl;
		for (vector<ConfSite>::const_iterator it = vConfSite.begin(); it != vConfSite.end(); ++it)
			ss << *it << endl;
	}
};

// forward declaration
// base class for DataBase 
// only pure virtual functions are defined 
// user needs to heritate this class 
class EbeamDataBase
{
	public:
		virtual void set_ebeam_unit(int) = 0;
		virtual void set_ebeam_boundary(EbeamBoundary const&) = 0;
		virtual void add_ebeam_macro(Macro const&) = 0;
};

} // namespace DefParser

#endif
