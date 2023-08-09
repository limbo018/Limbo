/**
 * @file   CplexApi.h
 * @brief  CPLEX API wrapper using its C API. 
 * @author Yibo Lin
 * @date   Aug 2023
 */

#ifndef LIMBO_SOLVERS_API_CPLEXAPI_H
#define LIMBO_SOLVERS_API_CPELXAPI_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp> 
#include <limbo/solvers/Solvers.h>
// make sure CPLEX is configured properly 
extern "C" 
{
#include <ilcplex/cplexx.h>
#include <string.h>
#include <stdlib.h>
}

/// namespace for Limbo
namespace limbo 
{ 
/// namespace for Solvers 
namespace solvers 
{

/// @brief Base class for custom CPLEX parameters 
class CplexParameters
{
    public:
        /// @brief constructor 
        CplexParameters() 
            : m_outputFlag(0)
            , m_numThreads(std::numeric_limits<int>::max())
        {
        }
        /// @brief destructor 
        virtual ~CplexParameters() {}
        /// @brief customize environment 
        /// @param env Cplex environment 
        virtual void operator()(GRBenv* env) const 
        {
            // mute the log from the LP solver
            GRBsetintparam(env, GRB_INT_PAR_OUTPUTFLAG, m_outputFlag); 
            if (m_numThreads > 0 && m_numThreads != std::numeric_limits<int>::max())
                GRBsetintparam(env, GRB_INT_PAR_THREADS, m_numThreads);
        }
        /// @brief customize model 
        /// 
        /// param model CPLEX model 
        virtual void operator()(GRBmodel* /*model*/) const 
        {
        }

        /// @brief set output flag 
        /// @param v value 
        void setOutputFlag(int v) {m_outputFlag = v;}
        /// @brief set number of threads 
        /// @param v value 
        void setNumThreads(int v) {m_numThreads = v;}

    protected:
        int m_outputFlag; ///< control log from CPLEX 
        int m_numThreads; ///< number of threads 
};

/// @brief Round floating point solutions to integer if the variable type is integer. 
/// If not rounded, there might be precision issues. 
template <typename T, std::size_t = std::numeric_limits<T>::is_integer>
struct SmartRound
{
    inline T operator()(double value) const 
    {
        return value; 
    }
}; 

template <typename T>
struct SmartRound<T, 1>
{
    inline T operator()(double value) const 
    {
        return std::round(value); 
    }
}; 

/// @brief CPLEX API with @ref limbo::solvers::LinearModel
/// @tparam T coefficient type 
/// @tparam V variable type 
template <typename T, typename V>
class CplexLinearApi 
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
        typedef CplexParameters parameter_type; 
        /// @endnowarn
        
        /// @brief constructor 
        /// @param model pointer to the model of problem 
        CplexLinearApi(model_type* model)
            : m_model(model)
              , m_cplexModel(NULL)
        {
        }
        /// @brief destructor 
        ~CplexLinearApi()
        {
        }
        
