/*************************************************************************
    > File Name: test_ChromaticNumber.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 11 Feb 2015 04:44:03 PM CST
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <limbo/algorithms/coloring/ChromaticNumber.h>
#include <boost/graph/erdos_renyi_generator.hpp>

using std::cout;
using std::endl;
using std::ofstream;
using namespace boost;

enum vertex_id_t { vertex_id = 500 };
enum edge_id_t { edge_id = 501 };
namespace boost 
{
	BOOST_INSTALL_PROPERTY(vertex, id);
	BOOST_INSTALL_PROPERTY(edge, id);
}

int main()
{
	typedef adjacency_list<setS, setS, undirectedS, property<vertex_id_t, std::size_t>, property<edge_id_t, std::size_t> > graph_type;
	typedef property<vertex_id_t, std::size_t> VertexId;
	typedef property<edge_id_t, std::size_t> EdgeID;

	graph_type g;
	property_map<graph_type, vertex_id_t>::type vertex_id_map = get(vertex_id, g);
	property_map<graph_type, edge_id_t>::type edge_id_map = get(edge_id, g);

	for (size_t i = 0; i < 5; ++i)
		add_vertex(i, g);

	size_t cnt = 0;
	BGL_FORALL_VERTICES_T(u, g, graph_type)
	{
		BGL_FORALL_VERTICES_T(v, g, graph_type)
		{
			if (u != v && cnt%3 == 0)
			{
				add_edge(u, v, g);
			}
			cnt += 1;
		}
	}

	//limbo::algorithms::LawlerChromaticNumber lcn;
	//cout << "chromatic number = " << lcn(g) << endl;
	
	print_edges2(g, vertex_id_map, edge_id_map);
	print_graph(g, vertex_id_map);

	graph_type gp;
	limbo::algorithms::complement_graph(g, gp);

	return 0;
}
