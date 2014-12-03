/*************************************************************************
    > File Name: GdsDriver.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 12 Nov 2014 01:23:35 PM CST
 ************************************************************************/

#ifndef _GDSPARSER_GDSDRIVER_H
#define _GDSPARSER_GDSDRIVER_H

/// ======================================================
///        class: GdsDriver
///        attribute: high-level wrapper for GdsReader
///                   try to mimic same callback functions in GdsTxtParser
///                   there will be many self-included classes for temporary storage
///                   this class is more convenient but less general 
/// ======================================================

#include <sstream>
#include <limbo/parsers/gdsii/stream/GdsReader.h>
#include <limbo/preprocessor/AssertMsg.h>

using std::ostringstream;

namespace GdsParser 
{

typedef int int32_t;
typedef unsigned int uint32_t;

/// internal structure to store gds information
struct GdsBoundary 
{
	int32_t layer;
	int32_t datatype;
	vector<vector<int32_t> > vPoint;
	void reset()
	{
		layer = -1;
		datatype = -1;
		vPoint.clear();
	}
};
struct GdsText 
{
	int32_t layer;
	int32_t texttype;
	int32_t presentation;
	int32_t strans;
	double mag;
	vector<int32_t> position;
	string content;
	GdsText() 
	{
		position.resize(2, 0);
	}
	void reset()
	{
		layer = texttype = presentation = strans = 0;
		mag = 0;
		position.resize(2, 0);
		content = "";
	}
};
/// thanks to Biying Xu for the benchmarks and sample code 
struct GdsSref
{
	string sname;
	vector<int32_t> position;
	GdsSref() 
	{
		position.resize(2, 0);
	}
	void reset()
	{
		sname = "";
		position.resize(2, 0);
	}
};
struct GdsCell 
{
	string cell_name;
	vector<GdsBoundary> vBoundary;
	vector<GdsText> vText;
	vector<GdsSref> vSref;
	void reset()
	{
		cell_name = "";
		vBoundary.clear();
		vText.clear();
		vSref.clear();
	}
};
struct GdsLib 
{
	string lib_name;
	vector<double> unit;
	vector<GdsCell> vCell;
	GdsLib()
	{
		unit.resize(2, 0);
	}
	void reset()
	{
		lib_name = "";
		unit.resize(2, 0);
		vCell.clear();
	}
};
class GdsDriverDataBase
{
	public:
		/// required callback function
		virtual void add_gds_lib(GdsLib const&) = 0;
};

/// high-level wrapper class for GdsReader 
/// everything is saved in an internal data structure and users only need to provide simple callbacks
class GdsDriver : public GdsDataBase
{
	public:
		typedef GdsDataBase base_type;
		typedef GdsDriverDataBase database_type;

		GdsDriver(database_type&);

		/// top function for GdsDriver
		bool operator()(string const& filename);

	protected:
		/// required callbacks from GdsDataBase
		virtual void bit_array_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vBitArray);
		virtual void integer_2_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vInteger);
		virtual void integer_4_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vInteger);
		virtual void real_4_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<double> const& vFloat);
		virtual void real_8_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<double> const& vFloat);
		virtual void string_cbk(const char* ascii_record_type, const char* ascii_data_type, string const& str);
		virtual void begin_end_cbk(const char* ascii_record_type); // begin or end indicater of a block 
		/// generalized callback for all cases 
		template <typename ContainerType>
		void general_cbk(string const& ascii_record_type, string const& ascii_data_type, ContainerType const& vData);

		database_type& m_db; ///< database type 
		GdsLib m_lib; ///< temporary GdsLib object 
									///< when parsed a lib, pass it using add_gds_lib function
		string m_current; ///< current block name 
						///< it can be HEADER, LIBRARY, CELL, BOUNDARY, BOX, TEXT, SREF
};

