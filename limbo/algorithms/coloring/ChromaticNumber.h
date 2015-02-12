/*************************************************************************
    > File Name: ChromaticNumber.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 11 Feb 2015 11:00:48 AM CST
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_COLORING_CHROMATICNUMBER
#define LIMBO_ALGORITHMS_COLORING_CHROMATICNUMBER

#include <vector>
#include <set>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/subgraph.hpp>
#include <limbo/algorithms/MaxIndependentSet.h>

using std::vector;
using std::set;

/// =====================================================
/// class: LawlerChromaticNumber
/// description: return chromatic number of a graph
/// implement the algorithm in 
/// A note on the complexity of the chromatic number problem.
/// E.L. Lawler
/// Inf. Process. Lett. 
///
/// Candidates for possible improvments
/// 1. Chromatic Number in Time O(2.4023^n) Using Maximal Independent Sets
/// Jesper Makholm Byskov
/// BRICS, 2002
/// 2. Small Maximal Independent Sets and Faster Exact Graphing Coloring
/// David Eppstein
/// Worksh. Algorithms and Data Structures, 2001
/// =====================================================

namespace limbo { namespace algorithms { namespace coloring {
	
template <typename GraphType>
class LawlerChromaticNumber
{
	public:
		typedef GraphType graph_type;
		typedef boost::subgraph<graph_type> subgraph_type;
		typedef typename boost::graph_traits<graph_type>::vertex_descriptor graph_vertex_type;

		struct mis_visitor_type
		{
			vector<set<graph_vertex_type> >& mMisNode; ///< bind mis nodes 

			mis_visitor_type(vector<set<graph_vertex_type> >& mMisNode_) : mMisNode(mMisNode_) {}
			mis_visitor_type(mis_visitor_type const& rhs) : mMisNode(rhs.mMisNode) {}

			/// requied callback for max_independent_set function
			/// \param MisType is a container type, default is std::deque
			template <typename MisType>
			void mis(MisType const& is)
			{
				// only record maximal independent sets 
				if (!mMisNode.empty())
				{
					if (mMisNode.front().size() < is.size())
						mMisNode.clear();
					else if (mMisNode.front().size() > is.size())
						return;
				}

				mMisNode.push_back(set<graph_vertex_type>());
				for (typename MisType::const_iterator it = is.begin(); 
						it != is.end(); ++it)
					mMisNode.back().insert(*it);
			}
		};
		int operator()(subgraph_type& g) const 
		{
			return chromatic_number(g);
		}

	protected:
		int chromatic_number(subgraph_type& g) const
		{
			int cn = boost::num_vertices(g); // initial chromatic number 

			// stop recursion
			if (cn <= 1) return cn;
			else if (cn == 2) 
			{
				BGL_FORALL_EDGES_T(e, g, subgraph_type)
				{
					// the only two vertices are connected
					if (boost::source(e, g) != boost::target(e, g))
						return 2;
				}
				// they are not connected
				return 1;
			}

			vector<set<graph_vertex_type> > mMisNode;
			limbo::algorithms::max_independent_set(g, mis_visitor_type(mMisNode), limbo::algorithms::MaxIndependentSetByMaxClique());

			for (typename vector<set<graph_vertex_type> >::const_iterator it1 = mMisNode.begin(); 
					it1 != mMisNode.end(); ++it1)
			{
				set<graph_vertex_type> const& sMisNode = *it1;
				subgraph_type& g_s = g.create_subgraph(); // subgraph, G \ I
				for (typename set<graph_vertex_type>::const_iterator it2 = sMisNode.begin();
						it2 != sMisNode.end(); ++it2)
				{
					if (!sMisNode.count(*it2))
						boost::add_vertex(*it2, g_s);
				}

				// get chromatic number of complementary MIS graph
				int comp_cn = chromatic_number(g_s);

				if (cn > comp_cn) cn = comp_cn;
			}

			return cn+1;
		}
};

}}} // namespace limbo  // namespace algorithms // namespace coloring

#endif
