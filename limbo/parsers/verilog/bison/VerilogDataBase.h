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
    int low; 
    int high;
    Range() {low = 0; high = 0;}
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
        virtual void verilog_instance_cbk(std::string const& macro_name, std::string const& inst_name, std::vector<NetPin> const& vNetPin) = 0;
        virtual void verilog_net_declare_cbk(std::string const& net_name, Range const& range) = 0;
        virtual void verilog_pin_declare_cbk(std::string const& pin_name, unsigned type, Range const& range) = 0;
};

} // namespace VerilogParser

#endif
