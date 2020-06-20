/**
 * @file   Coloring.h
 * @brief  base class for all graph coloring algorithms 
 * @author Yibo Lin
 * @date   Jun 2015
 */

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

/// namespace for Limbo 
namespace limbo 
{ 
/// namespace for Limbo.Algorithms 
namespace algorithms 
{ 
/// namespace for Limbo.Algorithms.Coloring 
namespace coloring 
{

using boost::uint32_t;
using boost::int32_t;
using boost::int8_t;

namespace la = limbo::algorithms;

/// function object to write vertex label 
/// @tparam GraphType graph type 
template <typename GraphType>
struct ColoringVertexLabelWriter : public la::VertexLabelWriter<GraphType>
{
    /// @nowarn 
    typedef GraphType graph_type;
    typedef la::VertexLabelWriter<graph_type> base_type;
    typedef typename base_type::vertex_descriptor vertex_descriptor;
    /// @endnowarn
    
    std::vector<int8_t> const& vColor; ///< coloring solutions 

    /// constructor 
    /// @param g graph 
    /// @param vc coloring solutions 
    ColoringVertexLabelWriter(graph_type const& g, std::vector<int8_t> const& vc) : base_type(g), vColor(vc) {}

    /// get label of vertex 
    /// @param v vertex 
    /// @return label of vertex 
    std::string label(vertex_descriptor v) const 
    {
        std::ostringstream oss; 
        oss << v << ":" << (int32_t)vColor[v];
        return oss.str();
    }
};

/// function object to write edge label 
/// @tparam GraphType graph type 
template <typename GraphType>
struct ColoringEdgeLabelWriter : public la::EdgeLabelWriter<GraphType>
{
    /// @nowarn
    typedef GraphType graph_type;
    typedef la::EdgeLabelWriter<graph_type> base_type;
    typedef typename base_type::edge_descriptor edge_descriptor;
    typedef typename base_type::edge_weight_type edge_weight_type;
    typedef typename boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor;
    /// @endnowarn

    std::vector<int8_t> const& vColor; ///< coloring solutions 

    /// constructor 
    /// @param g graph 
    /// @param vc coloring solutions 
    ColoringEdgeLabelWriter(graph_type const& g, std::vector<int8_t> const& vc) : base_type(g), vColor(vc) {}

    /// get label of edge 
    /// @param e edge 
    /// @return label of edge 
    edge_weight_type label(edge_descriptor e) const {return boost::get(boost::edge_weight, this->g, e);}
    /// get color of edge 
    /// @param e edge 
    /// @return color of edge 
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
    /// get style of edge 
    /// @param e edge 
    /// @return style of edge 
    std::string style(edge_descriptor e) const {return (boost::get(boost::edge_weight, this->g, e) >= 0)? "solid" : "dashed";}
};

/// @class limbo::algorithms::coloring::Coloring
/// Base class for all coloring algorithms.  
/// All coloring algorithms support 3 and 4 colors. 
/// @tparam GraphType graph type 
template <typename GraphType>
class Coloring 
{
	public:
        /// @nowarn 
		typedef GraphType graph_type;
		typedef typename boost::graph_traits<graph_type>::vertex_descriptor graph_vertex_type;
		typedef typename boost::graph_traits<graph_type>::edge_descriptor graph_edge_type;
		typedef typename boost::graph_traits<graph_type>::vertex_iterator vertex_iterator_type;
		typedef typename boost::graph_traits<graph_type>::edge_iterator edge_iterator_type;
        typedef typename boost::graph_traits<graph_type>::adjacency_iterator adjacency_iterator;
        // value type for edge weight, integer or double...
        typedef typename boost::property_traits<typename boost::property_map<graph_type, boost::edge_weight_t>::const_type>::value_type edge_weight_type;
		// edge weight is used to differentiate conflict edge and stitch edge 
		// non-negative weight implies conflict edge 
		// negative weight implies stitch edge 
        typedef typename boost::property_traits<typename boost::property_map<graph_type, boost::edge_index_t>::const_type>::value_type edge_index_type;
        
