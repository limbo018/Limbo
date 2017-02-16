/**
 * @file   Solvers.h
 * @author Yibo Lin
 * @date   Feb 2017
 * @brief  Basic utilities such as variables and linear expressions in solvers 
 */
#include <iostream>
#include <limit>
#include <string>
#include <vector>
#include <algorithm>
#include <limbo/preprocessor/Msg.h>

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
    SUBOPTIMAL ///< the model is suboptimal 
};

/// @brief Describe variables in optimization problem 
class Variable 
{
    public:
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
    protected:
        /// @brief copy object 
        void copy(Variable const& rhs)
        {
            m_id = rhs.m_id; 
        }

        unsigned int m_id; ///< variable index 
};

/// @brief Describe properties of a variable 
/// @tparam T type of variable bound 
template <typename T>
class VariableProperty
{
    public:
        /// type of bounds 
        typedef T value_type; 

        /// @brief constructor 
        /// @param lb lower bound 
        /// @param ub upper bound 
        /// @param nt numeric type 
        /// @param n name 
        VariableProperty(value_type lb, value_type ub, SolverProperty nt, std::string const& n)
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
        value_type lowerBound() const {return m_lowerBound;}
        /// @param lb lower bound 
        void setLowerBound(value_type lb) {m_lowerBound = lb;}
        /// @param lb lower bound 
        void updateLowerBound(value_type lb) {m_lowerBound = std::max(m_lowerBound, lb);}
        /// @return upper bound 
        value_type upperBound() const {return m_upperBound;}
        /// @param up upper bound 
        void setUpperBound(value_type ub) {m_upperBound = ub;}
        /// @param up upper bound 
        void updateUpperBound(value_type ub) {m_upperBound = std::min(m_upperBound, ub);}
        /// @return numeric type 
        SolverProperty numericType() const {return m_numericType;}
        /// @param nt numeric type 
        void setNumericType(SolverProperty nt) {m_numericType = nt;}
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

        value_type m_lowerBound; ///< lower bound 
        value_type m_upperBound; ///< upper bound 
        SolverProperty m_numericType; ///< numeric type, BINARY, INTEGER, CONTINUOUS
        std::string m_name; ///< name of variable 
};

/// @brief Linear term 
/// @tparam T coefficient type 
template <typename T>
class LinearTerm
{
    public:
        /// @coefficient type 
        typedef T value_type;

        /// @brief constructor 
        /// @param var variable 
        /// @param coef coefficient 
        LinearTerm(Variable var, value_type coef = 1)
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
        Variable const& variable() const {return m_var;}
        /// @param var variable
        void setVariable(Variable const& var) {m_var = var;}
        /// @return coefficient 
        value_type coefficient() const {return m_coef;}
        /// @param coef coefficient 
        void setCoefficient(value_type coef) {m_coef = coef;}

        /// overload multiply by a value 
        /// @param coef coefficient 
        /// @return reference to the object 
        LinearTerm& operator*(value_type coef)
        {
            m_coef *= coef; 
            return *this;
        }
        /// overload a value multiply a term
        friend LinearTerm operator*(value_type coef, LinearTerm const& term)
        {
            return term*coef; 
        }
        /// overload divide by a value 
        /// @param coef coefficient 
        /// @return reference to the object 
        LinearTerm& operator/(value_type coef)
        {
            m_coef /= coef; 
            return *this; 
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

        Variable m_var; ///< variable 
        value_type m_coef; ///< coefficient 
};

/// @brief Comapre term by variable 
struct CompareTermByVariable
{
    /// @tparam TermType term type 
    /// @param t1 term 
    /// @param t2 term 
    /// @return true if the variable of \t1 is smaller than that of \t2 
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
        typedef T value_type;

        /// @brief constructor
        /// @param c constant value 
        LinearExpression()
        {
        }
        /// @brief constructor 
        LinearExpression(LinearTerm const& term)
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

        /// overload plus 
        /// @param term right hand side is a term 
        /// @return the object 
        LinearExpression& operator+(LinearTerm const& term)
        {
            m_vTerm.push_back(term); 
            return *this; 
        }
        /// overload minus 
        /// @param term right hand side is a term 
        /// @return the object 
        LinearExpression& operator-(LinearTerm term)
        {
            term.setCoefficient(-term.coefficient());
            return this->operator+(term);
        }
        /// overload multiply 
        /// @param c constant value 
        /// @return the object 
        LinearExpression& operator*(value_type c)
        {
            for (std::vector<LinearTerm<value_type> >::iterator it = m_vTerm.begin(); it != m_vTerm.end(); ++it)
                it->setCoefficient(c*it->coefficient());
            return *this; 
        }
        /// overload multiply in case of c*expr 
        /// @param c constant value 
        /// @param expr expression 
        /// @return the object of \expr
        friend LinearExpression& operator*(value_type c, LinearExpression& expr)
        {
            return expr.operator*(c); 
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
            for (std::vector<LinearTerm<value_type> >::iterator it = m_vTerm.begin(); it != m_vTerm.end(); ++it)
                it->setCoefficient(-it->coefficient());
            return *this; 
        }

