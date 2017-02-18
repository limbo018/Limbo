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
    std::vector<MultiKnapsackLagRelax::constraint_type> const& vConstraint; ///< constraints 

    /// @brief constructor 
    /// @param v array of constraints 
    CapacityConstraintPred(std::vector<MultiKnapsackLagRelax::constraint_type> const& v) : vConstraint(v) {}

    /// @return true if \constr is a capacity constraint 
    /// @param constr constraint 
    bool operator()(MultiKnapsackLagRelax::constraint_type const& constr) const 
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
    bool operator()(MultiKnapsackLagRelax::variable_type const& v1, MultiKnapsackLagRelax::variable_type const& v2) const 
    {
        return vObjCoef[v1.id()] < vObjCoef[v2.id()]; 
    }
};

MultiKnapsackLagRelax::MultiKnapsackLagRelax(model_type* model)
{
    m_model = model; 
    m_lagObj = 0; 
    m_objConstant = 0; 
    m_iter = 0; 
    m_maxIters = 1000; 
    m_bestObj = std::numeric_limits<coefficient_value_type>::max();
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
MultiKnapsackLagRelax::~MultiKnapsackLagRelax() 
{
}
SolverProperty MultiKnapsackLagRelax::operator()(LagMultiplierUpdater* updater, ProblemScaler* scaler) 
{
    return solve(updater);
}
unsigned int MultiKnapsackLagRelax::maxIterations() const 
{
    return m_maxIters;
}
void MultiKnapsackLagRelax::setMaxIterations(unsigned int maxIter) 
{
    m_maxIters = maxIters; 
}
void MultiKnapsackLagRelax::copy(MultiKnapsackLagRelax const& rhs)
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
SolverProperty MultiKnapsackLagRelax::solve(LagMultiplierUpdater* updater, ProblemScaler* scaler)
{
    bool defaultUpdater = false; 
    bool defaultScaler = false; 
    // use default updater if NULL 
    if (updater == NULL)
    {
        updater = new SubGradientDescent(); 
        defaultUpdater = true; 
    }
    // use default scaler if NULL 
    if (scaler == NULL)
    {
        scaler = new ProblemScaler(); 
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

    // still not converge 
    // try to find a feasible solution by post refinement 
    if (status != OPTIMAL)
        status = postRefine(); 

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
void MultiKnapsackLagRelax::scale(ProblemScaler* scaler)
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
void MultiKnapsackLagRelax::unscale()
{
    // constraints 
    for (unsigned int i = 0, ie = m_model->constraints().size(); i < ie; ++i)
        m_model->scaleConstraint(i, m_vScalingFactor[i]);
    // objective 
    m_model->scaleObjective(m_vScalingFactor.back());
}
void MultiKnapsackLagRelax::prepare() 
{
    // initialize weights of variables in objective 
    m_vObjCoef.assign(m_model->numVariables(), 0); 
    for (std::vector<term_type>::const_iterator it = m_model->objective().terms().begin(), ite = m_model->objective().terms().end(); it != ite; ++it)
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
        for (std::vector<term_type>::const_iterator itt = expr.terms().begin(), itte = expr.terms().end(); itt != itte; ++itt)
            m_vVariableGroup[i].push_back(itt->variable());
    }

}
void MultiKnapsackLagRelax::updateLagMultipliers(LagMultiplierUpdater* updater)
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
    for (std::vector<std::vector<variable_type> >::iterator it = m_vVariableGroup.begin(), ite = m_vVariableGroup.end(); it != ite; ++it)
    {
        // find the bin with minimum cost for each item 
        std::vector<variable_type>::iterator itv = std::min_element(it->begin(), it->end(), CompareVariableByCoefficient(m_vObjCoef));
        m_model->setVariableSolution(*itv, 1);
    }
    // evaluate current objective 
    m_lagObj = evaluateLagObjective();

}
void MultiKnapsackLagRelax::computeSlackness() 
{
    // for each capacity constraint of bin 
    for (unsigned int i = 0, ie = m_vSlackness.size(); i < ie; ++i)
    {
        constraint_type const& constr = m_model->constraints().at(m_vConstraintPartition[i]); 
        // compute slackness with current solution 
        m_vSlackness[i] = m_model->evaluateConstraint(constr);
    }
}
MultiKnapsackLagRelax::coefficient_value_type MultiKnapsackLagRelax::evaluateLagObjective() const 
{
    // evaluate current objective 
    coefficient_value_type objValue = m_objConstant; 
    unsigned int i = 0; 
    for (std::vector<coefficient_value_type>::const_iterator it = m_vObjCoef.begin(); it != m_vObjCoef.end(); ++it, ++i)
        objValue += (*it)*m_model->variableSolution(variable_type(i));
    return objValue; 
}
SolverProperty MultiKnapsackLagRelax::converge() const
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
SolverProperty MultiKnapsackLagRelax::postRefine()
{
    limboAssertMsg(0, "not implemented yet");

    return SUBOPTIMAL;
}
std::ostream& MultiKnapsackLagRelax::printVariableGroup(std::ostream& os) const 
{
    os << __func__ << " iteration " << m_iter << "\n";
    unsigned int i = 0; 
    for (std::vector<std::vector<variable_type> >::const_iterator it = m_vVariableGroup.begin(); it != m_vVariableGroup.end(); ++it, ++i)
    {
        os << "[" << i << "]";
        for (std::vector<variable_type>::const_iterator itv = it->begin(); itv != it->end(); ++itv)
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
std::ostream& MultiKnapsackLagRelax::printObjCoef(std::ostream& os) const 
{
    os << __func__ << " iteration " << m_iter << "\n";
    os << "lagrangian objective = " << m_lagObj << "\n";
    os << "objective = " << m_model->evaluateObjective() << "\n";
    for (unsigned int i = 0, ie = m_vObjCoef.size(); i < ie; ++i)
        os << m_model->variableName(variable_type(i)) << " = " << m_vObjCoef[i] << "\n";
    return os; 
}
std::ostream& MultiKnapsackLagRelax::printLagMultiplier(std::ostream& os) const 
{
    os << __func__ << " iteration " << m_iter << "\n";
    for (unsigned int i = 0, ie = m_vLagMultiplier.size(); i < ie; ++i)
        os << "[C" << m_vConstraintPartition[i] << "] = " << m_vLagMultiplier[i] 
            << " slack = " << m_vSlackness[i]
            << "\n";
    return os; 
}

LagMultiplierUpdater::LagMultiplierUpdater()
{
}
LagMultiplierUpdater::~LagMultiplierUpdater()
{
}

SubGradientDescent::SubGradientDescent(SubGradientDescent::value_type alpha)
    : SubGradientDescent::base_type()
    , m_alpha(alpha)
    , m_iter(std::numeric_limits<unsigned int>::max())
    , m_scalingFactor(1)
{
}
SubGradientDescent::SubGradientDescent(SubGradientDescent const& rhs)
    : SubGradientDescent::base_type(rhs)
{
    copy(rhs);
}
SubGradientDescent& SubGradientDescent::operator=(SubGradientDescent const& rhs) 
{
    if (this != &rhs)
    {
        this->base_type::operator=(rhs);
        copy(rhs);
    }
    return *this; 
}
SubGradientDescent::~SubGradientDescent() 
{
}
void SubGradientDescent::copy(SubGradientDescent const& rhs)
{
    m_alpha = rhs.m_alpha;
    m_iter = rhs.m_iter; 
    m_scalingFactor = rhs.m_scalingFactor; 
}
SubGradientDescent::value_type SubGradientDescent::operator()(unsigned int iter, SubGradientDescent::value_type multiplier, SubGradientDescent::value_type slackness)
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

ProblemScaler::ProblemScaler()
{
}
ProblemScaler::~ProblemScaler()
{
}
ProblemScaler::value_type ProblemScaler::operator()(expression_type const& expr) const 
{
    value_type result = 0; 
    for (std::vector<term_type>::const_iterator it = expr.terms().begin(), ite = expr.terms().end(); it != ite; ++it)
        result += it->coefficient()*it->coefficient(); 
    return result; 
}
ProblemScaler::value_type ProblemScaler::operator()(constraint_type const& constr) const 
{
    return this->operator()(constr.expression());
}

} // namespace solvers 
} // namespace limbo 
