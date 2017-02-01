Limbo.Solvers {#Solvers}
---------

[TOC]

# Introduction {#Solvers_Introduction}

Solvers and API for specialized problems, such as solving special linear programming problems with min-cost flow algorithms. 
It also wraps solvers like semidefinite programming solver [Csdp](https://projects.coin-or.org/Csdp "Csdp") and convex optimization solver [Gurobi](www.gurobi.com "Gurobi"). 

# Examples {#Solvers_Examples}

## Min-Cost Flow Solvers {#Solvers_Examples_MCF}

The analysis and background of using dual min-cost flow to solve linear programming problem can be found in the detailed description of class @ref limbo::solvers::lpmcf::LpDualMcf. 

See documented version: [test/solvers/lpmcf/test_lpmcf.cpp](@ref test_lpmcf.cpp)
\include test/solvers/lpmcf/test_lpmcf.cpp

Compiling and running commands (assuming LIMBO_DIR, BOOST_DIR and LEMON_DIR are well defined). 
@ref Parsers_LpParser is required for @ref limbo::solvers::lpmcf::LpDualMcf to read input files in .lp format. 
~~~~~~~~~~~~~~~~
g++ -o test_lpmcf compare.cpp -I $LIMBO_DIR/include -I $BOOST_DIR/include -I $LEMON_DIR/include -L $LEMON_DIR/lib -lemon -L $LIMBO_DIR/lib -llpparser
# test 1: min-cost flow for network graph 
./test_lpmcf benchmarks/graph.lgf 
# test 2: dual min-cost flow for linear programming problem 
./test_lpmcf benchmarks/problem.lp
~~~~~~~~~~~~~~~~

Output of test 1
~~~~~~~~~~~~~~~~
# graph1.lgf 
@nodes
label	name	supply	
0	x3	0	
1	x1	0	
2	x2	0	
3	L2	-1	
4	L1	-2	
5	R2	1	
6	R1	2	
7	st	0	
@arcs
		label	capacity_lower	capacity_upper	cost	
0	3	0	0	1000000	2	
5	2	1	0	1000000	-1	
2	3	2	0	1000000	1	
2	4	3	0	1000000	1	
5	0	4	0	1000000	-2	
6	1	5	0	1000000	-2	
1	4	6	0	1000000	2	
6	2	7	0	1000000	-1	
2	1	8	0	1000000	-4	
4	7	9	0	1000000	2	
7	4	10	0	1000000	2	
~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~
# benchmarks/graph.lgf.sol 
total cost: -6
############# MCF Flow #############
10: st->L1: 0
9: L1->st: 0
8: x2->x1: 2
7: R1->x2: 2
6: x1->L1: 2
5: R1->x1: 0
4: R2->x3: 0
3: x2->L1: 0
2: x2->L2: 1
1: R2->x2: 1
0: x3->L2: 0
############# MCF Potential #############
st: -2
R1: 0
R2: 0
L1: -3
L2: 0
x2: -1
x1: -5
x3: -2
~~~~~~~~~~~~~~~~

Output of test 2
~~~~~~~~~~~~~~~~
# graph2.lgf 
@nodes
label	name	supply	
0	x3	0	
1	x1	0	
2	x2	0	
3	L2	-1	
4	L1	-2	
5	R2	1	
6	R1	2	
7	lpmcf_additional_node	0	
@arcs
		label	capacity_lower	capacity_upper	cost	
0	3	0	0	562949953421312	2	
5	2	1	0	562949953421312	-1	
2	3	2	0	562949953421312	1	
2	4	3	0	562949953421312	1	
5	0	4	0	562949953421312	-2	
6	1	5	0	562949953421312	-2	
1	4	6	0	562949953421312	2	
6	2	7	0	562949953421312	-1	
2	1	8	0	562949953421312	-4	
0	7	9	0	562949953421312	10	
1	7	10	0	562949953421312	10	
2	7	11	0	562949953421312	10	
3	7	12	0	562949953421312	10	
4	7	13	0	562949953421312	-2	
7	4	14	0	562949953421312	2	
5	7	15	0	562949953421312	10	
6	7	16	0	562949953421312	10	
~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~
# benchmarks/problem.lp.sol
total cost: -6
############# MCF Flow #############
16: R1->lpmcf_additional_node: 0
15: R2->lpmcf_additional_node: 0
14: lpmcf_additional_node->L1: 562949953421312
13: L1->lpmcf_additional_node: 562949953421312
12: L2->lpmcf_additional_node: 0
11: x2->lpmcf_additional_node: 0
10: x1->lpmcf_additional_node: 0
9: x3->lpmcf_additional_node: 0
8: x2->x1: 2
7: R1->x2: 2
6: x1->L1: 2
5: R1->x1: 0
4: R2->x3: 0
3: x2->L1: 0
2: x2->L2: 1
1: R2->x2: 1
0: x3->L2: 0
############# MCF Potential #############
lpmcf_additional_node: -7
R1: -2
R2: -2
L1: -5
L2: -2
x2: -3
x1: -7
x3: -4
############# LP Solution #############
x3: 3
x1: 0
x2: 4
L2: 5
L1: 2
R2: 5
R1: 5
~~~~~~~~~~~~~~~~

## Csdp Solver {#Solvers_Csdp}

See documented version: [limbo/algorithms/coloring/SDPColoringCsdp.h](@ref SDPColoringCsdp.h)
\include limbo/algorithms/coloring/SDPColoringCsdp.h
See documented version: [test/algorithms/test_SDPColoring.cpp](@ref test_SDPColoring.cpp)
\include test/algorithms/test_SDPColoring.cpp

Compiling and running commands (assuming LIMBO_DIR, BOOST_DIR and LEMON_DIR are well defined). 
@ref Parsers_LpParser is required for @ref limbo::solvers::lpmcf::LpDualMcf to read input files in .lp format. 
~~~~~~~~~~~~~~~~
g++ -o test_lpmcf compare.cpp -I $LIMBO_DIR/include -I $BOOST_DIR/include -I $LEMON_DIR/include -L $LEMON_DIR/lib -lemon -L $LIMBO_DIR/lib -llpparser
# test: min-cost flow for network graph 
./test_lpmcf benchmarks/graph.lgf 
~~~~~~~~~~~~~~~~

# References {#Solvers_References}

- [limbo/solvers/lpmcf/Lgf.h](@ref Lgf.h)
- [limbo/solvers/lpmcf/LpDualMcf.h](@ref LpDualMcf.h)
- [limbo/solvers/api/CsdpEasySdpApi.h](@ref CsdpEasySdpApi.h)
- [limbo/solvers/api/GurobiApi.h](@ref GurobiApi.h)
