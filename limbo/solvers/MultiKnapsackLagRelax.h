/**
 * @file   MultiKnapsackLagRelax.h
 * @author Yibo Lin
 * @date   Feb 2017
 * @brief  Solve multiple knapsack problem with lagrangian relaxation 
 */
#ifndef LIMBO_SOLVERS_MULTIKNAPSACKLAGRELAX_H
#define LIMBO_SOLVERS_MULTIKNAPSACKLAGRELAX_H

#include <cmath>
#include <limbo/solvers/Solvers.h>

/// namespace for Limbo 
namespace limbo 
{
/// namespace for Limbo.Solvers 
namespace solvers 
{

// forward declaration 
template <typename T>
class LagMultiplierUpdater;
template <typename T>
class SubGradientDescent; 
template <typename T, typename V>
class ProblemScaler; 

/// @brief Solve multiple knapsack problem with lagrangian relaxation 
/// 
/// Suppose we have a set of item \f$C\f$ and a set of knapsack \f$B\f$. 
/// Use \f$x_{ij}\f$ to denote item \f$i\f$ is assigned to knapsack \f$j\f$. 
/// The primal problem \f$P\f$ is as follows, \n
/// \f{eqnarray*}{
/// & min. & \sum_{i,j} c_{ij} \cdot x_{ij}, \\
/// & s.t. & \sum_{i} a_i x_{ij} \le b_j, \forall j \in B,  \\
/// &      & \sum_{j} x_{ij} = 1, \forall i \in C, \\
/// &      & x_{ij} \in \{0, 1\}, \forall i \in C, j \in B.  
/// \f}
/// \n
/// 
/// The procedure to solve the problem is to iteratively solve following 
/// lagrangian subproblem \f$L\f$, 
/// \f{eqnarray*}{
/// & min. & \sum_{i,j} c_{ij} \cdot x_{ij} + \sum_{j} \lambda_j (\sum_{i} a_i x_{ij} - b_j), \\
/// & s.t. & \sum_{j} x_{ij} = 1, \forall i \in C, \\
/// &      & x_{ij} \in \{0, 1\}, \forall i \in C, j \in B.  
/// \f}
/// \n
/// where the subproblem can be solved simply by sorting the weight of \f$x_{ij}\f$ 
/// and pick the ones with least cost in each iteration. 
/// However, it is difficult to check optimality conditions. 
/// So we track the evolution of capacity violations 
/// and stop once we observe no significant improvement. 
/// The rest violations are solved by heuristic approaches. 
/// 
/// @tparam T coefficient type 
/// @tparam V variable type 
template <typename T, typename V>
class MultiKnapsackLagRelax
{
    public:
        /// @brief linear model type for the problem 
        typedef LinearModel<T, V> model_type; 
        /// @nowarn
        typedef typename model_type::coefficient_value_type coefficient_value_type; 
        typedef typename model_type::variable_value_type variable_value_type; 
        typedef typename model_type::variable_type variable_type;
        typedef typename model_type::constraint_type constraint_type; 
        typedef typename model_type::expression_type expression_type; 
        typedef typename model_type::term_type term_type; 
        typedef typename model_type::property_type property_type;
        typedef LagMultiplierUpdater<coefficient_value_type> updater_type; 
        typedef ProblemScaler<coefficient_value_type, variable_value_type> scaler_type; 
        /// @endnowarn
        
        /// @brief constructor 
        /// @param model pointer to the model of problem 
        MultiKnapsackLagRelax(model_type* model);
        /// @brief copy constructor 
        /// @param rhs right hand side 
        MultiKnapsackLagRelax(MultiKnapsackLagRelax const& rhs);
        /// @brief assignment
        /// @param rhs right hand side 
        MultiKnapsackLagRelax& operator=(MultiKnapsackLagRelax const& rhs);
        /// @brief destructor 
        ~MultiKnapsackLagRelax(); 
        
