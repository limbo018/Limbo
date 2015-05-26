/*************************************************************************
    > File Name: ILPColoring.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Sat 23 May 2015 11:21:08 AM CDT
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_COLORING_ILPCOLORING
#define LIMBO_ALGORITHMS_COLORING_ILPCOLORING

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <limits>
#include <cassert>
#include <cmath>
#include <stdlib.h>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <boost/cstdint.hpp>
#include <boost/unordered_map.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/subgraph.hpp>
#include <boost/property_map/property_map.hpp>
//#include <boost/graph/bipartite.hpp>
//#include <boost/graph/kruskal_min_spanning_tree.hpp>
//#include <boost/graph/prim_minimum_spanning_tree.hpp>
//#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <limbo/string/String.h>
#include "gurobi_c++.h"

namespace limbo { namespace algorithms { namespace coloring {

using std::vector;
using std::cout;
using std::endl;
using std::ofstream;
using std::pair;
using std::ostringstream;
using std::string;
using boost::unordered_map;
using boost::uint32_t;
using boost::int32_t;

template <typename GraphType>
class ILPColoring 
{
	public:
		typedef GraphType graph_type;
		//typedef boost::subgraph_type<graph_type> subgraph_type;
		typedef typename boost::graph_traits<graph_type>::vertex_descriptor graph_vertex_type;
		typedef typename boost::graph_traits<graph_type>::edge_descriptor graph_edge_type;
		typedef typename boost::graph_traits<graph_type>::vertex_iterator vertex_iterator_type;
		typedef typename boost::graph_traits<graph_type>::edge_iterator edge_iterator_type;
		/// edge weight is used to differentiate conflict edge and stitch edge 
		/// non-negative weight implies conflict edge 
		/// negative weight implies stitch edge 
		typedef typename boost::property_map<graph_type, boost::edge_weight_t>::type edge_weight_map_type;
		typedef typename boost::property_map<graph_type, boost::edge_weight_t>::const_type const_edge_weight_map_type;
		/// use vertex color to save vertex stitch candidate number 
		typedef typename boost::property_map<graph_type, boost::vertex_color_t>::type vertex_color_map_type;
		typedef typename boost::property_map<graph_type, boost::vertex_color_t>::const_type const_vertex_color_map_type;

		enum ColorNumType
		{
			THREE = 3, 
			FOUR = 4
		};
		// hasher class for graph_edge_type
		struct edge_hash_type : std::unary_function<graph_edge_type, std::size_t>
		{
			std::size_t operator()(graph_edge_type const& e) const 
			{
				std::size_t seed = 0;
				boost::hash_combine(seed, e.m_source);
				boost::hash_combine(seed, e.m_target);
				return seed;
			}
		};

		/// member functions
		/// constructor
		ILPColoring(graph_type const& g) 
			  : m_graph(g)
			  , m_vColor(boost::num_vertices(g), -1)
			  , m_stitch_weight(0.1)
			  , m_threads(std::numeric_limits<int32_t>::max())
		{}
		/// destructor
		~ILPColoring() {};

		/// top api 
		/// \return objective value 
		double operator()() {return this->coloring();}

		/// color number 
		void color_num(ColorNumType cn) {m_color_num = cn;} 
		void color_num(int8_t cn) {m_color_num = (cn == 3)? THREE : FOUR;}

		/// precolored vertex 
		template <typename Iterator>
		void precolor(Iterator first, Iterator last) {m_vColor.assign(first, last);}
		void precolor(graph_vertex_type v, int8_t c) {m_vColor[v] = c;}

		/// stitch weight 
		double stitch_weight() const {return m_stitch_weight;}
		void stitch_weight(double w) {m_stitch_weight = w;}

		/// threads 
		void threads(int32_t t) {m_threads = t;}

		/// \return coloring solution 
		int8_t color(graph_vertex_type v) const {return m_vColor[v];}

		/// for debug 
		void write_graph(string const& filename) const;
	protected:
		/// \return objective value 
		double coloring();

		graph_type const& m_graph;
		vector<int8_t> m_vColor;

		ColorNumType m_color_num;
		double m_stitch_weight;
		int32_t m_threads; ///< control number of threads for ILP solver 
};

template <typename GraphType>
double ILPColoring<GraphType>::coloring()
{
	uint32_t vertex_num = boost::num_vertices(m_graph);
	uint32_t edge_num = boost::num_edges(m_graph);
	uint32_t vertex_variable_num = vertex_num<<1;

	unordered_map<graph_vertex_type, uint32_t> hVertexIdx; // vertex index 
	unordered_map<graph_edge_type, uint32_t, edge_hash_type> hEdgeIdx; // edge index 

	vertex_iterator_type vi, vie;
	uint32_t cnt = 0;
	for (boost::tie(vi, vie) = boost::vertices(m_graph); vi != vie; ++vi, ++cnt)
		hVertexIdx[*vi] = cnt;
	edge_iterator_type ei, eie;
	cnt = 0; 
	for (boost::tie(ei, eie) = boost::edges(m_graph); ei != eie; ++ei, ++cnt)
		hEdgeIdx[*ei] = cnt;

	// ILP environment
	GRBEnv env = GRBEnv();
	//mute the log from the LP solver
	env.set(GRB_IntParam_OutputFlag, 0);
	// set threads 
	if (m_threads > 0 && m_threads < std::numeric_limits<int32_t>::max())
		env.set(GRB_IntParam_Threads, m_threads);
	GRBModel opt_model = GRBModel(env);
	//set up the ILP variables
	vector<GRBVar> vVertexBit;
	vector<GRBVar> vEdgeBit;

	// vertex variables 
	vVertexBit.reserve(vertex_variable_num); 
	for (uint32_t i = 0; i != vertex_variable_num; ++i)
	{
		uint32_t vertex_idx = (i>>1);
		ostringstream oss; 
		oss << "v" << i;
		if (m_vColor[vertex_idx] >= 0 && m_vColor[vertex_idx] < m_color_num) // precolored 
		{
			int8_t color_bit;
			if ((i&1) == 0) color_bit = (m_vColor[vertex_idx]>>1)&1;
			else color_bit = m_vColor[vertex_idx]&1;
			vVertexBit.push_back(opt_model.addVar(color_bit, color_bit, color_bit, GRB_INTEGER, oss.str()));
		}
		else // uncolored 
			vVertexBit.push_back(opt_model.addVar(0, 1, 0, GRB_INTEGER, oss.str()));
	}

	// edge variables 
	vEdgeBit.reserve(edge_num);
	for (uint32_t i = 0; i != edge_num; ++i)
	{
		ostringstream oss;
		oss << "e" << i;
		vEdgeBit.push_back(opt_model.addVar(0, 1, 0, GRB_CONTINUOUS, oss.str()));
	}

	// update model 
	opt_model.update();

	// set up the objective 
	GRBLinExpr obj (0);
	for (boost::tie(ei, eie) = edges(m_graph); ei != eie; ++ei)
	{
		int32_t w = boost::get(boost::edge_weight, m_graph, *ei);
		if (w > 0) // weighted conflict 
			obj += w*vEdgeBit[hEdgeIdx[*ei]];
		else if (w < 0) // weighted stitch 
			obj += m_stitch_weight*(-w)*vEdgeBit[hEdgeIdx[*ei]];
	}
	opt_model.setObjective(obj, GRB_MINIMIZE);

	// set up the constraints
	uint32_t constr_num = 0;
	for (boost::tie(ei, eie) = boost::edges(m_graph); ei != eie; ++ei)
	{
		graph_vertex_type s = boost::source(*ei, m_graph);
		graph_vertex_type t = boost::target(*ei, m_graph);
		uint32_t sIdx = hVertexIdx[s];
		uint32_t tIdx = hVertexIdx[t];

		uint32_t vertex_idx1 = sIdx<<1;
		uint32_t vertex_idx2 = tIdx<<1;

		int32_t w = boost::get(boost::edge_weight, m_graph, *ei);
		uint32_t edge_idx = hEdgeIdx[*ei];

		char buf[100];
		string tmpConstr_name;
		if (w >= 0) // constraints for conflict edges 
		{
			sprintf(buf, "R%u", constr_num++);  
			opt_model.addConstr(
					vVertexBit[vertex_idx1] + vVertexBit[vertex_idx1+1] 
					+ vVertexBit[vertex_idx2] + vVertexBit[vertex_idx2+1] 
					+ vEdgeBit[edge_idx] >= 1
					, buf);

			sprintf(buf, "R%u", constr_num++);  
			opt_model.addConstr(
					1 - vVertexBit[vertex_idx1] + vVertexBit[vertex_idx1+1] 
					+ 1 - vVertexBit[vertex_idx2] + vVertexBit[vertex_idx2+1] 
					+ vEdgeBit[edge_idx] >= 1
					, buf);

			sprintf(buf, "R%u", constr_num++);  
			opt_model.addConstr(
					vVertexBit[vertex_idx1] + 1 - vVertexBit[vertex_idx1+1] 
					+ vVertexBit[vertex_idx2] + 1 - vVertexBit[vertex_idx2+1] 
					+ vEdgeBit[edge_idx] >= 1
					, buf);

			sprintf(buf, "R%u", constr_num++);  
			opt_model.addConstr(
					1 - vVertexBit[vertex_idx1] + 1 - vVertexBit[vertex_idx1+1] 
					+ 1 - vVertexBit[vertex_idx2] + 1 - vVertexBit[vertex_idx2+1] 
					+ vEdgeBit[edge_idx] >= 1
					, buf);

		}
		else // constraints for stitch edges 
		{
			sprintf(buf, "R%u", constr_num++);  
			opt_model.addConstr(
					vVertexBit[vertex_idx1] - vVertexBit[vertex_idx2] - vEdgeBit[edge_idx] <= 0
					, buf);

			sprintf(buf, "R%u", constr_num++);  
			opt_model.addConstr(
					vVertexBit[vertex_idx2] - vVertexBit[vertex_idx1] - vEdgeBit[edge_idx] <= 0
					, buf);

			sprintf(buf, "R%u", constr_num++);  
			opt_model.addConstr(
					vVertexBit[vertex_idx1+1] - vVertexBit[vertex_idx2+1] - vEdgeBit[edge_idx] <= 0
					, buf);      

			sprintf(buf, "R%u", constr_num++);  
			opt_model.addConstr(
					vVertexBit[vertex_idx2+1] - vVertexBit[vertex_idx1+1] - vEdgeBit[edge_idx] <= 0
					, buf);
		}
	}

	// additional constraints for 3-coloring 
	if (m_color_num == THREE)
	{
		char buf[100];
		for(uint32_t k = 0; k != vertex_variable_num; k += 2) 
		{
			sprintf(buf, "R%u", constr_num++);  
			opt_model.addConstr(vVertexBit[k] + vVertexBit[k+1] <= 1, buf);
		}
	}

	//optimize model 
	opt_model.update();
	opt_model.optimize();
#ifdef DEBUG_ILPCOLORING
	opt_model.write("graph.lp");
	opt_model.write("graph.sol");
#endif 
	int32_t opt_status = opt_model.get(GRB_IntAttr_Status);
	if(opt_status == GRB_INFEASIBLE) 
	{
		cout << "ERROR: The model is infeasible... EXIT" << endl;
		exit(1);
	}

	// collect coloring solution 
	for (uint32_t k = 0; k != vertex_variable_num; k += 2)
	{
		int8_t color = (vVertexBit[k].get(GRB_DoubleAttr_X)*2)+vVertexBit[k+1].get(GRB_DoubleAttr_X);
		uint32_t vertex_idx = (k>>1);

		assert(color >= 0 && color < m_color_num);
		if (m_vColor[vertex_idx] >= 0 && m_vColor[vertex_idx] < m_color_num) // check precolored vertex 
			assert(m_vColor[vertex_idx] == color);
		else // assign color to uncolored vertex 
			m_vColor[vertex_idx] = color;
	}

	// return objective value 
	return opt_model.get(GRB_DoubleAttr_ObjVal);
}

template <typename GraphType>
void ILPColoring<GraphType>::write_graph(string const& filename) const 
{
	ofstream dot_file((filename+".gv").c_str());
	dot_file << "graph D { \n"
		<< "  randir = LR\n"
		<< "  size=\"4, 3\"\n"
		<< "  ratio=\"fill\"\n"
		<< "  edge[style=\"bold\",fontsize=200]\n" 
		<< "  node[shape=\"circle\",fontsize=200]\n";

	//output nodes 
	uint32_t vertex_num = num_vertices(m_graph);
	for(uint32_t k = 0; k < vertex_num; ++k) 
	{
		dot_file << "  " << k << "[shape=\"circle\"";
		//output coloring label
		dot_file << ",label=\"" << k << ":" << m_vColor[k] << "\"";
		dot_file << "]\n";
	}//end for

	//output edges
	edge_iterator_type ei, eie;
	for (boost::tie(ei, eie) = boost::edges(m_graph); ei != eie; ++ei)
	{
		int32_t w = boost::get(boost::edge_weight, m_graph, *ei);
		graph_vertex_type s = boost::source(*ei);
		graph_vertex_type t = boost::target(*ei);
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
