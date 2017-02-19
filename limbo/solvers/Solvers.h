/**
 * @file   Solvers.h
 * @author Yibo Lin
 * @date   Feb 2017
 * @brief  Basic utilities such as variables and linear expressions in solvers 
 */

#ifndef LIMBO_SOLVERS_SOLVERS_H
#define LIMBO_SOLVERS_SOLVERS_H

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <limbo/preprocessor/Msg.h>
#include <limbo/math/Math.h>
#include <limbo/parsers/lp/bison/LpDriver.h>

/// namespace for Limbo 
namespace limbo 
{
/// namespace for Limbo.Solvers 
namespace solvers 
{

/// @brief Some enums used in solver 
enum SolverProperty
{
    MIN, ///< minimize objective 
    MAX, ///< maximize objective 
    BINARY, ///< binary number 
    INTEGER, ///< integer number 
    CONTINUOUS, ///< floating point number 
    OPTIMAL, ///< optimally solved 
    INFEASIBLE, ///< the model is infeasible 
    SUBOPTIMAL, ///< the model is suboptimal 
    UNBOUNDED ///< the model is unbounded 
};

/// @brief Convert @ref limbo::solvers::SolverProperty to std::string 
/// @param sp solver property 
inline std::string toString(SolverProperty sp)
{
    switch (sp)
    {
        case MIN:
            return "MIN";
        case MAX:
            return "MAX";
        case BINARY:
            return "BINARY";
        case INTEGER:
            return "INTEGER";
        case CONTINUOUS:
            return "CONTINUOUS";
        case OPTIMAL:
            return "OPTIMAL";
        case INFEASIBLE:
            return "INFEASIBLE";
        case SUBOPTIMAL:
        default:
            return "SUBOPTIMAL";
    }
}

// forward declaration 
template <typename T>
class Variable;
template <typename T>
class VariableProperty;
template <typename T>
class LinearTerm; 
template <typename T>
class LinearExpression;
template <typename T>
class LinearConstraint;
template <typename T, typename V>
class LinearModel; 

/// @brief Describe variables in optimization problem 
/// @tparam T coefficient type of the variable, not the value type of variable itself. It is necessary for operator overloading 
template <typename T>
class Variable 
{
    public:
        /// @brief coefficient type 
        typedef T coefficient_value_type;

        /// @brief constructor 
        /// @param id variable index 
        Variable(unsigned int id = std::numeric_limits<unsigned int>::max()) 
            : m_id(id) 
        {
        }
        /// @brief copy constructor 
        /// @param rhs right hand side 
        Variable(Variable const& rhs)
        {
            copy(rhs);
        }
        /// @brief assignment 
        /// @param rhs right hand side 
        Variable& operator=(Variable const& rhs)
        {
            if (this != &rhs)
                copy(rhs);
            return *this; 
        }
        /// @brief destructor 
        ~Variable() {}

        /// @return variable index 
        unsigned int id() const {return m_id;}
        /// @brief set variable index 
        /// @param id index 
        void setId(unsigned int id) {m_id = id;}

        /// overload equal 
        /// @param rhs right hand side 
        /// @return true if the indices of variables are equal 
        bool operator==(Variable const& rhs) const 
        {
            return m_id == rhs.m_id;
        }
        /// overload negation 
        /// @return a copy of new object 
        LinearTerm<coefficient_value_type> operator-() const 
        {
            LinearTerm<coefficient_value_type> term (*this); 
            return term.negate();
        }
        /// overload multiply var*coef  
        /// @param var variable 
        /// @param coef coefficient 
        /// @return result object 
        friend LinearTerm<coefficient_value_type> operator*(Variable const& var, coefficient_value_type coef)
        {
            return LinearTerm<coefficient_value_type>(var, coef); 
        }
        /// overload multiply coef*var 
        /// @param var variable 
        /// @param coef coefficient 
        /// @return result object 
        friend LinearTerm<coefficient_value_type> operator*(coefficient_value_type coef, Variable const& var)
        {
            return var*coef; 
        }
        /// overload divide var/coef 
        /// @param var variable 
        /// @param coef coefficient 
        /// @return result object 
        friend LinearTerm<coefficient_value_type> operator/(Variable const& var, coefficient_value_type coef)
        {
            return LinearTerm<coefficient_value_type>(var)/coef; 
        }
        /// overload plus var+var
        /// @param var1 variable 
        /// @param var2 variable 
        /// @return result object 
        friend LinearExpression<coefficient_value_type> operator+(Variable const& var1, Variable const& var2)
        {
            return LinearTerm<coefficient_value_type>(var1)+var2; 
        }
        /// overload minus var-var
        /// @param var1 variable 
        /// @param var2 variable 
        /// @return result object 
        friend LinearExpression<coefficient_value_type> operator-(Variable const& var1, Variable const& var2)
        {
            return LinearTerm<coefficient_value_type>(var1)-var2; 
        }
    protected:
        /// @brief copy object 
        void copy(Variable const& rhs)
        {
            m_id = rhs.m_id; 
        }

        unsigned int m_id; ///< variable index 
};

/// @brief Describe properties of a variable 
/// @tparam V type of variable bound 
template <typename V>
class VariableProperty
{
    public:
        /// type of bounds 
        typedef V variable_value_type; 

