/*************************************************************************
    > File Name: LefDataBase.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Fri 10 Oct 2014 11:49:28 PM CDT
 ************************************************************************/

#ifndef LEFPARSER_DATABASE_H
#define LEFPARSER_DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "lefiUser.hpp"
#include "lefiDefs.hpp"
#include "lefiUtil.hpp"

namespace LefParser {

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
// forward declaration
// base class for DataBase 
// only pure virtual functions are defined 
// user needs to heritate this class 
class LefDataBase
{
	public:
		LefDataBase();
		double current_version() const;
		void current_version(double);

		// although it is true that I can use pure virtual functions for all callbacks
		// run-time information is better than compile-time errors.
		// because most LEF files are so simple that we only need several callbacks 
		// then user does not need to provide some callbacks.
		virtual void lef_version_cbk(string const&);
		virtual void lef_version_cbk(double);
		virtual void lef_dividerchar_cbk(string const&);
		virtual void lef_casesensitive_cbk(int);
		virtual void lef_nowireextension_cbk(string const&);
		virtual void lef_manufacturing_cbk(double);
		virtual void lef_useminspacing_cbk(lefiUseMinSpacing const&);
		virtual void lef_clearancemeasure_cbk(string const&);
		virtual void lef_units_cbk(lefiUnits const&);
		virtual void lef_busbitchars_cbk(string const&);
		virtual void lef_layer_cbk(lefiLayer const&);
		virtual void lef_maxstackvia_cbk(lefiMaxStackVia const&);
		virtual void lef_via_cbk(lefiVia const&);
		virtual void lef_viarule_cbk(lefiViaRule const&);
		virtual void lef_spacing_cbk(lefiSpacing const&);
		virtual void lef_irdrop_cbk(lefiIRDrop const&);
		virtual void lef_minfeature_cbk(lefiMinFeature const&);
		virtual void lef_dielectric_cbk(double);
		virtual void lef_nondefault_cbk(lefiNonDefault const&);
		virtual void lef_site_cbk(lefiSite const&);
		virtual void lef_macro_cbk(lefiMacro const&);
		//virtual void lef_obstruction_cbk(lefiObstruction const&);
		virtual void lef_density_cbk(lefiDensity const&);
		virtual void lef_timing_cbk(lefiTiming const&);
		virtual void lef_array_cbk(lefiArray const&);
		virtual void lef_prop_cbk(lefiProp const&);
		virtual void lef_noisemargin_cbk(lefiNoiseMargin const&);
		virtual void lef_edgeratethreshold1_cbk(double);
		virtual void lef_edgeratethreshold2_cbk(double);
		virtual void lef_edgeratescalefactor_cbk(double);
		virtual void lef_noisetable_cbk(lefiNoiseTable const&);
		virtual void lef_correctiontable_cbk(lefiCorrectionTable const&);
		virtual void lef_inputantenna_cbk(double);
		virtual void lef_outputantenna_cbk(double);
		virtual void lef_inoutantenna_cbk(double);
		virtual void lef_antennainput_cbk(double);
		virtual void lef_antennaoutput_cbk(double);
		virtual void lef_antennainout_cbk(double);
		virtual void lef_extension_cbk(string const&);
	protected:
		double m_current_version; /* default current lef version, use static variable to mimic definitions */
	public:
		static int lefNamesCaseSensitive; /* case sensitive or not, mimic global variable lefNamesCaseSensitive */
		static int lefrShiftCase; /* shift to upper case or not  */
	private:
		void lef_user_cbk_reminder(const char*) const;
};

} // namespace LefParser

namespace LefParser {

enum lefiConstantEnum
{
	C_EQ = 0,
	C_NE = 1,
	C_LT = 2,
	C_LE = 3,
	C_GT = 4,
	C_GE = 5
};

/***************** custom help functions here ******************/
// copy from lex.h and lex.cpph
void* lefMalloc(int lef_size);
void* lefRealloc(void *name, int lef_size);
void lefFree(void *name);

} // namespace LefParser

#endif