        /// @brief API to run the algorithm 
        /// @param param set additional parameters, use default if NULL 
        SolverProperty operator()(parameter_type* param = NULL)
        {
            bool defaultParam = false; 
            if (param == NULL)
            {
                param = new CplexParameters;
                defaultParam = true; 
            }

            // ILP environment
            CPXENVptr env = NULL; 
            m_cplexModel = NULL; 
            int status; 
            // Create environment
            env = CPXXopenCPLEX (&status);
            if (env == NULL)
            {
              char  errmsg[CPXMESSAGEBUFSIZE];
              CPXXgeterrorstring (env, status, errmsg);
              limboAssertMsg(0, "Could not open CPLEX environment: %s", errmsg);
            }
            param->operator()(env); 
            // Create an empty model 
            m_cplexModel = CPXXcreateprob (env, &status, "CplexLinearApi");
            if (status) 
            {
              limboAssertMsg(0, "Could not create model");
            }

            CPXDIM   numcols = m_model->numVariables();
            CPXDIM   numrows = m_model->constraints().size();
            int      objsen;
            std::vector<double> obj (numcols, 0);
            std::vector<double> rhs (numrows, 0);
            std::vector<char> sense (numrows, '=');
            std::vector<CPXNNZ> matbeg (numcols, 0);
            std::vector<CPXDIM> matcnt (numcols, 0);
            std::vector<CPXDIM> matind (numnz, 0);
            std::vector<double> matval (numnz, 0);
            std::vector<double> lb (numcols);
            std::vector<double> ub (numcols);
            std::vector<char> ctype (numcols);
            // create variables 
            for (unsigned int i = 0, ie = m_model->numVariables(); i < ie; ++i)
            {
                variable_type var (i);
                lb[var.id()] = m_model->variableLowerBound(var);
                ub[var.id()] = m_model->variableUpperBound(var);
                // error = GRBsetdblattrelement(m_cplexModel, GRB_DBL_ATTR_START, var.id(), m_model->variableSolution(var));
                ctype[var.id()] = m_model->variableNumericType(var) == CONTINUOUS? 'C' : 'I';
            }

            // create constraints 
            // initialize matcnt 
            for (unsigned int i = 0, ie = m_model->constraints().size(); i < ie; ++i)
            {
                constraint_type const& constr = m_model->constraints().at(i);

                for (typename std::vector<term_type>::const_iterator it = constr.expression().terms().begin(), ite = constr.expression().terms().end(); it != ite; ++it)
                {
                    if (it->coefficient() != 0)
                    {
                      matcnt[it->variable().id()] += 1; 
                    }
                }
            }
            // initialize matbeg 
            for (unsigned int i = 0; i < numcols - 1; ++i)
            {
              matbeg[i + 1] = matbeg[i] + matcnt[i];
            }
            // initialize matind, matval, sense, rhs
            for (unsigned int i = 0, ie = m_model->constraints().size(); i < ie; ++i)
            {
                constraint_type const& constr = m_model->constraints().at(i);

                for (typename std::vector<term_type>::const_iterator it = constr.expression().terms().begin(), ite = constr.expression().terms().end(); it != ite; ++it)
                {
                    if (it->coefficient() != 0)
                    {
                      matind[matbeg[it->variable().id()] + i] = i; 
                      matval[matbeg[it->variable().id()] + i] = it->coefficient(); 
                    }
                }

                switch (constr.sense())
                {
                  case '<':
                    sense[i] = 'L'; break; 
                  case '=':
                    sense[i] = 'E'; break; 
                  case '>':
                    sense[i] = 'G'; break; 
                  default:
                    limboAssertMsg(0, "Unknown sense for row %u: %c", i, constr.sense());
                    break; 
                }

                rhs[i] = constr.rightHandSide();
            }

            // create objective 
            for (typename std::vector<term_type>::const_iterator it = m_model->objective().terms().begin(), ite = m_model->objective().terms().end(); it != ite; ++it)
            {
              obj[it->variable().id()] = it->coefficient();
            }
            objsen = m_model->optimizeType() == MIN? CPX_MIN : CPX_MAX;

            // call parameter setting before optimization 
            param->operator()(m_cplexModel); 
            status = CPXXcopylp (env, m_cplexModel, numcols, numrows, objsen, obj.data(), rhs.data(),
                sense.data(), matbeg.data(), matcnt.data(), matind.data(), matval.data(),
                lb.data(), ub.data(), NULL);
            if (status)
            {
              limboAssertMsg(0, "CPXXcopylp failed");
            }
            status = CPXXcopyctype (env, m_cplexModel, ctype.data());
            if (status)
            {
              limboAssertMsg(0, "CPXXcopyctype failed");
            }

#ifdef DEBUG_CPLEXAPI
            status = CPXXwriteprob (env, m_cplexModel, "problem.lp", NULL);
            if (status)
            {
              limboAssertMsg(0, "CPXXwriteprob failed");
            }
#endif 
            status = CPXXmipopt (env, m_cplexModel);
            if (status)
            {
              limboAssertMsg(0, "CPXXmipopt failed");
            }

            int solstat = CPXXgetstat (env, m_cplexModel);
            if (status)
            {
              limboAssertMsg(0, "CPXXgetstat failed");
            }

            if (solstat == GRB_INFEASIBLE)
            {
                error = GRBcomputeIIS(m_cplexModel);
                errorHandler(env, error); 
                GRBwrite(m_cplexModel, "problem.ilp");
                limboPrint(kERROR, "Model is infeasible, compute IIS and write to problem.ilp\n");
            }
#ifdef DEBUG_CPLEXAPI
            status = CPXXwriteprob (env, m_cplexModel, "problem.sol.lp", NULL);
            if (status)
            {
              limboAssertMsg(0, "CPXXwriteprob failed");
            }
#endif 

            cur_numrows = CPXXgetnumrows (env, lp);
            cur_numcols = CPXXgetnumcols (env, lp);
            status = CPXXgetx (env, lp, x, 0, cur_numcols-1);
            if (status)
            {
              limboAssertMsg(0, "CPXXgetx failed");
            }
            // round if the variable type is integer 
            SmartRound<V> sround; 
            for (unsigned int i = 0; i < m_model->numVariables(); ++i)
            {
                variable_type var = m_model->variable(i); 
                double value = x[var.id()]; 
                m_model->setVariableSolution(m_model->variable(i), sround(value));
            }

            if (defaultParam)
                delete param; 
            // Free model 
            if (m_cplexModel != NULL) 
            {
              status = CPXXfreeprob (env, &m_cplexModel);
              if (status)
              {
                limboAssertMsg(0, "CPXXfreeprob failed");
              }
            }
            // Free environment 
            if (env != NULL)
            {
              status = CPXXcloseCPLEX (&env);
              if (status)
              {
                limboAssertMsg(0, "CPXXcloseCPLEX failed");
              }
            }

            switch (solstat)
            {
                case CPX_STAT_OPTIMAL:
                    return OPTIMAL;
                case CPX_STAT_INFEASIBLE:
                    return INFEASIBLE;
                case CPX_STAT_INForUNBD:
                case CPX_STAT_UNBOUNDED:
                    return UNBOUNDED;
                default:
                    limboAssertMsg(0, "unknown status %d", solstat);
            }
        }

    protected:
        /// @brief copy constructor, forbidden 
        /// @param rhs right hand side 
        CplexLinearApi(CplexLinearApi const& rhs);
        /// @brief assignment, forbidden 
        /// @param rhs right hand side 
        CplexLinearApi& operator=(CplexLinearApi const& rhs);

        model_type* m_model; ///< model for the problem 
        CPXLPptr m_cplexModel; ///< model for CPLEX 
};

#if CPLEXFILEAPI == 1
#include <ilcplex/ilocplex.h>
/// This api needs a file in LP format as input.
/// And then read the solution output by CPLEX 
/// I plan to come up with more efficient api without file io operations 
template <typename T>
struct CplexFileApi 
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
	/// Core function to solve lp problem with CPLEX. 
	/// It is modified from examples of CPLEX. 
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
#endif

} // namespace solvers
} // namespace limbo

#endif 
