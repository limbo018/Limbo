/*************************************************************************
    > File Name: GdsReader.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 22 Oct 2014 10:41:23 PM CDT
 ************************************************************************/

#ifndef _GDSPARSER_GDSREADER_H
#define _GDSPARSER_GDSREADER_H

#include <string>
#include <vector>
#include <limbo/parsers/gdsii/stream/GdsRecords.h>
using std::string;
using std::vector;

namespace GdsParser 
{

/// =============================================================
/// Why do I need to wrap GdsDataBaseKernel into GdsDataBase?
/// This is mainly for backward compatibility reasons. 
/// In old version limbo library, user only needs to implement child database class for GdsDataBase 
/// and use those ascii callbacks. 
/// I hope user does not need to change their code in the new version, so the old api must still be available. 
/// By adding new base class GdsDataBaseKernel, it is possible to achieve both. 
/// If user want to use old api, they can write child class for GdsDataBase, 
/// while if they want to use new api, please inheritate GdsDataBaseKernel. 
/// =============================================================

/// =============================================================
/// Kernel callbacks for GdsReader.
/// These callbacks use enum for record_type and data_type, 
/// which is faster than ascii callbacks.
/// =============================================================
class GdsDataBaseKernel
{
	public:
		virtual void bit_array_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<int> const& vBitArray) = 0;
		virtual void integer_2_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<int> const& vInteger) = 0;
		virtual void integer_4_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<int> const& vInteger) = 0;
		virtual void real_4_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<double> const& vFloat) = 0;
		virtual void real_8_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<double> const& vFloat) = 0;
		virtual void string_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, string const& str) = 0;
		virtual void begin_end_cbk(GdsRecords::EnumType record_type) = 0; // begin or end indicater of a block 
};

/// =============================================================
/// GdsDataBase redirects callbacks of GdsDataBaseKernel to ascii callbacks
/// =============================================================
class GdsDataBase : public GdsDataBaseKernel
{
	public:
		virtual void bit_array_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vBitArray) = 0;
		virtual void integer_2_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vInteger) = 0;
		virtual void integer_4_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vInteger) = 0;
		virtual void real_4_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<double> const& vFloat) = 0;
		virtual void real_8_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<double> const& vFloat) = 0;
		virtual void string_cbk(const char* ascii_record_type, const char* ascii_data_type, string const& str) = 0;
		virtual void begin_end_cbk(const char* ascii_record_type) = 0; // begin or end indicater of a block 
    private:
        /// these callbacks are disabled for users 
		virtual void bit_array_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<int> const& vBitArray);
		virtual void integer_2_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<int> const& vInteger);
		virtual void integer_4_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<int> const& vInteger);
		virtual void real_4_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<double> const& vFloat);
		virtual void real_8_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<double> const& vFloat);
		virtual void string_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, string const& str);
		virtual void begin_end_cbk(GdsRecords::EnumType record_type); // begin or end indicater of a block 
};

/// inline redirection from enum callbacks to ascii callbacks
inline void GdsDataBase::bit_array_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<int> const& vBitArray)
{this->bit_array_cbk(gds_record_ascii(record_type), gds_data_ascii(data_type), vBitArray);}
inline void GdsDataBase::integer_2_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<int> const& vInteger)
{this->integer_2_cbk(gds_record_ascii(record_type), gds_data_ascii(data_type), vInteger);}
inline void GdsDataBase::integer_4_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<int> const& vInteger)
{this->integer_4_cbk(gds_record_ascii(record_type), gds_data_ascii(data_type), vInteger);}
inline void GdsDataBase::real_4_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<double> const& vFloat)
{this->real_4_cbk(gds_record_ascii(record_type), gds_data_ascii(data_type), vFloat);}
inline void GdsDataBase::real_8_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, vector<double> const& vFloat)
{this->real_8_cbk(gds_record_ascii(record_type), gds_data_ascii(data_type), vFloat);}
inline void GdsDataBase::string_cbk(GdsRecords::EnumType record_type, GdsData::EnumType data_type, string const& str)
{this->string_cbk(gds_record_ascii(record_type), gds_data_ascii(data_type), str);}
inline void GdsDataBase::begin_end_cbk(GdsRecords::EnumType record_type) // begin or end indicater of a block 
{this->begin_end_cbk(gds_record_ascii(record_type));}

class GdsReader
{
	public: 
		GdsReader(GdsDataBaseKernel& db) : m_db(db) {}

		bool operator()(const char* filename);

	protected:
        void find_record_type (int numeric, GdsRecords::EnumType& record_name, int& expected_data_type);
        void find_data_type (int numeric, GdsData::EnumType& data_name);
        void print_bit_array_comments (GdsRecords::EnumType enum_record_type, int bit_array, int indent_amount);

		GdsDataBaseKernel& m_db;
};

bool read(GdsDataBaseKernel& db, string const& filename);

} // namespace GdsParser

#endif 
