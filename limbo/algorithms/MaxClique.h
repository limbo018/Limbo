/*************************************************************************
    > File Name: MaxClique.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Sat 09 May 2015 04:06:45 PM CDT
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_MAXCLIQUE_H
#define LIMBO_ALGORITHMS_MAXCLIQUE_H

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

#include <deque>
#include <boost/graph/bron_kerbosch_all_cliques.hpp>

namespace limbo { namespace algorithms {

/// callback for boost::bron_kerbosch_all_cliques
template <typename GraphType>
struct max_clique_visitor_type
{
	typedef GraphType graph_type;
	typedef typename boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor_type; 
	typedef vector<vertex_descriptor_type> clique_type;
	typedef vector<clique_type> clique_container_type;

	clique_container_type& vClique;

	max_clique_visitor_type(clique_container_type& vc) : vClique(vc) {}
	max_clique_visitor_type(clique_container_type const& rhs) : vClique(rhs.vClique) {}

	/// \param c, clique vertices in graph 
	template <typename CliqueType>
	void clique(CliqueType const& c, graph_type const& cg)
	{
		// convert to vertices in original graph

		// for debug 
		if (boost::num_vertices(cg) > 0)
			assert(!c.empty());

		vClique.push_back(clique_type(c.begin(), c.end()));
	}
};

/// \return a set of cliques with at least \param clique_num vertices 
template <typename GraphType>
inline vector<vector<typename boost::graph_traits<GraphType>::vertex_descriptor> >
max_clique(GraphType const& g, size_t clique_num)
{
	vector<vector<typename boost::graph_traits<GraphType>::vertex_descriptor> > vClique;
	// search for all cliques with at least clique_num vertices
	boost::bron_kerbosch_all_cliques(g, max_clique_visitor_type<GraphType>(vClique), clique_num);

	return vClique;
}

}} // namespace limbo // namespace algorithms

#endif