        /// @brief API to run the algorithm 
        /// @param updater an object to update lagrangian multipliers, use default updater if NULL  
        /// @param scaler an object to scale constraints and objective, use default scaler if NULL 
        SolverProperty operator()(updater_type* updater = NULL, scaler_type* scaler = NULL); 

        /// @return maximum iterations 
        unsigned int maxIterations() const;
        /// @brief set maximum iterations 
        void setMaxIterations(unsigned int maxIter);

        /// @name print functions for debug 
        ///@{
        /// @brief print variable groups 
        /// @param os output stream 
        /// @return output stream 
        std::ostream& printVariableGroup(std::ostream& os = std::cout) const; 
        /// @brief print coefficients of variables in objective  
        /// @param os output stream 
        /// @return output stream 
        std::ostream& printObjCoef(std::ostream& os = std::cout) const; 
        /// @brief print lagrangian multipliers 
        /// @param os output stream 
        /// @return output stream 
        std::ostream& printLagMultiplier(std::ostream& os = std::cout) const; 
        ///@}

        /// @brief Predicate whether a constraint is a capacity constraint 
        struct CapacityConstraintPred
        {
            std::vector<constraint_type> const& vConstraint; ///< constraints 

            /// @brief constructor 
            /// @param v array of constraints 
            CapacityConstraintPred(std::vector<constraint_type> const& v) : vConstraint(v) {}

            /// @return true if \constr is a capacity constraint 
            /// @param constr constraint 
            bool operator()(constraint_type const& constr) const 
            {
                return constr.sense() != '='; 
            }
            /// @return true if constraint is a capacity constraint 
            /// @param id constraint index 
            bool operator()(unsigned int id) const 
            {
                return vConstraint[id].sense() != '='; 
            }
        };

        /// @brief Predicate to sort variables according to their coefficient from small to large 
        struct CompareVariableByCoefficient
        {
            std::vector<coefficient_value_type> const& vObjCoef; ///< coefficients in objective for comparison 

            /// @brief constructor 
            /// @param v array of coefficients in objective 
            CompareVariableByCoefficient(std::vector<coefficient_value_type> const& v) 
                : vObjCoef(v)
            {
            }

            /// @param v1 variable 
            /// @param v2 variable 
            /// @return true if \v1 has smaller coefficient than \v2 
            bool operator()(variable_type const& v1, variable_type const& v2) const 
            {
                return vObjCoef[v1.id()] < vObjCoef[v2.id()]; 
            }
        };

    protected:
        /// @brief copy object 
        void copy(MultiKnapsackLagRelax const& rhs);
        /// @brief kernel function to solve the problem 
        /// @param updater an object to update lagrangian multipliers
        /// @param scaler an object to scale constraints and objective, use default scaler if NULL 
        SolverProperty solve(updater_type* updater, scaler_type* scaler);
        /// @brief scale problem for better numerical instability 
        /// @param scaler an object to scale constraints and objective, use default scaler if NULL 
        void scale(scaler_type* scaler); 
        /// @brief recover problem from scaling 
        void unscale(); 
        /// @brief prepare weights of variables in objective 
        /// and classify constraints by marking capacity constraints and single item constraints 
        void prepare();
        /// @brief update lagrangian multipliers 
        /// @param updater an object to update lagrangian multipliers
        void updateLagMultipliers(updater_type* updater); 
        /// @brief solve lagrangian subproblem 
        void solveLag(); 
        /// @brief compute slackness in an iteration 
        void computeSlackness(); 
        /// @brief evaluate objective of the lagrangian subproblem 
        coefficient_value_type evaluateLagObjective() const;
        /// @brief check convergence of current solution 
        /// @return @ref limbo::solvers::SolverProperty OPTIMAL if converged; @ref limbo::solvers::SolverProperty  SUBOPTIMAL if a feasible solution found 
        SolverProperty converge(); 
        /// @brief post process solution if failed to converge to OPTIMAL after maximum iteration. 
        /// It choose the best feasible solutions in store 
        /// @param status current status of solutions 
        SolverProperty postProcess(SolverProperty status); 

        model_type* m_model; ///< model for the problem 

