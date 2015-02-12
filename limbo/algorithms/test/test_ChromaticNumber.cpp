/*************************************************************************
    > File Name: test_ChromaticNumber.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 11 Feb 2015 04:44:03 PM CST
 ************************************************************************/

#include <iostream>
#include <fstream>
//#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <limbo/algorithms/coloring/ChromaticNumber.h>
#include <boost/graph/erdos_renyi_generator.hpp>

#include <boost/version.hpp>
#if BOOST_VERSION <= 14601
#include <boost/graph/detail/is_same.hpp>
#else
#include <boost/type_traits/is_same.hpp>
#endif

using std::cout;
using std::endl;
using std::ofstream;
using namespace boost;

struct MisVisitor
{
	template <typename MisType>
	void mis(MisType const&)
	{}
};

int main()
{
	typedef adjacency_list<vecS, vecS, undirectedS, 
			property<vertex_index_t, std::size_t>, 
			property<edge_index_t, std::size_t, property<edge_weight_t, int> > > graph_type;
	typedef subgraph<graph_type> subgraph_type;
	typedef property<vertex_index_t, std::size_t> VertexId;
	typedef property<edge_index_t, std::size_t> EdgeID;
	typedef typename boost::graph_traits<subgraph_type>::vertex_descriptor vertex_descriptor; 

	subgraph_type g (5);
	property_map<subgraph_type, vertex_index_t>::type vertex_index_map = get(vertex_index, g);
	property_map<subgraph_type, edge_index_t>::type edge_index_map = get(edge_index, g);

	size_t cnt = 0;
	BGL_FORALL_VERTICES_T(u, g, subgraph_type)
	{
		BGL_FORALL_VERTICES_T(v, g, subgraph_type)
		{
			if (u != v && cnt%3 == 0)
			{
				add_edge(u, v, g);
			}
			cnt += 1;
		}
	}

	//print_edges2(g, vertex_index_map, edge_index_map);
	cout << "original graph" << endl;
	print_graph(g, vertex_index_map);

	// test complement_graph
	{
		subgraph_type gp;
		std::map<vertex_descriptor, vertex_descriptor> mCompG2G;
		limbo::algorithms::complement_graph(g, gp, mCompG2G);

		cout << "complement graph" << endl;
		BGL_FORALL_VERTICES_T(v, gp, subgraph_type)
		{
			cout << vertex_index_map[mCompG2G[v]] << " <--> ";
			boost::graph_traits<subgraph_type>::out_edge_iterator e, e_end;
			for (boost::tie(e, e_end) = out_edges(v, gp); e != e_end; ++e)
				cout << vertex_index_map[mCompG2G[target(*e, gp)]] << " ";
			cout << endl;
		}
	}

	// test max_independent_set
	{
		limbo::algorithms::max_independent_set(g, MisVisitor(), limbo::algorithms::MaxIndependentSetByMaxClique());
	}

	limbo::algorithms::coloring::LawlerChromaticNumber<graph_type> lcn;
	cout << "chromatic number = " << lcn(g) << endl;
	
	return 0;
}