        /// @brief constructor 
        /// @param lb lower bound 
        /// @param ub upper bound 
        /// @param nt numeric type 
        /// @param n name 
        VariableProperty(variable_value_type lb, variable_value_type ub, SolverProperty nt, std::string const& n)
            : m_lowerBound(lb)
            , m_upperBound(ub)
            , m_numericType(nt)
            , m_name(n)
        {
        }
        /// @brief copy constructor 
        /// @param rhs right hand side 
        VariableProperty(VariableProperty const& rhs)
        {
            copy(rhs);
        }
        /// @brief assignment 
        /// @param rhs right hand side 
        VariableProperty& operator=(VariableProperty const& rhs)
        {
            if (this != &rhs)
                copy(rhs);
            return *this;
        }

        /// @return lower bound 
        variable_value_type lowerBound() const {return m_lowerBound;}
        /// @param lb lower bound 
        void setLowerBound(variable_value_type lb) {m_lowerBound = lb;}
        /// @param lb lower bound 
        void updateLowerBound(variable_value_type lb) {m_lowerBound = std::max(m_lowerBound, lb);}
        /// @return upper bound 
        variable_value_type upperBound() const {return m_upperBound;}
        /// @param ub upper bound 
        void setUpperBound(variable_value_type ub) {m_upperBound = ub;}
        /// @param ub upper bound 
        void updateUpperBound(variable_value_type ub) {m_upperBound = std::min(m_upperBound, ub);}
        /// @return numeric type 
        SolverProperty numericType() const {return m_numericType;}
        /// @param nt numeric type 
        void setNumericType(SolverProperty nt) 
        {
            m_numericType = nt;
            if (m_numericType == BINARY) // update bounds for binary 
            {
                m_lowerBound = 0; 
                m_upperBound = 1; 
            }
        }
        /// @return name of variable 
        std::string const& name() const {return m_name;}
        /// @param n name 
        void setName(std::string const& n) {m_name = n;}

    protected:
        /// @brief copy object  
        /// @param rhs right hand side 
        void copy(VariableProperty const& rhs)
        {
            m_lowerBound = rhs.m_lowerBound;
            m_upperBound = rhs.m_upperBound; 
            m_numericType = rhs.m_numericType; 
            m_name = rhs.m_name;
        }

        variable_value_type m_lowerBound; ///< lower bound 
        variable_value_type m_upperBound; ///< upper bound 
        SolverProperty m_numericType; ///< numeric type, BINARY, INTEGER, CONTINUOUS
        std::string m_name; ///< name of variable 
};

/// @brief Linear term 
/// @tparam T coefficient type 
template <typename T>
class LinearTerm
{
    public:
        /// @brief coefficient type 
        typedef T coefficient_value_type;
        /// @brief variable type 
        typedef Variable<coefficient_value_type> variable_type; 

        /// @brief constructor 
        /// @param var variable 
        /// @param coef coefficient 
        LinearTerm(variable_type var = variable_type(), coefficient_value_type coef = 1)
            : m_var(var)
            , m_coef(coef)
        {
        }
        /// @brief copy constructor 
        /// @param rhs right hand side 
        LinearTerm(LinearTerm const& rhs)
        {
            copy(rhs);
        }
        /// @brief assignment 
        /// @param rhs right hand side 
        LinearTerm& operator=(LinearTerm const& rhs)
        {
            if (this != &rhs)
                copy(rhs);
            return *this;
        }
        /// @brief destructor 
        ~LinearTerm()
        {
        }

        /// @return variable 
        variable_type const& variable() const {return m_var;}
        /// @param var variable
        void setVariable(variable_type const& var) {m_var = var;}
        /// @return coefficient 
        coefficient_value_type coefficient() const {return m_coef;}
        /// @param coef coefficient 
        void setCoefficient(coefficient_value_type coef) {m_coef = coef;}