template <typename ContainerType>
void GdsDriver::general_cbk(string const& ascii_record_type, string const&, ContainerType const& vData)
{
	if (ascii_record_type == "HEADER")
	{
		m_current = "HEADER";
	}
	else if (ascii_record_type == "BGNLIB")
	{
		m_current = "LIBRARY";
	}
	else if (ascii_record_type == "LIBNAME")
	{
		m_lib.lib_name.assign(vData.begin(), vData.end());
	}
	else if (ascii_record_type == "UNITS")
	{
		m_lib.unit[0] = vData[0]; 
		m_lib.unit[1] = vData[1]; 
	}
	else if (ascii_record_type == "BGNSTR")
	{
		m_current = "CELL";
		m_lib.vCell.push_back(GdsCell());
	}
	else if (ascii_record_type == "STRNAME")
	{
		m_lib.vCell.back().cell_name.assign(vData.begin(), vData.end());
	}
	else if (ascii_record_type == "BOUNDARY" || ascii_record_type == "BOX") // BOUNDARY and BOX are generalized to BOUNDARY
	{
		m_current = "BOUNDARY";
		assert_msg(!m_lib.vCell.empty(), ascii_record_type << " block must be in a BGNSTR block");
		m_lib.vCell.back().vBoundary.push_back(GdsBoundary());
	}
	else if (ascii_record_type == "TEXT")
	{
		m_current = "TEXT";
		assert_msg(!m_lib.vCell.empty(), ascii_record_type << " block must be in a BGNSTR block");
		m_lib.vCell.back().vText.push_back(GdsText());
	}
	else if (ascii_record_type == "SREF")
	{
		m_current = "SREF";
		assert_msg(!m_lib.vCell.empty(), ascii_record_type << " block must be in a BGNSTR block");
		m_lib.vCell.back().vSref.push_back(GdsSref());
	}
	else if (ascii_record_type == "LAYER")
	{
		if (m_current == "BOUNDARY")
			m_lib.vCell.back().vBoundary.back().layer = vData[0];
		else if (m_current == "TEXT")
			m_lib.vCell.back().vText.back().layer = vData[0];
	}
	else if (ascii_record_type == "DATATYPE") // here're some information I don't see any usage
	{
		if (m_current == "BOUNDARY")
			m_lib.vCell.back().vBoundary.back().datatype = vData[0];
	}
	else if (ascii_record_type == "TEXTTYPE")
	{
		if (m_current == "TEXT")
			m_lib.vCell.back().vText.back().texttype = vData[0];
	}
	else if (ascii_record_type == "PRESENTATION")
	{
		if (m_current == "TEXT")
			m_lib.vCell.back().vText.back().presentation = vData[0];
	}
	else if (ascii_record_type == "STRANS")
	{
		if (m_current == "TEXT")
			m_lib.vCell.back().vText.back().strans = vData[0];
	}
	else if (ascii_record_type == "MAG")
	{
		if (m_current == "TEXT")
			m_lib.vCell.back().vText.back().mag = vData[0];
	}
	else if (ascii_record_type == "SNAME")
	{
		if (m_current == "SREF")
			m_lib.vCell.back().vSref.back().sname.assign(vData.begin(), vData.end());
	}
	else if (ascii_record_type == "XY")
	{
		if (m_current == "BOUNDARY")
		{
			assert_msg((vData.size() % 2) == 0 && vData.size() > 4, "invalid size of data array: " << vData.size());
			for (uint32_t i = 0; i < vData.size(); i += 2)
			{
				vector<int32_t> point (2);
				point[0] = vData[i];
				point[1] = vData[i+1];
				m_lib.vCell.back().vBoundary.back().vPoint.push_back(point);
			}
		}
		else if (m_current == "TEXT")
		{
			assert_msg(vData.size() == 2, "invalid size of data array for " 
					<< m_current << ": " << vData.size());
			m_lib.vCell.back().vText.back().position.assign(vData.begin(), vData.end());
		}
		else if (m_current == "SREF")
		{
			assert_msg(vData.size() == 2, "invalid size of data array for " 
					<< m_current << ": " << vData.size());
			m_lib.vCell.back().vSref.back().position.assign(vData.begin(), vData.end());
		}
		else assert_msg(0, "record XY should only appear in BOUNDARY, BOX, TEXT, SREF");
	}
	else if (ascii_record_type == "STRING")
	{
		assert_msg(m_current == "TEXT", "record type STRING must appear in TEXT block rather than " << m_current);
		m_lib.vCell.back().vText.back().content.assign(vData.begin(), vData.end());
	}
	else if (ascii_record_type == "ENDEL")
	{
		assert_msg(m_current == "BOUNDARY" || m_current == "TEXT"
				|| m_current == "SREF", 
				"currently only support BOUNDARY, BOX, and TEXT");
		m_current = "CELL"; // go back to upper 
	}
	else if (ascii_record_type == "ENDSTR")
	{
		assert_msg(m_current == "CELL", "BGNSTR and ENDSTR should be in pair");
		m_current = "LIBRARY"; // go back to upper 
	}
	else if (ascii_record_type == "ENDLIB")
	{
		assert_msg(m_current == "LIBRARY", "BGNLIB and ENDLIB should be in pair");
		m_current = "HEADER"; 
		// call db 
		m_db.add_gds_lib(m_lib);
		m_lib.reset();
	}
	else assert_msg(0, "unsupported record type: " << ascii_record_type);
}

/// top api function for GdsDriver
bool read(GdsDriverDataBase& db, string const& filename);

} // namespace GdsParser

#endif 
