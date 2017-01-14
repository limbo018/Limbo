/*************************************************************************
    > File Name: test.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 22 Oct 2014 10:43:22 PM CDT
 ************************************************************************/

#include <iostream>
#include <limbo/parsers/gdsii/stream/GdsReader.h>
using std::cout;
using std::endl;

/// test ascii callbacks 
struct AsciiDataBase : public GdsParser::GdsDataBase
{
	AsciiDataBase()
	{
		cout << "constructing AsciiDataBase" << endl;
	}
	///////////////////// required callbacks /////////////////////
	virtual void bit_array_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vBitArray)
	{
		cout << __func__ << endl;
		this->general_cbk(ascii_record_type, ascii_data_type, vBitArray);
	}
	virtual void integer_2_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vInteger)
	{
		cout << __func__ << endl;
		this->general_cbk(ascii_record_type, ascii_data_type, vInteger);
	}
	virtual void integer_4_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vInteger)
	{
		cout << __func__ << endl;
		this->general_cbk(ascii_record_type, ascii_data_type, vInteger);
	}
	virtual void real_4_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<double> const& vFloat) 
	{
		cout << __func__ << endl;
		this->general_cbk(ascii_record_type, ascii_data_type, vFloat);
	}
	virtual void real_8_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<double> const& vFloat) 
	{
		cout << __func__ << endl;
		this->general_cbk(ascii_record_type, ascii_data_type, vFloat);
	}
	virtual void string_cbk(const char* ascii_record_type, const char* ascii_data_type, string const& str) 
	{
		cout << __func__ << endl;
		this->general_cbk(ascii_record_type, ascii_data_type, str);
	}
	virtual void begin_end_cbk(const char* ascii_record_type)
	{
		cout << __func__ << endl;
		this->general_cbk(ascii_record_type, "", vector<int>(0));
	}

	template <typename ContainerType>
	void general_cbk(string const& ascii_record_type, string const& ascii_data_type, ContainerType const& data)
	{
		cout << "ascii_record_type: " << ascii_record_type << endl
			<< "ascii_data_type: " << ascii_data_type << endl 
			<< "data size: " << data.size() << endl;
		if (ascii_record_type == "UNITS")
		{
		}
		else if (ascii_record_type == "BOUNDARY")
		{
		}
		else if (ascii_record_type == "LAYER")
		{
		}
		else if (ascii_record_type == "XY")
		{
			cout << data.size() << endl;
		}
		else if (ascii_record_type == "ENDEL")
		{
		}
	}
};

/// test enum callbacks
struct EnumDataBase : public GdsParser::GdsDataBaseKernel
{
	EnumDataBase()
	{
		cout << "constructing EnumDataBase" << endl;
	}
	///////////////////// required callbacks /////////////////////
	virtual void bit_array_cbk(GdsParser::GdsRecords::EnumType record_type, GdsParser::GdsData::EnumType data_type, vector<int> const& vBitArray)
	{
		cout << __func__ << endl;
		this->general_cbk(record_type, data_type, vBitArray);
	}
	virtual void integer_2_cbk(GdsParser::GdsRecords::EnumType record_type, GdsParser::GdsData::EnumType data_type, vector<int> const& vInteger)
	{
		cout << __func__ << endl;
		this->general_cbk(record_type, data_type, vInteger);
	}
	virtual void integer_4_cbk(GdsParser::GdsRecords::EnumType record_type, GdsParser::GdsData::EnumType data_type, vector<int> const& vInteger)
	{
		cout << __func__ << endl;
		this->general_cbk(record_type, data_type, vInteger);
	}
	virtual void real_4_cbk(GdsParser::GdsRecords::EnumType record_type, GdsParser::GdsData::EnumType data_type, vector<double> const& vFloat) 
	{
		cout << __func__ << endl;
		this->general_cbk(record_type, data_type, vFloat);
	}
	virtual void real_8_cbk(GdsParser::GdsRecords::EnumType record_type, GdsParser::GdsData::EnumType data_type, vector<double> const& vFloat) 
	{
		cout << __func__ << endl;
		this->general_cbk(record_type, data_type, vFloat);
	}
	virtual void string_cbk(GdsParser::GdsRecords::EnumType record_type, GdsParser::GdsData::EnumType data_type, string const& str) 
	{
		cout << __func__ << endl;
		this->general_cbk(record_type, data_type, str);
	}
	virtual void begin_end_cbk(GdsParser::GdsRecords::EnumType record_type)
	{
		cout << __func__ << endl;
		this->general_cbk(record_type, GdsParser::GdsData::NO_DATA, vector<int>(0));
	}

	template <typename ContainerType>
	void general_cbk(GdsParser::GdsRecords::EnumType record_type, GdsParser::GdsData::EnumType data_type, ContainerType const& data)
	{
		cout << "ascii_record_type: " << GdsParser::gds_record_ascii(record_type) << endl
			<< "ascii_data_type: " << GdsParser::gds_data_ascii(data_type) << endl 
			<< "data size: " << data.size() << endl;
        switch (record_type)
        {
            case GdsParser::GdsRecords::UNITS:
                break;
            case GdsParser::GdsRecords::BOUNDARY:
                break;
            case GdsParser::GdsRecords::LAYER:
                cout << "LAYER = " << data[0] <<  endl;
                break;
            case GdsParser::GdsRecords::XY:
                for (typename ContainerType::const_iterator it = data.begin(); it != data.end(); ++it)
                    cout << *it << " "; 
                cout << endl; 
                cout << data.size() << endl;
                break;
            case GdsParser::GdsRecords::ENDEL:
                break;
            default:
                break;
        }
	}
};

/* ===========================================
example to read .gds.gz 
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>

EnumDataBase edb; 
boost::iostreams::filtering_istream in; 
in.push(boost::iostreams::gzip_decompressor());
in.push(boost::iostreams::file_source(argv[1]));

cout << "test enum api\n" << GdsParser::read(edb, in) << endl;
=========================================== */

int main(int argc, char** argv)
{
	if (argc > 1)
    {
        AsciiDataBase adb;
		cout << "test ascii api\n" << GdsParser::read(adb, argv[1]) << endl;
        EnumDataBase edb;
		cout << "test enum api\n" << GdsParser::read(edb, argv[1]) << endl;
    }
	else cout << "at least 1 argument is required" << endl;

	return 0;
}
