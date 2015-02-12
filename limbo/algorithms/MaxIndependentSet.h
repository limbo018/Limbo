/*************************************************************************
    > File Name: MaxIndependentSet.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 11 Feb 2015 02:07:55 PM CST
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_MAXINDEPENDENTSET_H
#define LIMBO_ALGORITHMS_MAXINDEPENDENTSET_H

#include <boost/graph/bron_kerbosch_all_cliques.hpp>
#include <limbo/algorithms/GraphUtility.h>

namespace limbo { namespace algorithms {

struct MaxIndependentSetByMaxClique 
{
	template <typename MisVisitorType>
	struct clique_visitor_type
	{
		MisVisitorType& mis_visitor; ///< bind mis visitor

		clique_visitor_type(MisVisitorType& mv) : mis_visitor(mv) {}
		clique_visitor_type(clique_visitor_type const& rhs) : mis_visitor(rhs.mis_visitor) {}

		template <typename CliqueType, typename GraphType>
		void clique(CliqueType const& c, GraphType& g)
		{
			mis_visitor.mis(c, g);
		}
	};
};

template <typename GraphType, typename VisitorType, typename AlgorithmType>
inline void max_independent_set(GraphType const& g, VisitorType vis, AlgorithmType const&);

template <typename GraphType, typename MisVisitorType>
inline void max_independent_set(GraphType const& g, MisVisitorType vis, MaxIndependentSetByMaxClique const&)
{
	GraphType cg; // complement graph
	limbo::algorithms::complement_graph(g, cg);

	boost::bron_kerbosch_all_cliques(cg, MaxIndependentSetByMaxClique::clique_visitor_type<MisVisitorType>(vis));
}

}} // namespace limbo // namespace algorithms

#endif
