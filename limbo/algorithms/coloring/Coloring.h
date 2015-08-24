/*************************************************************************
    > File Name: Coloring.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Mon Jun  1 21:46:55 2015
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_COLORING_COLORING
#define LIMBO_ALGORITHMS_COLORING_COLORING

#include <vector>
#include <boost/cstdint.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/property_map/property_map.hpp>
#include <limbo/preprocessor/AssertMsg.h>

namespace limbo { namespace algorithms { namespace coloring {

using std::vector;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::ofstream;
using boost::uint32_t;
using boost::int32_t;
using boost::int8_t;

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
		/// edge weight is used to differentiate conflict edge and stitch edge 
		/// non-negative weight implies conflict edge 
		/// negative weight implies stitch edge 

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
        inline virtual int32_t edge_weight(graph_edge_type const& e) const {return boost::get(boost::edge_weight, m_graph, e);}

		/// for debug 
		virtual void write_graph(string const& filename) const;
	protected:
		/// \return objective value 
		virtual double coloring() = 0;

		/// \return cost with a coloring solution 
		virtual double calc_cost(vector<int8_t> const& vColor) const;

		graph_type const& m_graph;
		vector<int8_t> m_vColor;

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
double Coloring<GraphType>::calc_cost(vector<int8_t> const& vColor) const 
{
	assert(vColor.size() == boost::num_vertices(this->m_graph));
	double cost = 0;
	edge_iterator_type ei, eie;
	for (boost::tie(ei, eie) = boost::edges(m_graph); ei != eie; ++ei)
	{
		int32_t w = boost::get(boost::edge_weight, m_graph, *ei);
		graph_vertex_type s = boost::source(*ei, m_graph);
		graph_vertex_type t = boost::target(*ei, m_graph);
		if (w >= 0) // conflict edge 
			cost += (vColor[s] == vColor[t])*w;
		else // stitch edge 
			cost += (vColor[s] != vColor[t])*w;
	}
	return cost;
}

template <typename GraphType>
void Coloring<GraphType>::write_graph(string const& filename) const 
{
	ofstream dot_file((filename+".gv").c_str());
	dot_file << "graph D { \n"
		<< "  randir = LR\n"
		<< "  size=\"4, 3\"\n"
		<< "  ratio=\"fill\"\n"
		<< "  edge[style=\"bold\",fontsize=200]\n" 
		<< "  node[shape=\"circle\",fontsize=200]\n";

	//output nodes 
	uint32_t vertex_num = boost::num_vertices(m_graph);
	for(uint32_t k = 0; k < vertex_num; ++k) 
	{
		dot_file << "  " << k << "[shape=\"circle\"";
		//output coloring label
		dot_file << ",label=\"" << k << ":" << (int32_t)m_vColor[k] << "\"";
		dot_file << "]\n";
	}//end for

	//output edges
	edge_iterator_type ei, eie;
	for (boost::tie(ei, eie) = boost::edges(m_graph); ei != eie; ++ei)
	{
		int32_t w = boost::get(boost::edge_weight, m_graph, *ei);
		graph_vertex_type s = boost::source(*ei, m_graph);
		graph_vertex_type t = boost::target(*ei, m_graph);
		if (w >= 0) // conflict edge 
		{
			bool conflict_flag = (m_vColor[s] >= 0 && m_vColor[s] == m_vColor[t]);

			if(conflict_flag)
				dot_file << "  " << s << "--" << t << "[color=\"red\",style=\"solid\",penwidth=3]\n";
			else 
				dot_file << "  " << s << "--" << t << "[color=\"black\",style=\"solid\",penwidth=3]\n";
		}
		else // stitch edge 
			dot_file << "  " << s << "--" << t << "[color=\"black\",style=\"dashed\",penwidth=3]\n";
	}
	dot_file << "}";
	dot_file.close();
	char cmd[100];
	sprintf(cmd, "dot -Tpdf %s.gv -o %s.pdf", filename.c_str(), filename.c_str());
	system(cmd);
}

}}} // namespace limbo // namespace algorithms // namespace coloring

#endif