        /// @brief simplify expression by merge terms of the same variables 
        void simplify()
        {
            std::sort(m_vTerm.begin(), m_vTerm.end(), CompareTermByVariable()); 
            std::vector<LinearTerm>::iterator itw = m_vTerm.begin(); // write iterator 
            std::vector<LinearTerm>::iterator itr = m_vTerm.begin(); // read iterator 
            std::vector<LinearTerm>::iterator ite = m_vTerm.end();
            for (; itr != ite; ++itr)
            {
                if (itr != itw)
                {
                    if (itr->variable() == itw->variable())
                        itw->setCoefficient(itw->coefficient()+itr->coefficient());
                    else
                        ++itw; 
                }
            }
            m_vTerm.resize(std::distance(m_vTerm.begin(), itw+1));
        }

    protected:
        /// @brief copy object 
        /// @param rhs right hand side 
        void copy(LinearExpression const& rhs)
        {
            m_vTerm = rhs.m_vTerm;
        }

        std::vector<LinearTerm> m_vTerm; ///< linear expression with terms 
};

/// @brief Describe linear constraint 
/// @tparam T coefficient type 
template <typename T>
class LinearConstraint
{
    public:
        /// @brief coefficient type 
        typedef T value_type; 

        /// @brief constructor 
        /// @param expr expression 
        /// @param rhs right hand side 
        /// @param s sense 
        LinearConstraint(LinearExpression expr = LinearExpression(), value_type rhs = 0, char s = '<')
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
        LinearExpression<value_type> const& expression() const {return m_expr;}
        /// @param expr expression
        void setExpression(LinearExpression<value_type> const& expr) {m_expr = expr;}
        /// @return right hand side constant 
        value_type rightHandSide() const {return m_rhs;}
        /// @param rhs right hand side 
        void setRightHandSide(value_type rhs) {m_rhs = rhs;}
        /// @return sense 
        char sense() const {return m_sense;}
        /// @param s sense 
        void setSense(char s) {m_sense = s;}
        /// @brief normalize sense 
        /// @param s target sense 
        void normalize(char s)
        {
            if ((m_sense == '<' && s == '>')
                    || (m_sense == '>' && s == '<'))
            {
                m_expr.negate();
                m_rhs = -m_rhs; 
                m_sense = s; 
            }
        }

