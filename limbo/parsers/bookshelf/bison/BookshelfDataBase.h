/**
 * @file   BookshelfDataBase.h
 * @brief  Database for Bookshelf parser 
 * @author Yibo Lin
 * @date   Oct 2014
 */

#ifndef BOOKSHELFPARSER_DATABASE_H
#define BOOKSHELFPARSER_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <limits>

/// namespace for BookshelfParser
namespace BookshelfParser {

/// @nowarn
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
/// @endnowarn

/// @brief bison does not support vector very well, 
/// so here create a dummy class for integer array. 
class IntegerArray : public vector<int>
{
	public: 
        /// @nowarn 
		typedef vector<int> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;
        /// @endnowarn

        /// constructor 
        /// @param alloc memory allocator 
		IntegerArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
        /// constructor 
        /// @param n number of values 
        /// @param val data value
        /// @param alloc memory allocator 
		IntegerArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
			: base_type(n, val, alloc) {}
};

/// @brief bison does not support vector very well, 
/// so here create a dummy class for string array. 
class StringArray : public vector<string>
{
	public: 
        /// @nowarn 
		typedef vector<string> base_type;
		using base_type::size_type;
		using base_type::value_type;
		using base_type::allocator_type;
        /// @endnowarn

        /// constructor 
        /// @param alloc memory allocator 
		StringArray(const allocator_type& alloc = allocator_type())
			: base_type(alloc) {}
        /// constructor 
        /// @param n number of values 
        /// @param val data value
        /// @param alloc memory allocator 
		StringArray(size_type n, const value_type& val, const allocator_type& alloc = allocator_type())
			: base_type(n, val, alloc) {}
};

/// @brief Temporary data structures to hold parsed data. 
/// Base class for all temporary data structures. 
struct Item 
{
    /// print data members 
	virtual void print(ostream&) const {};
    /// print data members with stream operator 
    /// @param ss output stream 
    /// @param rhs target object 
    /// @return output stream 
	friend ostream& operator<<(ostream& ss, Item const& rhs)
	{
		rhs.print(ss);
		return ss;
	}
};
/// @brief placement row 
struct Row : public Item
{
	int32_t origin[2]; ///< x, y
	string orient; ///< orientation 
    int32_t height; ///< row height 
	int32_t site_num; ///< number of sites 
	int32_t site_width; ///< width of a site 
    int32_t site_spacing; ///< spacing of a site 
    int32_t site_orient; ///< orientation of a site, one of these two will be valid  
    string site_orient_str; ///< orientation of a site in string
    int32_t site_symmetry; ///< symmetry of a site 
    string site_symmetry_str; ///< symmetry of a site in string 
    /// constructor 
    Row()
    {
        reset();
    }
    /// reset all data members 
	void reset()
	{
		orient = "";
		origin[0] = origin[1]  = -1;
        height = 0;
        site_num = 0;
        site_width = site_spacing = site_orient = site_symmetry = 0;
        site_orient_str = "";
        site_symmetry_str = "";
	}
    /// print data members 
    /// @param ss output stream 
	virtual void print(ostream& ss) const
	{
		ss << "//////// Row ////////" << endl
			<< "origin = " << origin[0] << " " << origin[1] << endl 
			<< "orient = " << orient << endl 
            << "site width = " << site_width << endl 
            << "site_spacing = " << site_spacing << endl 
            << "site_orient = " << site_orient << endl 
            << "site_orient_str = " << site_orient_str << endl
            << "site_symmetry = " << site_symmetry << endl
            << "site_symmetry_str = " << site_symmetry_str << endl;
	}
};
/// @brief describe a pin of a net 
struct NetPin : public Item 
{
    string node_name; ///< node name 
    string pin_name; ///< pin name 
    char direct; ///< direction 
    double offset[2]; ///< offset (x, y) to node origin 
    double size[2]; ///< sizes (x, y) of pin 

