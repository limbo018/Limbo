/*************************************************************************
    > File Name: io.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Thu 06 Nov 2014 08:53:46 AM CST
 ************************************************************************/

#ifndef LIMBO_PARSERS_GDSII_GDSDB_GDSIO_H
#define LIMBO_PARSERS_GDSII_GDSDB_GDSIO_H

#include <fstream>
#include <limits>
#include <limbo/parsers/gdsii/stream/GdsReader.h>
#include <limbo/parsers/gdsii/stream/GdsWriter.h>

#include <limbo/parsers/gdsii/gdsdb/GdsObjects.h>

namespace limbo { namespace GdsParser {

/// read gds file 
class GdsReader : ::GdsParser::GdsDataBaseKernel
{
	public:
		typedef GdsDB gdsdb_type;
		typedef gdsdb_type::coordinate_type coordinate_type;
		typedef gdsdb_type::point_type point_type;

		GdsReader(gdsdb_type& db) : m_db(db) {}

		/// top api 
		bool operator() (std::string const& filename); 

		// required callbacks in parser 
		virtual void bit_array_cbk(::GdsParser::GdsRecords::EnumType record_type, ::GdsParser::GdsData::EnumType data_type, std::vector<int> const& vBitArray);
		virtual void integer_2_cbk(::GdsParser::GdsRecords::EnumType record_type, ::GdsParser::GdsData::EnumType data_type, std::vector<int> const& vInteger);
		virtual void integer_4_cbk(::GdsParser::GdsRecords::EnumType record_type, ::GdsParser::GdsData::EnumType data_type, std::vector<int> const& vInteger);
		virtual void real_4_cbk(::GdsParser::GdsRecords::EnumType record_type, ::GdsParser::GdsData::EnumType data_type, std::vector<double> const& vFloat);
		virtual void real_8_cbk(::GdsParser::GdsRecords::EnumType record_type, ::GdsParser::GdsData::EnumType data_type, std::vector<double> const& vFloat);
		virtual void string_cbk(::GdsParser::GdsRecords::EnumType record_type, ::GdsParser::GdsData::EnumType data_type, std::string const& str);
		virtual void begin_end_cbk(::GdsParser::GdsRecords::EnumType record_type);

		/// helper functions 
		void integer_cbk(::GdsParser::GdsRecords::EnumType record_type, ::GdsParser::GdsData::EnumType data_type, std::vector<int> const& vData);
		void float_cbk(::GdsParser::GdsRecords::EnumType record_type, ::GdsParser::GdsData::EnumType data_type, std::vector<double> const& vData);

	protected:
		/// reset all temporary data to default values 
		void reset(); 
		void printUnsupportRecords() const; 

		/// temporary data 
		std::string m_string; ///< STRING 
		std::string m_sname; ///< SNAME 
		int m_layer; ///< LAYER 
		int m_datatype; ///< DATATYPE
		int m_pathtype; ///< PATHTYPE
		int m_texttype; ///< TEXTTYPE
		int m_spacing[2]; ///< SPACING 
		int m_width; ///< WIDTH 
		int m_columns; ///< COLROW 
		int m_rows; 
		double m_angle; ///< ANGLE 
		double m_magnification; ///< MAG 
		int m_strans; ///< STRANS
		int m_presentation; ///< PRESENTATION
		std::vector<point_type> m_vPoint; ///< XY

		::GdsParser::GdsRecords::EnumType m_status; 
		int m_fileSize; // in bytes 
		gdsdb_type& m_db; 

		std::vector<unsigned int> m_vUnsupportRecord; ///< try to be clean at screen output, record the times of unsupported records 
};

/// write gds file 
class GdsWriter
{
	public:
		typedef GdsDB gdsdb_type;

		/// constructor
		GdsWriter(gdsdb_type const& db) : m_db(db) {}

		void operator() (std::string const& filename) const;

		/// helper functions to write gdsii objects 
		/// there is no need to use different name, since we pass different parameters
		void write(::GdsParser::GdsWriter& gw, GdsCell const& cell) const; 
		void write(::GdsParser::GdsWriter& gw, GdsPolygon const& object) const; 
		void write(::GdsParser::GdsWriter& gw, GdsPath const& object) const; 
		void write(::GdsParser::GdsWriter& gw, GdsText const& object) const; 
		void write(::GdsParser::GdsWriter& gw, GdsCellReference const& object) const; 
		void write(::GdsParser::GdsWriter& gw, GdsCellArray const& object) const; 

	protected:
		gdsdb_type const& m_db; 
};

}} // namespace limbo // GdsParser

#endif 
