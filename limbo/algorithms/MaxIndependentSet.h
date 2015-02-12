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

struct MaxIndependentSetByMaxClique 
{
	template <typename GraphType, typename MisVisitorType>
	struct clique_visitor_type
	{
		typedef GraphType graph_type;
		typedef MisVisitorType mis_visitor_type;
		typedef typename boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor_type; 
		typedef std::map<vertex_descriptor_type, vertex_descriptor_type> map_type;

		MisVisitorType& mis_visitor; ///< bind mis visitor
		map_type& mCompG2G; ///< bind vertex mapping from complement graph to original graph

		clique_visitor_type(mis_visitor_type& mv, map_type& mCG2G) : mCompG2G(mCG2G), mis_visitor(mv) {}
		clique_visitor_type(clique_visitor_type const& rhs) : mCompG2G(rhs.mCompG2G), mis_visitor(rhs.mis_visitor) {}

		template <typename CliqueType>
		void clique(CliqueType const& c, graph_type const& cg)
		//void clique(std::deque<vertex_descriptor_type> const& c, graph_type const& cg)
		{
			// convert to vertices in original graph
			//typedef std::deque<vertex_descriptor_type> clique_type;
			typedef CliqueType clique_type;
			clique_type is;
			for (typename clique_type::const_iterator it = c.begin(); 
					it != c.end(); ++it)
				is.push_back(mCompG2G[*it]);

			mis_visitor.mis(is);
		}
	};
};

template <typename GraphType, typename VisitorType, typename AlgorithmType>
inline void max_independent_set(GraphType const& g, VisitorType vis, AlgorithmType const&);

template <typename GraphType, typename MisVisitorType>
inline void max_independent_set(GraphType const& g, MisVisitorType vis, MaxIndependentSetByMaxClique const&)
{
	typedef typename boost::graph_traits<GraphType>::vertex_descriptor vertex_descriptor_type; 
	GraphType cg; // complement graph
	std::map<vertex_descriptor_type, vertex_descriptor_type> mCompG2G; 

	limbo::algorithms::complement_graph(g, cg, mCompG2G);

	boost::bron_kerbosch_all_cliques(cg, MaxIndependentSetByMaxClique::clique_visitor_type<GraphType, MisVisitorType>(vis, mCompG2G));
}

}} // namespace limbo // namespace algorithms

#endif
