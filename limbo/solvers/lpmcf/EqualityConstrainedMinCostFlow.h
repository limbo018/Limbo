/**
 * @file   EqualityConstrainedMinCostFlow.h
 * @brief  Solve equality constrained min-cost flow problem 
 *
 * [Lemon](https://lemon.cs.elte.hu) is used as min-cost flow solver 
 *
 * @author Yibo Lin
 * @date   Feb 2017
 */

#ifndef _LIMBO_SOLVERS_LPMCF_EQUALITYCONSTRAINEDMINCOSTFLOW_H
#define _LIMBO_SOLVERS_LPMCF_EQUALITYCONSTRAINEDMINCOSTFLOW_H

#include <vector>
#include <lemon/list_graph.h>
#include <lemon/smart_graph.h>

#include <lemon/lgf_reader.h>
#include <lemon/lgf_writer.h>
#include <lemon/graph_to_eps.h>
#include <lemon/math.h>

#include <lemon/capacity_scaling.h>

#include <limbo/preprocessor/AssertMsg.h>
#include <limbo/math/Math.h>

/// namespace for Limbo 
namespace limbo 
{ 
/// namespace for Limbo.Solvers 
namespace solvers 
{ 
/// namespace for Limbo.Solvers.lpmcf 
namespace lpmcf 
{

/// @brief Solve equality constrained min-cost flow by lagrangian relaxation and iterative min-cost flow. 
/// 
/// Given a graph \f$G = (V, E) \f$ and a set \f$EQ\f$ which stores the pairs of edges 
/// whose flows must be the same, 
/// the primal problem \f$P\f$ is defined as follows, 
/// \f{eqnarray*}{
/// & min. & \sum_{ij \in E} c_{ij} f_{ij}, \\
/// & s.t. & \sum_{ij \in E} f_{ij} - \sum_{ji \in E} f_{ji} = b_i, \forall i \in V, \\
/// &      & l_{ij} \le f_{ij} \le u_{ij}, \forall (i, j) \in E, \\
/// &      & f_{i_1 j_1} - f_{i_2 j_2} = 0, \forall ((i_1, j_1), (i_2, j_2)) \in EQ. 
/// \f}
/// Due to the last constraint, it is no longer a min-cost flow problem. 
/// 
/// We can relax the last constraint to the objective and get a lagrangian relaxation problem \f$L\f$, 
/// \f{eqnarray*}{
/// & min. & \sum_{ij \in E} c_{ij} f_{ij} + \sum_{l=1}^{|EQ|} \mu_l (f_{i_1 j_1} - f_{i_2 j_2}), \\
/// & s.t. & \sum_{ij \in E} f_{ij} - \sum_{ji \in E} f_{ji} = b_i, \forall i \in V, \\
/// &      & l_{ij} \le f_{ij} \le u_{ij}, \forall (i, j) \in E. \\
/// \f}
/// 
/// The lagrangian problem \f$L\f$ can be rewritten as, 
/// \f{eqnarray*}{
/// & min. & \sum_{ij \in E} c'_{ij} f_{ij}, \\
/// & s.t. & \sum_{ij \in E} f_{ij} - \sum_{ji \in E} f_{ji} = b_i, \forall i \in V, \\
/// &      & l_{ij} \le f_{ij} \le u_{ij}, \forall (i, j) \in E, \\
/// \f}
/// where, 
/// \f{eqnarray*}{
///   c'_{ij} & = c_{ij} + \sum_{((i, j), (i_2, j_2)) \in EQ} \mu_l - \sum_{((i_1, j_1), (i, j)) \in EQ} \mu_l. 
/// \f}
/// 
/// The lagrangian problem \f$L\f$ is a typical min-cost flow problem with real number costs and integer bounds of capacities on edges. 
/// So solving problem \f$L\f$ gets integer flows. 
/// By adjusting lagrangian multiplier $\mu$ with subgradient descent method, 
/// \f{eqnarray*}{
/// & \mu_l^{k+1} & = \mu_l^k + \theta_k (f_{i_1 j_1}^k - f_{i_2 j_2}^k), \\
/// & \theta_k & = \frac{\lambda (UB - L(\mu^k))}{\| A_{EQ} f \|^2}, \\
/// &          & = \frac{\lambda (UB - L(\mu^k))}{\sum_{EQ} (f_{i_1 j_1} - f_{i_2 j_2})^2}. 
/// \f}
/// The scalar \f$\theta_k\f$ must be a value between 0 and 2. 
/// One can start from 2 and reduce it by a factor of 2 if \f$L(\mu_k)\f$ fails to increase in a specific iteration \cite FLOW_B2005_Ahuja . 
/// 
/// 
/// 
/// @tparam GR The digraph type the algorithm runs on.
/// @tparam V The number type used for flow amounts, capacity bounds
/// and supply values in the algorithm. By default, it is \c int.
/// @tparam C The number type used for costs and potentials in the
/// algorithm. By default, it is the same as \c V.
/// @tparam TR The traits class that defines various types used by the
/// algorithm. By default, it is \ref CapacityScalingDefaultTraits
/// "CapacityScalingDefaultTraits<GR, V, C>".
/// In most cases, this parameter should not be set directly,
/// consider to use the named template parameters instead.
///
/// @warning Both \c V and \c C must be signed number types.
/// @warning Capacity bounds and supply values must be integer, but
/// arc costs can be arbitrary real numbers.
/// @warning This algorithm does not support negative costs for
/// arcs having infinite upper bound.
template < typename GR, typename V = int, typename C = V, 
         typename TR = lemon::CapacityScalingDefaultTraits<GR, V, C> >
class EqualityConstrainedMinCostFlow : public lemon::CapacityScaling<GR, V, C, TR>
{
    public:
        /// @nowarn
        typedef lemon::CapacityScaling<GR, V, C, TR> base_type; 
        typedef GR graph_type; 
        typedef V value_type; 
        typedef C cost_type; 
		typedef typename graph_type::Node node_type;
		typedef typename graph_type::Arc arc_type;
		//typedef typename graph_type::NodeMap<value_type> node_value_map_type;
		//typedef typename graph_type::ArcMap<value_type> arc_value_map_type;
		//typedef typename graph_type::ArcMap<value_type> arc_cost_map_type;
		//typedef typename graph_type::ArcMap<value_type> arc_flow_map_type;
		//typedef typename graph_type::NodeMap<value_type> node_pot_map_type; // potential of each node 
        typedef typename std::vector<std::pair<arc_type, arc_type> > equality_map_type; ///< map for equality constraints 
        /// @endnowarn
        
