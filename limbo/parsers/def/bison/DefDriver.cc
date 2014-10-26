// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the example::Driver class. */

#include "DefDriver.h"
#include "DefScanner.h"

namespace DefParser {

Driver::Driver(DefDataBase& db)
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

void Driver::dividerchar_cbk(string const& s) 
{
	m_db.set_def_dividerchar(s);
}
void Driver::busbitchars_cbk(string const& s)
{
	m_db.set_def_busbitchars(s);
}
void Driver::version_cbk(double v) 
{
	// use stringstream to convert double to string 
	std::stringstream ss;
	ss << v;
	m_db.set_def_version(ss.str());
}
void Driver::design_cbk(string const& s) 
{
	m_db.set_def_design(s);
}
void Driver::unit_cbk(int v) 
{
	m_db.set_def_unit(v);
}
void Driver::diearea_cbk(int xl, int yl, int xh, int yh) 
{
	m_db.set_def_diearea(xl, yl, xh, yh);
}

void Driver::row_cbk(string const& row_name, string const& macro_name, 
		int originx, int originy, string const& orient, 
		int repeatx, int repeaty, int stepx, int stepy) 
{
	m_row.row_name = row_name; 
	m_row.macro_name = macro_name;
	m_row.origin[0] = originx; 
	m_row.origin[1] = originy; 
	m_row.orient = orient;
	m_row.repeat[0] = repeatx; m_row.repeat[1] = repeaty;
	m_row.step[0] = stepx; m_row.step[1] = stepy;
	m_db.add_def_row(m_row);
#ifdef DEBUG_DEFPARSER
	std::cerr << m_row << std::endl;
#endif 
	m_row.reset();
}
void Driver::component_cbk(string const& comp_name, string const& macro_name, string const& status) 
{
	m_comp.comp_name = comp_name;
	m_comp.macro_name = macro_name;
	m_comp.status = status;
	assert(status == "UNPLACED");
	m_db.add_def_component(m_comp);
#ifdef DEBUG_DEFPARSER
	std::cerr << m_comp << std::endl;
#endif 
	m_comp.reset();
}
void Driver::component_cbk(string const& comp_name, string const& macro_name, 
		string const& status, int originx, int originy, string const& orient) 
{
	m_comp.comp_name = comp_name;
	m_comp.macro_name = macro_name;
	m_comp.status = status;
	m_comp.origin[0] = originx; m_comp.origin[1] = originy;
	m_comp.orient = orient;
	m_db.add_def_component(m_comp);
#ifdef DEBUG_DEFPARSER
	std::cerr << m_comp << std::endl;
#endif 
	m_comp.reset();
}
void Driver::component_cbk_size(int size) 
{
	m_db.resize_def_component(size);
}
void Driver::pin_cbk(string const& pin_name, string const& net_name, string const& direct, string const& status, 
		int originx, int originy, string const& orient, string const& layer_name, int xl, int yl, int xh, int yh) 
{
	m_pin.pin_name = pin_name;
	m_pin.net_name = net_name;
	m_pin.direct = direct;
	m_pin.status = status;
	m_pin.origin[0] = originx; m_pin.origin[1] = originy;
	m_pin.orient = orient;
	m_pin.layer_name = layer_name;
	m_pin.bbox[0] = xl; m_pin.bbox[1] = yl;
	m_pin.bbox[2] = xh; m_pin.bbox[3] = yh;
	m_db.add_def_pin(m_pin);
#ifdef DEBUG_DEFPARSER
	std::cerr << m_pin << std::endl;
#endif 
	m_pin.reset();
}
void Driver::pin_cbk_size(int size) 
{
	m_db.resize_def_pin(size);
}
void Driver::net_cbk_name(string const& net_name) 
{
	// due to the feature of LL 
	// net_cbk_pin will be called before net_cbk_name 
	m_net.net_name = net_name;
	m_net.vNetPin = m_vNetPin;
	m_db.add_def_net(m_net);
#ifdef DEBUG_DEFPARSER
	std::cerr << m_net << std::endl;
#endif 
	m_net.reset();
	// remember to clear m_vNetPin
	m_vNetPin.clear();
}
void Driver::net_cbk_pin(string const& node_name, string const& pin_name) 
{
	m_vNetPin.push_back(make_pair(node_name, pin_name));
}
void Driver::net_cbk_size(int size) 
{
	m_db.resize_def_net(size);
}

bool read(DefDataBase& db, const string& defFile)
{
	Driver driver (db);
	//driver.trace_scanning = true;
	//driver.trace_parsing = true;

	return driver.parse_file(defFile);
}

} // namespace example
