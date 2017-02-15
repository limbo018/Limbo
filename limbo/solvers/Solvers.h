/**
 * @file   Solvers.h
 * @author Yibo Lin
 * @date   Feb 2017
 * @brief  Basic utilities such as variables and linear expresions in solvers 
 */
#include <vector>
#include <limit>

/// namespace for Limbo 
namespace limbo 
{
/// namespace for Limbo.Solvers 
namespace solvers 
{

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
    protected:
        /// @brief copy object 
        void copy(Variable const& rhs)
        {
            m_id = rhs.m_id; 
        }

        unsigned int m_id; ///< variable index 
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

/// @brief Describe linear expresions in optimization problem 
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

/// @brief Optimization objective 
enum OptObjective
{
    MIN, ///< minimize objective 
    MAX ///< maximize objective 
};

/// @brief model to describe an optimization problem 
/// @param T coefficient type 
template <typename T>
class LinearModel 
{
    public:
        /// @brief T coefficient 
        typedef T value_type; 

        /// @brief constructor 
        LinearModel()
        {
        }
        /// @brief copy constructor 
        /// @param rhs right hand side 
        LinearModel(LinearModel const& rhs)
        {
            copy(rhs);
        }
        /// @brief assignment 
        /// @param rhs right hand side 
        LinearModel& operator=(LinearModel const& rhs)
        {
            if (this != &rhs)
                copy(rhs);
            return *this;
        }
        /// @brief destructor 
        ~LinearModel()
        {
        }

        /// @return array of constraints 
        std::vector<LinearConstraint<value_type> > const& constraints() const {return m_vConstraint;}
        /// @param vConstraint array of constraints 
        void setConstraints(std::vector<LinearConstraint<value_type> > const& vConstraint) {m_vConstraint = vConstraint;}
        /// @return objective 
        LinearExpression<value_type> const& objective() const {return m_objective;}
        /// @param obj objective 
        void setObjective(LinearExpression<value_type> const& obj) {m_objective = obj;}
        /// @return optimization objective, whether maximize or minimize the objective 
        OptObjective optObjective() const {return m_optObj;}
        /// @param optObj optimization objective 
        void setOptObjective(OptObjective optObj) {m_optObj = optObj;}
    protected:
        /// @brief copy object 
        void copy(LinearModel const& rhs)
        {
            m_vConstraint = rhs.m_vConstraint;
            m_objective = rhs.m_objective; 
            m_optObj = rhs.m_optObj;
        }

        std::vector<LinearConstraint<value_type> > m_vConstraint; ///< constraints 
        LinearExpression<value_type> m_objective; ///< objective 
        OptObjective m_optObj; ///< optimization objective 
};

} // namespace solvers 
} // namespace limbo 