        /// @brief constructor 
        EqualityConstrainedMinCostFlow(graph_type const& graph)
            : base_type(graph)
        {
            m_lambda = 2.0; 
            m_prevLagTotalCost = std::numeric_limits<cost_type>::max();
        }
        /// @brief destructor 
        ~EqualityConstrainedMinCostFlow()
        {
        }
        /// @brief API to run the algorithm 
        /// @param maxIters maximum number of iterations 
        /// @param factor The capacity scaling factor. It must be larger than
        /// one to use scaling. If it is less or equal to one, then scaling
        /// will be disabled.
        /// @return solving status 
		typename base_type::ProblemType operator()(int maxIters, int factor = 4)
		{
            m_maxIters = maxIters;
            this->_factor = factor;
            typename base_type::ProblemType pt = this->init();
            if (pt != base_type::OPTIMAL) return pt;
            return runKernel();
		}

        /// @brief Set equality constraints 
        /// @param map for equality constraints in pairs of \f$((i_1, j_1), (i_2, j_2))\f$
        /// which denotes \f$f_{i_1 j_1} - f_{i_2 j_2} = 0\f$
        /// @return a reference to the object 
        EqualityConstrainedMinCostFlow& equalityMap(equality_map_type const& map)
        {
            m_equalityMap.assign(map.begin(), map.end());
            return *this; 
        }

    protected:
        /// @brief kernel function for the algorithm 
        /// @return solving status 
        typename base_type::ProblemType runKernel()
        {
            typename base_type::ProblemType pt = base_type::OPTIMAL; 
            for (int iter = 0; iter < m_maxIters; ++iter)
            {
                // solve min-cost flow 
                pt = this->start(); 

                // compute multiplier step theta 
                cost_type theta = computeMultiplierStepTheta(iter); 
                // exit if theta is small enough, which means optimal solution found 
                if (limbo::abs(theta) < std::numeric_limits<cost_type>::epsilon())
                    break; 
                // compute lagrangian multiplier for next iteration 
                // and update edge cost 
                // \mu^{k+1} = \mu^k + theta * (A_{EQ} f - b)
                computeMultiplierAndUpdateEdgeCost(theta); 

                // a naive way to refresh data members 
                // @todo update in a less expensive way 
                this->init();
            }
            return pt; 
        }

