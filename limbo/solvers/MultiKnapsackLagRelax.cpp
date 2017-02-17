/**
 * @file   MultiKnapsackLagRelax.cpp
 * @author Yibo Lin
 * @date   Feb 2017
 */
#include <limbo/solvers/MultiKnapsackLagRelax.h>
#include <cmath>

/// namespace for Limbo 
namespace limbo 
{
/// namespace for Limbo.Solvers 
namespace solvers 
{

/// @brief Predicate whether a constraint is a capacity constraint 
struct CapacityConstraintPred
{
    /// @return true if \constr is a capacity constraint 
    /// @param constr constraint 
    bool operator()(MultiKnapsackLagRelax::constraint_type const& constr) const 
    {
        return constr.sense() != '='; 
    }
};

/// @brief Predicate to sort variables according to their coefficient from small to large 
struct CompareVariableByCoefficient
{
    std::vector<MultiKnapsackLagRelax::coefficient_value_type> const& vObjCoef; ///< coefficients in objective for comparison 

    /// @brief constructor 
    /// @param v array of coefficients in objective 
    CompareVariableByCoefficient(std::vector<MultiKnapsackLagRelax::coefficient_value_type> const& v) 
        : vObjCoef(v)
    {
    }

    /// @param v1 variable 
    /// @param v2 variable 
    /// @return true if \v1 has smaller coefficient than \v2 
    bool operator()(Variable const& v1, Variable const& v2) const 
    {
        return vObjCoef[v1.id()] < vObjCoef[v2.id()]; 
    }
};

MultiKnapsackLagRelax::MultiKnapsackLagRelax(model_type* model, LagMultiplierUpdater* updater)
{
    m_model = model; 
    if (updater)
    {
        m_lagMultiplierUpdater = updater; 
        m_defaultUpdater = false; 
    }
    else 
    {
        m_lagMultiplierUpdater = new LagMultiplierUpdater(0.1); 
        m_defaultUpdater = true; 
    }
    m_lagObj = 0; 
    m_objConstant = 0; 
    m_iter = 0; 
    m_maxIters = 100; 
}
MultiKnapsackLagRelax::MultiKnapsackLagRelax(MultiKnapsackLagRelax const& rhs)
{
    copy(rhs);
}
MultiKnapsackLagRelax& MultiKnapsackLagRelax::operator=(MultiKnapsackLagRelax const& rhs)
{
    if (this != &rhs)
        copy(rhs);
    return *this;
}
SolverProperty MultiKnapsackLagRelax::operator()() 
{
    return solve();
}
MultiKnapsackLagRelax::~MultiKnapsackLagRelax() 
{
    if (m_defaultUpdater)
        delete m_lagMultiplierUpdater; 
}
void MultiKnapsackLagRelax::copy(MultiKnapsackLagRelax const& rhs)
{
    m_model = rhs.m_model; 
    m_lagMultiplierUpdater = rhs.m_lagMultiplierUpdater;
    m_vObjCoef = rhs.m_vObjCoef; 
    m_vVariableGroup = rhs.m_vVariableGroup;
    m_vLagMultiplier = rhs.m_vLagMultiplier;
    m_objConstant = rhs.m_objConstant; 
    m_lagObj = rhs.m_lagObj; 
    m_iter = rhs.m_iter; 
    m_maxIters = rhs.m_maxIters;
}
SolverProperty MultiKnapsackLagRelax::solve()
{
    bool convergeFlag = false; 
    for (m_iter = 0; m_iter < m_maxIters; ++m_iter)
    {
        solveLag(); 
        updateLagMultipliers();

        if ((convergeFlag = converge()))
            break; 
    }

    // still not converge 
    // try to find a feasible solution by post refinement 
    if (!convergeFlag)
        return postRefine(); 

    return OPTIMAL;
}
void MultiKnapsackLagRelax::prepare() 
{
    // initialize weights of variables in objective 
    m_vObjCoef.assign(m_model->numVariables(), 0); 
    for (std::vector<term_type>::const_iterator it = m_model->objective().terms().begin(), ite = m_model->objective().terms().end(); it != ite; ++it)
        m_vObjCoef[it->variable().id()] += it->coefficient();

    // partition all capacity constraints to the beginning of the array 
    std::vector<constraint_type>::iterator bound = std::partition(m_model->constraints().begin(), m_model->constraints().end(), CapacityConstraintPred());
    m_vLagMultiplier.assign(std::distance(m_model->constraints().begin(), bound), 0); 

    // change the sense of '>' to '<'
    for (std::vector<constraint_type>::iterator it = m_model->constraints().begin(); it != bound; ++it)
        it->normalize('<');

    // group variables according items 
    // the variables for one item will be grouped 
    // I assume the rest constraints are all single item constraints 
    m_vVariableGroup.resize(std::distance(bound, m_model->constraints().end()));
    for (std::vector<constraint_type>::iterator it = bound, ite = m_model->constraints().end(); it != ite; ++it)
    {
        limboAssert(it->sense() == '='); 
        expression_type const& expr = it->expression();
        for (std::vector<term_type>::const_iterator itt = expr.terms().begin(), itte = expr.terms().end(); itt != itte; ++itt)
            m_vVariableGroup[itt->variable().id()].push_back(itt->variable());
    }
}
void MultiKnapsackLagRelax::updateLagMultipliers()
{
    // for each capacity constraint of bin 
    for (unsigned int i = 0, ie = m_vLagMultiplier.size(); i < ie; ++i)
    {
        constraint_type const& constr = m_model->constraints().at(i); 
        // compute slackness with current solution 
        coefficient_value_type slackness = m_model->evaluateConstraint(constr);

        coefficient_value_type& multiplier = m_vLagMultiplier[i];

        // compute new lagrangian multiplier 
        coefficient_value_type newMultiplier = m_lagMultiplierUpdater->operator()(m_iter, multiplier, slackness);
        coefficient_value_type deltaMultiplier = newMultiplier-multiplier; 

        // apply lagrangian multiplier to objective 
        // \f$ \sum_j \lambda_j (a_i x_{ij}) \f$
        for (std::vector<term_type>::const_iterator it = constr.expression().terms().begin(), ite = constr.expression().terms().end(); it != ite; ++it)
            m_vObjCoef[it->variable().id()] += it->coefficient()*deltaMultiplier;
        // \f$ \sum_j -\lambda_j b_j \f$
        m_objConstant += -constr.rightHandSide()*deltaMultiplier;

        // update multiplier 
        multiplier = newMultiplier; 
    }
}
void MultiKnapsackLagRelax::solveLag()
{
    // reset all bins 
    for (std::vector<variable_value_type>::iterator it = m_model->variableSolutions().begin(), ite = m_model->variableSolutions().end(); it != ite; ++it)
        *it = 0; 
    // for each item 
    for (std::vector<std::vector<Variable> >::iterator it = m_vVariableGroup.begin(), ite = m_vVariableGroup.end(); it != ite; ++it)
    {
        // find the bin with minimum cost for each item 
        std::vector<Variable>::iterator itv = std::min_element(it->begin(), it->end(), CompareVariableByCoefficient(m_vObjCoef));
        m_model->setVariableSolution(*itv, 1);
    }
    // evaluate current objective 
    m_lagObj = evaluateLagObjective();
}
MultiKnapsackLagRelax::coefficient_value_type MultiKnapsackLagRelax::evaluateLagObjective() const 
{
    // evaluate current objective 
    coefficient_value_type objValue = m_objConstant; 
    unsigned int i = 0; 
    for (std::vector<coefficient_value_type>::const_iterator it = m_vObjCoef.begin(); it != m_vObjCoef.end(); ++it, ++i)
        objValue += (*it)*m_model->variableSolution(Variable(i));
    return objValue; 
}
bool MultiKnapsackLagRelax::converge() const
{
    bool convergeFlag = true; 
    for (std::vector<coefficient_value_type>::const_iterator it = m_vLagMultiplier.begin(); it != m_vLagMultiplier.end(); ++it)
    {
        if (*it > 0)
        {
            convergeFlag = false; 
            break; 
        }
    }

    return convergeFlag;
}
SolverProperty MultiKnapsackLagRelax::postRefine()
{
    limboAssertMsg(0, "not implemented yet");

    return SUBOPTIMAL;
}

LagMultiplierUpdater::LagMultiplierUpdater(LagMultiplierUpdater::value_type alpha)
    : m_alpha(alpha)
    , m_iter(std::numeric_limits<unsigned int>::max())
    , m_scalingFactor(1)
{
}
LagMultiplierUpdater::LagMultiplierUpdater(LagMultiplierUpdater const& rhs)
{
    copy(rhs);
}
LagMultiplierUpdater& LagMultiplierUpdater::operator=(LagMultiplierUpdater const& rhs) 
{
    if (this != &rhs)
        copy(rhs);
    return *this; 
}
LagMultiplierUpdater::~LagMultiplierUpdater() 
{
}
void LagMultiplierUpdater::copy(LagMultiplierUpdater const& rhs)
{
    m_alpha = rhs.m_alpha;
    m_iter = rhs.m_iter; 
    m_scalingFactor = rhs.m_scalingFactor; 
}
LagMultiplierUpdater::value_type LagMultiplierUpdater::operator()(unsigned int iter, LagMultiplierUpdater::value_type multiplier, LagMultiplierUpdater::value_type slackness)
{
    // avoid frequent computation of scaling factor  
    if (m_iter != iter)
    {
        m_scalingFactor = pow(m_iter+1, -m_alpha);
        m_iter = iter; 
    }
    return std::max((value_type)0, multiplier+m_scalingFactor*(-slackness));
}

} // namespace solvers 
} // namespace limbo 
