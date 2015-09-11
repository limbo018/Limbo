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

#include <fstream>
#include <string>
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

/// default VertexLabelWriter for write_graph
template <typename GraphType>
struct VertexLabelWriter
{
    typedef GraphType graph_type;
    typedef typename boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor;

    graph_type const& g; ///< bind graph object 

    VertexLabelWriter(graph_type const& _g) : g(_g) {}
    vertex_descriptor label(vertex_descriptor v) const {return v;}
};

/// default EdgeLabelWriter for write_graph 
template <typename GraphType>
struct EdgeLabelWriter 
{
    typedef GraphType graph_type;
    typedef typename boost::graph_traits<graph_type>::edge_descriptor edge_descriptor;
    typedef typename boost::property_traits<typename boost::property_map<graph_type, boost::edge_weight_t>::const_type>::value_type edge_weight_type;

    graph_type const& g; ///< bind graph object 

    EdgeLabelWriter(graph_type const& _g) : g(_g) {}
    edge_weight_type label(edge_descriptor e) const {return boost::get(boost::edge_weight, g, e);}
    std::string color(edge_descriptor ) const {return "black";}
    std::string style(edge_descriptor ) const {return "solid";}
};

/// write graph to graphviz format and convert to pdf 
/// although Boost.Graph has write_graphviz component, it is not easy to use 
/// \param vl, VertexLabelType must provide label() member function 
/// \param el, EdgeLabelType must provide label(), color(), and style() member function
template <typename GraphType, typename VertexLabelType, typename EdgeLabelType>
void write_graph(std::ofstream& out, GraphType const& g, VertexLabelType const& vl, EdgeLabelType const& el) 
{
	out << "graph D { \n"
		<< "  randir = LR\n"
		<< "  size=\"4, 3\"\n"
		<< "  ratio=\"fill\"\n"
		<< "  edge[style=\"bold\",fontsize=200]\n" 
		<< "  node[shape=\"circle\",fontsize=200]\n";

	//output nodes 
	uint32_t vertex_num = boost::num_vertices(g);
	for(uint32_t k = 0; k < vertex_num; ++k) 
	{
		// output vertex label
		out << "  " << k << "[shape=\"circle\""<< ",label=\"" << vl.label(k) << "\"]\n";
	}//end for

	//output edges
    typename boost::graph_traits<GraphType>::edge_iterator ei, eie;
	for (boost::tie(ei, eie) = boost::edges(g); ei != eie; ++ei)
    {
        out << "  " << boost::source(*ei, g) << "--" << boost::target(*ei, g) 
            << "[label=" << el.label(*ei) << ",color=\"" << el.color(*ei) << "\",style=\"" << el.style(*ei) << "\",penwidth=3]\n";
    }
	out << "}";
}

/// convert graphviz format to pdf 
/// the input filename should be filename+suffix
inline void graphviz2pdf(std::string const& filename, const char* suffix = ".gv")
{
	char cmd[100];
	sprintf(cmd, "dot -Tpdf %s%s -o %s.pdf", filename.c_str(), suffix, filename.c_str());
	system(cmd);
}

}} // namespace limbo // namespace algorithms

#endif