        /// @brief compute multiplier step \f$\theta_k\f$
        /// @param iter iteration \f$k\f$
        /// @return \f$\theta_k\f$
        cost_type computeMultiplierStepTheta(int iter) 
        {
            cost_type lagTotalCost = this->totalCost();
            // reduce lambda if the lagrangian objective fails to increase 
            if (iter && lagTotalCost <= m_prevLagTotalCost)
                m_lambda /= 2; 
            m_prevLagTotalCost = lagTotalCost;
            // I am not sure how to setup UB yet 
            cost_type upperBound = 10000; 

            // compute squared 2-norm of A_{EQ}f - b
            value_type squared2Norm = 0; 
            for (typename equality_map_type::const_iterator it = m_equalityMap.begin(), ite = m_equalityMap.end(); it != ite; ++it)
            {
                value_type gradient = computeEqualityGradient(it->first, it->second); 
                squared2Norm += gradient*gradient; 
            }

            cost_type theta = (squared2Norm == 0)? 0 : m_lambda*(upperBound-lagTotalCost)/(cost_type)squared2Norm;
            return theta; 
        }

        /// @brief compute lagrangian multiplier for next iteration 
        /// and update edge cost 
        /// @param theta multiplier step \f$\theta_k\f$ 
        void computeMultiplierAndUpdateEdgeCost(cost_type theta)
        {
            for (typename equality_map_type::const_iterator it = m_equalityMap.begin(), ite = m_equalityMap.end(); it != ite; ++it)
            {
                cost_type gradient = computeEqualityGradient(it->first, it->second); 
                cost_type step = theta*gradient; 

                // forward edges 
                this->_cost[this->_arc_idf[it->first]] += step; 
                this->_cost[this->_arc_idf[it->second]] -= step; 

                // reverse edges
                this->_cost[this->_arc_idb[it->first]] -= step; 
                this->_cost[this->_arc_idb[it->second]] += step; 

#ifdef DEBUG_EQUALITYCONSTRAINEDMINCOSTFLOW
                limboAssertMsg(limbo::abs(this->_cost[this->_arc_idf[it->first]] + this->_cost[this->_arc_idb[it->first]]) < 1.0e-6, "%g != %g", 
                        this->_cost[this->_arc_idf[it->first]], this->_cost[this->_arc_idb[it->first]]);
                limboAssertMsg(limbo::abs(this->_cost[this->_arc_idf[it->second]] + this->_cost[this->_arc_idb[it->second]]) < 1.0e-6, "%g != %g", 
                        this->_cost[this->_arc_idf[it->second]], this->_cost[this->_arc_idb[it->second]]);
#endif 
            }
        }

        /// @brief Compute gradient of an equality constraint according to current solution. 
        /// @param arc1 arc \f$(i_1, j_1)\f$
        /// @param arc2 arc \f$(i_2, j_2)\f$
        /// @return \f$f_{i_1 j_1} - f_{i_2 j_2}\f$
        value_type computeEqualityGradient(arc_type const& arc1, arc_type const& arc2) const 
        {
            value_type flow1 = this->flow(arc1);
            value_type flow2 = this->flow(arc2); 
            return flow1-flow2; 
        }

        equality_map_type m_equalityMap; ///< map for equality constraints, \f$((i_1, j_1), (i_2, j_2))\f$ which denotes \f$f_{i_1 j_1} - f_{i_2 j_2} = 0\f$
        int m_maxIters; ///< maximum number of iterations 
        cost_type m_lambda; ///< a scaling factor \f$\lambda_k\f$ for computing multiplier step \f$theta_k\f$
        cost_type m_prevLagTotalCost; ///< previous total cost of lagrangian problem \f$L\f$, updated in each iteration 
};

} // namespace lpmcf
} // namespace solvers
} // limbo 

#endif
