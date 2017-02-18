/**
 * @file   MultiKnapsackLagRelax.h
 * @author Yibo Lin
 * @date   Feb 2017
 * @brief  Solve multiple knapsack problem with lagrangian relaxation 
 */
#ifndef LIMBO_SOLVERS_MULTIKNAPSACKLAGRELAX_H
#define LIMBO_SOLVERS_MULTIKNAPSACKLAGRELAX_H

#include <limbo/solvers/Solvers.h>

/// namespace for Limbo 
namespace limbo 
{
/// namespace for Limbo.Solvers 
namespace solvers 
{

// forward declaration 
struct LagMultiplierUpdater;
struct ProblemScaler; 

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
        typedef model_type::variable_type variable_type;
        typedef model_type::constraint_type constraint_type; 
        typedef model_type::expression_type expression_type; 
        typedef model_type::term_type term_type; 
        typedef model_type::property_type property_type;
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
        SolverProperty operator()(LagMultiplierUpdater* updater = NULL, ProblemScaler* scaler = NULL); 

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
    protected:
        /// @brief copy object 
        void copy(MultiKnapsackLagRelax const& rhs);
        /// @brief kernel function to solve the problem 
        /// @param updater an object to update lagrangian multipliers
        /// @param scaler an object to scale constraints and objective, use default scaler if NULL 
        SolverProperty solve(LagMultiplierUpdater* updater, ProblemScaler* scaler);
        /// @brief scale problem for better numerical instability 
        /// @param scaler an object to scale constraints and objective, use default scaler if NULL 
        void scale(ProblemScaler* scaler); 
        /// @brief recover problem from scaling 
        void unscale(); 
        /// @brief prepare weights of variables in objective 
        /// and classify constraints by marking capacity constraints and single item constraints 
        void prepare();
        /// @brief update lagrangian multipliers 
        /// @param updater an object to update lagrangian multipliers
        void updateLagMultipliers(LagMultiplierUpdater* updater); 
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

/// @brief A base helper function object to update lagrangian multipliers using subgradient descent. 
/// All other schemes can be derived from this class 
class LagMultiplierUpdater
{
    public:
        /// @brief value type 
        typedef MultiKnapsackLagRelax::coefficient_value_type value_type; 

        /// @brief constructor 
        LagMultiplierUpdater();
        /// @brief destructor 
        virtual ~LagMultiplierUpdater();

        /// @brief API to update lagrangian multiplier 
        /// @param iter current iteration 
        /// @param multiplier current multiplier value 
        /// @param slackness current slackness value assuming the constraint is in \f$ Ax \le b \f$ and compute \f$ b-Ax \f$
        /// @return updated multiplier value 
        virtual value_type operator()(unsigned int iter, value_type multiplier, value_type slackness) = 0;
};

/// @brief Update lagrangian multiplier with subgradient descent 
class SubGradientDescent : public LagMultiplierUpdater
{
    public:
        /// @brief base type 
        typedef LagMultiplierUpdater base_type;

        /// @brief constructor 
        /// @param alpha the power term for scaling factor \f$ t_k = k^{-\alpha} \f$
        SubGradientDescent(value_type alpha = 1);
        /// @brief copy constructor 
        /// @brief right hand side 
        SubGradientDescent(SubGradientDescent const& rhs);
        /// @brief assignment 
        /// @brief right hand side 
        SubGradientDescent& operator=(SubGradientDescent const& rhs); 
        /// @brief destructor 
        ~SubGradientDescent();

        /// @brief API to update lagrangian multiplier using subgradient descent 
        /// @param iter current iteration 
        /// @param multiplier current multiplier value 
        /// @param slackness current slackness value assuming the constraint is in \f$ Ax \le b \f$ and compute \f$ b-Ax \f$
        /// @return updated multiplier value 
        value_type operator()(unsigned int iter, value_type multiplier, value_type slackness);
    protected:
        /// @brief copy object 
        /// @brief right hand side 
        void copy(SubGradientDescent const& rhs);

        value_type m_alpha; ///< power 
        unsigned int m_iter; ///< current iteration 
        value_type m_scalingFactor; ///< scaling factor \f$ t_k = k^{-\alpha} \f$
};

/// @brief Base class for scaling scheme with default L2 norm scaling  
class ProblemScaler
{
    public:
        /// @brief value type 
        typedef MultiKnapsackLagRelax::coefficient_value_type value_type; 
        /// @brief expression type 
        typedef MultiKnapsackLagRelax::expression_type expression_type; 
        /// @brief constraint type 
        typedef MultiKnapsackLagRelax::constraint_type constraint_type; 
        /// @brief term type 
        typedef MultiKnapsackLagRelax::term_type term_type; 

        /// @brief constructor 
        ProblemScaler();
        /// @brief destructor 
        virtual ~ProblemScaler();

        /// @brief API to compute scaling factor for expression using L2 norm  
        /// @param expr expression 
        /// @return scaling factor 
        virtual value_type operator()(expression_type const& expr) const;
        /// @brief API to compute scaling factor for constraints  using L2 norm 
        /// @param constr constraint 
        /// @return scaling factor 
        virtual value_type operator()(constraint_type const& constr) const;
};

} // namespace solvers 
} // namespace limbo 

#endif
