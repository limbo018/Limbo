/**
 * @file   GurobiApi.h
 * @brief  Gurobi API by writing out problem file in LP format and read solution. 
 *         Consider the file IO overhead before using it. 
 * @author Yibo Lin
 * @date   Nov 2014
 */

#ifndef LIMBO_SOLVERS_API_GUROBIAPI_H
#define LIMBO_SOLVERS_API_GUROBIAPI_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp> 
// make sure gurobi is configured properly 
#include "gurobi_c++.h"

/// namespace for Limbo
namespace limbo 
{ 
/// namespace for Solvers 
namespace solvers 
{

/// @brief Base class for custom Gurobi parameters 
class GurobiParameters
{
    public:
        /// @brief constructor 
        GurobiParameters() 
            : m_outputFlag(0)
            , m_numThreads(std::numeric_limits<int>::max())
        {
        }
        /// @brief destructor 
        virtual ~GurobiParameters() {}
        /// @brief customize environment 
        /// @param env Gurobi environment 
        virtual void operator()(GRBEnv& env) const 
        {
            // mute the log from the LP solver
            env.set(GRB_IntParam_OutputFlag, m_outputFlag);
            if (m_numThreads > 0 && m_numThreads != std::numeric_limits<int>::max())
                env.set(GRB_IntParam_Threads, m_numThreads);
        }
        /// @brief customize model 
        /// @param model Gurobi model 
        virtual void operator()(GRBModel& /*model*/) const 
        {
        }

        void setOutputFlag(int v) {m_outputFlag = v;}
        void setNumThreads(int v) {m_numThreads = v;}
    protected:
        int m_outputFlag; ///< control log from Gurobi 
        int m_numThreads; ///< number of threads 
};

/// @brief Gurobi API with @ref limbo::solvers::LinearModel
/// @tparam T coefficient type 
/// @tparam V variable type 
template <typename T, typename V>
class GurobiLinearApi 
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
        typedef GurobiParameters parameter_type; 
        /// @endnowarn
        
        /// @brief constructor 
        /// @param model pointer to the model of problem 
        GurobiLinearApi(model_type* model);
        /// @brief destructor 
        ~GurobiLinearApi(); 
        
        /// @brief API to run the algorithm 
        /// @param param set additional parameters, use default if NULL 
        SolverProperty operator()(parameter_type* param = NULL); 

    protected:
        /// @brief copy constructor, forbidden 
        /// @param rhs right hand side 
        GurobiLinearApi(GurobiLinearApi const& rhs);
        /// @brief assignment, forbidden 
        /// @param rhs right hand side 
        GurobiLinearApi& operator=(GurobiLinearApi const& rhs);

        model_type* m_model; ///< model for the problem 
        GRBModel* m_grbModel; ///< model for Gurobi 
};

template <typename T, typename V>
GurobiLinearApi<T, V>::GurobiLinearApi(GurobiLinearApi<T, V>::model_type* model)
    : m_model(model)
    , m_grbModel(NULL)
{
}
template <typename T, typename V>
GurobiLinearApi<T, V>::~GurobiLinearApi()
{
}
template <typename T, typename V>
SolverProperty GurobiLinearApi<T, V>::operator()(GurobiLinearApi<T, V>::parameter_type* param)
{
    bool defaultParam = false; 
    if (param == NULL)
    {
        param = new GurobiParameters;
        defaultParam = true; 
    }

	// ILP environment
	GRBEnv env = GRBEnv();
    param->operator()(env); 
	m_grbModel = new GRBModel(env);

    // create variables 
    GRBVar* vGrbVar = m_grbModel->addVars(m_model->numVariables()); 
    m_grbModel->update();
    for (unsigned int i = 0, ie = m_model->numVariables(); i < ie; ++i)
    {
        variable_type var (i);
        GRBVar& grbVar = vGrbVar[i]; 
        grbVar.set(GRB_DoubleAttr_LB, m_model->variableLowerBound(var)); 
        grbVar.set(GRB_DoubleAttr_UB, m_model->variableUpperBound(var)); 
        grbVar.set(GRB_DoubleAttr_Start, m_model->variableSolution(var)); 
        grbVar.set(GRB_CharAttr_VType, m_model->variableNumericType(var) == CONTINUOUS? GRB_CONTINUOUS : GRB_INTEGER); 
        grbVar.set(GRB_StringAttr_VarName, m_model->variableName(var));
    }

    // create constraints 
    GRBLinExpr expr; 
    for (unsigned int i = 0, ie = m_model->constraints().size(); i < ie; ++i)
    {
        constraint_type const& constr = m_model->constraints().at(i);

        expr.clear();
        for (typename std::vector<term_type>::const_iterator it = constr.expression().terms().begin(), ite = constr.expression().terms().end(); it != ite; ++it)
            expr += vGrbVar[it->variable().id()]*it->coefficient();

        m_grbModel->addConstr(expr, constr.sense(), constr.rightHandSide(), m_model->constraintName(constr)); 
    }

    // create objective 
    expr.clear();
    for (typename std::vector<term_type>::const_iterator it = m_model->objective().terms().begin(), ite = m_model->objective().terms().end(); it != ite; ++it)
        expr += vGrbVar[it->variable().id()]*it->coefficient();
    m_grbModel->setObjective(expr, m_model->optimizeType() == MIN? GRB_MINIMIZE : GRB_MAXIMIZE); 

    // call parameter setting before optimization 
    param->operator()(*m_grbModel); 

    m_grbModel->update(); 

#ifdef DEBUG_GUROBIAPI
    m_grbModel->write("problem.lp");
#endif 
    m_grbModel->optimize();

    int status = m_grbModel->get(GRB_IntAttr_Status);
    if (status == GRB_INFEASIBLE)
    {
        m_grbModel->computeIIS();
        m_grbModel->write("problem.ilp");
        limboPrint(kERROR, "Model is infeasible, compute IIS and write to problem.ilp\n");
    }
#ifdef DEBUG_GUROBIAPI
    m_grbModel->write("problem.sol");
#endif 

    for (unsigned int i = 0, ie = m_model->numVariables(); i < ie; ++i)
    {
        variable_type var (i);
        GRBVar& grbVar = vGrbVar[i]; 

        m_model->setVariableSolution(var, grbVar.get(GRB_DoubleAttr_X));
    }

    if (defaultParam)
        delete param; 
    delete m_grbModel; 

    switch (status)
    {
        case GRB_OPTIMAL:
            return OPTIMAL;
        case GRB_INFEASIBLE:
            return INFEASIBLE;
        case GRB_INF_OR_UNBD:
        case GRB_UNBOUNDED:
            return UNBOUNDED;
        default:
            limboAssertMsg(0, "unknown status %d", status);
    }
}

/// This api needs a file in LP format as input.
/// And then read the solution output by gurobi 
/// I plan to come up with more efficient api without file io operations 
template <typename T>
struct GurobiFileApi 
{
    /// @brief value type 
	typedef T value_type;

