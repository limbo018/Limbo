/**
 * @file   MultiKnapsackLagRelax.h
 * @author Yibo Lin
 * @date   Feb 2017
 * @brief  Solve multiple knapsack problem with lagrangian relaxation 
 */
#include <limbo/solvers/Solvers.h>

/// namespace for Limbo 
namespace limbo 
{
/// namespace for Limbo.Solvers 
namespace solvers 
{

// forward declaration 
struct LagMultiplierUpdater;

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
class MultiKnapsackLagRelax
{
    public:
        /// @brief linear model type for the problem 
        typedef LinearModel<float, int> model_type; 
        /// @nowarn
        typedef model_type::coefficient_value_type coefficient_value_type; 
        typedef model_type::variable_value_type variable_value_type; 
        typedef model_type::constraint_type constraint_type; 
        typedef model_type::expression_type expression_type; 
        typedef model_type::term_type term_type; 
        typedef model_type::property_type property_type;
        /// @endnowarn

        /// @brief constructor 
        /// @param model pointer to the model of problem 
        /// @param updater an object to update lagrangian multipliers 
        MultiKnapsackLagRelax(model_type* model, LagMultiplierUpdater* updater = NULL);
        /// @brief copy constructor 
        /// @param rhs right hand side 
        MultiKnapsackLagRelax(MultiKnapsackLagRelax const& rhs);
        /// @brief assignment
        /// @param rhs right hand side 
        MultiKnapsackLagRelax operator=(MultiKnapsackLagRelax const& rhs);
        /// @brief destructor 
        ~MultiKnapsackLagRelax(); 
        
        /// @brief API to run the algorithm 
        SolverProperty operator()(); 
    protected:
        /// @brief copy object 
        void copy(MultiKnapsackLagRelax const& rhs);
        /// @brief kernel function to solve the problem 
        SolverProperty solve();
        /// @brief prepare weights of variables in objective 
        /// and classify constraints by marking capacity constraints and single item constraints 
        void prepare();
        /// @brief update lagrangian multipliers 
        void updateLagMultipliers(); 
        /// @brief solve lagrangian subproblem 
        void solveLag(); 
        /// @brief evaluate objective of the lagrangian subproblem 
        coefficient_value_type evaluateLagObjective() const;
        /// @brief check convergence of current solution 
        /// @return true if already converged 
        bool converge() const; 
        /// @brief post refine solution if failed to converge after maximum iteration 
        SolverProperty postRefine(); 

        model_type* m_model; ///< model for the problem 
        LagMultiplierUpdater* m_lagMultiplierUpdater; ///< an object to update lagrangian multipliers
        bool m_defaultUpdater; ///< a flag to record whether default updater is used 

        std::vector<coefficient_value_type> m_vObjCoef; ///< coefficients variables in objective 
        std::vector<std::vector<Variable> > m_vVariableGroup; ///< group variables according to item 
        std::vector<coefficient_value_type> m_vLagMultiplier; ///< array of lagrangian multipliers 
        coefficient_value_type m_objConstant; ///< constant value in objective from lagrangian relaxation
        coefficient_value_type m_lagObj; ///< current objective of the lagrangian subproblem 
        unsigned int m_iter; ///< current iteration 
        unsigned int m_maxIters; ///< maximum number of iterations 
};

/// @brief A helper function object to update lagrangian multipliers using subgradient descent. 
/// All other schemes can be derived from this class 
class LagMultiplierUpdater
{
    public:
        typedef MultiKnapsackLagRelax::coefficient_value_type value_type; 

        /// @brief constructor 
        /// @param alpha the power term for scaling factor \f$ t_k = k^{-\alpha} \f$
        LagMultiplierUpdater(value_type alpha);
        /// @brief copy constructor 
        /// @brief right hand side 
        LagMultiplierUpdater(LagMultiplierUpdater const& rhs);
        /// @brief assignment 
        /// @brief right hand side 
        LagMultiplierUpdater& operator=(LagMultiplierUpdater const& rhs); 

        /// @brief API to update lagrangian multiplier using subgradient descent 
        /// @param iter current iteration 
        /// @param multiplier current multiplier value 
        /// @param slackness current slackness value assuming the constraint is in \f$ Ax \le b \f$ and compute \f$ b-Ax \f$
        /// @return updated multiplier value 
        virtual value_type operator()(unsigned int iter, value_type multiplier, value_type slackness);
    protected:
        /// @brief copy object 
        /// @brief right hand side 
        void copy(LagMultiplierUpdater const& rhs);

        value_type m_alpha; ///< power 
        unsigned int m_iter; ///< current iteration 
        value_type m_scalingFactor; ///< scaling factor \f$ t_k = k^{-\alpha} \f$
};

} // namespace solvers 
} // namespace limbo 