        /// @endnowarn

        /// number of colors 
		enum ColorNumType
		{
            TWO = 2,
			THREE = 3, 
			FOUR = 4
		};
		/// hasher class for graph_edge_type
		struct EdgeHashType : std::unary_function<graph_edge_type, std::size_t>
		{
            /// API to get edge hash value 
            /// @param e edge 
			std::size_t operator()(graph_edge_type const& e) const 
			{
				std::size_t seed = 0;
				boost::hash_combine(seed, e.m_source);
				boost::hash_combine(seed, e.m_target);
				return seed;
			}
		};


		/// constructor
        /// @param g graph 
		Coloring(graph_type const& g);
		/// destructor
		virtual ~Coloring() {};

		// member functions
		/// top API 
		/// @return objective value 
		virtual double operator()(); 

		/// set number of colors 
        /// @param cn number of colors 
		virtual void color_num(ColorNumType cn) {m_color_num = cn;} 
		/// set number of colors 
        /// @param cn number of colors 
		virtual void color_num(int8_t cn) {m_color_num = (cn == 3)? THREE : (cn == 2)? TWO : FOUR;}
        /// @return number of colors 
        virtual ColorNumType color_num() const {return m_color_num;}

		/// set precolored vertex 
        /// @param v vertex 
        /// @param c color 
		virtual void precolor(graph_vertex_type v, int8_t c) {m_vColor[v] = c; m_has_precolored = true;}

        /// @return true if contain precolored vertices 
        virtual bool has_precolored() const {return m_has_precolored;}

		/// @return stitch weight 
		virtual double stitch_weight() const {return m_stitch_weight;}
        /// set weight of stitch 
        /// @param w weight 
		virtual void stitch_weight(double w) {m_stitch_weight = w;}

		/// set number of threads 
        /// @param t number of threads 
		virtual void threads(int32_t t) {m_threads = t;}

        /// retrieve coloring solution 
        /// @param v vertex 
		/// @return coloring solution 
		virtual int8_t color(graph_vertex_type v) const {return m_vColor[v];}

        // helper functions 
        /// get edge weight 
        /// @param e edge 
        /// @return edge weight 
        inline virtual edge_weight_type edge_weight(graph_edge_type const& e) const {return boost::get(boost::edge_weight, m_graph, e);}

        /// compute cost of coloring solutions
        /// @param vColor coloring solutions 
		/// @return cost with a coloring solution 
		virtual edge_weight_type calc_cost(std::vector<int8_t> const& vColor) const;

        /// check edge weight within \a lb and \a ub 
        /// @param g graph 
        /// @param lb lower bound 
        /// @param ub upper bound 
        void check_edge_weight(graph_type const& g, edge_weight_type lb, edge_weight_type ub) const;

        /// print edge weight 
        /// @param g graph 
        void print_edge_weight(graph_type const& g) const;
        
        // search vertexes in stitch relation
        // @param v vertex
        // @param stitch_relatiin_set recording for each vertex indicating the stitch relation
        // @param visited is visited in DFS
        // @param stitch_edge_num total stitch edge number in graph
        void depth_first_search_stitch(graph_vertex_type v, std::vector<int32_t>& stitch_relation_set,
            std::vector<bool>& visited,uint32_t& stitch_edge_num,int32_t stitch_index);
		// for debug 
        /// write graph in graphviz format 
        /// @param filename output file name 
		virtual void write_graph(std::string const& filename) const;
        /// write graph in graphviz format 
        /// @param filename output file name 
        /// @param g graph 
        /// @param vColor coloring solutions 
        virtual void write_graph(std::string const& filename, graph_type const& g, std::vector<int8_t> const& vColor) const;
	protected:
		/// @return objective value 
		virtual double coloring() = 0;

		graph_type const& m_graph; ///< initial graph 
		std::vector<int8_t> m_vColor; ///< coloring solutions 