        /// overload negation 
        /// @return a copy of new object 
        LinearTerm operator-() const 
        {
            LinearTerm term (*this); 
            return term.negate();
        }
        /// self-negation 
        /// @return the object 
        LinearTerm& negate() 
        {
            m_coef = -m_coef; 
            return *this; 
        }
        /// overload multiply by a value 
        /// @param term term 
        /// @param coef coefficient 
        /// @return result object 
        friend LinearTerm operator*(LinearTerm const& term, coefficient_value_type coef)
        {
            LinearTerm other (term); 
            other *= coef; 
            return other; 
        }
        /// overload a value multiply a term
        /// @param coef coefficient
        /// @param term term 
        /// @return result object 
        friend LinearTerm operator*(coefficient_value_type coef, LinearTerm const& term)
        {
            return term*coef; 
        }
        /// overload multiply and assignment  
        /// @param coef coefficient 
        /// @return reference to the object 
        LinearTerm& operator*=(coefficient_value_type coef)
        {
            m_coef *= coef; 
            return *this;
        }
        /// overload divide by a value 
        /// @param term term 
        /// @param coef coefficient 
        /// @return reference to the object 
        friend LinearTerm operator/(LinearTerm const& term, coefficient_value_type coef)
        {
            LinearTerm other (term); 
            other /= coef; 
            return other; 
        }
        /// overload divide and assignment 
        /// @param coef coefficient 
        /// @return reference to the object 
        LinearTerm& operator/=(coefficient_value_type coef)
        {
            m_coef /= coef; 
            return *this; 
        }
        /// overload plus term+var 
        /// @param term term 
        /// @param var variable 
        /// @return expression 
        friend LinearExpression<coefficient_value_type> operator+(LinearTerm const& term, variable_type const& var)
        {
            return term+LinearTerm(var);
        }
        /// overload plus term+var 
        /// @param term term 
        /// @param var variable 
        /// @return expression 
        friend LinearExpression<coefficient_value_type> operator+(variable_type const& var, LinearTerm const& term)
        {
            return LinearTerm(var)+term;
        }
        /// overload plus for two terms 
        /// @param term1 term 
        /// @param term2 term 
        /// @return result expression 
        friend LinearExpression<coefficient_value_type> operator+(LinearTerm const& term1, LinearTerm const& term2)
        {
            LinearExpression<coefficient_value_type> expr (term1);
            expr += term2; 
            return expr; 
        }
        /// overload minus term-var 
        /// @param term term 
        /// @param var variable 
        /// @return expression 
        friend LinearExpression<coefficient_value_type> operator-(LinearTerm const& term, variable_type const& var)
        {
            return term-LinearTerm(var);
        }
        /// overload minus term-var 
        /// @param term term 
        /// @param var variable 
        /// @return expression 
        friend LinearExpression<coefficient_value_type> operator-(variable_type const& var, LinearTerm const& term)
        {
            return LinearTerm(var)-term;
        }
        /// overload minus for two terms 
        /// @param term1 term 
        /// @param term2 term 
        /// @return result expression 
        friend LinearExpression<coefficient_value_type> operator-(LinearTerm const& term1, LinearTerm const& term2)
        {
            LinearExpression<coefficient_value_type> expr (term1);
            expr -= term2; 
            return expr; 
        }
        /// @brief overload < 
        /// @param term linear term 
        /// @param rhs right hand side constant 
        friend LinearConstraint<coefficient_value_type> operator<(LinearTerm const& term, coefficient_value_type rhs)
        {
            return LinearConstraint<coefficient_value_type>(term, rhs, '<');
        }
        /// @brief overload <=, same as < 
        /// @param term linear term 
        /// @param rhs right hand side constant 
        friend LinearConstraint<coefficient_value_type> operator<=(LinearTerm const& term, coefficient_value_type rhs)
        {
            return (term < rhs);
        }
        /// @brief overload > 
        /// @param term linear term 
        /// @param rhs right hand side constant 
        friend LinearConstraint<coefficient_value_type> operator>(LinearTerm const& term, coefficient_value_type rhs)
        {
            return LinearConstraint<coefficient_value_type>(term, rhs, '>');
        }
        /// @brief overload >=, same as >
        /// @param term linear term 
        /// @param rhs right hand side constant 
        friend LinearConstraint<coefficient_value_type> operator>=(LinearTerm const& term, coefficient_value_type rhs)
        {
            return (term > rhs);
        }
        /// overload == 
        /// @param term linear term 
        /// @param rhs right hand side constant 
        friend LinearConstraint<coefficient_value_type> operator==(LinearTerm const& term, coefficient_value_type rhs)
        {
            return LinearConstraint<coefficient_value_type>(term, rhs, '=');
        }
        /// overload equal 
        /// @param rhs right hand side 
        /// @return true if two terms are equal 
        bool operator==(LinearTerm const& rhs) const 
        {
            return m_var == rhs.m_var && m_coef == rhs.m_coef;
        }
    protected:
        /// @brief copy object 
        /// @param rhs right hand side 
        void copy(LinearTerm const& rhs)
        {
            m_var = rhs.m_var;
            m_coef = rhs.m_coef; 
        }

        variable_type m_var; ///< variable 
        coefficient_value_type m_coef; ///< coefficient 
};

/// @brief Comapre term by variable 
struct CompareTermByVariable
{
    /// @tparam TermType term type 
    /// @param t1 term 
    /// @param t2 term 
    /// @return true if the variable of \a t1 is smaller than that of \a t2 
    template <typename TermType>
    bool operator()(TermType const& t1, TermType const& t2) const 
    {
        return t1.variable().id() < t2.variable().id();
    }
};

/// @brief Describe linear expressions in optimization problem 
/// @tparam T coefficient type 
template <typename T>
class LinearExpression 
{
    public:
        /// @brief coefficient type 
        typedef T coefficient_value_type;
        /// @brief term type 
        typedef LinearTerm<coefficient_value_type> term_type;
        /// @brief variable type 
        typedef Variable<coefficient_value_type> variable_type; 

        /// @brief constructor
        LinearExpression()
        {
        }
        /// @brief constructor 
        LinearExpression(term_type const& term)
        {
            m_vTerm.push_back(term);
        }
        /// @brief copy constructor 
        /// @param rhs right hand side 
        LinearExpression(LinearExpression const& rhs)
        {
            copy(rhs);
        }
        /// @brief assignment 
        /// @param rhs right hand side 
        LinearExpression& operator=(LinearExpression const& rhs)
        {
            if (this != &rhs)
                copy(rhs);
            return *this;
        }
        /// @brief destructor 
        ~LinearExpression()
        {
        }

        /// @return terms 
        std::vector<term_type> const& terms() const {return m_vTerm;}
        /// @brief clear expression 
        void clear() {m_vTerm.clear();}