        std::vector<coefficient_value_type> m_vObjCoef; ///< coefficients variables in objective 
        std::vector<std::vector<variable_type> > m_vVariableGroup; ///< group variables according to item 
        std::vector<unsigned int> m_vConstraintPartition; ///< indices of constraints, the first partition is capacity constraints 
        std::vector<coefficient_value_type> m_vLagMultiplier; ///< array of lagrangian multipliers 
        std::vector<coefficient_value_type> m_vSlackness; ///< array of slackness values in each iteration, \f$ b-Ax \f$
        std::vector<coefficient_value_type> m_vScalingFactor; ///< scaling factor for constraints and objective, last entry is for objective
        coefficient_value_type m_objConstant; ///< constant value in objective from lagrangian relaxation
        coefficient_value_type m_lagObj; ///< current objective of the lagrangian subproblem 
        unsigned int m_iter; ///< current iteration 
        unsigned int m_maxIters; ///< maximum number of iterations 

        std::vector<variable_value_type> m_vBestVariableSol; ///< best feasible solution found so far 
        coefficient_value_type m_bestObj; ///< best objective found so far 
};

template <typename T, typename V>
MultiKnapsackLagRelax<T, V>::MultiKnapsackLagRelax(typename MultiKnapsackLagRelax<T, V>::model_type* model)
{
    // T must be a floating point number 
    limboStaticAssert(!std::numeric_limits<T>::is_integer);
    // V must be an integer number 
    limboStaticAssert(std::numeric_limits<V>::is_integer);

    m_model = model; 
    m_lagObj = 0; 
    m_objConstant = 0; 
    m_iter = 0; 
    m_maxIters = 1000; 
    m_bestObj = std::numeric_limits<coefficient_value_type>::max();
}
template <typename T, typename V>
MultiKnapsackLagRelax<T, V>::MultiKnapsackLagRelax(MultiKnapsackLagRelax<T, V> const& rhs)
{
    copy(rhs);
}
template <typename T, typename V>
MultiKnapsackLagRelax<T, V>& MultiKnapsackLagRelax<T, V>::operator=(MultiKnapsackLagRelax<T, V> const& rhs)
{
    if (this != &rhs)
        copy(rhs);
    return *this;
}
template <typename T, typename V>
MultiKnapsackLagRelax<T, V>::~MultiKnapsackLagRelax() 
{
}
template <typename T, typename V>
SolverProperty MultiKnapsackLagRelax<T, V>::operator()(typename MultiKnapsackLagRelax<T, V>::updater_type* updater, typename MultiKnapsackLagRelax<T, V>::scaler_type* scaler) 
{
    return solve(updater, scaler);
}
template <typename T, typename V>
unsigned int MultiKnapsackLagRelax<T, V>::maxIterations() const 
{
    return m_maxIters;
}
template <typename T, typename V>
void MultiKnapsackLagRelax<T, V>::setMaxIterations(unsigned int maxIters) 
{
    m_maxIters = maxIters; 
}
template <typename T, typename V>
void MultiKnapsackLagRelax<T, V>::copy(MultiKnapsackLagRelax<T, V> const& rhs)
{
    m_model = rhs.m_model; 
    m_vObjCoef = rhs.m_vObjCoef; 
    m_vVariableGroup = rhs.m_vVariableGroup;
    m_vConstraintPartition = rhs.m_vConstraintPartition;
    m_vLagMultiplier = rhs.m_vLagMultiplier;
    m_vSlackness = rhs.m_vSlackness;
    m_objConstant = rhs.m_objConstant; 
    m_lagObj = rhs.m_lagObj; 
    m_iter = rhs.m_iter; 
    m_maxIters = rhs.m_maxIters;

    m_vBestVariableSol = rhs.m_vBestVariableSol;
    m_bestObj = rhs.m_bestObj;
}
template <typename T, typename V>
SolverProperty MultiKnapsackLagRelax<T, V>::solve(typename MultiKnapsackLagRelax<T, V>::updater_type* updater, typename MultiKnapsackLagRelax<T, V>::scaler_type* scaler)
{
    bool defaultUpdater = false; 
    bool defaultScaler = false; 
    // use default updater if NULL 
    if (updater == NULL)
    {
        updater = new SubGradientDescent<coefficient_value_type>(); 
        defaultUpdater = true; 
    }
    // use default scaler if NULL 
    if (scaler == NULL)
    {
        scaler = new ProblemScaler<coefficient_value_type, variable_value_type>(); 
        defaultScaler = true; 
    }

    // scale problem 
    scale(scaler); 
    // prepare data structure 
    prepare(); 

    // solve lagrangian subproblem 
    SolverProperty status = INFEASIBLE; 
    for (m_iter = 0; m_iter < m_maxIters; ++m_iter)
    {
        solveLag(); 
        computeSlackness();
#ifdef DEBUG_MULTIKNAPSACKLAGRELAX
        printVariableGroup(std::cout);
        printObjCoef(std::cout);
        printLagMultiplier(std::cout);
#endif
        if ((status = converge()) == OPTIMAL)
            break; 

        updateLagMultipliers(updater);

    }

    // try to find a feasible solution by post refinement 
    status = postProcess(status); 

    // recover problem from scaling 
    unscale();

    // recycle default updater 
    if (defaultUpdater)
        delete updater; 
    // recycle default scaler 
    if (defaultScaler)
        delete scaler;

    return status;
}
template <typename T, typename V>
void MultiKnapsackLagRelax<T, V>::scale(typename MultiKnapsackLagRelax<T, V>::scaler_type* scaler)
{
    // compute scaling factors and perform scale 
    m_vScalingFactor.resize(m_model->constraints().size()+1);
    // constraints 
    for (unsigned int i = 0, ie = m_model->constraints().size(); i < ie; ++i)
    {
        m_vScalingFactor[i] = scaler->operator()(m_model->constraints()[i]); 
        m_model->scaleConstraint(i, 1.0/m_vScalingFactor[i]);
    }
    // objective 
    m_vScalingFactor.back() = scaler->operator()(m_model->objective()); 
    m_model->scaleObjective(1.0/m_vScalingFactor.back());
}
template <typename T, typename V>
void MultiKnapsackLagRelax<T, V>::unscale()
{
    // constraints 
    for (unsigned int i = 0, ie = m_model->constraints().size(); i < ie; ++i)
        m_model->scaleConstraint(i, m_vScalingFactor[i]);
    // objective 
    m_model->scaleObjective(m_vScalingFactor.back());
}
template <typename T, typename V>
void MultiKnapsackLagRelax<T, V>::prepare() 
{
    // initialize weights of variables in objective 
    m_vObjCoef.assign(m_model->numVariables(), 0); 
    for (typename std::vector<term_type>::const_iterator it = m_model->objective().terms().begin(), ite = m_model->objective().terms().end(); it != ite; ++it)
        m_vObjCoef[it->variable().id()] += it->coefficient();

    // partition all capacity constraints to the beginning of the array 
    m_vConstraintPartition.resize(m_model->constraints().size()); 
    unsigned int i = 0; 
    for (unsigned int ie = m_model->constraints().size(); i < ie; ++i)
        m_vConstraintPartition[i] = i; 
    std::vector<unsigned int>::iterator bound = std::partition(m_vConstraintPartition.begin(), m_vConstraintPartition.end(), CapacityConstraintPred(m_model->constraints()));
    m_vLagMultiplier.assign(std::distance(m_vConstraintPartition.begin(), bound), 0); 
    m_vSlackness.assign(m_vLagMultiplier.size(), 0);

    // change the sense of '>' to '<'
    for (std::vector<unsigned int>::iterator it = m_vConstraintPartition.begin(); it != bound; ++it)
        m_model->constraints().at(*it).normalize('<');

    // group variables according items 
    // the variables for one item will be grouped 
    // I assume the rest constraints are all single item constraints 
    m_vVariableGroup.resize(std::distance(bound, m_vConstraintPartition.end()));
    i = 0; 
    for (std::vector<unsigned int>::iterator it = bound, ite = m_vConstraintPartition.end(); it != ite; ++it, ++i)
    {
        constraint_type const& constr = m_model->constraints()[*it];
#ifdef DEBUG_MULTIKNAPSACKLAGRELAX
        limboAssert(constr.sense() == '='); 
#endif
        expression_type const& expr = constr.expression();
        for (typename std::vector<term_type>::const_iterator itt = expr.terms().begin(), itte = expr.terms().end(); itt != itte; ++itt)
            m_vVariableGroup[i].push_back(itt->variable());
    }

}
template <typename T, typename V>
void MultiKnapsackLagRelax<T, V>::updateLagMultipliers(typename MultiKnapsackLagRelax<T, V>::updater_type* updater)
{
    // for each capacity constraint of bin 
    for (unsigned int i = 0, ie = m_vLagMultiplier.size(); i < ie; ++i)
    {
        constraint_type const& constr = m_model->constraints().at(m_vConstraintPartition[i]); 
        // get slackness with current solution 
        coefficient_value_type slackness = m_vSlackness[i];

        coefficient_value_type& multiplier = m_vLagMultiplier[i];

        // compute new lagrangian multiplier 
        coefficient_value_type newMultiplier = updater->operator()(m_iter, multiplier, slackness);
        coefficient_value_type deltaMultiplier = newMultiplier-multiplier; 

        // apply lagrangian multiplier to objective 
        // \f$ \sum_j \lambda_j (a_i x_{ij}) \f$
        for (typename std::vector<term_type>::const_iterator it = constr.expression().terms().begin(), ite = constr.expression().terms().end(); it != ite; ++it)
            m_vObjCoef[it->variable().id()] += it->coefficient()*deltaMultiplier;
        // \f$ \sum_j -\lambda_j b_j \f$
        m_objConstant += -constr.rightHandSide()*deltaMultiplier;

        // update multiplier 
        multiplier = newMultiplier; 
    }
}
template <typename T, typename V>
void MultiKnapsackLagRelax<T, V>::solveLag()
{
    // reset all bins 
    for (typename std::vector<variable_value_type>::iterator it = m_model->variableSolutions().begin(), ite = m_model->variableSolutions().end(); it != ite; ++it)
        *it = 0; 
    // for each item 
    for (typename std::vector<std::vector<variable_type> >::iterator it = m_vVariableGroup.begin(), ite = m_vVariableGroup.end(); it != ite; ++it)
    {
        // find the bin with minimum cost for each item 
        typename std::vector<variable_type>::iterator itv = std::min_element(it->begin(), it->end(), CompareVariableByCoefficient(m_vObjCoef));
        m_model->setVariableSolution(*itv, 1);
    }
    // evaluate current objective 
    m_lagObj = evaluateLagObjective();

}
template <typename T, typename V>
void MultiKnapsackLagRelax<T, V>::computeSlackness() 
{
    // for each capacity constraint of bin 
    for (unsigned int i = 0, ie = m_vSlackness.size(); i < ie; ++i)
    {
        constraint_type const& constr = m_model->constraints().at(m_vConstraintPartition[i]); 
        // compute slackness with current solution 
        m_vSlackness[i] = m_model->evaluateConstraint(constr);
    }
}
template <typename T, typename V>
typename MultiKnapsackLagRelax<T, V>::coefficient_value_type MultiKnapsackLagRelax<T, V>::evaluateLagObjective() const 
{
    // evaluate current objective 
    coefficient_value_type objValue = m_objConstant; 
    unsigned int i = 0; 
    for (typename std::vector<coefficient_value_type>::const_iterator it = m_vObjCoef.begin(); it != m_vObjCoef.end(); ++it, ++i)
        objValue += (*it)*m_model->variableSolution(variable_type(i));
    return objValue; 
}
template <typename T, typename V>
SolverProperty MultiKnapsackLagRelax<T, V>::converge()
{
    bool feasibleFlag = true; 
    bool convergeFlag = true; 
    for (unsigned int i = 0, ie = m_vLagMultiplier.size(); i < ie; ++i)
    {
        coefficient_value_type multiplier = m_vLagMultiplier[i];
        coefficient_value_type slackness = m_vSlackness[i];
        // must satisfy KKT condition 
        // lambda >= 0
        // g(x) <= 0
        // lambda * g(x) = 0
        //
        // g(x) = Ax-b = -slackness 
        if (slackness < 0)
        {
            convergeFlag = feasibleFlag = false; 
            break; 
        }
        else if (multiplier*slackness != 0)
        {
            convergeFlag = false; 
        }
    }
    SolverProperty status = INFEASIBLE; 
    // store feasible solutions with better objective 
    if (feasibleFlag)
    {
        coefficient_value_type obj = m_model->evaluateObjective(); 
        if (obj < m_bestObj)
            m_vBestVariableSol = m_model->variableSolutions();
        status = SUBOPTIMAL;
    }
    if (convergeFlag)
        status = OPTIMAL;

    return status;
}
template <typename T, typename V>
SolverProperty MultiKnapsackLagRelax<T, V>::postProcess(SolverProperty status)
{
    if (status == OPTIMAL) // already OPTIMAL
        return status; 
    else if (m_bestObj == std::numeric_limits<coefficient_value_type>::max()) // no best solutions in store 
        return status; 
    else // there is a best feasible solution in store 
    {
        m_model->variableSolutions() = m_vBestVariableSol; 
        return SUBOPTIMAL;
    }
}
template <typename T, typename V>
std::ostream& MultiKnapsackLagRelax<T, V>::printVariableGroup(std::ostream& os) const 
{
    os << __func__ << " iteration " << m_iter << "\n";
    unsigned int i = 0; 
    for (typename std::vector<std::vector<variable_type> >::const_iterator it = m_vVariableGroup.begin(); it != m_vVariableGroup.end(); ++it, ++i)
    {
        os << "[" << i << "]";
        for (typename std::vector<variable_type>::const_iterator itv = it->begin(); itv != it->end(); ++itv)
        {
            if (m_model->variableSolution(*itv) == 1)
                os << " *" << m_model->variableName(*itv) << "*";
            else 
                os << " " << m_model->variableName(*itv);
        }
        os << "\n";
    }
    return os; 
}
template <typename T, typename V>
std::ostream& MultiKnapsackLagRelax<T, V>::printObjCoef(std::ostream& os) const 
{
    os << __func__ << " iteration " << m_iter << "\n";
    os << "lagrangian objective = " << m_lagObj << "\n";
    os << "objective = " << m_model->evaluateObjective() << "\n";
    for (unsigned int i = 0, ie = m_vObjCoef.size(); i < ie; ++i)
        os << m_model->variableName(variable_type(i)) << " = " << m_vObjCoef[i] << "\n";
    return os; 
}
template <typename T, typename V>
std::ostream& MultiKnapsackLagRelax<T, V>::printLagMultiplier(std::ostream& os) const 
{
    os << __func__ << " iteration " << m_iter << "\n";
    for (unsigned int i = 0, ie = m_vLagMultiplier.size(); i < ie; ++i)
        os << "[C" << m_vConstraintPartition[i] << "] = " << m_vLagMultiplier[i] 
            << " slack = " << m_vSlackness[i]
            << "\n";
    return os; 
}

/// @brief A base helper function object to update lagrangian multipliers using subgradient descent. 
/// All other schemes can be derived from this class 
/// @tparam T coefficient value type 
template <typename T>
class LagMultiplierUpdater
{
    public:
        /// @brief value type 
        typedef T value_type; 

