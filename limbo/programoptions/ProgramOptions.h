/*************************************************************************
    > File Name: ProgramOptions.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Mon 13 Jul 2015 08:44:13 PM CDT
 ************************************************************************/

#ifndef _LIMBO_PROGRAMOPTIONS_PROGRAMOPTIONS_H
#define _LIMBO_PROGRAMOPTIONS_PROGRAMOPTIONS_H

/// ===================================================================
///    File          : ProgramOptions
///    Function      : Mimic Boost.ProgramOptions 
///                    Easy wrapper for program command line options
///
/// ===================================================================

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <exception>
#include <limbo/string/String.h>
#include <limbo/preprocessor/AssertMsg.h>
#include <limbo/programoptions/ConversionHelpers.h>

namespace limbo { namespace programoptions {

class ProgramOptionsException : public std::exception
{
    public:
        typedef std::exception base_type;
        ProgramOptionsException(std::string const& msg) : base_type(), m_msg(msg) {}
        ProgramOptionsException(ProgramOptionsException const& rhs) : base_type(rhs), m_msg(rhs.m_msg) {}
        virtual ~ProgramOptionsException() throw() {}
        virtual const char* what() const throw () {return m_msg.c_str();}
    protected:
        std::string m_msg; 
};

class ValueBase
{
    public:
        ValueBase(std::string const& cat, std::string const& m)
            : m_category(cat)
            , m_msg(m)
            , m_required(false)
            , m_valid(false)
            , m_toggle(false)
        {}
        ValueBase(ValueBase const& rhs) {copy(rhs);}
        ValueBase& operator=(ValueBase const& rhs)
        {
            if (this != &rhs)
                copy(rhs);
            return *this;
        }
        virtual ~ValueBase() {}

        /// parse command 
        /// \return true if succeeded 
        virtual bool parse(const char*) = 0;
        /// print target value 
        virtual void print(std::ostream& os) const = 0;
        /// print default value 
        virtual void print_default(std::ostream& os) const = 0;
        /// apply default value 
        virtual void apply_default() = 0;
        /// apply toggle value 
        virtual void apply_toggle() = 0;
        /// \return true if target pointer is defined 
        virtual bool valid_target() const = 0;
        /// \return true if default value is set 
        virtual bool valid_default() const = 0;
        /// \return true if toggle value is set 
        virtual bool valid_toggle() const = 0;
        /// \return the length of string if default value is printed 
        virtual unsigned count_default_chars() const = 0;

        std::string const& category() const {return m_category;}
        std::string const& msg() const {return m_msg;}
        bool required() const {return m_required;}
        bool valid() const {return m_valid;}
        bool toggle() const {return m_toggle;}
        void print_category(std::ostream& os) const {os << category();}
        void print_msg(std::ostream& os) const {os << msg();}
    protected:
        void copy(ValueBase const& rhs)
        {
            m_category = rhs.m_category;
            m_msg = rhs.m_msg;
            m_required = rhs.m_required;
            m_valid = rhs.m_valid;
            m_toggle = rhs.m_toggle;
        }

        std::string m_category; ///< category 
        std::string m_msg; ///< helper message 
        bool m_required; ///< whether the value is a required option
        bool m_valid; ///< true if target is set, not default 
        bool m_toggle; ///< true if this option is a toggle value 
};

template <typename T>
class Value : public ValueBase
{
    public:
        typedef T value_type;
        typedef ValueBase base_type;

        Value(std::string const& cat, value_type* target, std::string const& m)
            : base_type(cat, m)
            , m_target(target)
            , m_default_value(NULL)
            , m_toggle_value(NULL)
            , m_default_display("")
        {}
        Value(Value const& rhs) 
            : base_type(rhs)
        {
            copy(rhs);
        }
        Value& operator=(Value const& rhs)
        {
            if (this != &rhs)
            {
                this->base_type::copy(rhs);
                this->copy(rhs);
            }
            return *this;
        }
        virtual ~Value() 
        {
            if (m_default_value)
                delete m_default_value;
            if (m_toggle_value)
                delete m_toggle_value;
        }

