/**
 * @file   test_CplexApi.cpp
 * @author Yibo Lin
 * @date   Aug 2023
 * @brief  Test CPLEX API @ref limbo::solvers::CplexLinearApi
 */
#include <iostream>
#include <limbo/solvers/api/CplexApi.h>

/// @brief main function 
/// 
/// Solve following problem, 
/// \f{eqnarray*}{
/// & min. & x_1 + x_2 + x_3 + x_4, \\
/// & s.t. & x_1 - x_2 \ge 0.5,  \\
/// &     & x_4 - x_3 \ge 0.1, \\
/// &     & x_2 - x_3 \ge 0.2.  
/// \f}
/// 
/// @return 0 
int main()
{
    // ILP model 
    typedef limbo::solvers::LinearModel<double, double> model_type; 
    model_type optModel; 

    // create variables 
    model_type::variable_type var1 = optModel.addVariable(0, 1, limbo::solvers::CONTINUOUS, "x1");
    model_type::variable_type var2 = optModel.addVariable(0, 1, limbo::solvers::CONTINUOUS, "x2");
    model_type::variable_type var3 = optModel.addVariable(0, 1, limbo::solvers::CONTINUOUS, "x3");
    model_type::variable_type var4 = optModel.addVariable(0, 1, limbo::solvers::CONTINUOUS, "x4");

    // create objective
    optModel.setObjective(var1+var2+var3+var4); 
    optModel.setOptimizeType(limbo::solvers::MIN);

    // create constraints 
    optModel.addConstraint(var1 - var2 >= 0.5, "c1"); 
    optModel.addConstraint(var4 - var3 >= 0.1, "c2"); 
    optModel.addConstraint(var2 - var3 >= 0.2, "c3"); 

    // solve by CPLEX 
    typedef limbo::solvers::CplexLinearApi<model_type::coefficient_value_type, model_type::variable_value_type> solver_type; 
    solver_type solver (&optModel); 
    limbo::solvers::CplexParameters cplexParams; 
    cplexParams.setNumThreads(1);
    cplexParams.setOutputFlag(1); 

    limbo::solvers::SolverProperty optStatus = solver(&cplexParams); 

    std::cout << "optStatus = " << optStatus << std::endl; 

    std::cout << optModel.variableName(var1) << " = " << optModel.variableSolution(var1) << "\n";
    std::cout << optModel.variableName(var2) << " = " << optModel.variableSolution(var2) << "\n";
    std::cout << optModel.variableName(var3) << " = " << optModel.variableSolution(var3) << "\n";
    std::cout << optModel.variableName(var4) << " = " << optModel.variableSolution(var4) << "\n";

    return 0; 
}
