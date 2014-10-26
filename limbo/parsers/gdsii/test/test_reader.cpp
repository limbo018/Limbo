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

struct DataBase : public GdsParser::GdsDataBase
{
	DataBase()
	{
		cout << "constructing DataBase" << endl;
	}
	///////////////////// required callbacks /////////////////////
	virtual void bit_array_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<int> const& vBitArray)
	{
		cout << __func__ << endl;
		this->general_cbk(ascii_record_type, ascii_data_type, vBitArray);
	}
	virtual void integer_2_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<unsigned int> const& vInteger)
	{
		cout << __func__ << endl;
		this->general_cbk(ascii_record_type, ascii_data_type, vInteger);
	}
	virtual void integer_4_cbk(const char* ascii_record_type, const char* ascii_data_type, vector<unsigned int> const& vInteger)
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
		}
		else if (ascii_record_type == "ENDEL")
		{
		}
	}
};

int main(int argc, char** argv)
{
	DataBase db;
	if (argc > 1)
		cout << GdsParser::read(db, argv[1]) << endl;
	else cout << "at least 1 argument is required" << endl;

	return 0;
}