        virtual bool parse(const char* v) 
        {
            if (m_target)
            {
                bool flag = parse_helper<value_type>()(*m_target, v);
                if (flag) 
                    m_valid = true;
                return flag;
            }
            return false;
        }
        virtual void print(std::ostream& os) const 
        {
            if (m_target)
                print_helper<value_type>()(os, *m_target);
        }
        virtual void print_default(std::ostream& os) const 
        {
            if (m_default_value)
            {
                if (m_default_display.empty())
                    print_helper<value_type>()(os, *m_default_value);
                else os << m_default_display;
            }
        }
        virtual void apply_default()
        {
            if (m_target && m_default_value)
                assign_helper<value_type>()(*m_target, *m_default_value);
        }
        virtual void apply_toggle()
        {
            if (m_target && m_toggle_value)
            {
                assign_helper<value_type>()(*m_target, *m_toggle_value);
                m_valid = true;
            }
        }
        virtual bool valid_target() const
        {
            return (m_target != NULL);
        }
        virtual bool valid_default() const 
        {
            return (m_default_value != NULL);
        }
        virtual bool valid_toggle() const 
        {
            return (m_toggle_value != NULL);
        }
        virtual unsigned count_default_chars() const 
        {
            std::ostringstream oss;
            print_default(oss);
            return oss.str().size();
        }
        /// set default value 
        virtual Value& default_value(value_type const& v, std::string const& d = "")
        {
            if (m_default_value) // in case for multiple calls 
                delete m_default_value;
            m_default_value = new value_type (v);
            m_default_display = d;
            return *this;
        }
        /// set toggle value 
        virtual Value& toggle_value(value_type const& v)
        {
            if (m_toggle_value) // in case for multiple calls 
                delete m_toggle_value;
            m_toggle_value = new value_type (v);
            return *this;
        }
        virtual Value& required(bool r)
        {
            m_required = r;
            return *this;
        }
        virtual Value& toggle(bool t)
        {
            m_toggle = t;
            return *this;
        }

    protected:
        void copy(Value const& rhs)
        {
            m_target = rhs.m_target;
            m_default_value = NULL;
            m_toggle_value = NULL;
            if (rhs.m_default_value)
                default_value(*rhs.m_default_value, rhs.m_default_display);
            if (rhs.m_toggle_value)
                toggle_value(*rhs.m_toggle_value);
        }

        value_type* m_target; ///< NULL for help 
        value_type* m_default_value;
        value_type* m_toggle_value; ///< only valid when this option is a toggle value 
        std::string m_default_display; ///< display default value 
};


class ProgramOptions
{
    public:
        typedef std::map<std::string, unsigned> cat2index_map_type;

        ProgramOptions(std::string const& title = "Available options") : m_title(title) {}
        ProgramOptions(ProgramOptions const& rhs);
        ~ProgramOptions();

        template <typename ValueType>
        ProgramOptions& add_option(ValueType const& data);
        bool parse(int argc, char** argv);

        /// \return true if the option is set by command 
        bool count(std::string const& cat) const; 

        /// print help message 
        void print() const {print(std::cout);}
        /// print help message 
        void print(std::ostream& os) const;
        /// override operator<<
        friend std::ostream& operator<<(std::ostream& os, ProgramOptions const& rhs)
        {
            rhs.print(os);
            return os;
        }
    protected:
        /// print a specific number of spaces 
        inline void print_space(std::ostream& os, unsigned num) const 
        {
            assert_msg(num < 1000, "num out of bounds: " << num);
            os << std::string (num, ' ');
        }

