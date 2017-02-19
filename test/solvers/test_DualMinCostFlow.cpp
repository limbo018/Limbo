/**
 * @file   ../../test/solvers/test_DualMinCostFlow.cpp
 * @author Yibo Lin
 * @date   Feb 2017
 */

#include <iostream>
#include <limbo/solvers/DualMinCostFlow.h>

/// @brief test file API 
/// @param filename input lp file 
void test(std::string const& filename)
{
    typedef limbo::solvers::LinearModel<int, int> model_type; 
    model_type optModel; 
    optModel.read(filename); 

    // print problem 
    optModel.print(std::cout); 

    limbo::solvers::DualMinCostFlow solver (&optModel); 

    // solve 
    limbo::solvers::SolverProperty status = solver();
    std::cout << "Problem solved " << limbo::solvers::toString(status) << "\n";

    // print solutions 
    optModel.printSolution(std::cout);
    // print problem 
    optModel.print(std::cout); 
}

/// @brief main function 
/// 
/// Given .lp file, solver linear programming problem with dual min-cost flow by @ref limbo::solvers::DualMinCostFlow. 
/// 
/// @param argc number of arguments 
/// @param argv values of arguments 
/// @return 0 
int main(int argc, char** argv)
{
	if (argc > 1)
	{
        // test file API 
        test(argv[1]);
	}
	else 
		std::cout << "at least 1 argument required\n";

	return 0;
}
