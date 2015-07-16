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
#include <limbo/programoptions/ConversionHelpers.h>

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

class ValueBase
{
    public:
        ValueBase(std::string const& cat, std::string const& help_msg)
            : m_category(cat)
            , m_msg(help_msg)
            , m_required(false)
            , m_valid(false)
        {}
        virtual ~ValueBase() {}
        /// parse command 
        virtual void parse(const char*) = 0;
        /// print target value 
        virtual void print(std::ostream& os) const = 0;
        /// print default value 
        virtual void print_default(std::ostream& os) const = 0;
        /// \return apply default value 
        virtual void apply_default() = 0;
        /// \return true if default value is set 
        bool valid_default() const = 0;
        std::string const& category() const {return m_category;}
        std::string const& msg() const {return m_msg;}
        bool required() const {return m_required;}
        bool valid() const {return m_valid;}
    protected:
        std::string const& m_category; ///< category 
        std::string const& m_msg; ///< helper message 
        bool m_required; ///< whether the value is a required option
        bool m_valid; ///< true if target is set, not default 
};

template <typename T>
class Value : public ValueBase
{
    public:
        typedef T value_type;
        typedef ValueBase base_type;

        Value(std::string const& cat, value_type* target, std::string const& help_msg)
            : base_type(cat, help_msg)
            , m_target(target)
            , m_default(NULL)
        {}
        virtual ~Value();

        virtual void parse(const char* v) 
        {
            parse_helper<value_type>(*m_target, v);
        }
        virtual void print(std::ostream& os) const 
        {
            print_helper<value_type>(os, *m_target);
        }
        virtual void print_default(std::ostream& os) const 
        {
            print_helper<value_type>(os, *m_default);
        }
        virtual void apply_default()
        {
            if (m_target && m_default)
                assign_helper<value_type>(*m_target, *m_default);
        }
        virtual bool valid_default() const 
        {
            return (m_default != NULL);
        }

    protected:
        value_type* m_target;
        value_type* m_default;
};


class ProgramOptions
{
    public:
        typedef std::map<std::string, POData> data_map_type;

        ProgramOptions() {}
        ~ProgramOptions();

        template <typename ValueType>
        ProgramOptions& add_option(std::string const& category, ValueType const& data);
        bool parse(int argc, char** argv);
        void print() const {print(stdout);}
        void print(std::ostream& os) const;
    protected:
        std::map<std::string, ValueBase*> m_mData; ///< saving mapping for flag and options 
};

template <typename ValueType>
ProgramOptions& ProgramOptions::add_option(std::string const& category, ValueType const& data) 
{
    m_mData.insert(std::make_pair(category, new ValueType (data)));
    return *this;
}

bool ProgramOptions::parse(int argc, char** argv)
{
    // skip the first argument 
    for (int i = 1; i < argc; ++i)
    {
        data_map_type::iterator found = m_mData.find(argv[i]);
        if (found != m_mData.end())
        {
            ValueBase* pData = found->second;
            i += 1;
            if (i < argc)
            {
                const char* value = argv[i];
                pData->parse(value);
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
        ValueBase* pData = it->second;
        if (!pData->valid())
        {
            if (pData->valid_default())
                pData->apply_default();
            else if (pData->required())
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
