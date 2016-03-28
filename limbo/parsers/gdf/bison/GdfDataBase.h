/*************************************************************************
    > File Name: GdfDataBase.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 10 Oct 2014 11:49:28 PM CDT
 ************************************************************************/

#ifndef GDFPARSER_DATABASE_H
#define GDFPARSER_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

/// =============================================================
/// main DataBase for GDF parser 
/// see http://cadlab.cs.ucla.edu/~pubbench/routing/.index.html
/// for the format of GDF file. 
/// It is an academic format for routing. 
/// =============================================================

namespace GdfParser {

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

class NumberArray : public vector<double>
{
	public: 
		typedef vector<double> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;

		NumberArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
		NumberArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
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

struct Point : public Item 
{
    double x;
    double y;

    Point() 
    {
        reset();
    }
    void reset() 
    {
        x = y = 0.0;
    }
    virtual void print(ostream& ss) const 
    {
        ss << "(" << x << "," << y << ")";
    }
};

struct CellPort : public Item
{
    enum PortTypeEnum 
    {
        IN, 
        OUT, 
        INOUT, 
        POWER, 
        GROUND, 
        UNKNOWN
    };
    string name; 
    string layer; 
    Point point;
    PortTypeEnum portType; 

    CellPort() 
    {
        reset();
    }
    void reset()
    {
        name.clear();
        layer.clear();
        point.reset();
        portType = UNKNOWN;
    }
    inline friend ostream& operator<<(ostream& ss, CellPort::PortTypeEnum portType) 
    {
        switch (portType) 
        {
            case CellPort::IN: 
                ss << "IN"; break; 
            case CellPort::OUT: 
                ss << "OUT"; break; 
            case CellPort::INOUT: 
                ss << "INOUT"; break; 
            case CellPort::POWER: 
                ss << "POWER"; break; 
            case CellPort::GROUND: 
                ss << "GROUND"; break; 
            case CellPort::UNKNOWN: 
            default:
                ss << "UNKNOWN"; break; 
        }
        return ss;
    }

    virtual void print(ostream& ss) const 
    {
		ss << "//////// CellPort ////////" << endl
           << "name = " << name << endl 
           << "layer = " << layer << endl 
           << "point = " << point << endl 
           << "type = " << portType << endl;
    }
};

struct CellInstance : public Item 
{
    std::string name; 
    std::string cellType; 
    Point position; 
    int32_t orient; 

    void reset()
    {
        name.clear();
        cellType.clear();
        position.reset();
        orient = 0;
    }

    virtual void print(ostream& ss) const 
    {
		ss << "//////// CellInstance ////////" << endl
           << "name = " << name << endl 
           << "cellType = " << cellType << endl 
           << "position = " << position << endl 
           << "orient = " << orient << endl;
    }
};

struct PathObj : public Item 
{
    enum PathObjTypeEnum 
    {
        SEGMENT, 
        VIA, 
        STRING, 
        UNKNOWN
    };
    PathObjTypeEnum pathObjType; 
    std::string name; ///< only valid when pathObjType is STRING
    std::string layer; 
    double width; 
    Point startPoint; 
    Point endPoint; ///< not always valid 

    PathObj()
    {
        reset();
    }
    void reset()
    {
        pathObjType = UNKNOWN;
        name.clear();
        layer.clear();
        width = 0;
        startPoint.reset();
        endPoint.reset();
    }
};

struct Path : public Item
{
    std::string name; 
    std::vector<PathObj> vPathObj; 

    Path()
    {
        reset();
    }
    void reset()
    {
        name.clear();
        vPathObj.clear();
    }
    virtual void print(ostream& ss) const 
    {
		ss << "//////// Path ////////" << endl
			<< "name = " << name << endl; 
        ss << "path objects\n";
		for (uint32_t i = 0; i < vPathObj.size(); ++i)
			ss << "name = " << vPathObj[i].name  << " "
               << "layer = " << vPathObj[i].layer << " "
               << "width = " << vPathObj[i].width  << " "
               << "startPoint = " << vPathObj[i].startPoint  << " "
               << "endPoint = " << vPathObj[i].endPoint << " "
               << endl;
    }
};

struct Text : public Item 
{
    enum TextTypeEnum 
    {
        NUMBER_OF_LAYERS, 
        WIRE_SPACINGS, 
        VIA_SPACINGS, 
        WIRE_WIDTHS, 
        VIA_WIDTHS, 
        VERTICAL_WIRE_COSTS, 
        HORIZONTAL_WIRE_COSTS, 
        VIA_COSTS, 
        STRING, 
        UNKNOWN
    };

    TextTypeEnum textType; 
    std::string name; ///< more information for textType
    std::string content; 

    Text() 
    {
        reset();
    }
    void reset()
    {
        textType = UNKNOWN;
        content.clear();
    }
    virtual void print(ostream& ss) const 
    {
		ss << "//////// Text ////////" << endl
			<< "name = " << name << endl; 
        ss << "content = " << content << endl; 
    }
};

struct NetPort : public Item 
{
    std::string name; 
    std::string instName; ///< empty for PI/PO  

    NetPort()
    {
        reset();
    }
    void reset()
    {
        name.clear();
        instName.clear();
    }
};
struct Net : public Item 
{
    std::string name; 
    std::vector<NetPort> vNetPort; 

    Net() 
    {
        reset();
    }
    void reset()
    {
        name.clear();
        vNetPort.clear();
    }
    virtual void print(ostream& ss) const 
    {
		ss << "//////// Net ////////" << endl
			<< "name = " << name << endl; 
		for (uint32_t i = 0; i < vNetPort.size(); ++i)
			ss << "(" << vNetPort[i].name << ", " << vNetPort[i].instName << ") ";
		ss << endl;
    }
};

struct Cell : public Item 
{
    std::string name; 
    std::vector<CellPort> vCellPort; 
    std::vector<Path> vPath; 
    std::vector<CellInstance> vCellInstance; 
    std::vector<Net> vNet; 
    std::vector<Text> vText; 

    Cell()
    {
        reset();
    }
    void reset()
    {
        name.clear();
        vCellPort.clear();
        vPath.clear();
        vCellInstance.clear();
        vNet.clear();
        vText.clear();
    }
    virtual void print(ostream& ss) const 
    {
        ss << "//////// Cell ////////" << endl
            << "name = " << name << endl; 
        for (uint32_t i = 0; i < vCellPort.size(); ++i)
            ss << vCellPort[i];
        for (uint32_t i = 0; i < vPath.size(); ++i)
            ss << vPath[i];
        for (uint32_t i = 0; i < vCellInstance.size(); ++i)
            ss << vCellInstance[i];
        for (uint32_t i = 0; i < vNet.size(); ++i)
            ss << vNet[i];
        for (uint32_t i = 0; i < vText.size(); ++i)
            ss << vText[i];
        ss << endl;
    }
};

// forward declaration
// base class for DataBase 
// only pure virtual functions are defined 
// user needs to heritate this class 
class GdfDataBase
{
	public:
        /// it is safe to directly swap the contents in the cell for efficiency  
        virtual void add_gdf_cell(Cell&) = 0;
};

} // namespace GdfParser

#endif