        /// overload plus 
        /// @param expr expression 
        /// @param term right hand side is a term 
        /// @return result object 
        friend LinearExpression operator+(LinearExpression const& expr, term_type const& term)
        {
            LinearExpression other (expr); 
            other += term; 
            return other; 
        }
        /// overload plus term+expr 
        /// @param expr expression 
        /// @param term a term 
        /// @return result object 
        friend LinearExpression operator+(term_type const& term, LinearExpression const& expr)
        {
            return expr+term; 
        }
        /// overload plus expr+expr 
        /// @param expr1 expression 
        /// @param expr2 expression
        /// @return result object 
        friend LinearExpression operator+(LinearExpression const& expr1, LinearExpression const& expr2)
        {
            LinearExpression other (expr1);
            other += expr2; 
            return other; 
        }
        /// overload plus assignment  
        /// @param term right hand side is a term 
        /// @return the object 
        LinearExpression& operator+=(term_type const& term)
        {
            m_vTerm.push_back(term); 
            return *this; 
        }
        /// overload plus assignment for expression 
        /// @param expr right hand side is an expression
        /// @return the object 
        LinearExpression& operator+=(LinearExpression const& expr)
        {
            m_vTerm.insert(m_vTerm.end(), expr.terms().begin(), expr.terms().end()); 
            return *this; 
        }
        /// overload minus 
        /// @param expr expression 
        /// @param term right hand side is a term 
        /// @return the object 
        friend LinearExpression operator-(LinearExpression const& expr, term_type const& term)
        {
            LinearExpression other (expr); 
            other -= term; 
            return other; 
        }
        /// overload minus term-expr
        /// @param term term 
        /// @param expr expression 
        /// @return the object 
        friend LinearExpression operator-(term_type const& term, LinearExpression const& expr)
        {
            return (-expr)+term; 
        }
        /// overload minus 
        /// @param expr1 expression 
        /// @param expr2 expression 
        /// @return the object 
        friend LinearExpression operator-(LinearExpression const& expr1, LinearExpression const& expr2)
        {
            LinearExpression other (expr1); 
            other -= expr2; 
            return other; 
        }
        /// overload minus assignment  
        /// @param term right hand side is a term 
        /// @return the object 
        LinearExpression& operator-=(term_type term)
        {
            term.setCoefficient(-term.coefficient());
            return this->operator+=(term);
        }
        /// overload minus assignment for expression  
        /// @param expr right hand side is an expression
        /// @return the object 
        LinearExpression& operator-=(LinearExpression const& expr)
        {
            for (typename std::vector<term_type>::const_iterator it = expr.terms().begin(), ite = expr.terms().end(); it != ite; ++it)
                this->operator-=(*it);
            return *this;
        }
        /// overload multiply 
        /// @param expr expression 
        /// @param c constant value 
        /// @return the object 
        friend LinearExpression operator*(LinearExpression const& expr, coefficient_value_type c)
        {
            LinearExpression other (expr);
            other *= c; 
            return other; 
        }
        /// overload multiply in case of c*expr 
        /// @param c constant value 
        /// @param expr expression 
        /// @return the object of \a expr
        friend LinearExpression operator*(coefficient_value_type c, LinearExpression const& expr)
        {
            return expr*c; 
        }
        /// overload multiply assignment 
        /// @param c constant value 
        /// @return the object 
        LinearExpression& operator*=(coefficient_value_type c)
        {
            for (typename std::vector<term_type>::iterator it = m_vTerm.begin(); it != m_vTerm.end(); ++it)
                it->setCoefficient(c*it->coefficient());
            return *this; 
        }
        /// overload divide  
        /// @param expr expression 
        /// @param c constant value 
        /// @return the object 
        friend LinearExpression operator/(LinearExpression const& expr, coefficient_value_type c)
        {
            LinearExpression other (expr);
            other /= c; 
            return other; 
        }
        /// overload divide assignment 
        /// @param c constant value 
        /// @return the object 
        LinearExpression& operator/=(coefficient_value_type c)
        {
            for (typename std::vector<term_type>::iterator it = m_vTerm.begin(); it != m_vTerm.end(); ++it)
                it->setCoefficient(it->coefficient()/c);
            return *this; 
        }
        /// overload negation 
        /// @return a copy of new object 
        LinearExpression operator-() const 
        {
            LinearExpression expr (*this); 
            return expr.negate();
        }
        /// self-negation 
        /// @return the object 
        LinearExpression& negate() 
        {
            for (typename std::vector<term_type>::iterator it = m_vTerm.begin(); it != m_vTerm.end(); ++it)
                it->setCoefficient(-it->coefficient());
            return *this; 
        }
        /// @brief overload < 
        /// @param expr linear expression 
        /// @param rhs right hand side constant 
        friend LinearConstraint<coefficient_value_type> operator<(LinearExpression const& expr, coefficient_value_type rhs)
        {
            return LinearConstraint<coefficient_value_type>(expr, rhs, '<');
        }
        /// @brief overload <=, same as < 
        /// @param expr linear expression 
        /// @param rhs right hand side constant 
        friend LinearConstraint<coefficient_value_type> operator<=(LinearExpression const& expr, coefficient_value_type rhs)
        {
            return (expr < rhs);
        }
        /// @brief overload > 
        /// @param expr linear expression 
        /// @param rhs right hand side constant 
        friend LinearConstraint<coefficient_value_type> operator>(LinearExpression const& expr, coefficient_value_type rhs)
        {
            return LinearConstraint<coefficient_value_type>(expr, rhs, '>');
        }
        /// @brief overload >=, same as >
        /// @param expr linear expression 
        /// @param rhs right hand side constant 
        friend LinearConstraint<coefficient_value_type> operator>=(LinearExpression const& expr, coefficient_value_type rhs)
        {
            return (expr > rhs);
        }
        /// overload == 
        /// @param expr linear expression 
        /// @param rhs right hand side constant 
        friend LinearConstraint<coefficient_value_type> operator==(LinearExpression const& expr, coefficient_value_type rhs)
        {
            return LinearConstraint<coefficient_value_type>(expr, rhs, '=');
        }

