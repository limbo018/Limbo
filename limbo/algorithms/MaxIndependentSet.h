/*************************************************************************
    > File Name: MaxIndependentSet.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 11 Feb 2015 02:07:55 PM CST
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_MAXINDEPENDENTSET_H
#define LIMBO_ALGORITHMS_MAXINDEPENDENTSET_H

#include <deque>
#include <boost/graph/bron_kerbosch_all_cliques.hpp>
#include <limbo/algorithms/GraphUtility.h>

namespace limbo { namespace algorithms {

/// a tag for solving maximum independent sets with maximum cliques 
struct MaxIndependentSetByMaxClique 
{
	/// callback for boost::bron_kerbosch_all_cliques
	template <typename GraphType, typename MisVisitorType>
	struct clique_visitor_type
	{
		typedef GraphType graph_type;
		typedef MisVisitorType mis_visitor_type;
		typedef typename boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor_type; 
		typedef std::map<vertex_descriptor_type, vertex_descriptor_type> map_type;

		MisVisitorType& mis_visitor; ///< bind mis visitor
		map_type& mCompG2G; ///< bind vertex mapping from complement graph to original graph

		clique_visitor_type(mis_visitor_type& mv, map_type& mCG2G) : mis_visitor(mv), mCompG2G(mCG2G) {}
		clique_visitor_type(clique_visitor_type const& rhs) : mis_visitor(rhs.mis_visitor), mCompG2G(rhs.mCompG2G) {}

		/// \param c, clique vertices in complement graph 
		/// \param cg, complement graph
		template <typename CliqueType>
		void clique(CliqueType const& c, graph_type const& cg)
		{
			// convert to vertices in original graph
			typedef CliqueType clique_type;
			clique_type is;

			// for debug 
			if (boost::num_vertices(cg) > 0)
				assert(!c.empty());

			for (typename clique_type::const_iterator it = c.begin(); 
					it != c.end(); ++it)
				is.push_back(mCompG2G[*it]);

			mis_visitor.mis(is);
		}
	};
};

/// generic function to calculate maximum independent sets with different algorithms 
/// \param vis, once an independent set is found, callback vis.mis(MisType const&) will be called 
/// in this way, user can choose to store all the independent sets or process one by one 
template <typename GraphType, typename VisitorType, typename AlgorithmType>
inline void max_independent_set(GraphType const& g, VisitorType vis, AlgorithmType const&);

/// a maximum independent set of a graph g is also a maximum clique of its complement graph 
/// this function searches maximum cliques of the complement graph to get maximum independent sets
template <typename GraphType, typename MisVisitorType>
inline void max_independent_set(GraphType const& g, MisVisitorType vis, MaxIndependentSetByMaxClique const&)
{
	typedef typename boost::graph_traits<GraphType>::vertex_descriptor vertex_descriptor_type; 
	GraphType cg; // complement graph
	std::map<vertex_descriptor_type, vertex_descriptor_type> mCompG2G; // mapping from vertices in complement graph to original graph 

	// calculate complement graph 
	limbo::algorithms::complement_graph(g, cg, mCompG2G);

	// search for all cliques with at least 1 vertex 
	boost::bron_kerbosch_all_cliques(cg, MaxIndependentSetByMaxClique::clique_visitor_type<GraphType, MisVisitorType>(vis, mCompG2G), 1);
}

}} // namespace limbo // namespace algorithms

#endif
