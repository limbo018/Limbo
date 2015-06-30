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

struct Range 
{
    int low; 
    int high;
    Range() {low = std::numeric_limits<int>::min(); high = std::numeric_limits<int>::max();}
    Range(int l, int h) : low(l), high(h) {}
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

// forward declaration
// base class for DataBase 
// only pure virtual functions are defined 
// user needs to heritate this class 
class VerilogDataBase
{
	public:
        virtual void verilog_instance_cbk(std::string const& macro_name, std::string inst_name, std::vector<NetPin> const& vNetPin) = 0;
        virtual void verilog_net_declare_cbk(std::string const& net_name, Range const& range) = 0;
};

} // namespace VerilogParser

#endif
