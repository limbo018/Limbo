/*************************************************************************
    > File Name: test_lpmcf.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 15 Oct 2014 05:08:44 PM CDT
 ************************************************************************/

#include <iostream>
#include <boost/algorithm/string/predicate.hpp>
#include <limbo/solvers/lpmcf/Lgf.h>
#include <limbo/solvers/lpmcf/LpDualMcf.h>

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		limbo::solvers::lpmcf::Lgf<long> lpsolver1;
		limbo::solvers::lpmcf::LpDualMcf<long> lpsolver2;

		string filename = argv[1];
		if (boost::ends_with(filename, ".lgf"))
		{
			lpsolver1(filename);
			lpsolver1.print_graph("graph1");
		}
		else if (boost::ends_with(filename, ".lp"))
		{
			lpsolver2(filename);
			lpsolver2.print_graph("graph2");
		}
		else 
			cout << "only support .lgf and .lp file formats" << endl;

		//lpsolver();
	}
	else 
		cout << "at least 1 argument required\n";

	return 0;
}
