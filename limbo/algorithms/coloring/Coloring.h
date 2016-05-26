/*************************************************************************
    > File Name: Coloring.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Mon Jun  1 21:46:55 2015
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_COLORING_COLORING
#define LIMBO_ALGORITHMS_COLORING_COLORING

#include <fstream>
#include <vector>
#include <boost/cstdint.hpp>
#include <boost/functional/hash.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>
#include <limbo/preprocessor/AssertMsg.h>
#include <limbo/algorithms/GraphUtility.h>

namespace limbo { namespace algorithms { namespace coloring {

using boost::uint32_t;
using boost::int32_t;
using boost::int8_t;

namespace la = limbo::algorithms;

template <typename GraphType>
struct ColoringVertexLabelWriter : public la::VertexLabelWriter<GraphType>
{
    typedef GraphType graph_type;
    typedef la::VertexLabelWriter<graph_type> base_type;
    typedef typename base_type::vertex_descriptor vertex_descriptor;
    
    std::vector<int8_t> const& vColor;

    ColoringVertexLabelWriter(graph_type const& g, std::vector<int8_t> const& vc) : base_type(g), vColor(vc) {}

    std::string label(vertex_descriptor v) const 
    {
        std::ostringstream oss; 
        oss << v << ":" << (int32_t)vColor[v];
        return oss.str();
    }
};

template <typename GraphType>
struct ColoringEdgeLabelWriter : public la::EdgeLabelWriter<GraphType>
{
    typedef GraphType graph_type;
    typedef la::EdgeLabelWriter<graph_type> base_type;
    typedef typename base_type::edge_descriptor edge_descriptor;
    typedef typename base_type::edge_weight_type edge_weight_type;
    typedef typename boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor;

    std::vector<int8_t> const& vColor;

    ColoringEdgeLabelWriter(graph_type const& g, std::vector<int8_t> const& vc) : base_type(g), vColor(vc) {}

    edge_weight_type label(edge_descriptor e) const {return boost::get(boost::edge_weight, this->g, e);}
    std::string color(edge_descriptor e) const 
    {
		vertex_descriptor s = boost::source(e, this->g);
		vertex_descriptor t = boost::target(e, this->g);
		edge_weight_type w = boost::get(boost::edge_weight, this->g, e);
        bool conflict_flag = (vColor[s] >= 0 && vColor[s] == vColor[t]);
        if (w >= 0 && conflict_flag) // conflict 
            return "red";
        else return "black";
    }
    std::string style(edge_descriptor e) const {return (boost::get(boost::edge_weight, this->g, e) >= 0)? "solid" : "dashed";}
};

/// base class for all coloring algorithms 
template <typename GraphType>
class Coloring 
{
	public:
		typedef GraphType graph_type;
		typedef typename boost::graph_traits<graph_type>::vertex_descriptor graph_vertex_type;
		typedef typename boost::graph_traits<graph_type>::edge_descriptor graph_edge_type;
		typedef typename boost::graph_traits<graph_type>::vertex_iterator vertex_iterator_type;
		typedef typename boost::graph_traits<graph_type>::edge_iterator edge_iterator_type;
        /// value type for edge weight, integer or double...
        typedef typename boost::property_traits<typename boost::property_map<graph_type, boost::edge_weight_t>::const_type>::value_type edge_weight_type;
		/// edge weight is used to differentiate conflict edge and stitch edge 
		/// non-negative weight implies conflict edge 
		/// negative weight implies stitch edge 
        typedef typename boost::property_traits<typename boost::property_map<graph_type, boost::edge_index_t>::const_type>::value_type edge_index_type;

		enum ColorNumType
		{
			THREE = 3, 
			FOUR = 4
		};
		// hasher class for graph_edge_type
		struct EdgeHashType : std::unary_function<graph_edge_type, std::size_t>
		{
			std::size_t operator()(graph_edge_type const& e) const 
			{
				std::size_t seed = 0;
				boost::hash_combine(seed, e.m_source);
				boost::hash_combine(seed, e.m_target);
				return seed;
			}
		};


		/// constructor
		Coloring(graph_type const& g);
		/// destructor
		virtual ~Coloring() {};

		/// member functions
		/// top api 
		/// \return objective value 
		virtual double operator()(); 

		/// color number 
		virtual void color_num(ColorNumType cn) {m_color_num = cn;} 
		virtual void color_num(int8_t cn) {m_color_num = (cn == 3)? THREE : FOUR;}
        virtual ColorNumType color_num() const {return m_color_num;}

		/// precolored vertex 
		virtual void precolor(graph_vertex_type v, int8_t c) {m_vColor[v] = c; m_has_precolored = true;}

        /// \return true if contain precolored vertices 
        virtual bool has_precolored() const {return m_has_precolored;}

		/// stitch weight 
		virtual double stitch_weight() const {return m_stitch_weight;}
		virtual void stitch_weight(double w) {m_stitch_weight = w;}

		/// threads 
		virtual void threads(int32_t t) {m_threads = t;}

		/// \return coloring solution 
		virtual int8_t color(graph_vertex_type v) const {return m_vColor[v];}

        /// helper functions 
        inline virtual edge_weight_type edge_weight(graph_edge_type const& e) const {return boost::get(boost::edge_weight, m_graph, e);}

		/// \return cost with a coloring solution 
		virtual edge_weight_type calc_cost(std::vector<int8_t> const& vColor) const;

        /// check edge weight within lb and ub 
        void check_edge_weight(graph_type const& g, edge_weight_type lb, edge_weight_type ub) const;

        /// print edge weight 
        void print_edge_weight(graph_type const& g) const;

		/// for debug 
		virtual void write_graph(std::string const& filename) const;
        virtual void write_graph(std::string const& filename, graph_type const& g, std::vector<int8_t> const& vColor) const;
	protected:
		/// \return objective value 
		virtual double coloring() = 0;

		graph_type const& m_graph;
		std::vector<int8_t> m_vColor;

		ColorNumType m_color_num;
		double m_stitch_weight;
		int32_t m_threads; ///< control number of threads for ILP solver 
        bool m_has_precolored; ///< whether contain precolored vertices 
};

template <typename GraphType>
Coloring<GraphType>::Coloring(Coloring<GraphType>::graph_type const& g) 
    : m_graph(g)
    , m_vColor(boost::num_vertices(g), -1)
    , m_color_num(THREE)
    , m_stitch_weight(0.1)
    , m_threads(std::numeric_limits<int32_t>::max())
    , m_has_precolored(false)
{}

template <typename GraphType>
double Coloring<GraphType>::operator()()
{
    if (boost::num_vertices(m_graph) <= color_num()) // if vertex number is no larger than color number, directly assign color
    {
        // need to consider precolored vertices
        bool unusedColors[4] = {true, true, true, true};
        if (color_num() == THREE)
            unusedColors[3] = false;
        for (int32_t i = 0, ie = m_vColor.size(); i != ie; ++i)
        {
            if (m_vColor[i] < 0) // if not precolored, assign to an unused color
            {
                for (int8_t c = 0; c != 4; ++c)
                    if (unusedColors[c])
                    {
                        m_vColor[i] = c;
                        break;
                    }
            }
            // must have valid color after assignment 
            assert(m_vColor[i] >= 0);
            unusedColors[m_vColor[i]] = false;
        }
        return calc_cost(m_vColor);
    }
    else // perform coloring algorithm 
        return this->coloring();
}

template <typename GraphType>
typename Coloring<GraphType>::edge_weight_type Coloring<GraphType>::calc_cost(std::vector<int8_t> const& vColor) const 
{
	assert(vColor.size() == boost::num_vertices(this->m_graph));
	double cost = 0;
	edge_iterator_type ei, eie;
	for (boost::tie(ei, eie) = boost::edges(m_graph); ei != eie; ++ei)
	{
		edge_weight_type w = boost::get(boost::edge_weight, m_graph, *ei);
		graph_vertex_type s = boost::source(*ei, m_graph);
		graph_vertex_type t = boost::target(*ei, m_graph);
        if (s == t) // skip self edges 
            continue; 
		if (w >= 0) // conflict edge 
			cost += (vColor[s] == vColor[t])*w;
		else // stitch edge 
			cost += (vColor[s] != vColor[t])*w;
	}
	return cost;
}

template <typename GraphType>
void Coloring<GraphType>::check_edge_weight(typename Coloring<GraphType>::graph_type const& g, typename Coloring<GraphType>::edge_weight_type lb, typename Coloring<GraphType>::edge_weight_type ub) const 
{
	edge_iterator_type ei, eie;
	for (boost::tie(ei, eie) = boost::edges(g); ei != eie; ++ei)
	{
		edge_weight_type w = boost::get(boost::edge_weight, m_graph, *ei);
        assert_msg(w >= lb && w <= ub, "edge weight out of range: " << w);
    }
}

template <typename GraphType>
void Coloring<GraphType>::print_edge_weight(typename Coloring<GraphType>::graph_type const& g) const 
{
	edge_iterator_type ei, eie;
	for (boost::tie(ei, eie) = boost::edges(g); ei != eie; ++ei)
	{
		edge_weight_type w = boost::get(boost::edge_weight, m_graph, *ei);
        std::cout << w << " ";
    }
    std::cout << "\n";
}

template <typename GraphType>
void Coloring<GraphType>::write_graph(std::string const& filename) const 
{
    write_graph(filename, m_graph, m_vColor);
}

template <typename GraphType>
void Coloring<GraphType>::write_graph(std::string const& filename, Coloring<GraphType>::graph_type const& g, std::vector<int8_t> const& vColor) const
{
    std::ofstream out ((filename+".gv").c_str());
    la::write_graph(out, g, ColoringVertexLabelWriter<graph_type>(g, vColor), ColoringEdgeLabelWriter<graph_type>(g, vColor));
    out.close();
    la::graphviz2pdf(filename);
}

}}} // namespace limbo // namespace algorithms // namespace coloring

#endif
