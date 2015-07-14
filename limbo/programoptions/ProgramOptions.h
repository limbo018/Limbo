/*************************************************************************
    > File Name: ProgramOptions.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Mon 13 Jul 2015 08:44:13 PM CDT
 ************************************************************************/

#ifdef _LIMBO_PROGRAMOPTIONS_PROGRAMOPTIONS_H
#define _LIMBO_PROGRAMOPTIONS_PROGRAMOPTIONS_H

/// ===================================================================
///    File          : ProgramOptions
///    Function      : Mimic Boost.ProgramOptions 
///                    Easy wrapper for program command line options
///
/// ===================================================================

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limbo/string/String.h>
#include <limbo/preprocessor/AssertMsg.h>

namespace limbo { namespace programoptions {

enum DataType {
    CHAR = 0x0, 
    BOOLEAN = 0x2, 
    INTEGER = 0x4, 
    FLOAT = 0x8,
    STRING = 0x10
};

/// only support stl containers 
enum ContainerType {
    NONE = 0x100, 
    VECTOR = 0x200, 
    SET = 0x400 
};

union Data 
{
    char ch;
    bool b;
    int i;
    double fp;
    std::string* str;
    std::vector<char>* vChar;
    std::vector<bool>* vBool;
    std::vector<int>* vInt;
    std::vector<double>* vDouble;
    std::vector<std::string>* vString;
    std::set<char>* sChar;
    std::set<int>* sInt;
    std::set<double>* sDouble;
    std::set<std::string>* sString;
};

struct POData
{
    DataType data_tag;
    ContainerType container_tag;
    Data data;
    bool required;
    bool has_default; ///< whether has default value 
    bool valid; ///< whether data is set 
    Data dvalue; ///< default value 

    void assign_default();
};

class ProgramOptions
{
    public:
        typedef std::map<std::string, POData> data_map_type;

        ProgramOptions& add_option(std::string const& category, POData const& data)
        {
            m_mData.insert(std::make_pair(category, data));
            return *this;
        }
        bool parse(int argc, char** argv);
        void print(std::ostream& os = stdout) const;
    protected:
        void assign(DataType data_tag, ContainerType container_tag, Data& d, const char* v);

        std::map<std::string, POData> m_mData; ///< saving mapping for flag and options 
};

void POData::assign_default()
{
    switch (data_tag)
    {
        case CHAR:
        {
            if (container_tag == NONE) data.ch = dvalue.ch; 
            else if (container_tag == VECTOR) std::swap(data.vChar, dvalue.vChar);
            else if (container_tag == SET) std::swap(data.sChar, dvalue.sChar);
            break;
        }
        case BOOLEAN:
        {
            bool value;
            if (limbo::iequals(v, "true")) value = true;
            else if (limbo::iequals(v, "false")) value = false;
            else value = atoi(v);
            if (container_tag == NONE) data.b = value;
            else if (container_tag == VECTOR) std::swap(data.vBool, dvalue.vBool);
            break;
        }
        case INTEGER:
        {
            int value = atoi(v);
            if (container_tag == NONE) data.i = value;
            else if (container_tag == VECTOR) std::swap(data.vInt, dvalue.vInt);
            else if (container_tag == SET) std::swap(data.sInt, dvalue.vInt);
            break;
        }
        case FLOAT:
        {
            double value = atof(v);
            if (container_tag == NONE) data.fp = value;
            else if (container_tag == VECTOR) std::swap(data.vDouble, dvalue.vDouble);
            else if (container_tag == SET) std::swap(data.sDouble, dvalue.sDouble);
            break;
        }
        case STRING:
        {
            if (container_tag == NONE) data.str->assign(v);
            else if (container_tag == VECTOR) std::swap(data.vString, dvalue.vString);
            else if (container_tag == SET) std::swap(data.sString, dvalue.sString);
            break;
        }
        default:
            assert_msg(0, "unknown tag type");
    }
}

void ProgramOptions::assign(DataType data_tag, ContainerType container_tag, Data& d, const char* v)
{
    switch (data_tag)
    {
        case CHAR:
        {
            if (container_tag == NONE) d.ch = *v; 
            else if (container_tag == VECTOR) d.vChar->push_back(*v);
            else if (container_tag == SET) d.sChar->insert(*v);
            break;
        }
        case BOOLEAN:
        {
            bool value;
            if (limbo::iequals(v, "true")) value = true;
            else if (limbo::iequals(v, "false")) value = false;
            else value = atoi(v);
            if (container_tag == NONE) d.b = value;
            else if (container_tag == VECTOR) d.vBool->push_back(value);
            break;
        }
        case INTEGER:
        {
            int value = atoi(v);
            if (container_tag == NONE) d.i = value;
            else if (container_tag == VECTOR) d.vInt->push_back(value);
            else if (container_tag == SET) d.sInt->insert(value);
            break;
        }
        case FLOAT:
        {
            double value = atof(v);
            if (container_tag == NONE) d.fp = value;
            else if (container_tag == VECTOR) d.vDouble->push_back(value);
            else if (container_tag == SET) d.sDouble->insert(value);
            break;
        }
        case STRING:
        {
            if (container_tag == NONE) d.str->assign(v);
            else if (container_tag == VECTOR) d.vString->push_back(v);
            else if (container_tag == SET) d.sString->insert(v);
            break;
        }
        default:
            assert_msg(0, "unknown tag type");
    }
}

bool ProgramOptions::parse(int argc, char** argv)
{
    // skip the first argument 
    for (int i = 1; i < argc; ++i)
    {
        data_map_type::iterator found = m_mData.find(argv[i]);
        if (found != m_mData.end())
        {
            POData& poData = found->second;
            i += 1;
            if (i < argc)
            {
                const char* value = argv[i];
                assign(poData.data_tag, poData.container_tag, poData.data, value);
            }
            else 
            {
                std::cerr << "invalid appending option\n";
                return false;
            }
        }
    }
    // check required and default value 
    for (data_map_type::iterator it = m_mData.begin(); it != m_mData.end(); ++it)
    {
        std::string const& category = it->first;
        POData& poData = it->second;
        if (!poData.valid)
        {
            if (poData.has_default)
                poData.assign_default();
            else if (poData.required)
            {
                std::cerr << "required option not set: " << category << "\n";
                return false;
            }
        }
    }
    return true;
}

void ProgramOptions::print(std::ostream& os) const 
{
}

}} // namespace limbo // programoptions

#endif
