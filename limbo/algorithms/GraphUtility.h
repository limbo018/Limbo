/*************************************************************************
    > File Name: GraphUtility.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 11 Feb 2015 02:25:12 PM CST
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_GRAPHUTILITY_H
#define LIMBO_ALGORITHMS_GRAPHUTILITY_H

/// =====================================================
/// class: GraphUtility
/// description: add-ons for Boost Graph Library
/// =====================================================

#include <algorithm>
#include <map>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/iteration_macros.hpp>

namespace limbo { namespace algorithms {

/// \param mCompG2G, a vertex mapping from complement graph to original graph 
/// get the complement graph of original graph 
template <typename GraphType>
void complement_graph(GraphType const& g, GraphType& gp, 
		std::map<typename boost::graph_traits<GraphType>::vertex_descriptor, 
		typename boost::graph_traits<GraphType>::vertex_descriptor>& mCompG2G) 
{ 
	typedef typename boost::graph_traits<GraphType>::vertex_descriptor vertex_descriptor; 
	std::map<vertex_descriptor, vertex_descriptor> vmap; 

	BGL_FORALL_VERTICES_T(v, g, GraphType) 
	{
		vertex_descriptor u = boost::add_vertex(gp); 
		vmap[v] = u;
		mCompG2G[u] = v;
	}

	BGL_FORALL_VERTICES_T(u, g, GraphType) 
	{ 
		std::vector<vertex_descriptor> neighbors(
				adjacent_vertices(u, g).first, 
				adjacent_vertices(u, g).second
				); 
		std::sort(neighbors.begin(), neighbors.end()); 
		BGL_FORALL_VERTICES_T(v, g, GraphType) 
		{ 
			// Might want to check for self-loops 
			if (v != u && !std::binary_search(neighbors.begin(), neighbors.end(), v)) 
				boost::add_edge(vmap[u], vmap[v], gp); 
		} 
	} 
} 

}} // namespace limbo // namespace algorithms

#endif
