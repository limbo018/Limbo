/*************************************************************************
    > File Name: VerilogDataBase.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 10 Oct 2014 11:49:28 PM CDT
 ************************************************************************/

#ifndef VERILOGPARSER_DATABASE_H
#define VERILOGPARSER_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <limits>

namespace VerilogParser {

enum PinType
{
    kINPUT = 0x1, 
    kOUTPUT = 0x2,
    kREG = 0x4
};

struct Range 
{
    int low; ///< min infinity if not specified
    int high;
    Range() {low = high = std::numeric_limits<int>::min();}
    Range(int l, int h) : low(l), high(h) {}
};

struct GeneralName
{
    std::string name; ///< empty if not specified
    Range range; ///< min infinity if not specified 

    GeneralName(std::string const& n = "") {name = n; range.low = range.high = std::numeric_limits<int>::min();}
    GeneralName(std::string const& n, int low, int high) {name = n; range.low = low; range.high = high;}
};

struct NetPin
{
    std::string net;
    std::string pin;
    Range range;

    NetPin(std::string& n, std::string& p, Range const& r = Range())
    {
        net.swap(n);
        pin.swap(p);
        range = r;
    }
};

class StringArray : public std::vector<std::string>
{
	public: 
		typedef std::vector<std::string> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;

		StringArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
		StringArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
			: base_type(n, val, alloc) {}
};

class GeneralNameArray : public std::vector<GeneralName>
{
	public: 
		typedef std::vector<GeneralName> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;

		GeneralNameArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
		GeneralNameArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
			: base_type(n, val, alloc) {}
};

// forward declaration
// base class for DataBase 
// only pure virtual functions are defined 
// user needs to heritate this class 
class VerilogDataBase
{
	public:
        virtual void verilog_instance_cbk(std::string const& macro_name, std::string const& inst_name, std::vector<NetPin> const& vNetPin) = 0;
        virtual void verilog_net_declare_cbk(std::string const& net_name, Range const& range) = 0;
        virtual void verilog_pin_declare_cbk(std::string const& pin_name, unsigned type, Range const& range) = 0;
};

} // namespace VerilogParser

#endif