        /// @brief constructor 
        LagMultiplierUpdater() {}
        /// @brief destructor 
        virtual ~LagMultiplierUpdater() {}

        /// @brief API to update lagrangian multiplier 
        /// @param iter current iteration 
        /// @param multiplier current multiplier value 
        /// @param slackness current slackness value assuming the constraint is in \f$ Ax \le b \f$ and compute \f$ b-Ax \f$
        /// @return updated multiplier value 
        virtual value_type operator()(unsigned int iter, value_type multiplier, value_type slackness) = 0;
};

/// @brief Update lagrangian multiplier with subgradient descent 
/// @tparam T coefficient value type 
template <typename T>
class SubGradientDescent : public LagMultiplierUpdater<T>
{
    public:
        /// @brief base type 
        typedef LagMultiplierUpdater<T> base_type;
        /// @brief value type 
        typedef typename base_type::value_type value_type;

        /// @brief constructor 
        /// @param alpha the power term for scaling factor \f$ t_k = k^{-\alpha} \f$
        SubGradientDescent(value_type alpha = 1)
            : SubGradientDescent::base_type()
            , m_alpha(alpha)
            , m_iter(std::numeric_limits<unsigned int>::max())
            , m_scalingFactor(1)
        {
        }
        /// @brief copy constructor 
        /// @brief right hand side 
        SubGradientDescent(SubGradientDescent const& rhs)
        {
            copy(rhs);
        }
        /// @brief assignment 
        /// @brief right hand side 
        SubGradientDescent& operator=(SubGradientDescent const& rhs)
        {
            if (this != &rhs)
            {
                this->base_type::operator=(rhs);
                copy(rhs);
            }
            return *this; 
        }
        /// @brief destructor 
        ~SubGradientDescent()
        {
        }