        /// @brief simplify expression by merge terms of the same variables 
        /// and remove terms with zero coefficients 
        void simplify()
        {
            std::sort(m_vTerm.begin(), m_vTerm.end(), CompareTermByVariable()); 
            // merge terms 
            typename std::vector<term_type>::iterator itw = m_vTerm.begin(); // write iterator 
            typename std::vector<term_type>::iterator itr = m_vTerm.begin(); // read iterator 
            typename std::vector<term_type>::iterator ite = m_vTerm.end();
            for (; itr != ite; ++itr)
            {
                if (itr != itw)
                {
                    if (itr->variable() == itw->variable())
                        itw->setCoefficient(itw->coefficient()+itr->coefficient());
                    else
                    {
                        ++itw; 
                        *itw = *itr; 
                    }
                }
            }
            m_vTerm.resize(std::distance(m_vTerm.begin(), itw+1));
            // remove terms with zero coefficients 
            // the order is not maintained 
            for (itr = m_vTerm.begin(); itr != m_vTerm.end(); )
            {
                if (itr->coefficient() == 0)
                {
                    *itr = m_vTerm.back(); 
                    m_vTerm.pop_back(); 
                }
                else 
                    ++itr; 
            }
        }

    protected:
        /// @brief copy object 
        /// @param rhs right hand side 
        void copy(LinearExpression const& rhs)
        {
            m_vTerm = rhs.m_vTerm;
        }

        std::vector<term_type> m_vTerm; ///< linear expression with terms 
};

/// @brief Describe linear constraint 
/// @tparam T coefficient type 
template <typename T>
class LinearConstraint
{
    public:
        /// @brief coefficient type 
        typedef T coefficient_value_type; 
        /// @brief variable type 
        typedef Variable<coefficient_value_type> variable_type; 
        /// @brief term type 
        typedef LinearTerm<coefficient_value_type> term_type;
        /// @brief expression type 
        typedef LinearExpression<coefficient_value_type> expression_type;

        /// @brief constructor 
        /// @param expr expression 
        /// @param rhs right hand side 
        /// @param s sense 
        LinearConstraint(expression_type expr = expression_type(), coefficient_value_type rhs = 0, char s = '<')
            : m_expr(expr)
            , m_rhs(rhs)
            , m_sense(s)
        {
        }
        /// @brief copy constructor 
        LinearConstraint(LinearConstraint const& rhs)
        {
            copy(rhs);
        }
        /// @brief assignment 
        LinearConstraint& operator=(LinearConstraint const& rhs)
        {
            if (this != &rhs)
                copy(rhs);
            return *this; 
        }
        /// @brief destructor 
        ~LinearConstraint()
        {
        }

        /// @return linear expression 
        expression_type const& expression() const {return m_expr;}
        /// @param expr expression
        void setExpression(expression_type const& expr) {m_expr = expr;}
        /// @return right hand side constant 
        coefficient_value_type rightHandSide() const {return m_rhs;}
        /// @param rhs right hand side 
        void setRightHandSide(coefficient_value_type rhs) {m_rhs = rhs;}
        /// @return sense 
        char sense() const {return m_sense;}
        /// @param s sense 
        void setSense(char s) {m_sense = s;}
        /// @brief simplify expression by merge terms of the same variables 
        void simplify()
        {
            m_expr.simplify();
        }
        /// @brief normalize sense 
        /// @param s target sense 
        void normalize(char s)
        {
            simplify();
            if ((m_sense == '<' && s == '>')
                    || (m_sense == '>' && s == '<'))
            {
                m_expr.negate();
                m_rhs = -m_rhs; 
                m_sense = s; 
            }
        }
        /// @brief scale constraint by a scaling factor 
        /// @param factor scaling factor 
        void scale(coefficient_value_type factor)
        {
            // in case factor is negative 
            if (factor < 0)
            {
                if (m_sense == '<')
                    m_sense = '>';
                else if (m_sense == '>')
                    m_sense = '<';
            }
            m_expr *= factor; 
            m_rhs *= factor; 
        }

    protected:
        /// @brief copy object 
        /// @param rhs right hand side 
        void copy(LinearConstraint const& rhs)
        {
            m_expr = rhs.m_expr;
            m_rhs = rhs.m_rhs;
            m_sense = rhs.m_sense;
        }

        expression_type m_expr; ///< linear expression 
        coefficient_value_type m_rhs; ///< constant at the right hand side 
        char m_sense; ///< sign of operator, < (<=), > (>=), = (==)
};

/// @brief model to describe an optimization problem 
/// @tparam T coefficient type 
/// @tparam V variable type 
template <typename T, typename V>
class LinearModel : public LpParser::LpDataBase
{
    public:
        /// @brief T coefficient 
        typedef T coefficient_value_type; 
        /// @brief V variable 
        typedef V variable_value_type; 
        /// @brief base class 
        typedef LpParser::LpDataBase base_type; 
        /// @brief variable type 
        typedef Variable<coefficient_value_type> variable_type; 
        /// @brief term type 
        typedef LinearTerm<coefficient_value_type> term_type; 
        /// @brief expression type 
        typedef LinearExpression<coefficient_value_type> expression_type; 
        /// @brief constraint type 
        typedef LinearConstraint<coefficient_value_type> constraint_type; 
        /// @brief variable property type 
        typedef VariableProperty<variable_value_type> property_type; 

