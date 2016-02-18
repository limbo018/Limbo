// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the example::Driver class. */

#include "BookshelfDriver.h"
#include "BookshelfScanner.h"

namespace BookshelfParser {

Driver::Driver(BookshelfDataBase& db)
    : trace_scanning(false),
      trace_parsing(false),
      m_db(db)
{
}

bool Driver::parse_stream(std::istream& in, const std::string& sname)
{
    streamname = sname;

    Scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    Parser parser(*this);
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool Driver::parse_file(const std::string &filename)
{
    std::ifstream in(filename.c_str());
    if (!in.good()) return false;
    return parse_stream(in, filename);
}

bool Driver::parse_string(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::error(const class location& l,
		   const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void Driver::error(const std::string& m)
{
    std::cerr << m << std::endl;
}

// .nodes file 
void Driver::numNodeCbk(int n)
{
    m_db.resize_bookshelf_node(n);
}
void Driver::numTerminalsCbk(int n)
{
    m_db.resize_bookshelf_terminals(n);
}
void Driver::terminalEntryCbk(string& name, int w, int h)
{
    m_db.add_bookshelf_terminal(name, w, h);
}
void Driver::nodeEntryCbk(string& name, int w, int h, string&)
{
    m_db.add_bookshelf_node(name, w, h);
}
void Driver::nodeEntryCbk(string& name, int w, int h)
{
    m_db.add_bookshelf_node(name, w, h);
}
// .nets file 
void Driver::numNetCbk(int n)
{
    m_db.resize_bookshelf_net(n);
}
void Driver::numPinCbk(int n)
{
    m_db.resize_bookshelf_pin(n);
}
void Driver::netPinEntryCbk(string& node_name, char direct, double offsetX, double offsetY, double w, double h, string& pin_name)
{
    // not sure whether w or h has the correct meaning 
    m_net.vNetPin.push_back(NetPin(node_name, direct, offsetX, offsetY, w, h, pin_name));
}
void Driver::netPinEntryCbk(string& node_name, char direct, double offsetX, double offsetY)
{
    m_net.vNetPin.push_back(NetPin(node_name, direct, offsetX, offsetY, 0, 0));
}
void Driver::netNameAndDegreeCbk(string& net_name, int degree)
{
    m_net.net_name.swap(net_name);
    m_net.vNetPin.clear();
    m_net.vNetPin.reserve(degree);
}
void Driver::netEntryCbk()
{
    m_db.add_bookshelf_net(m_net);
    m_net.reset();
}
// .pl file 
void Driver::plNodeEntryCbk(string& node_name, int x, int y, string& orient, string& status)
{
    m_db.set_bookshelf_node_position(node_name, x, y, orient, status);
}
void Driver::plNodeEntryCbk(string& node_name, int x, int y, string& orient)
{
    m_db.set_bookshelf_node_position(node_name, x, y, orient, "MOVABLE");
}
// .scl file 
void Driver::sclNumRows(int n)
{
    m_db.resize_bookshelf_row(n);
}
void Driver::sclCoreRowStart(string const& orient)
{
    m_row.orient = orient;
}
void Driver::sclCoreRowCoordinate(int y)
{
    m_row.origin[1] = y;
}
void Driver::sclCoreRowHeight(int h)
{
    m_row.height = h;
}
void Driver::sclCoreRowSitewidth(int site_width)
{
    m_row.site_width = site_width;
}
void Driver::sclCoreRowSitespacing(int site_spacing)
{
    m_row.site_spacing = site_spacing;
}
void Driver::sclCoreRowSiteorient(int site_orient)
{
    m_row.site_orient = site_orient;
}
void Driver::sclCoreRowSitesymmetry(int site_symmetry)
{
    m_row.site_symmetry = site_symmetry;
}
void Driver::sclCoreRowSubRowOrigin(int x)
{
    m_row.origin[0] = x;
}
void Driver::sclCoreRowNumSites(int site_num)
{
    m_row.site_num = site_num;
}
void Driver::sclCoreRowEnd()
{
    m_db.add_bookshelf_row(m_row);
    m_row.reset();
}
// .wts file 
// .aux file 
void Driver::auxCbk(string& design_name, vector<string>& vBookshelfFiles)
{
    m_db.set_bookshelf_design(design_name);
}

bool read(BookshelfDataBase& db, const string& auxFile)
{
	Driver driver (db);
	//driver.trace_scanning = true;
	//driver.trace_parsing = true;

	return driver.parse_file(auxFile);
}

} // namespace example