        /// @brief overload < 
        /// @param expr linear expression 
        /// @param rhs right hand side constant 
        friend LinearConstraint& operator<(LinearExpression const& expr, value_type rhs)
        {
            return LinearConstraint(expr, rhs, '<');
        }
        /// @brief overload <=, same as < 
        /// @param expr linear expression 
        /// @param rhs right hand side constant 
        friend LinearConstraint& operator<=(LinearExpression const& expr, value_type rhs)
        {
            return (expr < rhs);
        }
        /// @brief overload > 
        /// @param expr linear expression 
        /// @param rhs right hand side constant 
        friend LinearConstraint& operator>(LinearExpression const& expr, value_type rhs)
        {
            return LinearConstraint(expr, rhs, '>');
        }
        /// @brief overload >=, same as >
        /// @param expr linear expression 
        /// @param rhs right hand side constant 
        friend LinearConstraint& operator>=(LinearExpression const& expr, value_type rhs)
        {
            return (expr > rhs);
        }
        /// overload == 
        /// @param expr linear expression 
        /// @param rhs right hand side constant 
        friend LinearConstraint& operator==(LinearExpression const& expr, value_type rhs)
        {
            return LinearConstraint(expr, rhs, '=');
        }
    protected:
        LinearExpression<value_type> m_expr; ///< linear expression 
        value_type m_rhs; ///< constant at the right hand side 
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
                        limboAssertMsg(0, 'Unknown sense %c', constr.sense());
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
        /// @return objective 
        expression_type& objective() const {return m_objective;}
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
        Variable variable(unsigned int id) const {return Variable(id);}
        /// @return name of variables 
        std::string variableName(Variable const& var) const
        {
            char buf[256];
            if (m_vVariableProperty.at(var.id()).name().empty())
                limboSPrint(kNONE, buf, "x%u", var.id());
            else 
                limboSPrint(kNONE, buf, "%s", m_vVariableProperty.at(var.id()).name().c_str());
            return buf; 
        }
        /// @return lower bound of variables 
        variable_value_type variableLowerBound(Variable const& var) {return m_vVariableProperty.at(var.id()).lowerBound();}
        /// @return upper bound of variables 
        variable_value_type variableUpperBound(Variable const& var) {return m_vVariableProperty.at(var.id()).upperBound();}
        /// @return numeric type of variable 
        SolverProperty variableNumericType(Variable const& var) {return m_vVariableProperty.at(var.id()).numericType();}
        /// @brief add one variable 
        /// @param lb lower bound 
        /// @param ub upper bound 
        /// @param nt numeric type 
        /// @param name variable name 
        /// @return variable 
        Variable addVariable(variable_value_type lb, variable_value_type ub, SolverProperty nt, std::string name = "") 
        {
            m_vVariableProperty.push_back(VariableProperty(lb, ub, nt, name)); 
            m_vVariableSol.push_back(lb);
            return Variable(m_vVariableProperty.size()-1);
        }
        /// @return array of solution 
        std::vector<variable_value_type> const& variableSolutions() const {return m_vVariableSol;}
        /// @return array of solution 
        std::vector<variable_value_type>& variableSolutions() {return m_vVariableSol;}
        /// @return solution of a variable 
        variable_value_type variableSolution(Variable const& var) const {return m_vVariableSol.at(var.id());}
        /// @param var variable 
        /// @param v initial solution 
        void setVariableSolution(Variable const& var, variable_value_type v) {m_vVariableSol.at(var.id()) = v;}
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
        /// @brief evaluate expression given solutions of variables 
        /// @param expr expression 
        /// @param vVariableSol variable solutions 
        /// @return result of the expression after applying the solutions 
        coefficient_value_type evaluateExpression(expression_type const& expr, std::vector<variable_value_type> const& vVariableSol) const 
        {
            coefficient_value_type result = 0; 
            for (std::vector<term_type>::const_iterator it = expr.terms().begin(), ite = expr.terms().end(); it != ite; ++it)
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
		void read_lp(string const& filename) 
		{
			LpParser::read(*this, filename);
		}

        /// @brief print problem in lp format 
        /// @param os output stream 
        /// @return output stream 
        std::ostream& print(std::ostream& os) const 
        {
            switch (optType())
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
            for (std::vector<constraint_type>::const_iterator it = constraints().begin(), ite = constraints().end(); it != ite; ++it, ++i)
            {
                os << "C" << i << ": ";
                print(os, *it); 
                os << "\n";
            }

            // print bounds 
            for (std::vector<property_type>::const_iterator it = m_vVariableProperty.begin(), ite = m_vVariableProperty.end(); it != ite; ++it)
            {
                if (it->lowerBound() <= std::numeric_limits<variable_value_type>::min() && it->upperBound() >= std::numeric_limits<variable_value_type>::max())
                    os << it->name() << " free";
                else if (it->lowerBound() <= std::numeric_limits<variable_value_type>::min())
                    os << it->name() << " <= " << it->upperBound();
                else if (it->upperBound() >= std::numeric_limits<variable_value_type>::max())
                    os << it->name() << " >= " << it->lowerBound();
                else 
                    os << it->lowerBound() << " <= " << it->name() << " <= " << it->upperBound();
                os << "\n";
            }

            // print numeric type 
            os << "General\n";
            for (std::vector<property_type>::const_iterator it = m_vVariableProperty.begin(), ite = m_vVariableProperty.end(); it != ite; ++it)
            {
                if (it->numericType() == BINARY || it->numericType() == INTEGER)
                    os << it->name() << "\n";
            }

            os << "End"; 

            return os; 
        }
        /// @brief print expression 
        /// @param os output stream 
        /// @param expr term
        /// @return output stream 
        std::ostream& print(std::ostream& os, term_type const& term) const 
        {
            os << term.coefficient() << "*" << variableName(term.variable());
            return os; 
        }
        /// @brief print expression 
        /// @param os output stream 
        /// @param expr expression
        /// @return output stream 
        std::ostream& print(std::ostream& os, expression_type const& expr) const 
        {
            int i = 0; 
            for (std::vector<term_type>::const_iterator it = expr.terms().begin(), ite = expr.terms().end(); it != ite; ++it, ++i)
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
            os << " " << constr.sense() << " " << constr.rightHandSide();
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
        }

        std::vector<constraint_type> m_vConstraint; ///< constraints 
        expression_type m_objective; ///< objective 
        std::vector<property_type> m_vVariableProperty; ///< variable properties  
        SolverProperty m_optType; ///< optimization objective 

        std::vector<variable_value_type> m_vVariableSol; ///< variable solutions, it can be either initial solution or final solution 
};

} // namespace solvers 
} // namespace limbo 