        /// @brief constructor 
        LinearModel() 
            : base_type()
        {
            m_optType = MIN; 
        }
        /// @brief copy constructor 
        /// @param rhs right hand side 
        LinearModel(LinearModel const& rhs) 
            : base_type(rhs)
        {
            copy(rhs);
        }
        /// @brief assignment 
        /// @param rhs right hand side 
        LinearModel& operator=(LinearModel const& rhs)
        {
            if (this != &rhs)
            {
                this->base_type::operator=(rhs);
                copy(rhs);
            }
            return *this;
        }
        /// @brief destructor 
        ~LinearModel()
        {
        }

        /// @return array of constraints 
        std::vector<constraint_type> const& constraints() const {return m_vConstraint;}
        /// @return array of constraints 
        std::vector<constraint_type>& constraints() {return m_vConstraint;}
        /// @brief add a constraint 
        /// @param constr constraint 
        /// @return true if added 
        bool addConstraint(constraint_type constr) 
        {
            // simplify constraint 
            constr.simplify();
            // verify whether the constraint is actually a bound constraint 
            std::vector<term_type> const& vTerm = constr.expression().terms();
            if (vTerm.empty())
                return false;
            if (vTerm.size() == 1) // one term, bound constraint  
            {
                term_type const& term = vTerm.front();
                switch (constr.sense())
                {
                    case '>':
                        if (term.coefficient() > 0) // lower bound 
                            m_vVariableProperty.at(term.variable().id()).updateLowerBound(constr.rightHandSide()/term.coefficient());
                        else if (term.coefficient() < 0) // upper bound 
                            m_vVariableProperty.at(term.variable().id()).updateUpperBound(constr.rightHandSide()/term.coefficient());
                        break; 
                    case '<':
                        if (term.coefficient() > 0) // upper bound 
                            m_vVariableProperty.at(term.variable().id()).updateUpperBound(constr.rightHandSide()/term.coefficient());
                        else if (term.coefficient() < 0) // lower bound 
                            m_vVariableProperty.at(term.variable().id()).updateLowerBound(constr.rightHandSide()/term.coefficient());
                        break; 
                    case '=':
                        // lower bound 
                        m_vVariableProperty.at(term.variable().id()).updateLowerBound(constr.rightHandSide()/term.coefficient());
                        // upper bound 
                        m_vVariableProperty.at(term.variable().id()).updateUpperBound(constr.rightHandSide()/term.coefficient());
                        break; 
                    default:
                        limboAssertMsg(0, "Unknown sense %c", constr.sense());
                }
            }
            else // actual constraint 
            {
                m_vConstraint.push_back(constr);
            }
            return true; 
        }
        /// @return objective 
        expression_type const& objective() const {return m_objective;}
        /// @param expr objective 
        void setObjective(expression_type const& expr) 
        {
            m_objective = expr;
            m_objective.simplify();
        }
        /// @return optimization objective, whether maximize or minimize the objective 
        SolverProperty optimizeType() const {return m_optType;}
        /// @param optType optimization objective 
        void setOptimizeType(SolverProperty optType) {m_optType = optType;}
        /// @return array of variable properties 
        std::vector<property_type> const& variableProperties() const {return m_vVariableProperty;}
        /// @return array of variable properties 
        std::vector<property_type>& variableProperties() {return m_vVariableProperty;}
        /// @return number of variables 
        unsigned int numVariables() const {return m_vVariableProperty.size();}
        /// @return variable 
        variable_type variable(unsigned int id) const {return variable_type(id);}
        /// @return name of variables 
        std::string variableName(variable_type const& var) const
        {
            char buf[256];
            if (m_vVariableProperty.at(var.id()).name().empty())
                limboSPrint(kNONE, buf, "x%u", var.id());
            else 
                limboSPrint(kNONE, buf, "%s", m_vVariableProperty.at(var.id()).name().c_str());
            return buf; 
        }
        /// @return lower bound of variables 
        variable_value_type variableLowerBound(variable_type const& var) {return m_vVariableProperty.at(var.id()).lowerBound();}
        /// @return upper bound of variables 
        variable_value_type variableUpperBound(variable_type const& var) {return m_vVariableProperty.at(var.id()).upperBound();}
        /// @return numeric type of variable 
        SolverProperty variableNumericType(variable_type const& var) {return m_vVariableProperty.at(var.id()).numericType();}
        /// @brief add one variable 
        /// @param lb lower bound 
        /// @param ub upper bound 
        /// @param nt numeric type 
        /// @param name variable name 
        /// @return variable 
        variable_type addVariable(variable_value_type lb, variable_value_type ub, SolverProperty nt, std::string name = "") 
        {
            m_vVariableProperty.push_back(property_type(lb, ub, nt, name)); 
            m_vVariableSol.push_back(lb);
            return variable_type(m_vVariableProperty.size()-1);
        }
        /// @return array of solution 
        std::vector<variable_value_type> const& variableSolutions() const {return m_vVariableSol;}
        /// @return array of solution 
        std::vector<variable_value_type>& variableSolutions() {return m_vVariableSol;}
        /// @return solution of a variable 
        variable_value_type variableSolution(variable_type const& var) const {return m_vVariableSol.at(var.id());}
        /// @param var variable 
        /// @param v initial solution 
        void setVariableSolution(variable_type const& var, variable_value_type v) {m_vVariableSol.at(var.id()) = v;}
        /// @brief reserve space for variables 
        /// @param n number of variables to reserve 
        void reserveVariables(unsigned int n)
        {
            m_vVariableProperty.reserve(n);
            m_vVariableSol.reserve(n);
        }
        /// @brief reserve space for constraints 
        /// @param n number of constraints to reserve 
        void reserveConstraints(unsigned int n)
        {
            m_vConstraint.reserve(n);
        }
        /// @brief scale objective 
        /// @param factor scaling factor 
        void scaleObjective(coefficient_value_type factor) {m_objective *= factor;}
        /// @brief scaling a constraint 
        /// @param id constraint index 
        /// @param factor scaling factor 
        void scaleConstraint(unsigned int id, coefficient_value_type factor) {m_vConstraint.at(id).scale(factor);}
        /// @brief evaluate expression given solutions of variables 
        /// @param expr expression 
        /// @param vVariableSol variable solutions 
        /// @return result of the expression after applying the solutions 
        coefficient_value_type evaluateExpression(expression_type const& expr, std::vector<variable_value_type> const& vVariableSol) const 
        {
            coefficient_value_type result = 0; 
            for (typename std::vector<term_type>::const_iterator it = expr.terms().begin(), ite = expr.terms().end(); it != ite; ++it)
                result += it->coefficient()*vVariableSol.at(it->variable().id());
            return result;
        }
        /// @brief evaluate objective 
        /// @param vVariableSol variable solutions 
        /// @return objective after applying the solution 
        coefficient_value_type evaluateObjective(std::vector<variable_value_type> const& vVariableSol) const 
        {
            return evaluateExpression(m_objective, vVariableSol);
        }
        /// @brief evaluate objective 
        /// @return objective after applying the solution 
        coefficient_value_type evaluateObjective() const 
        {
            return evaluateExpression(m_objective, m_vVariableSol);
        }
        /// @brief evaluate slackness of a constraint given solutions of variables 
        /// @param constr constraint 
        /// @param vVariableSol variable solutions 
        /// @return slackness is computed as right hand side minum left hand side assuming sense is '<' or '='
        coefficient_value_type evaluateConstraint(constraint_type const& constr, std::vector<variable_value_type> const& vVariableSol) const 
        {
            coefficient_value_type result = constr.rightHandSide()-evaluateExpression(constr.expression(), vVariableSol);
            if (constr.sense() == '>')
                return -result; 
            else 
                return result; 
        }
        /// @brief evaluate slackness of a constraint given solutions of variables 
        /// @param constr constraint 
        /// @return slackness is computed as right hand side minum left hand side assuming sense is '<' or '='
        coefficient_value_type evaluateConstraint(constraint_type const& constr) const 
        {
            return evaluateConstraint(constr, m_vVariableSol);
        }