    /// constructor 
    NetPin()
    {
        node_name = "";
        pin_name = ""; 
        direct = '\0';
        offset[0] = 0; 
        offset[1] = 0; 
        size[0] = 0;
        size[1] = 0;
    }
    /// constructor 
    /// @param nn node name 
    /// @param d direction 
    /// @param x, y offset of pin to node origin 
    /// @param w, h size of pin 
    /// @param pn pin name 
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
    /// constructor 
    /// @param nn node name 
    /// @param d direction 
    /// @param x, y offset of pin to node origin 
    /// @param w, h size of pin 
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
    /// reset all data members 
    void reset()
    {
        node_name = "";
        pin_name = "";
        direct = 'I';
        offset[0] = offset[1] = 0;
        size[0] = size[1] = 0;
    }
};
/// @brief net to describe interconnection of netlist 
struct Net : public Item
{
	string net_name; ///< net name 
	vector<NetPin> vNetPin; ///< array of pins in the net 
    /// reset all data members 
	void reset()
	{
		net_name = "";
		vNetPin.clear();
	}
    /// print data members 
    /// @param ss output stream 
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

/// @brief shape box to describe one node shape 
struct ShapeBox : public Item 
{
    string name; ///< shape name 
    double origin[2]; ///< lower left corner of the box
    double size[2]; ///< width and height

    /// @brief constructor 
    /// @param n shape name 
    /// @param x lower left coordinate 
    /// @param y lower left coordinate 
    /// @param w width 
    /// @param h height 
    ShapeBox(string& n, double x, double y, double w, double h)
    {
        name.swap(n); 
        origin[0] = x; 
        origin[1] = y; 
        size[0] = w; 
        size[1] = h; 
    }
    /// reset all data members 
    void reset()
    {
        name = "";
        origin[0] = origin[1] = 0;
        size[0] = size[1] = 0;
    }
};

/// @brief node shape to describe the shapes of node 
struct NodeShape : public Item 
{
    string node_name; ///< node name 
    vector<ShapeBox> vShapeBox; 

    /// reset all data members 
	void reset()
	{
		node_name = "";
		vShapeBox.clear();
	}
    /// print data members 
    /// @param ss output stream 
	virtual void print(ostream& ss) const
	{
		ss << "//////// NodeShape ////////" << endl
			<< "node_name = " << node_name << endl; 
		for (uint32_t i = 0; i < vShapeBox.size(); ++i)
			ss << vShapeBox[i].name 
                << " @(" << vShapeBox[i].origin[0] << ", " << vShapeBox[i].origin[1] << ") "
                << " w/h (" << vShapeBox[i].size[0] << ", " << vShapeBox[i].size[1] << ")" 
                << endl;
		ss << endl;
	}
};

/// @brief describe (pin, layer) pair 
struct IOPinLayer : public Item 
{
    string pin_name; ///< pin name 
    int layer; ///< layer 

    /// @brief constructor 
    IOPinLayer(string& name, int l)
    {
        pin_name.swap(name); 
        layer = l; 
    }
    /// @brief reset all data members 
    void reset()
    {
        pin_name = "";
        layer = std::numeric_limits<int>::max();
    }
};

/// @brief describe blockage node name, blocked layer list 
struct BlockageLayer : public Item 
{
    string node_name; ///< node name 
    vector<int> vLayer; ///< layer list 

    /// @brief reset all data members 
    void reset()
    {
        node_name = "";
        vLayer.clear();
    }
};

/// @brief information for routing to describe .route 
/// refer to DAC 2012 contest 
/// http://archive.sigda.org/dac2012/contest/other_files/Benchmark_Description.pdf
struct RouteInfo : public Item 
{
    int numGrids[2]; ///< global routing grids in X and Y 
    int numLayers; ///< number of layers 
    vector<int> vVerticalCapacity; ///< vertical capacity at each layer 
    vector<int> vHorizontalCapacity; ///< horizontal capacity at each layer 
    vector<int> vMinWireWidth; ///< min wire width for each layer 
    vector<int> vMinWireSpacing; ///< min wire spacing for each layer 
    vector<int> vViaSpacing; ///< via spacing per layer 
    double gridOrigin[2]; ///< Absolute coordinates of the origin of the grid (grid_lowerleft_X grid_lowerleft_Y)
    double tileSize[2]; ///< tile_width, tile_height
    int blockagePorosity; ///< Porosity for routing blockages (Zero implies the blockage completely blocks overlapping routing tracks. Default = 0)

