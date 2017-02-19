/**
 * @file   DualMinCostFlow.cpp
 * @author Yibo Lin
 * @date   Feb 2017
 */
#include <limbo/solvers/DualMinCostFlow.h>
#include <lemon/lgf_writer.h>

/// namespace for Limbo 
namespace limbo 
{
/// namespace for Limbo.Solvers 
namespace solvers 
{

DualMinCostFlow::DualMinCostFlow(model_type* model)
    : m_model(model)
    , m_graph()
    //, m_mLower(m_graph)
    , m_mUpper(m_graph)
    , m_mCost(m_graph)
    , m_mSupply(m_graph)
    , m_totalFlowCost(std::numeric_limits<DualMinCostFlow::value_type>::max())
    , m_bigM(std::numeric_limits<DualMinCostFlow::value_type>::max())
    , m_mFlow(m_graph)
    , m_mPotential(m_graph)
{
}
DualMinCostFlow::~DualMinCostFlow() 
{
}
SolverProperty DualMinCostFlow::operator()(MinCostFlowSolver* solver)
{
    return solve(solver);
}
DualMinCostFlow::graph_type const& DualMinCostFlow::graph() const 
{
    return m_graph;
}
//DualMinCostFlow::arc_value_map_type const& DualMinCostFlow::lowerMap() const
//{
//    return m_mLower;
//}
DualMinCostFlow::arc_value_map_type const& DualMinCostFlow::upperMap() const 
{
    return m_mUpper;
}
DualMinCostFlow::arc_cost_map_type const& DualMinCostFlow::costMap() const 
{
    return m_mCost;
}
DualMinCostFlow::node_value_map_type const& DualMinCostFlow::supplyMap() const 
{
    return m_mSupply;
}
DualMinCostFlow::arc_flow_map_type& DualMinCostFlow::flowMap() 
{
    return m_mFlow;
}
DualMinCostFlow::node_pot_map_type& DualMinCostFlow::potentialMap() 
{
    return m_mPotential;
}
DualMinCostFlow::value_type DualMinCostFlow::totalFlowCost() const
{
    return m_totalFlowCost; 
}
void DualMinCostFlow::setTotalFlowCost(DualMinCostFlow::value_type cost)
{
    m_totalFlowCost = cost; 
}
DualMinCostFlow::value_type DualMinCostFlow::totalCost() const 
{
    // the negation comes from we change maximization problem into minimization problem 
    // the dual LP problem should be a maximization problem, but we solve it with min-cost flow 
    return -(totalFlowCost()-m_bigM*m_reversedArcFlowCost);
}
void DualMinCostFlow::printGraph(bool writeSol) const
{
    limboPrint(kDEBUG, "bigM = %d, reversedArcFlowCost = %d\n", (int)m_bigM, m_reversedArcFlowCost);
    if (writeSol)
        limboPrint(kDEBUG, "totalFlowCost = %d, totalCost = %d\n", (int)totalFlowCost(), (int)totalCost()); 

    node_name_map_type nameMap (m_graph); 
    for (unsigned int i = 0, ie = m_model->numVariables(); i < ie; ++i)
        nameMap[m_graph.nodeFromId(i)] = m_model->variableName(variable_type(i)); 
    nameMap[m_graph.nodeFromId(m_graph.maxNodeId())] = "additional";

    // dump lgf file 
    lemon::DigraphWriter<graph_type> writer(m_graph, "debug.lgf");
    writer.nodeMap("supply", m_mSupply)
        .nodeMap("name", nameMap)
        .arcMap("capacity_upper", m_mUpper)
        .arcMap("cost", m_mCost);
    if (writeSol)
        writer.nodeMap("potential", m_mPotential)
            .arcMap("flow", m_mFlow);
    writer.run();
}
SolverProperty DualMinCostFlow::solve(MinCostFlowSolver* solver)
{
    bool defaultSolver = false; 
    // use default solver if NULL 
    if (solver == NULL)
    {
        solver = new CostScaling(); 
        defaultSolver = true; 
    }

    // prepare 
    prepare();
    // build graph 
    buildGraph();
    // solve min-cost flow problem 
    SolverProperty status = solver->operator()(this); 
    // apply solution 
    applySolution(); 

#ifdef DEBUG_DUALMINCOSTFLOW
    printGraph(true);
#endif

    if (defaultSolver)
        delete solver; 

    return status; 
}
void DualMinCostFlow::prepare() 
{
    // big M should be larger than the summation of all non-negative supply in the graph 
    // because this is the largest possible amount of flows. 
    // The supply for each node is the coefficient of variable in the objective. 
    m_bigM = 0; 
    for (std::vector<term_type>::const_iterator it = m_model->objective().terms().begin(), ite = m_model->objective().terms().end(); it != ite; ++it)
    {
        if (it->coefficient() > 0)
            m_bigM += it->coefficient();
    }
    //m_bigM *= 10000; 

    // reset data members
    m_reversedArcFlowCost = 0; 
}
void DualMinCostFlow::buildGraph() 
{
    // 1. preparing nodes 
    mapObjective2Graph();

    // reserve arcs 
    // use count arcs mode to compute number of arcs needed 
    unsigned int numArcs = mapDiffConstraint2Graph(true)+mapBoundConstraint2Graph(true);
    m_graph.reserveArc(numArcs); 

    // 2. preparing arcs for differential constraints 
    mapDiffConstraint2Graph(false);

    // 3. arcs for variable bounds 
    mapBoundConstraint2Graph(false);
}
void DualMinCostFlow::mapObjective2Graph() 
{
    // preparing nodes 
    // set supply to its weight in the objective 
    m_graph.reserveNode(m_model->numVariables()+1); // in case an additional node is necessary, which will be the last node  
    for (unsigned int i = 0, ie = m_model->numVariables(); i < ie; ++i)
        m_graph.addNode();
    for (std::vector<term_type>::const_iterator it = m_model->objective().terms().begin(), ite = m_model->objective().terms().end(); it != ite; ++it)
        m_mSupply[m_graph.nodeFromId(it->variable().id())] = it->coefficient();
}
unsigned int DualMinCostFlow::mapDiffConstraint2Graph(bool countArcs) 
{
    // preparing arcs 
    // arcs constraints like xi - xj >= cij 
    // add arc from node i to node j with cost -cij and capacity unlimited 

    unsigned int numArcs = m_model->constraints().size(); 
    if (!countArcs) // skip in count arcs mode 
    {
        // normalize to '>' format 
        for (std::vector<constraint_type>::iterator it = m_model->constraints().begin(), ite = m_model->constraints().end(); it != ite; ++it)
        {
            constraint_type& constr = *it; 
            limboAssertMsg(constr.expression().terms().size() == 2, "only support differential constraints like xi - xj >= cij");
            constr.normalize('>');
        }
        for (std::vector<constraint_type>::const_iterator it = m_model->constraints().begin(), ite = m_model->constraints().end(); it != ite; ++it)
        {
            constraint_type const& constr = *it; 
            std::vector<term_type> const& vTerm = constr.expression().terms();
            variable_type xi = (vTerm[0].coefficient() > 0)? vTerm[0].variable() : vTerm[1].variable();
            variable_type xj = (vTerm[0].coefficient() > 0)? vTerm[1].variable() : vTerm[0].variable();

            addArcForDiffConstraint(m_graph.nodeFromId(xi.id()), m_graph.nodeFromId(xj.id()), constr.rightHandSide());
        }
    }
    return numArcs; 
}
unsigned int DualMinCostFlow::mapBoundConstraint2Graph(bool countArcs) 
{
    // 3. arcs for variable bounds 
    // from node to additional node  

    // check whether there is node with non-zero lower bound or non-infinity upper bound 
    unsigned int numArcs = 0; 
    for (unsigned int i = 0, ie = m_model->numVariables(); i < ie; ++i)
    {
        value_type lowerBound = m_model->variableLowerBound(variable_type(i)); 
        value_type upperBound = m_model->variableUpperBound(variable_type(i)); 
        if (lowerBound != 0)
            ++numArcs; 
        if (upperBound != std::numeric_limits<value_type>::max())
            ++numArcs; 
    }
    if (!countArcs && numArcs) // skip in count arcs mode 
    {
        // 3.1 create additional node 
        // its corresponding weight is the negative sum of weight for other nodes 
        node_type addlNode = m_graph.addNode();
        value_type addlWeight = 0;
        for (std::vector<term_type>::const_iterator it = m_model->objective().terms().begin(), ite = m_model->objective().terms().end(); it != ite; ++it)
            addlWeight -= it->coefficient();
        m_mSupply[addlNode] = addlWeight; 

        for (unsigned int i = 0, ie = m_model->numVariables(); i < ie; ++i)
        {
            value_type lowerBound = m_model->variableLowerBound(variable_type(i)); 
            value_type upperBound = m_model->variableUpperBound(variable_type(i)); 
            // has lower bound 
            // add arc from node to additional node with cost d and cap unlimited
            if (lowerBound != 0)
                addArcForDiffConstraint(m_graph.nodeFromId(i), addlNode, lowerBound);
            // has upper bound 
            // add arc from additional node to node with cost u and capacity unlimited
            if (upperBound != std::numeric_limits<value_type>::max())
                addArcForDiffConstraint(addlNode, m_graph.nodeFromId(i), -upperBound); 
        }
    }
    return numArcs; 
}
void DualMinCostFlow::addArcForDiffConstraint(DualMinCostFlow::node_type xi, DualMinCostFlow::node_type xj, DualMinCostFlow::value_type cij) 
{
    // add constraint xi - xj >= cij 
    //
    // negative arc cost can be fixed by arc reversal 
    // for an arc with i -> j, with supply bi and bj, cost cij, capacity uij 
    // reverse the arc to 
    // i <- j, with supply bi-uij and bj+uij, cost -cij, capacity uij 

    if (cij <= 0)
    {
        arc_type arc = m_graph.addArc(xi, xj);
        m_mCost[arc] = -cij; 
        //m_mLower[arc] = 0;
        m_mUpper[arc] = m_bigM; 
    }
    else // reverse arc 
    {
        arc_type arc = m_graph.addArc(xj, xi); // arc reversal 
        m_mCost[arc] = cij; 
        //m_mLower[arc] = 0;
        m_mUpper[arc] = m_bigM;
        m_mSupply[xi] -= m_bigM;
        m_mSupply[xj] += m_bigM; 

        m_reversedArcFlowCost += cij;
    }
}
void DualMinCostFlow::applySolution()
{
    // update solution 
    value_type addlValue = 0;
    if ((unsigned int)m_graph.nodeNum() > m_model->numVariables()) // additional node has been introduced 
        addlValue = m_mPotential[m_graph.nodeFromId(m_graph.maxNodeId())];
    unsigned int i = 0; 
    for (std::vector<value_type>::iterator it = m_model->variableSolutions().begin(), ite = m_model->variableSolutions().end(); it != ite; ++it, ++i)
        *it = m_mPotential[m_graph.nodeFromId(i)]-addlValue; 
}

MinCostFlowSolver::MinCostFlowSolver()
{
}
MinCostFlowSolver::MinCostFlowSolver(MinCostFlowSolver const& rhs) 
{
    copy(rhs);
}
MinCostFlowSolver& MinCostFlowSolver::operator=(MinCostFlowSolver const& rhs) 
{
    if (this != &rhs)
        copy(rhs);
    return *this;
}
MinCostFlowSolver::~MinCostFlowSolver()
{
}
void MinCostFlowSolver::copy(MinCostFlowSolver const& /*rhs*/)
{
}

CapacityScaling::CapacityScaling(int factor)
    : CapacityScaling::base_type()
    , m_factor(factor)
{
}
CapacityScaling::CapacityScaling(CapacityScaling const& rhs) 
    : CapacityScaling::base_type(rhs)
{
    copy(rhs);
}
CapacityScaling& CapacityScaling::operator=(CapacityScaling const& rhs)
{
    if (this != &rhs)
    {
        this->base_type::operator=(rhs);
        copy(rhs);
    }
    return *this;
}
SolverProperty CapacityScaling::operator()(DualMinCostFlow* d) 
{
    // 1. choose algorithm 
    alg_type alg (d->graph());

    // 2. run 
    alg_type::ProblemType status = alg.reset().resetParams()
        //.lowerMap(d->lowerMap())
        .upperMap(d->upperMap())
        .costMap(d->costMap())
        .supplyMap(d->supplyMap())
        .run(m_factor);

    // 3. check results 
    SolverProperty solverStatus; 
    switch (status)
    {
        case alg_type::OPTIMAL:
            solverStatus = OPTIMAL; 
            break;
        case alg_type::INFEASIBLE:
            solverStatus = INFEASIBLE; 
            break;
        case alg_type::UNBOUNDED:
            solverStatus = UNBOUNDED; 
            break;
        default:
            limboAssertMsg(0, "unknown status");
    }

    // 4. apply results 
    // get dual solution of LP, which is the flow of min-cost flow, skip this if not necessary
    alg.flowMap(d->flowMap());
    // get solution of LP, which is the dual solution of min-cost flow 
    alg.potentialMap(d->potentialMap());
    // set total cost of min-cost flow 
    d->setTotalFlowCost(alg.totalCost());

    return solverStatus; 
}
void CapacityScaling::copy(CapacityScaling const& rhs) 
{
    m_factor = rhs.m_factor;
}

CostScaling::CostScaling(CostScaling::alg_type::Method method, int factor)
    : CostScaling::base_type()
    , m_method(method)
    , m_factor(factor)
{
}
CostScaling::CostScaling(CostScaling const& rhs) 
    : CostScaling::base_type(rhs)
{
    copy(rhs);
}
CostScaling& CostScaling::operator=(CostScaling const& rhs)
{
    if (this != &rhs)
    {
        this->base_type::operator=(rhs);
        copy(rhs);
    }
    return *this;
}
SolverProperty CostScaling::operator()(DualMinCostFlow* d)
{
    // 1. choose algorithm 
    alg_type alg (d->graph());

    // 2. run 
    alg_type::ProblemType status = alg.reset().resetParams()
        //.lowerMap(d->lowerMap())
        .upperMap(d->upperMap())
        .costMap(d->costMap())
        .supplyMap(d->supplyMap())
        .run(m_method, m_factor);

    // 3. check results 
    SolverProperty solverStatus; 
    switch (status)
    {
        case alg_type::OPTIMAL:
            solverStatus = OPTIMAL; 
            break;
        case alg_type::INFEASIBLE:
            solverStatus = INFEASIBLE; 
            break;
        case alg_type::UNBOUNDED:
            solverStatus = UNBOUNDED; 
            break;
        default:
            limboAssertMsg(0, "unknown status");
    }

    // 4. apply results 
    // get dual solution of LP, which is the flow of min-cost flow, skip this if not necessary
    alg.flowMap(d->flowMap());
    // get solution of LP, which is the dual solution of min-cost flow 
    alg.potentialMap(d->potentialMap());
    // set total cost of min-cost flow 
    d->setTotalFlowCost(alg.totalCost());

    return solverStatus; 
}
void CostScaling::copy(CostScaling const& rhs)
{
    m_method = rhs.m_method;
    m_factor = rhs.m_factor;
}

NetworkSimplex::NetworkSimplex(NetworkSimplex::alg_type::PivotRule pivotRule)
    : NetworkSimplex::base_type()
    , m_pivotRule(pivotRule)
{
}
NetworkSimplex::NetworkSimplex(NetworkSimplex const& rhs)
    : NetworkSimplex::base_type(rhs)
{
    copy(rhs);
}
NetworkSimplex& NetworkSimplex::operator=(NetworkSimplex const& rhs)
{
    if (this != &rhs)
    {
        this->base_type::operator=(rhs); 
        copy(rhs);
    }
    return *this;
}
SolverProperty NetworkSimplex::operator()(DualMinCostFlow* d)
{
    // 1. choose algorithm 
    alg_type alg (d->graph());

    // 2. run 
    alg_type::ProblemType status = alg.reset().resetParams()
        //.lowerMap(d->lowerMap())
        .upperMap(d->upperMap())
        .costMap(d->costMap())
        .supplyMap(d->supplyMap())
        .run(m_pivotRule);

    // 3. check results 
    SolverProperty solverStatus; 
    switch (status)
    {
        case alg_type::OPTIMAL:
            solverStatus = OPTIMAL; 
            break;
        case alg_type::INFEASIBLE:
            solverStatus = INFEASIBLE; 
            break;
        case alg_type::UNBOUNDED:
            solverStatus = UNBOUNDED; 
            break;
        default:
            limboAssertMsg(0, "unknown status");
    }

    // 4. apply results 
    // get dual solution of LP, which is the flow of min-cost flow, skip this if not necessary
    alg.flowMap(d->flowMap());
    // get solution of LP, which is the dual solution of min-cost flow 
    alg.potentialMap(d->potentialMap());
    // set total cost of min-cost flow 
    d->setTotalFlowCost(alg.totalCost());

    return solverStatus; 
}
void NetworkSimplex::copy(NetworkSimplex const& rhs) 
{
    m_pivotRule = rhs.m_pivotRule;
}

CycleCanceling::CycleCanceling(CycleCanceling::alg_type::Method method)
    : CycleCanceling::base_type()
    , m_method(method)
{
}
CycleCanceling::CycleCanceling(CycleCanceling const& rhs)
    : CycleCanceling::base_type(rhs)
{
    copy(rhs);
}
CycleCanceling& CycleCanceling::operator=(CycleCanceling const& rhs) 
{
    if (this != &rhs)
    {
        this->operator=(rhs);
        copy(rhs);
    }
    return *this;
}
SolverProperty CycleCanceling::operator()(DualMinCostFlow* d)
{
    // 1. choose algorithm 
    alg_type alg (d->graph());

    // 2. run 
    alg_type::ProblemType status = alg.reset().resetParams()
        //.lowerMap(d->lowerMap())
        .upperMap(d->upperMap())
        .costMap(d->costMap())
        .supplyMap(d->supplyMap())
        .run(m_method);

    // 3. check results 
    SolverProperty solverStatus; 
    switch (status)
    {
        case alg_type::OPTIMAL:
            solverStatus = OPTIMAL; 
            break;
        case alg_type::INFEASIBLE:
            solverStatus = INFEASIBLE; 
            break;
        case alg_type::UNBOUNDED:
            solverStatus = UNBOUNDED; 
            break;
        default:
            limboAssertMsg(0, "unknown status");
    }

    // 4. apply results 
    // get dual solution of LP, which is the flow of min-cost flow, skip this if not necessary
    alg.flowMap(d->flowMap());
    // get solution of LP, which is the dual solution of min-cost flow 
    alg.potentialMap(d->potentialMap());
    // set total cost of min-cost flow 
    d->setTotalFlowCost(alg.totalCost());

    return solverStatus; 
}
void CycleCanceling::copy(CycleCanceling const& rhs)
{
    m_method = rhs.m_method;
}

} // namespace solvers 
} // namespace limbo 