		/// @brief read lp format 
        /// @param filename input file in lp format 
		/// initializing graph 
		void read(std::string const& filename) 
		{
			LpParser::read(*this, filename);
		}
        /// @name required callback from @ref LpParser::LpDataBase
        ///@{
        /// @brief add variable that \a l <= \a vname <= \a r. 
        /// @param vname variable name 
        /// @param l lower bound 
        /// @param r upper bound 
		void add_variable(std::string const& vname, double l = limbo::lowest<double>(), double r = std::numeric_limits<double>::max())
        {
            // in case of overflow 
            variable_value_type lb = l; 
            variable_value_type ub = r;
            if (l == -10)
                limboAssert(lb == -10);
            if (l <= (double)limbo::lowest<variable_value_type>())
                lb = limbo::lowest<variable_value_type>();
            if (r >= (double)std::numeric_limits<variable_value_type>::max())
                ub = std::numeric_limits<variable_value_type>::max();
            limboAssertMsg(lb <= ub, "failed to add bound %g <= %s <= %g", l, vname.c_str(), r); 
            if (l == -10)
                limboAssert(lb == -10);

			// no variables with the same name is allowed 
            typename std::map<std::string, variable_type>::const_iterator found = m_mName2Variable.find(vname); 
			if (found == m_mName2Variable.end()) // new variable 
				limboAssertMsg(m_mName2Variable.insert(std::make_pair(vname, addVariable(lb, ub, CONTINUOUS, vname))).second,
						"failed to insert variable %s to hash table", vname.c_str());
			else // update variable 
			{
				m_vVariableProperty.at(found->second.id()).updateLowerBound(lb);
				m_vVariableProperty.at(found->second.id()).updateUpperBound(ub);
				limboAssertMsg(m_vVariableProperty.at(found->second.id()).lowerBound() <= m_vVariableProperty.at(found->second.id()).upperBound(), 
                        "failed to set bound %g <= %s <= %g", m_vVariableProperty.at(found->second.id()).lowerBound(), vname.c_str(), m_vVariableProperty.at(found->second.id()).upperBound());
			}
        }
        /// @brief add constraint that \a terms \a compare \a constant. 
        /// @param terms array of terms in left hand side 
        /// @param compare operator '<', '>', '='
        /// @param constant constant in the right hand side 
        void add_constraint(LpParser::TermArray const& terms, char compare, double constant) 
        {
            expression_type expr; 
            for (LpParser::TermArray::const_iterator it = terms.begin(); it != terms.end(); ++it)
            {
                // in case variable is not added yet 
                add_variable(it->var);
                expr += m_mName2Variable.at(it->var)*it->coef; 
            }
            addConstraint(constraint_type(expr, constant, compare));
        }
        /// @brief add object terms 
        /// @param minimize true denotes minimizing object, false denotes maximizing object 
        /// @param terms array of terms 
		void add_objective(bool minimize, LpParser::TermArray const& terms)
        {
            setOptimizeType((minimize)? MIN : MAX); 

            expression_type expr; 
            for (LpParser::TermArray::const_iterator it = terms.begin(); it != terms.end(); ++it)
            {
                // in case variable is not added yet 
                add_variable(it->var);
                expr += m_mName2Variable.at(it->var)*it->coef; 
            }
            setObjective(expr);
        }
        /// @brief set integer variables 
        /// @param vname integer variables  
        /// @param binary denotes whether they are binary variables 
        void set_integer(std::string const& vname, bool binary)
        {
            // in case variable is not added yet 
            add_variable(vname);
            variable_type var = m_mName2Variable.at(vname); 
            if (binary)
                m_vVariableProperty.at(var.id()).setNumericType(BINARY); 
            else 
                m_vVariableProperty.at(var.id()).setNumericType(INTEGER); 
        }
        ///@}

