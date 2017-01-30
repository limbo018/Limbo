/**
 * @file   ProgramOptions.h
 * @brief  Top API for Limbo.ProgramOptions
 *
 * Mimic Boost.ProgramOptions with easy wrapper for program to parser command line options
 *
 * @author Yibo Lin
 * @date   Jul 2015
 */

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
            , m_help(false)
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
        /// \return true if this option is a help option and it is on 
        virtual bool help_on() const = 0;

        std::string const& category() const {return m_category;}
        std::string const& msg() const {return m_msg;}
        bool help() const {return m_help;}
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
            m_help = rhs.m_help;
            m_required = rhs.m_required;
            m_valid = rhs.m_valid;
            m_toggle = rhs.m_toggle;
        }

        std::string m_category; ///< category 
        std::string m_msg; ///< helper message 
        unsigned char m_help : 1; ///< whether is help option 
        unsigned char m_required : 1; ///< whether the value is a required option
        unsigned char m_valid : 1; ///< true if target is set, not default 
        unsigned char m_toggle : 1; ///< true if this option is a toggle value 
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
        virtual bool help_on() const 
        {
            // only true when this option is already set 
            if (m_help && m_target && boolean_helper<value_type>()(*m_target))
                return true;
            else return false;
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
        virtual Value& help(bool h)
        {
            m_help = h;
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

        ProgramOptions(std::string const& title = "Available options");
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

inline ProgramOptions::ProgramOptions(std::string const& title) 
    : m_title(title) 
{}

template <typename ValueType>
ProgramOptions& ProgramOptions::add_option(ValueType const& data) 
{
    std::pair<cat2index_map_type::iterator, bool> insertRet = m_mCat2Index.insert(std::make_pair(data.category(), m_vData.size()));
    if (insertRet.second) // only create new data when it is not in the map
        m_vData.push_back(new ValueType (data));
    return *this;
}

}} // namespace limbo // programoptions

#endif