        std::map<std::string, unsigned> m_mCat2Index; ///< saving mapping for flag to option
        std::vector<ValueBase*> m_vData; ///< saving options 
        std::string m_title; ///< title of options 
};

ProgramOptions::~ProgramOptions()
{
    for (std::vector<ValueBase*>::iterator it = m_vData.begin(); it != m_vData.end(); ++it)
        delete *it;
}

template <typename ValueType>
ProgramOptions& ProgramOptions::add_option(ValueType const& data) 
{
    std::pair<cat2index_map_type::iterator, bool> insertRet = m_mCat2Index.insert(std::make_pair(data.category(), m_vData.size()));
    if (insertRet.second) // only create new data when it is not in the map
        m_vData.push_back(new ValueType (data));
    return *this;
}

bool ProgramOptions::parse(int argc, char** argv)
{
    // skip the first argument 
    for (int i = 1; i < argc; ++i)
    {
        cat2index_map_type::iterator found = m_mCat2Index.find(argv[i]);
        if (found != m_mCat2Index.end())
        {
            ValueBase* pData = m_vData.at(found->second);
            if (pData->toggle()) // toggle option 
                pData->apply_toggle();
            else // non-toggle option 
            {
                i += 1;
                if (i < argc) 
                {
                    const char* value = argv[i];
                    bool flag = pData->parse(value);
                    if (!flag) // fail or help 
                        throw ProgramOptionsException(std::string("failed to parse ")+value);
                }
                else 
                    throw ProgramOptionsException("invalid appending option");
            }
        }
        else 
            throw ProgramOptionsException(std::string("unknown option: ")+argv[i]);
    }
    // check required and default value 
    for (cat2index_map_type::const_iterator it = m_mCat2Index.begin(); it != m_mCat2Index.end(); ++it)
    {
        std::string const& category = it->first;
        ValueBase* pData = m_vData.at(it->second);
        if (!pData->valid()) // not set 
        {
            if (pData->valid_default()) // has default 
                pData->apply_default();
            else if (pData->required()) // required 
                throw ProgramOptionsException(std::string("required option not set: ")+category);
        }
    }
    return true;
}

bool ProgramOptions::count(std::string const& cat) const 
{
    cat2index_map_type::const_iterator found = m_mCat2Index.find(cat);
    if (found != m_mCat2Index.end())
        return m_vData.at(found->second)->valid();
    else return false;
}

void ProgramOptions::print(std::ostream& os) const 
{
    static const unsigned cat_prefix_spaces = 2;
    static const unsigned cat_option_spaces = 4;

    unsigned max_cat_count = 0;
    std::vector<unsigned> vPlaceholderLength;
    vPlaceholderLength.reserve(m_vData.size());

    os << m_title << ":" << std::endl;

    // calculate length of placeholders
    for (std::vector<ValueBase*>::const_iterator it = m_vData.begin(); it != m_vData.end(); ++it)
    {
        const ValueBase* pData = *it;
        // category (default value)
        unsigned extra_chars = 0;
        if (pData->valid_default()) // extra 3 characters 
            extra_chars = 3;
        vPlaceholderLength.push_back(pData->category().size()+pData->count_default_chars()+extra_chars);
        max_cat_count = std::max(max_cat_count, vPlaceholderLength.back()); 
    }
    std::vector<unsigned>::const_iterator itPhl = vPlaceholderLength.begin();
    for (std::vector<ValueBase*>::const_iterator it = m_vData.begin(); it != m_vData.end(); ++it, ++itPhl)
    {
        const ValueBase* pData = *it;
        // print cat 
        print_space(os, cat_prefix_spaces);
        pData->print_category(os);
        // print default value 
        if (pData->valid_default())
        {
            os << " ("; 
            pData->print_default(os);
            os << ")";
        }
        // print message 
        print_space(os, max_cat_count-*itPhl+cat_option_spaces);
        pData->print_msg(os);
        os << "\n";
    }
}

}} // namespace limbo // programoptions

#endif