    /// @brief reset all data members 
    void reset()
    {
        numGrids[0] = numGrids[1] = 0; 
        numLayers = 0; 
        vVerticalCapacity.clear(); 
        vHorizontalCapacity.clear(); 
        vMinWireWidth.clear(); 
        vMinWireSpacing.clear(); 
        vViaSpacing.clear(); 
        gridOrigin[0] = gridOrigin[1] = 0; 
        tileSize[0] = tileSize[1] = 0; 
        blockagePorosity = 0; 
    }
    /// print data members 
    /// @param ss output stream 
	virtual void print(ostream& ss) const
	{
		ss << "//////// RouteInfo ////////" << endl;
        ss << "grids = " << numGrids[0] << ", " << numGrids[1] << endl; 
        ss << "numLayers = " << numLayers << endl; 
        ss << "vVerticalCapacity = ";
        for (unsigned int i = 0; i < vVerticalCapacity.size(); ++i)
            ss << vVerticalCapacity[i] << " ";
        ss << endl; 
        ss << "vHorizontalCapacity = ";
        for (unsigned int i = 0; i < vHorizontalCapacity.size(); ++i)
            ss << vHorizontalCapacity[i] << " ";
        ss << endl; 
        ss << "vMinWireWidth = ";
        for (unsigned int i = 0; i < vMinWireWidth.size(); ++i)
            ss << vMinWireWidth[i] << " ";
        ss << endl; 
        ss << "vMinWireSpacing = ";
        for (unsigned int i = 0; i < vMinWireSpacing.size(); ++i)
            ss << vMinWireSpacing[i] << " ";
        ss << endl; 
        ss << "vViaSpacing = ";
        for (unsigned int i = 0; i < vViaSpacing.size(); ++i)
            ss << vViaSpacing[i] << " ";
        ss << endl; 
        ss << "gridOrigin = " << gridOrigin[0] << ", " << gridOrigin[1] << endl; 
        ss << "tileSize = " << tileSize[0] << ", " << tileSize[1] << endl; 
        ss << "blockagePorosity = " << blockagePorosity << endl; 
	}
};

// forward declaration
/// @brief Base class for bookshelf database. 
/// Only pure virtual functions are defined.  
/// User needs to inheritate this class and derive a custom database type with all callback functions defined.  
class BookshelfDataBase
{
	public:
        /// @brief set number of terminals 
        virtual void resize_bookshelf_node_terminals(int, int) = 0;
        /// @brief set number of nets 
        virtual void resize_bookshelf_net(int) = 0;
        /// @brief set number of pins 
        virtual void resize_bookshelf_pin(int) = 0;
        /// @brief set number of rows 
        virtual void resize_bookshelf_row(int) = 0;
        /// @brief set number of shapes 
        virtual void resize_bookshelf_shapes(int);
        /// @brief set number of NI terminals with layers 
        virtual void resize_bookshelf_niterminal_layers(int);
        /// @brief set number of blockage nodes with layers 
        virtual void resize_bookshelf_blockage_layers(int);
        /// @brief add terminal 
        virtual void add_bookshelf_terminal(string&, int, int) = 0;
        /// @brief add terminal_NI
        virtual void add_bookshelf_terminal_NI(string&, int, int);
        /// @brief add node 
        virtual void add_bookshelf_node(string&, int, int, bool) = 0;
        /// @brief add net 
        virtual void add_bookshelf_net(Net const&) = 0;
        /// @brief add row 
        virtual void add_bookshelf_row(Row const&) = 0;
        /// @brief set node position 
        virtual void set_bookshelf_node_position(string const&, double, double, string const&, string const&, bool) = 0;
        /// @brief set net weight 
        virtual void set_bookshelf_net_weight(string const& name, double w);
        /// @brief set node shapes 
        virtual void set_bookshelf_shape(NodeShape const&); 
        /// @brief set routing information 
        virtual void set_bookshelf_route_info(RouteInfo const&);
        /// @brief set NI terminal with layers 
        virtual void add_bookshelf_niterminal_layer(string const&, string const&);
        /// @brief set blockages with layers 
        virtual void add_bookshelf_blockage_layers(string const&, vector<string> const&);
        /// @brief set design name 
        virtual void set_bookshelf_design(string&) = 0;
        /// @brief a callback when a bookshelf file reaches to the end 
        virtual void bookshelf_end() = 0;
    private:
        /// @brief remind users to define some optional callback functions at runtime 
        /// @param str message including the information to the callback function in the reminder 
        void bookshelf_user_cbk_reminder(const char* str) const;
};

} // namespace BookshelfParser

#endif