    ColorNumType m_color_num; ///< number of colors 
    double m_stitch_weight; ///< stitch weight 
    int32_t m_threads; ///< control number of threads for ILP solver 
    bool m_has_precolored; ///< whether contain precolored vertices 

    // node num in big graph
    int32_t m_stitch_index;
    // edge num in big graph
    int32_t m_big_edge_num;
    std::vector<int32_t> m_stitch_relation_set;
    //a verctor of len(stitch_index*stitch_index) 
    std::vector<int32_t> m_edge_index_vector;
};

template <typename GraphType>
Coloring<GraphType>::Coloring(Coloring<GraphType>::graph_type const& g) 
    : m_graph(g)
    , m_vColor(boost::num_vertices(g), -1)
    , m_color_num(THREE)
    , m_stitch_weight(0.1)
    , m_threads(std::numeric_limits<int32_t>::max())
    , m_has_precolored(false)
    , m_stitch_index(0)
    , m_big_edge_num(0)
{}

template <typename GraphType>
double Coloring<GraphType>::operator()()
{
    double cost ;
    uint32_t stitch_edge_num = 0;
    //total wo-stitch node number
    
    //parent node in non-stitch graph index of each node in stitch graph


    //Step 1. Firstly, count the number of stitch edges and store all of the stitch relations
    vertex_iterator_type vi, vie,next;
    boost::tie(vi, vie) = vertices(m_graph);
    std::vector<bool> visited(boost::num_vertices(m_graph), false);
    m_stitch_relation_set.assign(boost::num_vertices(m_graph),-1);
    for (next = vi; vi != vie; vi = next)
    {
        ++next;
        graph_vertex_type v = *vi;
        if(visited[(int32_t)v]) continue;
        else{
            visited[(int32_t)v] = true;
            m_stitch_relation_set[(int32_t)v] = m_stitch_index;
            depth_first_search_stitch(v,m_stitch_relation_set,visited,stitch_edge_num,m_stitch_index);
            m_stitch_index ++;
        }
    }


    m_edge_index_vector.assign(m_stitch_index*m_stitch_index,-1);
    bool is_legal = true;

    //Step 2. Verify the feasibility of this method(no conflict should be introduced when inserting stitch)
    // Also, record the edge_index_vector
    boost::tie(vi, vie) = vertices(m_graph);
    for (next = vi; vi != vie; vi = next)
    {
        ++next;
        graph_vertex_type v = *vi;
        adjacency_iterator vi2, vie2,next2;
        boost::tie(vi2, vie2) = boost::adjacent_vertices(v, m_graph);
        for (next2 = vi2; vi2 != vie2; vi2 = next2){
            ++next2; 
            graph_vertex_type v2 = *vi2;
            std::pair<graph_edge_type, bool> e12 = boost::edge(v, v2, m_graph);
            limboAssert(e12.second);
            if(boost::get(boost::edge_weight, m_graph, e12.first) > 0){
                //if the big_edge is not considered, consider it and add 1
                if(m_edge_index_vector[m_stitch_relation_set[(int32_t)v]*m_stitch_index + m_stitch_relation_set[(int32_t)v2]] == -1){
                    m_edge_index_vector[m_stitch_relation_set[(int32_t)v]*m_stitch_index + m_stitch_relation_set[(int32_t)v2]] = m_big_edge_num;
                    m_big_edge_num++;
                }
            }
            if (boost::get(boost::edge_weight, m_graph, e12.first) > 0 && m_stitch_relation_set[(int32_t)v] == m_stitch_relation_set[(int32_t)v2])  is_legal = false;
        }
    }
    //Step 3. Assign the colors 
    std::vector<int32_t> stitch_relation_to_color(m_stitch_index,-1);
    std::vector<bool> unused_color(color_num(),true);


    if (boost::num_vertices(m_graph) <= color_num()+stitch_edge_num && is_legal) // if vertex number is no larger than color number, directly assign color
    {
        //Step 3.1: Assign pre-defined color firstly
        limboAssert(m_stitch_index <= color_num());
        for (int32_t i = 0, ie = m_vColor.size(); i != ie; ++i)
        {
            if (m_vColor[i] >= 0) // if not precolored, assign to an unused color
            {
                stitch_relation_to_color[m_stitch_relation_set[i]] = m_vColor[i];
                unused_color[m_vColor[i]] = false;
            }
        }

        //Step 3.2: Assign un-pre-defined color and keep colors of stitch vertexes same.
        for (int32_t i = 0, ie = m_vColor.size(); i != ie; ++i)
        {
            if (m_vColor[i] < 0) // if not precolored, assign to an unused color
            {
                if(stitch_relation_to_color[m_stitch_relation_set[i]] != -1){ 
                    m_vColor[i] = stitch_relation_to_color[m_stitch_relation_set[i]];
                    }
                else{
                    for(int32_t c= 0;c<color_num();c++){
                        if(unused_color[c]){
                            m_vColor[i] = c;
                            stitch_relation_to_color[m_stitch_relation_set[i]] = c;
                            unused_color[m_vColor[i]] = false;
                            break;
                        }
                    }
                }
                
            }
        }
        cost = calc_cost(m_vColor);
        limboAssert(cost == 0);
    }
    else // perform coloring algorithm 
        cost = this->coloring();
    // clock_t sub_comp_end = clock();
    return cost;
}

template <typename GraphType>
void Coloring<GraphType>::depth_first_search_stitch(graph_vertex_type v, std::vector<int32_t>& stitch_relation_set,\
std::vector<bool>& visited,uint32_t& stitch_edge_num, int32_t stitch_index)
{
    adjacency_iterator vi2, vie2,next2;
    boost::tie(vi2, vie2) = boost::adjacent_vertices(v, m_graph);
    for (next2 = vi2; vi2 != vie2; vi2 = next2){
        ++next2; 
        graph_vertex_type v2 = *vi2;
        if(visited[(int32_t)v2])    continue;
        std::pair<graph_edge_type, bool> e12 = boost::edge(v, v2, m_graph);
        limboAssert(e12.second);
        if (boost::get(boost::edge_weight, m_graph, e12.first) < 0) {
            visited[(int32_t)v2] = true;
            stitch_edge_num ++;
            stitch_relation_set[(int32_t)v2] = stitch_index;
            depth_first_search_stitch(v2,stitch_relation_set,visited,stitch_edge_num,stitch_index);
        }
    }
}


template <typename GraphType>
typename Coloring<GraphType>::edge_weight_type Coloring<GraphType>::calc_cost(std::vector<int8_t> const& vColor) const 
{
	limboAssert(vColor.size() == boost::num_vertices(this->m_graph));
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
        {
            cost += (vColor[s] == vColor[t])*w;
        }
		else // stitch edge 
        {
			cost -= (vColor[s] != vColor[t])*w*this->stitch_weight();
        }
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
        limboPrint(kNONE, "%g ", (double)w);
    }
    limboPrint(kNONE, "\n");
}

// it seems doxygen cannot handle template functions with the same name correctly 
/// @cond
template <typename GraphType>
void Coloring<GraphType>::write_graph(std::string const& filename) const 
{
    write_graph(filename, m_graph, m_vColor);
}

template <typename GraphType>
void Coloring<GraphType>::write_graph(std::string const& filename, Coloring<GraphType>::graph_type const& g, std::vector<int8_t> const& vColor) const
{
    std::ofstream out ((filename+".gv").c_str());
    limboPrint(kINFO, "write_graph : %s\n", filename.c_str());
    la::write_graph(out, g, ColoringVertexLabelWriter<graph_type>(g, vColor), ColoringEdgeLabelWriter<graph_type>(g, vColor));
    out.close();
    la::graphviz2pdf(filename);
}
/// @endcond

} // namespace coloring
} // namespace algorithms
} // namespace limbo

#endif
