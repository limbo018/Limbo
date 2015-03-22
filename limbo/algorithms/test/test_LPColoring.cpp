/*************************************************************************
    > File Name: test_ChromaticNumber.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 11 Feb 2015 04:44:03 PM CST
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <limbo/algorithms/coloring/ChromaticNumber.h>
#include <limbo/algorithms/coloring/GreedyColoring.h>
#include <limbo/algorithms/coloring/LPColoring.h>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/iteration_macros.hpp>

#include <boost/version.hpp>
#if BOOST_VERSION <= 14601
#include <boost/graph/detail/is_same.hpp>
#else
#include <boost/type_traits/is_same.hpp>
#endif

using std::cout;
using std::endl;
using std::ofstream;
using std::string;
using namespace boost;

int main()
{
	// do not use setS, it does not compile for subgraph
	// do not use custom property tags, it does not compile for most utilities
	typedef adjacency_list<vecS, vecS, undirectedS, 
			property<vertex_index_t, std::size_t>, 
			property<edge_index_t, std::size_t, property<edge_weight_t, int> >,
			property<graph_name_t, string> > graph_type;
	typedef subgraph<graph_type> subgraph_type;
	typedef property<vertex_index_t, std::size_t> VertexId;
	typedef property<edge_index_t, std::size_t> EdgeID;
	typedef typename boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor; 

	mt19937 gen;
	graph_type g;
	int N = 40;
	std::vector<vertex_descriptor> vertex_set;
	std::vector< std::pair<vertex_descriptor, vertex_descriptor> > edge_set;
	generate_random_graph(g, N, N * 2, gen,
			std::back_inserter(vertex_set),
			std::back_inserter(edge_set));

	//test relaxed LP based coloring
	limbo::algorithms::coloring::LPColoring<graph_type> lp_coloring (g); 
	lp_coloring.conflictCost(false);
	lp_coloring();
	return 0;
}