        /// @brief API to update lagrangian multiplier using subgradient descent 
        /// @param iter current iteration 
        /// @param multiplier current multiplier value 
        /// @param slackness current slackness value assuming the constraint is in \f$ Ax \le b \f$ and compute \f$ b-Ax \f$
        /// @return updated multiplier value 
        value_type operator()(unsigned int iter, value_type multiplier, value_type slackness)
        {
            // avoid frequent computation of scaling factor  
            if (m_iter != iter)
            {
                m_iter = iter; 
                m_scalingFactor = pow((value_type)m_iter+1, -m_alpha);
            }
            value_type result = std::max((value_type)0, multiplier+m_scalingFactor*(-slackness));
            return result; 
        }
    protected:
        /// @brief copy object 
        /// @brief right hand side 
        void copy(SubGradientDescent const& rhs)
        {
            m_alpha = rhs.m_alpha;
            m_iter = rhs.m_iter; 
            m_scalingFactor = rhs.m_scalingFactor; 
        }

        value_type m_alpha; ///< power 
        unsigned int m_iter; ///< current iteration 
        value_type m_scalingFactor; ///< scaling factor \f$ t_k = k^{-\alpha} \f$
};

/// @brief Base class for scaling scheme with default L2 norm scaling  
/// @tparam T coefficient value type 
/// @tparam V variable value type 
template <typename T, typename V>
class ProblemScaler
{
    public:
        /// @brief model type 
        typedef LinearModel<T, V> model_type; 
        /// @brief value type 
        typedef typename model_type::coefficient_value_type value_type; 
        /// @brief expression type 
        typedef typename model_type::expression_type expression_type; 
        /// @brief constraint type 
        typedef typename model_type::constraint_type constraint_type; 
        /// @brief term type 
        typedef typename model_type::term_type term_type; 

        /// @brief constructor 
        ProblemScaler() {}
        /// @brief destructor 
        virtual ~ProblemScaler() {}

        /// @brief API to compute scaling factor for expression using L2 norm  
        /// @param expr expression 
        /// @return scaling factor 
        virtual value_type operator()(expression_type const& expr) const
        {
            value_type result = 0; 
            for (typename std::vector<term_type>::const_iterator it = expr.terms().begin(), ite = expr.terms().end(); it != ite; ++it)
                result += it->coefficient()*it->coefficient(); 
            return sqrt(result/expr.terms().size()); 
        }
        /// @brief API to compute scaling factor for constraints  using L2 norm 
        /// @param constr constraint 
        /// @return scaling factor 
        virtual value_type operator()(constraint_type const& constr) const
        {
            return this->operator()(constr.expression());
        }
};

} // namespace solvers 
} // namespace limbo 

#endif
