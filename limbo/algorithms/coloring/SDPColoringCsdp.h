/*************************************************************************
    > File Name: SDPColoringCsdp.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Tue 01 Sep 2015 12:01:32 PM CDT
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_COLORING_SDPCOLORINGCSDP
#define LIMBO_ALGORITHMS_COLORING_SDPCOLORINGCSDP

#include <limbo/string/String.h>
#include <limbo/algorithms/coloring/Coloring.h>

namespace limbo { namespace algorithms { namespace coloring {

template <typename GraphType>
class SDPColoringCsdp : public Coloring<GraphType>
{
	public:
		typedef Coloring<GraphType> base_type;
		using typename base_type::graph_type;
		using typename base_type::graph_vertex_type;
		using typename base_type::graph_edge_type;
		using typename base_type::vertex_iterator_type;
		using typename base_type::edge_iterator_type;
		using typename base_type::ColorNumType;
        typedef typename base_type::EdgeHashType edge_hash_type;
		/// edge weight is used to differentiate conflict edge and stitch edge 
		/// non-negative weight implies conflict edge 
		/// negative weight implies stitch edge 
		typedef typename boost::property_map<graph_type, boost::edge_weight_t>::type edge_weight_map_type;
		typedef typename boost::property_map<graph_type, boost::edge_weight_t>::const_type const_edge_weight_map_type;

		/// constructor
		SDPColoringCsdp(graph_type const& g) 
			: base_type(g)
		{}
		/// destructor
		virtual ~SDPColoringCsdp() {}

	protected:
		/// \return objective value 
		virtual double coloring();
};

template <typename GraphType>
double SDPColoringCsdp<GraphType>::coloring()
{
}

}}} // namespace limbo // namespace algorithms // namespace coloring

#endif
