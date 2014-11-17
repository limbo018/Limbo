/*************************************************************************
    > File Name: GdsReader.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 22 Oct 2014 10:41:23 PM CDT
 ************************************************************************/

#ifndef _GDSPARSER_READER_H
#define _GDSPARSER_READER_H

#include <string>
#include <vector>
using std::string;
using std::vector;

namespace GdsParser 
{

class GdsDataBase 
{
	public:
		virtual void bit_array_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vBitArray) = 0;
		virtual void integer_2_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vInteger) = 0;
		virtual void integer_4_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vInteger) = 0;
		virtual void real_4_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<double> const& vFloat) = 0;
		virtual void real_8_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<double> const& vFloat) = 0;
		virtual void string_cbk(const char* ascii_record_type, const char* ascii_data_type, string const& str) = 0;
		virtual void begin_end_cbk(const char* ascii_record_type) = 0; // begin or end indicater of a block 
};

class GdsReader
{
	public: 
		GdsReader(GdsDataBase& db) : m_db(db) {}

		bool operator()(const char* filename);

	protected:
		void find_ascii_record_type (int numeric, char *record_name, char *record_description, int *expected_data_type);
		void find_ascii_data_type (int numeric, char *data_name, char *data_description);
		void print_bit_array_comments (char *ascii_record_type, int bit_array, char *indent_string);

		GdsDataBase& m_db;
};

bool read(GdsDataBase& db, string const& filename);

} // namespace GdsParser

#endif 