        /// @brief print problem in lp format 
        /// @param os output stream 
        /// @return output stream 
        std::ostream& print(std::ostream& os = std::cout) const 
        {
            switch (optimizeType())
            {
                case MIN:
                    os << "Minimize\n";
                    break; 
                case MAX:
                    os << "Maximize\n";
                    break; 
                default:
                    os << "Unknown\n";
                    break; 
            }

            // print objective 
            print(os, objective()); 

            os << "\n\nSubject To\n";

            // print constraints 
            unsigned int i = 0; 
            for (typename std::vector<constraint_type>::const_iterator it = constraints().begin(), ite = constraints().end(); it != ite; ++it, ++i)
            {
                os << "C" << i << ": ";
                print(os, *it); 
                os << "\n";
            }

            // print bounds 
            os << "Bounds\n";
            i = 0; 
            for (typename std::vector<property_type>::const_iterator it = m_vVariableProperty.begin(), ite = m_vVariableProperty.end(); it != ite; ++it, ++i)
            {
                if (it->lowerBound() <= limbo::lowest<variable_value_type>() && it->upperBound() >= std::numeric_limits<variable_value_type>::max())
                    os << variableName(variable_type(i)) << " free";
                else if (it->lowerBound() <= limbo::lowest<variable_value_type>())
                    os << variableName(variable_type(i)) << " <= " << it->upperBound();
                else if (it->upperBound() >= std::numeric_limits<variable_value_type>::max())
                    os << variableName(variable_type(i)) << " >= " << it->lowerBound();
                else 
                    os << it->lowerBound() << " <= " << variableName(variable_type(i)) << " <= " << it->upperBound();
                os << "\n";
            }

            // print numeric type 
            os << "Generals\n";
            i = 0; 
            for (typename std::vector<property_type>::const_iterator it = m_vVariableProperty.begin(), ite = m_vVariableProperty.end(); it != ite; ++it, ++i)
            {
                if (it->numericType() == BINARY || it->numericType() == INTEGER)
                    os << variableName(variable_type(i)) << "\n";
            }

            os << "End\n"; 

            return os; 
        }
        /// @brief print expression 
        /// @param os output stream 
        /// @param term term
        /// @return output stream 
        std::ostream& print(std::ostream& os, term_type const& term) const 
        {
            os << term.coefficient() << " " << variableName(term.variable());
            return os; 
        }
        /// @brief print expression 
        /// @param os output stream 
        /// @param expr expression
        /// @return output stream 
        std::ostream& print(std::ostream& os, expression_type const& expr) const 
        {
            int i = 0; 
            for (typename std::vector<term_type>::const_iterator it = expr.terms().begin(), ite = expr.terms().end(); it != ite; ++it, ++i)
            {
                if (i)
                    os << " + "; 
                print(os, *it);
                if (i%4 == 3)
                    os << "\n";
            }
            return os; 
        }
        /// @brief print constraint 
        /// @param os output stream 
        /// @param constr constraint 
        /// @return output stream 
        std::ostream& print(std::ostream& os, constraint_type const& constr) const 
        {
            print(os, constr.expression());
            if (constr.sense() == '=')
                os << " " << constr.sense() << " " << constr.rightHandSide();
            else 
                os << " " << constr.sense() << "= " << constr.rightHandSide();
            return os;  
        }
        /// @brief print solutions 
        /// @param os output stream 
        /// @return output stream 
        std::ostream& printSolution(std::ostream& os = std::cout) const 
        {
            coefficient_value_type obj = evaluateObjective(); 
            os << "# Objective " << obj << "\n";
            for (unsigned int i = 0, ie = variableSolutions().size(); i < ie; ++i)
                os << variableName(variable_type(i)) << " " << variableSolution(variable_type(i)) << "\n";
            return os; 
        }
    protected:
        /// @brief copy object 
        void copy(LinearModel const& rhs)
        {
            m_vConstraint = rhs.m_vConstraint;
            m_objective = rhs.m_objective; 
            m_vVariableProperty = rhs.m_vVariableProperty;
            m_optType = rhs.m_optType;

            m_vVariableSol = rhs.m_vVariableSol;

            m_mName2Variable = rhs.m_mName2Variable; 
        }

        std::vector<constraint_type> m_vConstraint; ///< constraints 
        expression_type m_objective; ///< objective 
        std::vector<property_type> m_vVariableProperty; ///< variable properties  
        SolverProperty m_optType; ///< optimization objective 

        std::vector<variable_value_type> m_vVariableSol; ///< variable solutions, it can be either initial solution or final solution 

        std::map<std::string, variable_type> m_mName2Variable; ///< mapping from variable name to variable, only used when reading from files 
};

} // namespace solvers 
} // namespace limbo 

#endif