	/// @brief data structure to save solution
	struct solution_type 
	{
		value_type obj; ///< objective value 
		std::list<std::pair<std::string, value_type> > vVariable; ///< std::list of (variable, solution) pairs 
	};
	/// @brief API function 
    /// @param fileName input file name 
    /// @return solution 
	virtual boost::shared_ptr<solution_type> operator()(std::string const& fileName, bool = true) const 
	{
		// better to use full path for file name 
		boost::shared_ptr<solution_type> pSol (new solution_type);
		// remove previous solution file 
		std::cout << "rm -rf "+fileName+".sol" << std::endl;
		std::cout << system(("rm -rf "+fileName+".sol").c_str()) << std::endl;;

		std::cout << "solve linear program "+fileName << std::endl;
		this->solve_lp(fileName);

		// read rpt 
		{
			std::ifstream solFile ((fileName+".sol").c_str(), std::ifstream::in);
			if (!solFile.good()) BOOST_ASSERT_MSG(false, ("failed to open " + fileName + ".sol").c_str());

			std::string var;
			double value;

			// read objective value 
			solFile >> var >> var >> var >> var >> value;
			pSol->obj = value;

			while (!solFile.eof())
			{
				solFile >> var >> value;
				pSol->vVariable.push_back(make_pair(var, value));
			}
			solFile.close();
		}

		return pSol;
	}
	/// Core function to solve lp problem with Gurobi. 
	/// It is modified from examples of Gurobi. 
	/// Basically it reads input problem file, and output solution file. 
    /// @param fileName input file 
	virtual void solve_lp(std::string fileName) const 
	{
		try 
		{
			GRBEnv env = GRBEnv();
			GRBModel model = GRBModel(env, fileName+".lp");

			model.optimize();

			int optimstatus = model.get(GRB_IntAttr_Status);

			if (optimstatus == GRB_INF_OR_UNBD) 
			{
				model.getEnv().set(GRB_IntParam_Presolve, 0);
				model.optimize();
				optimstatus = model.get(GRB_IntAttr_Status);
			}

			if (optimstatus == GRB_OPTIMAL) 
			{
				double objval = model.get(GRB_DoubleAttr_ObjVal);
				std::cout << "Optimal objective: " << objval << std::endl;
				// write result 
				model.write(fileName+".sol");
			} 
			else if (optimstatus == GRB_INFEASIBLE) 
			{
				std::cout << "Model is infeasible" << std::endl;

				// compute and write out IIS

				model.computeIIS();
				model.write(fileName+".ilp");
			} 
			else if (optimstatus == GRB_UNBOUNDED) 
			{
				std::cout << "Model is unbounded" << std::endl;
			} 
			else 
			{
				std::cout << "Optimization was stopped with status = "
					<< optimstatus << std::endl;
			}
		} 
		catch(GRBException e) 
		{
			std::cout << "Error code = " << e.getErrorCode() << std::endl;
			std::cout << e.getMessage() << std::endl;
		} 
		catch (...) 
		{
			std::cout << "Error during optimization" << std::endl;
		}
	}

};

} // namespace solvers
} // namespace limbo

#endif 
