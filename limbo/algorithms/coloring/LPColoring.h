#ifndef LIMBO_ALGORITHMS_COLORING_LP
#define LIMBO_ALGORITHMS_COLORING_LP

#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <cmath>
#include <stdlib.h>
#include <boost/cstdint.hpp>
#include <boost/unordered_map.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/subgraph.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/bipartite.hpp>
#include "gurobi_c++.h"

//#define TRIPLEPATTERNING 

using std::vector;
using std::set;
using std::cout;
using std::endl;
using std::ofstream;
using std::pair;
using boost::unordered_map;
using boost::uint32_t;
using boost::int32_t;

namespace limbo { namespace algorithms { namespace coloring {

template <typename GraphType>
class LPColoring 
{
	public:
		typedef GraphType graph_type;
		//typedef boost::subgraph_type<graph_type> subgraph_type;
		typedef typename boost::graph_traits<graph_type>::vertex_descriptor graph_vertex_type;
		typedef typename boost::graph_traits<graph_type>::edge_descriptor graph_edge_type;
		/// edge weight is used to differentiate conflict edge and stitch edge 
		/// non-negative weight implies conflict edge 
		/// negative weight implies stitch edge 
		typedef typename boost::property_map<graph_type, boost::edge_weight_t>::const_type edge_weight_map_type;

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
		LPColoring(graph_type const& g);
		/// destructor
		~LPColoring() {};

		/// top api 
		void operator()() {this->graphColoring();}

		bool conflictCost() const {return m_conflict_cost;}
		void conflictCost(bool flag) {m_conflict_cost = flag;}
		double stitchWeight() const {return m_stitch_weight;}
		void stitchWeight(double w) {m_stitch_weight = w;}

		/// DFS to search for the odd cycles, stored in m_odd_cycles
		void oddCycles(graph_vertex_type& v);

		/// relaxed linear programming based coloring for the conflict graph (m_graph)
		void graphColoring(); 
		/// ILP based coloring
		void ILPColoring(GRBModel& opt_model, vector<GRBVar>& coloringBits);
		/// rounding scheme
		void roundingColoring(vector<GRBVar>& coloringBits);

		/// coloring info
		uint32_t vertexColor(graph_vertex_type& node) const;
		uint32_t conflictNum() const;
		uint32_t stitchNum() const;

		pair<uint32_t, uint32_t> nonIntegerNum(const vector<GRBVar>& coloringBits, const vector<GRBVar>& vEdgeBit) const;
		/// for debug use
		void printBoolVec(vector<bool>& vec) const;
		void printBoolArray(bool* vec, uint32_t vec_size) const;
		/// print graphviz
		void write_graph_dot(graph_vertex_type& v) const;
		void write_graph_dot() const;
		void write_graph_color() const;

		/// members
		/// coloring bits
		const uint32_t COLORING_BITS;
	protected:
		/// set up the vertex map
		void setMap();

		/// members
		/// the graph 
		graph_type const& m_graph;
		/// the vertex map for the graph 
		unordered_map<graph_vertex_type, uint32_t> m_vertex_map;
		unordered_map<uint32_t, graph_vertex_type> m_inverse_vertex_map;
		/// edge map for the graph 
		unordered_map<graph_edge_type, uint32_t, edge_hash_type> m_edge_map;
		/// edge weight map 
		edge_weight_map_type m_edge_weight_map;
		/// LP coloring results
		unordered_map<graph_vertex_type, uint32_t> m_coloring;
		/// the lp coloring before rounding
		vector<double> m_lp_coloring;
		/// store the odd cycles
		vector< vector<graph_vertex_type> > m_odd_cycles;
		/// conflict control flag 
		/// whether put conflicts in ILP cost 
		bool m_conflict_cost;
		/// weight for stitch in the cost 
		double m_stitch_weight;
};

/// constructor
template <typename GraphType>
LPColoring<GraphType>::LPColoring(graph_type const& g) : COLORING_BITS(2), m_graph(g)
{
	m_conflict_cost = true;
	m_stitch_weight = 1.0;
	this->setMap();
}

//set the vertex map
template<typename GraphType>
void LPColoring<GraphType>::setMap() 
{
	// build the vertex-index map
	pair<typename graph_type::vertex_iterator, typename graph_type::vertex_iterator> vertex_range = vertices(m_graph);
	m_vertex_map.clear();
	m_inverse_vertex_map.clear();
	uint32_t vertex_num = 0;
	for(BOOST_AUTO(itr, vertex_range.first); itr != vertex_range.second; ++itr) 
	{
		m_vertex_map[*itr] = vertex_num;
		m_inverse_vertex_map[vertex_num] = *itr;
		++vertex_num;
	}
	// build edge-index map 
	pair<typename graph_type::edge_iterator, typename graph_type::edge_iterator> edge_range = edges(m_graph);
	m_edge_map.clear();
	uint32_t edge_num = 0;
	for (BOOST_AUTO(itr, edge_range.first); itr != edge_range.second; ++itr)
	{
		m_edge_map[*itr] = edge_num;
		++edge_num;
	}
	// build edge weight map 
	m_edge_weight_map = get(boost::edge_weight, m_graph);
}

//DFS to search for the odd cycles, stored in m_odd_cycles
template<typename GraphType>
void LPColoring<GraphType>::oddCycles(graph_vertex_type& v) 
{
	//if(m_vertex_map.empty() || m_inverse_vertex_map.empty()) this->setMap();
#ifdef ASSERT_LPCOLORING
	assert(m_vertex_map.find(v) != m_vertex_map.end());
#endif
	//odd_cycle results
	this->m_odd_cycles.clear();

	//the array denoting the distancevisiting of the graph 
	uint32_t vertex_num = num_edges(m_graph);
	int32_t nodeDist[vertex_num];
	bool nodeVisited[vertex_num];
	for(uint32_t k = 0; k < vertex_num; k++) 
	{
		nodeDist[k] = -1;
		nodeVisited[k] = false;
	}

	//inCycle flag
	bool inCycle[vertex_num];
	for(uint32_t k = 0; k < vertex_num; k++) inCycle[k] = false;

	//dfs_stack for DFS
	vector<graph_vertex_type> dfs_stack;
	dfs_stack.reserve(vertex_num);
	uint32_t v_index = m_vertex_map[v];
	nodeVisited[v_index] = true;
	nodeDist[v_index] = 0;
	dfs_stack.push_back(v);
	while(false == dfs_stack.empty()) 
	{
		//determine whether the top element needs to be popped
		bool popFlag = true;
		//access the top element on the dfs_stack
		graph_vertex_type curr_v = dfs_stack.back();
		uint32_t curr_index = m_vertex_map[curr_v];
		//access the neighbors 
		typename boost::graph_traits<graph_type>::adjacency_iterator vi_begin, vi_end;
		boost::tie(vi_begin, vi_end) = adjacent_vertices(curr_v, m_graph);
		for(BOOST_AUTO(vi, vi_begin); vi != vi_end; ++vi) 
		{
			BOOST_AUTO(found_edge, boost::edge(curr_v, *vi, m_graph));
#ifdef ASSERT_LPCOLORING
			assert(found_edge.second);
#endif
			// skip stitch edges 
			if (m_edge_weight_map[found_edge.first] < 0) continue;

			uint32_t next_index = m_vertex_map[*vi];
			if(nodeDist[next_index] < 0) 
			{
				nodeDist[next_index] = 1 - nodeDist[curr_index];
				nodeVisited[next_index] = true;
				//push to the dfs_stack
				dfs_stack.push_back(*vi);
				popFlag = false;
				break;
			}
		} //end for 

		if(true == popFlag) 
		{
			//detect the odd cycle
			for(BOOST_AUTO(vi, vi_begin); vi != vi_end; ++vi) 
			{
				uint32_t next_index = m_vertex_map[*vi];
				if(true == nodeVisited[next_index] && (nodeDist[next_index] == nodeDist[curr_index])) 
				{
					//suppose v/v_index is not in the current cycle 
					inCycle[v_index] = true;
					//detect the cycle between curr_v and *vi
					vector<graph_vertex_type> cycle;
					int cnt = dfs_stack.size();
					for(int k = cnt - 1; k >= 0; k--) 
					{
						cycle.push_back(dfs_stack[k]);
						//flag the nodes in cycle
						inCycle[m_vertex_map[dfs_stack[k]]] = true;
						if(dfs_stack[k] == (*vi)) break;
					}
					//store the cycle, when v/v_index is in cycle
					if(cycle.size() > 0 && inCycle[v_index]) 
					{
						this->m_odd_cycles.push_back(cycle);
					} 
					else if(cycle.size() == 0) 
					{
						cout << "ERROR: the cycle detected contains no nodes" << endl;
					}
				}//end if
			}//end for vi

			//pop the top element
			dfs_stack.pop_back();
			nodeVisited[curr_index] = false;
		}//end if popFlag

	}//end while
#ifdef DEBUG_LPCOLORING
	if(m_odd_cycles.size() > 0) cout << m_odd_cycles.size() << " cycles detected." << endl;
	else cout << "No cycles detected." << endl;
#endif
}

//relaxed linear programming based coloring for the conflict graph (m_graph)
template<typename GraphType> 
void LPColoring<GraphType>::graphColoring() 
{
	//build the vertex-index map
	//pair<typename graph_type::vertex_iterator, typename graph_type::vertex_iterator> vertex_range = vertices(m_graph);
#if 0
	//unordered_map<graph_vertex_type, uint32_t> m_vertex_map;
	//unordered_map<uint32_t, graph_vertex_type> m_inverse_vertex_map;
	m_vertex_map.clear(), m_inverse_vertex_map.clear();
	uint32_t vertex_num = 0;
	for(BOOST_AUTO(itr, vertex_range.first); itr != vertex_range.second; ++itr) 
	{
		m_vertex_map[*itr] = vertex_num;
		m_inverse_vertex_map[vertex_num] = *itr;
		vertex_num++;
	}
#endif
	uint32_t vertex_num = boost::num_vertices(m_graph);
	uint32_t edge_num = boost::num_edges(m_graph);
	uint32_t coloring_bits_num = COLORING_BITS*vertex_num;
	//uint32_t variable_num = coloring_bits_num+edge_num;

	//set up the LP environment
	GRBEnv env = GRBEnv();
	//mute the log from the LP solver
	//env.set(GRB_IntParam_OutputFlag, 0);
	GRBModel opt_model = GRBModel(env);
	//set up the LP variables
	vector<GRBVar> coloringBits;
	vector<GRBVar> vEdgeBit;
	// vertex and edge variables 
	coloringBits.reserve(coloring_bits_num);
	for (uint32_t i = 0; i != coloring_bits_num; ++i)
	{
		//coloringBits.push_back(opt_model.addVar(0.0, 1.0, 0.0, GRB_INTEGER));
		coloringBits.push_back(opt_model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS));
	}
	vEdgeBit.reserve(edge_num);
	for (uint32_t i = 0; i != edge_num; ++i)
	{
		// some variables here may not be used 
		//vEdgeBit.push_back(opt_model.addVar(0.0, 1.0, 0.0, GRB_INTEGER));
		vEdgeBit.push_back(opt_model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS));
	}
	// conflict edge variables 
	// they are used in objective function to minimize conflict cost 
	pair<typename graph_type::edge_iterator, typename graph_type::edge_iterator> edge_range = edges(m_graph);
	//Integrate new variables
	opt_model.update();

	//set up the objective
	GRBLinExpr obj_init (0);
	GRBLinExpr obj (0); // maybe useful 
	if (this->conflictCost())
	{
		for (BOOST_AUTO(itr, edge_range.first); itr != edge_range.second; ++itr)
		{
			BOOST_AUTO(w, m_edge_weight_map[*itr]);
			uint32_t edge_idx = m_edge_map[*itr];
			if (w >= 0) // conflict 
				obj_init += vEdgeBit[edge_idx];
			else // stitch 
				obj_init += m_stitch_weight*vEdgeBit[edge_idx];
		}
	}
	if(conflictCost()) obj = obj_init;
	opt_model.setObjective(obj, GRB_MINIMIZE);

	//set up the LP constraints
	//typename graph_type::edges_size_type edge_num = num_edges(m_graph);
	//typename graph_type::vertices_size_type vertex_num = num_vertices(m_graph); 
	for(BOOST_AUTO(itr, edge_range.first); itr != edge_range.second; ++itr) 
	{
		BOOST_AUTO(from, source(*itr, m_graph));
		uint32_t f_ind = m_vertex_map[from];
		BOOST_AUTO(to, target(*itr, m_graph));
		uint32_t t_ind = m_vertex_map[to];
		//coloring conflict constraints
		uint32_t vertex_idx1 = f_ind<<1;
		uint32_t vertex_idx2 = t_ind<<1;

		BOOST_AUTO(w, m_edge_weight_map[*itr]);
		if (w >= 0) // constraints for conflict edges 
		{
			if (!conflictCost())
			{
				opt_model.addConstr(
						coloringBits[vertex_idx1] + coloringBits[vertex_idx1+1] 
						+ coloringBits[vertex_idx2] + coloringBits[vertex_idx2+1] >= 1
						);
				opt_model.addConstr(
						1 - coloringBits[vertex_idx1] + coloringBits[vertex_idx1+1] 
						+ 1 - coloringBits[vertex_idx2] + coloringBits[vertex_idx2+1] >= 1
						);
				opt_model.addConstr(
						coloringBits[vertex_idx1] + 1 - coloringBits[vertex_idx1+1] 
						+ coloringBits[vertex_idx2] + 1 - coloringBits[vertex_idx2+1] >= 1
						);
				opt_model.addConstr(
						1 - coloringBits[vertex_idx1] + 1 - coloringBits[vertex_idx1+1] 
						+ 1 - coloringBits[vertex_idx2] + 1 - coloringBits[vertex_idx2+1] >= 1
						);
			}
			else 
			{
				uint32_t edge_idx = m_edge_map[*itr];
				opt_model.addConstr(
						coloringBits[vertex_idx1] + coloringBits[vertex_idx1+1] 
						+ coloringBits[vertex_idx2] + coloringBits[vertex_idx2+1] 
						+ vEdgeBit[edge_idx] >= 1
						);
				opt_model.addConstr(
						1 - coloringBits[vertex_idx1] + coloringBits[vertex_idx1+1] 
						+ 1 - coloringBits[vertex_idx2] + coloringBits[vertex_idx2+1] 
						+ vEdgeBit[edge_idx] >= 1
						);
				opt_model.addConstr(
						coloringBits[vertex_idx1] + 1 - coloringBits[vertex_idx1+1] 
						+ coloringBits[vertex_idx2] + 1 - coloringBits[vertex_idx2+1] 
						+ vEdgeBit[edge_idx] >= 1
						);
				opt_model.addConstr(
						1 - coloringBits[vertex_idx1] + 1 - coloringBits[vertex_idx1+1] 
						+ 1 - coloringBits[vertex_idx2] + 1 - coloringBits[vertex_idx2+1] 
						+ vEdgeBit[edge_idx] >= 1
						);
			}
		}
		else // constraints for stitch edges 
		{
			uint32_t edge_idx = m_edge_map[*itr];
			opt_model.addConstr(
					coloringBits[vertex_idx1] - coloringBits[vertex_idx2] - vEdgeBit[edge_idx] <= 0
					);
			opt_model.addConstr(
					coloringBits[vertex_idx2] - coloringBits[vertex_idx1] - vEdgeBit[edge_idx] <= 0
					);
			opt_model.addConstr(
					coloringBits[vertex_idx1+1] - coloringBits[vertex_idx2+1] - vEdgeBit[edge_idx] <= 0
					);
			opt_model.addConstr(
					coloringBits[vertex_idx2+1] - coloringBits[vertex_idx1+1] - vEdgeBit[edge_idx] <= 0
					);
		}
	}

#ifdef TRIPLEPATTERNING
	for(uint32_t k = 0; k < coloring_bits_num; k += COLORING_BITS) 
	{
		opt_model.addConstr(coloringBits[k] + coloringBits[k+1] <= 1);
	}
#endif
	//optimize model 
	opt_model.optimize();
	int optim_status = opt_model.get(GRB_IntAttr_Status);
	if(optim_status == GRB_INFEASIBLE) 
	{
		cout << "ERROR: The model is infeasible... EXIT" << endl;
		exit(1);
	}
	cout << endl;

	//iteratively scheme
	while(true) 
	{
		uint32_t non_integer_num, half_integer_num;
		BOOST_AUTO(pair, this->nonIntegerNum(coloringBits, vEdgeBit));
		non_integer_num = pair.first;
		half_integer_num = pair.second;
    if(non_integer_num == 0) break;
		//store the lp coloring results 
		m_lp_coloring.clear();
		m_lp_coloring.reserve(coloring_bits_num);
		for(uint32_t k = 0; k < coloring_bits_num; k++) 
		{
			double value = coloringBits[k].get(GRB_DoubleAttr_X);
			m_lp_coloring.push_back(value);
		}

		vector<bool> non_integer_flag(coloring_bits_num, false);
		//set the new objective
		//push the non-half_integer to 0/1
		// only check for vertices 
    
		for(uint32_t k = 0; k < coloring_bits_num; k++) 
		{
			double value = coloringBits[k].get(GRB_DoubleAttr_X);
			if(value < 0.5) 
			{
				if(!conflictCost()) obj = obj + 2*coloringBits[k];
				non_integer_flag[k] = false;
			} 
			else if (value > 0.5) 
			{
				if(!conflictCost()) obj = obj - 2*coloringBits[k];
				non_integer_flag[k] = false;
			} 
			else 
			{
				non_integer_flag[k] = true;
			}

		}//end for 
    
		//minimize the conflict number 
		for(BOOST_AUTO(itr, edge_range.first); itr != edge_range.second; ++itr) 
		{
			BOOST_AUTO(from, source(*itr, m_graph));
			uint32_t f_ind = m_vertex_map[from];
			BOOST_AUTO(to, target(*itr, m_graph));
			uint32_t t_ind = m_vertex_map[to];
  		uint32_t vertex_idx1 = f_ind<<1;
  		uint32_t vertex_idx2 = t_ind<<1;
			if (m_lp_coloring[vertex_idx1] > m_lp_coloring[vertex_idx2]) 
			{
				obj += coloringBits[vertex_idx2] - coloringBits[vertex_idx1];
			} 
			else if (m_lp_coloring[vertex_idx1] < m_lp_coloring[vertex_idx2]) 
			{
				obj += coloringBits[vertex_idx1] - coloringBits[vertex_idx2];
			}

      vertex_idx1 += 1;
      vertex_idx2 += 1;
			if (m_lp_coloring[vertex_idx1] > m_lp_coloring[vertex_idx2]) 
			{
				obj += coloringBits[vertex_idx2] - coloringBits[vertex_idx1];
			} 
			else if (m_lp_coloring[vertex_idx1] < m_lp_coloring[vertex_idx2]) 
			{
				obj += coloringBits[vertex_idx1] - coloringBits[vertex_idx2];
			}
		}//end for 

		opt_model.setObjective(obj);

		//add the new constraints
		//odd cycle trick from Prof. Baldick
		for(uint32_t k = 0; k < coloring_bits_num; k++) 
		{
			//if the current bit is already handled
			if(false == non_integer_flag[k]) continue;

			uint32_t vertex_index = k/COLORING_BITS;
#ifdef ASSERT_LPCOLORING
			assert(m_inverse_vertex_map.find(vertex_index) != m_inverse_vertex_map.end());
#endif
			graph_vertex_type curr_v = m_inverse_vertex_map[vertex_index];
			//detect the odd cycles related, stored in the m_odd_cycles; 
			this->oddCycles(curr_v);
#ifdef DEBUG_LPCOLORING
			this->write_graph_dot(curr_v);
#endif

			uint32_t odd_cycle_cnt = m_odd_cycles.size();
			for(uint32_t m = 0; m < odd_cycle_cnt; m++) 
			{
				uint32_t cycle_len = m_odd_cycles[m].size();
				GRBLinExpr constraint1 = 0;
				GRBLinExpr constraint2 = 0;
				for(uint32_t n = 0; n < cycle_len - 1; n++) 
				{
#ifdef ASSERT_LPCOLORING
					assert(m_vertex_map.find(m_odd_cycles[m][n]) != m_vertex_map.end());
#endif
					uint32_t vi_index = m_vertex_map[m_odd_cycles[m][n]];
					constraint1 += coloringBits[2*vi_index];
					constraint2 += coloringBits[2*vi_index+1];

					////non_integer nodes already handled
					for(uint32_t x = 0; x < COLORING_BITS; x++) 
					{
						non_integer_flag[vi_index*COLORING_BITS + x] = false;
					}//end for x
				}//end for
				opt_model.addConstr(constraint1 >= 1);
				opt_model.addConstr(constraint2 >= 1);
			}//end for m
			//for(uint32_t m = 0; m < COLORING_BITS; m++) 
			//{
			//  non_integer_flag[vertex_index*COLORING_BITS + m] = false;
			//}
		}//end for k

		//optimize the new model
		opt_model.optimize();
		optim_status = opt_model.get(GRB_IntAttr_Status);
		if(optim_status == GRB_INFEASIBLE) 
		{
			cout << "ERROR: the model is infeasible... EXIT" << endl;
			exit(1);
		}
		cout << endl;

		//no more non-integers are removed 
		uint32_t non_integer_num_updated, half_integer_num_updated;
		pair = this->nonIntegerNum(coloringBits, vEdgeBit);
		non_integer_num_updated = pair.first;
		half_integer_num_updated = pair.second;

		if (non_integer_num_updated == 0 || 
				(non_integer_num_updated >= non_integer_num && half_integer_num_updated >= half_integer_num)) break;
	}//end while

	//store the lp coloring results 
	m_lp_coloring.clear();
	m_lp_coloring.reserve(coloring_bits_num);
	for(uint32_t k = 0; k < coloring_bits_num; k++) 
	{
		double value = coloringBits[k].get(GRB_DoubleAttr_X);
		m_lp_coloring.push_back(value);
	}

	//the last round of ILP 
	//this->ILPColoring(opt_model, coloringBits);
	//rounding the coloring results
	this->roundingColoring(coloringBits);

	this->conflictNum();
	this->write_graph_color();
#ifdef DEBUG_LPCOLORING
	this->write_graph_dot();
#endif

}//end coloring

//ILP based coloring
template<typename GraphType>
void LPColoring<GraphType>::ILPColoring(GRBModel& opt_model, vector<GRBVar>& coloringBits) 
{
	uint32_t variable_cnt = coloringBits.size();
	for(uint32_t k = 0; k < variable_cnt; k++) 
	{
		double value = coloringBits[k].get(GRB_DoubleAttr_X);
		if(value == 0.0 || value == 1.0) continue;
		//coloringBits[k].get(GRB_CharAttr);
	}//end for
	opt_model.update();

	//optimize model 
	opt_model.optimize();
	int optim_status = opt_model.get(GRB_IntAttr_Status);
	if(optim_status == GRB_INFEASIBLE) 
	{
		cout << "ERROR: The model is infeasible... EXIT" << endl;
		exit(1);
	}
	cout << endl;
	cout << "ILP solved to seek a coloring solution." << endl;

}

//greedy rounding scheme
template<typename GraphType>
void LPColoring<GraphType>::roundingColoring(vector<GRBVar>& coloringBits) 
{

	//greedy rounding scheme
	uint32_t vec_size = coloringBits.size();
	//the rounding results
	bool coloringBinary[vec_size];
	//the flag denoting whether current bit is rounded or not
	bool roundingFlag[vec_size]; 
	//rounding by range
	for(uint32_t k = 0; k < vec_size; k++) 
	{
		double value = coloringBits[k].get(GRB_DoubleAttr_X);
		if (0.0 <= value && value < 0.5) 
		{
			coloringBinary[k] = false;
			roundingFlag[k] = true;
		} 
		else if (0.5 < value && value <= 1.0) 
		{
			coloringBinary[k] = true;
			roundingFlag[k] = true;
		} 
		else 
		{
			coloringBinary[k] = false;
			roundingFlag[k] = false;
		}//end if 
	}//end for 

	//rounding of the half integer
	//greedy rounding schme should minimize the conflict number instead of random strategy
	//to be added later on
	for(uint32_t k = 0; k < vec_size; k++) 
	{
		if(true == roundingFlag[k]) continue;
#ifdef DEBUG_LPCOLORING
		//this->printBoolArray(roundingFlag, vec_size);
		//this->printBoolArray(coloringBinary, vec_size);
		//cout << endl << endl;
#endif
		//greedy rounding scheme 
		uint32_t vertex_index = k/COLORING_BITS;
		vector<bool> color_bits;
		color_bits.reserve(COLORING_BITS);
		vector<bool> best_bits;
		best_bits.reserve(COLORING_BITS);
		//initialize the color_bits
		for(uint32_t m = 0; m < COLORING_BITS; ++m) 
		{
			color_bits.push_back(coloringBinary[vertex_index*COLORING_BITS + m]);
		}//end for

		//get the neighbors
		typename boost::graph_traits<graph_type>::adjacency_iterator vi_begin, vi_end;
		BOOST_AUTO(vertex_key, m_inverse_vertex_map[vertex_index]);
		boost::tie(vi_begin, vi_end) = adjacent_vertices(vertex_key, m_graph);
		//calculate the current 
		uint32_t same_color_bound = std::numeric_limits<uint32_t>::max(); 
		uint32_t same_color_count = 0;
		uint32_t color = 0;
		uint32_t base = 1;
		while(true) 
		{
			same_color_bound = std::numeric_limits<uint32_t>::max();
			same_color_count = 0;
			color = 0;
			base = 1;
			for(uint32_t m = 0; m < COLORING_BITS; ++m) 
			{
				if(color_bits[m]) color = color + base;
				base = base<<2;
			}//end for
			//check the same color neighbors
			for(BOOST_AUTO(vi, vi_begin); vi != vi_end; ++vi) 
			{
				if(this->m_coloring.find(*vi) == m_vertex_map.end()) continue;
				if(this->m_coloring[*vi] == color) same_color_count++;
			}//end for
			//assign better color
			if(same_color_count < same_color_bound) 
			{
				same_color_bound = same_color_count;
				best_bits = color_bits;
			}

			//explore the next color_bits
			bool nextFlag = false;
			for(uint32_t m = 0; m < COLORING_BITS; ++m) 
			{
				if(color_bits[m] == false && roundingFlag[vertex_index*COLORING_BITS + m] == false) 
				{
					//flip the color bit that has not be rounded 
					color_bits[m] = true;
					nextFlag = true;
          break;
				}
			}//end for m
			//all the color_bits are explored
			if(nextFlag == false) break;
		}//end while

		//the vertex is colored
		color = 0;
		base = 1;
		for(uint32_t m = 0; m < COLORING_BITS; m++) 
		{
			coloringBinary[vertex_index*COLORING_BITS + m] = best_bits[m];
			roundingFlag[vertex_index*COLORING_BITS + m] = true;
			if(best_bits[m]) color = color + base;
			base = base<<1;
		}
#ifdef ASSERT_LPCOLORING
    assert(color < 4);
#endif
		this->m_coloring[vertex_key] = color;
	}//end for k

	//assign the coloring results 
	for(uint32_t k = 0; k < vec_size; k = k + COLORING_BITS) 
	{
		BOOST_AUTO(vertex_key, this->m_inverse_vertex_map[(k/COLORING_BITS)]);
		uint32_t color = 0;
		uint32_t base = 1;
		for(uint32_t m = 0; m < COLORING_BITS; ++m) 
		{
			if(coloringBinary[k + m]) color = color + base;
			base = base<<1;
		}//end for k
		if(this->m_coloring.find(vertex_key) == this->m_coloring.end())
			this->m_coloring[vertex_key] = color;
#ifdef ASSERT_LPCOLORING
		else { 
      //cout << "stored color-" << this->m_coloring[vertex_key] << " vs assigned color-" << color << endl;
			assert(this->m_coloring[vertex_key] == color);
    }
#endif
	}//end for 
}


//get the vertex color
template<typename GraphType>
uint32_t LPColoring<GraphType>::vertexColor(graph_vertex_type& node) const
{
	//the graph is not colored
	if(this->m_coloring.empty()) this->graphColoring(m_graph);
	return this->m_coloring.at(node);
}

//report the conflict number
template<typename GraphType>
uint32_t LPColoring<GraphType>::conflictNum() const
{
	//the graph is not colored
	if (this->m_coloring.empty()) return 0; //this->graphColoring();
	//check the coloring results
	uint32_t conflict_edge_num = 0;
	uint32_t conflict_num = 0;
	pair<typename graph_type::edge_iterator, typename graph_type::edge_iterator> edge_range = edges(m_graph);
	for(BOOST_AUTO(itr, edge_range.first); itr != edge_range.second; ++itr) 
	{
		BOOST_AUTO(w, m_edge_weight_map[*itr]);
		// skip stitch edges 
		if (w < 0) continue;
		BOOST_AUTO(from, source(*itr, m_graph));
		BOOST_AUTO(to, target(*itr, m_graph));
#ifdef ASSERT_LPCOLORING
		assert(this->m_coloring.find(from) != this->m_coloring.end());
		assert(this->m_coloring.find(to) != this->m_coloring.end());
#endif
		if(this->m_coloring.at(from) == this->m_coloring.at(to)) 
		{
			++conflict_num;
		}
		++conflict_edge_num;
	}//end for itr
	cout << "Conflict number: " << conflict_num << " out of " << conflict_edge_num << " conflict edges" << endl;
	return conflict_num;
}

//report the stitch number
template<typename GraphType>
uint32_t LPColoring<GraphType>::stitchNum() const
{
	//the graph is not colored
	if(this->m_coloring.empty()) this->graphColoring(m_graph);

	//check the coloring results
	uint32_t stitch_edge_num = 0;
	uint32_t stitch_num = 0;
	pair<typename graph_type::edge_iterator, typename graph_type::edge_iterator> edge_range = edges(m_graph);
	for(BOOST_AUTO(itr, edge_range.first); itr != edge_range.second; ++itr) 
	{
		BOOST_AUTO(w, m_edge_weight_map[*itr]);
		// skip conflict edges 
		if (w >= 0) continue;
		BOOST_AUTO(from, source(*itr, m_graph));
		BOOST_AUTO(to, target(*itr, m_graph));
#ifdef ASSERT_LPCOLORING
		assert(this->m_coloring.count(from));
		assert(this->m_coloring.count(to));
#endif
		if(this->m_coloring.at(from) != this->m_coloring.at(to)) 
		{
			++stitch_num;
		}
		++stitch_edge_num;
	}//end for itr
	cout << "Stitch number: " << stitch_num << " out of " << stitch_edge_num << " stitch edges" << endl;
	return stitch_num;
}

//for debug use
template<typename GraphType>
pair<uint32_t, uint32_t> LPColoring<GraphType>::nonIntegerNum(const vector<GRBVar>& coloringBits, const vector<GRBVar>& vEdgeBit) const
{
	uint32_t non_integer_num = 0;
	uint32_t half_num = 0;
	uint32_t vec_size = coloringBits.size();
	for(uint32_t k = 0; k < vec_size; k = k + COLORING_BITS) 
	{
		for(uint32_t m = 0; m < COLORING_BITS; m++) 
		{
			double value = coloringBits[k + m].get(GRB_DoubleAttr_X);
			if(value != 0.0 && value != 1.0) 
			{
				non_integer_num++;
				//break;
			}
			if(value == 0.5) half_num++;
      cout << k+m << "-" << value << " ";
		}
	}//end for k
  cout << endl;
	cout << "NonInteger count: " << non_integer_num << ", half integer count: " << half_num << ", out of " << vec_size << " vertex variable" << endl;

  uint32_t non_integer_num_edge = 0;
  uint32_t half_num_edge = 0;
  uint32_t conflict_num = 0;
  vec_size = vEdgeBit.size();
  for(uint32_t k = 0; k < vec_size; ++k) 
	{
		double value = vEdgeBit[k].get(GRB_DoubleAttr_X);
		if(value != 0.0 && value != 1.0) 
		{
			non_integer_num_edge++;
			//break;
		}
		if(value == 0.5) half_num_edge++;
    if(value == 1) conflict_num++;
    cout << k << "-" << value << " ";
	}//end for k
  cout << endl;
	cout << "NonInteger count: " << non_integer_num_edge << ", half integer count: " << half_num_edge << ", out of " << vec_size << " edge variable" << endl;
  cout << "conflict number: " << conflict_num << endl;
	return pair<uint32_t, uint32_t>(non_integer_num+non_integer_num_edge, half_num+half_num_edge);
}

template<typename GraphType>
void LPColoring<GraphType>::printBoolVec(vector<bool>& vec) const
{
	uint32_t vec_size = vec.size();
	for(uint32_t k = 0; k < vec_size; k++) 
	{
		//cout << k << "-" << vec[k] << "; ";
		cout << vec[k];
	}//end for 
	cout << endl;
}

template<typename GraphType>
void LPColoring<GraphType>::printBoolArray(bool* vec, uint32_t vec_size) const
{
	for(uint32_t k = 0; k < vec_size; k++) 
	{
		//cout << k << "-" << vec[k] << "; ";
		cout << vec[k];
	}//end for 
	cout << endl;
}

//print graphviz
template<typename GraphType>
void LPColoring<GraphType>::write_graph_dot(graph_vertex_type& v) const
{
#ifdef ASSERT_LPCOLORING
	//  assert(m_graph_ptr);
#endif
	//if(m_vertex_map.empty() || m_inverse_vertex_map.empty()) this->setMap();

	ofstream dot_file("../test/graph.dot");
	dot_file << "graph D { \n"
		<< "  randir = LR\n"
		<< "  size=\"4, 3\"\n"
		<< "  ratio=\"fill\"\n"
		<< "  edge[style=\"bold\"]\n" 
		<< "  node[shape=\"circle\"]\n";

	//output nodes 
	uint32_t vertex_num = num_vertices(m_graph);
	//check cycles
	bool inCycle[vertex_num];
	for(uint32_t k = 0; k < vertex_num; k++) inCycle[k] = false;
	uint32_t cycle_cnt = m_odd_cycles.size();
	for(uint32_t k = 0; k < cycle_cnt; k++) 
	{
		uint32_t cycle_len = m_odd_cycles[k].size();
		for(uint32_t m = 0; m < cycle_len; m++) 
		{
			uint32_t index = m_vertex_map.at(m_odd_cycles[k][m]);
			inCycle[index] = true;
		}
	}//end for k

#ifdef ASSERT_LPCOLORING
	assert(m_vertex_map.find(v) != m_vertex_map.end());
#endif
	uint32_t start_index = m_vertex_map.at(v);
	for(uint32_t k = 0; k < vertex_num; k++) 
	{
		if(k == start_index) dot_file << "  " << k << "[shape=\"square\"";
		else dot_file << "  " << k << "[shape=\"circle\"";
		//output coloring label
		dot_file << ",label=\"(" << m_lp_coloring[2*k] << "," << m_lp_coloring[2*k+1] << ")\"";
		if(inCycle[k]) dot_file << ",color=\"red\"]\n";
		else dot_file << "]\n";
	}//end for

	//output edges
	pair<typename graph_type::edge_iterator, typename graph_type::edge_iterator> edge_range = edges(m_graph);
	for(BOOST_AUTO(itr, edge_range.first); itr != edge_range.second; ++itr) 
	{
		BOOST_AUTO(from, source(*itr, m_graph));
		uint32_t f_ind = m_vertex_map.at(from);
		BOOST_AUTO(to, target(*itr, m_graph));
		uint32_t t_ind = m_vertex_map.at(to);
    bool conflict_flag = false;
    if(m_lp_coloring[2*f_ind] == m_lp_coloring[2*t_ind] && m_lp_coloring[2*f_ind+1] == m_lp_coloring[2*t_ind+1]) {
      conflict_flag = true;
    }//end if
		if (m_edge_weight_map[*itr] >= 0) // conflict edge 
    {
      if(conflict_flag)
			  dot_file << "  " << f_ind << "--" << t_ind << "[color=\"blue\",style=\"solid\"]\n";
      else 
			  dot_file << "  " << f_ind << "--" << t_ind << "[color=\"black\",style=\"solid\"]\n";
    }
		else // stitch edge 
			dot_file << "  " << f_ind << "--" << t_ind << "[color=\"black\",style=\"dashed\"]\n";
	}
	dot_file << "}";
	dot_file.close();
	system("dot -Tpdf ../test/graph.dot -o ../test/graph.pdf");
}

//print graphviz
template<typename GraphType>
void LPColoring<GraphType>::write_graph_dot() const
{
#ifdef ASSERT_LPCOLORING
	//  assert(m_graph_ptr);
#endif
	//if(m_vertex_map.empty() || m_inverse_vertex_map.empty()) this->setMap();

	ofstream dot_file("../test/graph.dot");
	dot_file << "graph D { \n"
		<< "  randir = LR\n"
		<< "  size=\"4, 3\"\n"
		<< "  ratio=\"fill\"\n"
		<< "  edge[style=\"bold\"]\n" 
		<< "  node[shape=\"circle\"]\n";

	//output nodes 
	uint32_t vertex_num = num_vertices(m_graph);
	for(uint32_t k = 0; k < vertex_num; k++) 
	{
		dot_file << "  " << k << "[shape=\"circle\"";
		//output coloring label
		dot_file << ",label=\"(" << m_lp_coloring[2*k] << "," << m_lp_coloring[2*k+1] << ")\"";
		dot_file << "]\n";
	}//end for

	//output edges
	pair<typename graph_type::edge_iterator, typename graph_type::edge_iterator> edge_range = edges(m_graph);
	for(BOOST_AUTO(itr, edge_range.first); itr != edge_range.second; ++itr) 
	{
		BOOST_AUTO(from, source(*itr, m_graph));
		uint32_t f_ind = m_vertex_map.at(from);
		BOOST_AUTO(to, target(*itr, m_graph));
		uint32_t t_ind = m_vertex_map.at(to);
    bool conflict_flag = false;
    if(m_lp_coloring[2*f_ind] == m_lp_coloring[2*t_ind] && m_lp_coloring[2*f_ind+1] == m_lp_coloring[2*t_ind+1]) {
      conflict_flag = true;
    }//end if
		if (m_edge_weight_map[*itr] >= 0) // conflict edge 
    {
      if(conflict_flag)
			  dot_file << "  " << f_ind << "--" << t_ind << "[color=\"red\",style=\"solid\"]\n";
      else 
			  dot_file << "  " << f_ind << "--" << t_ind << "[color=\"black\",style=\"solid\"]\n";
    }
		else // stitch edge 
			dot_file << "  " << f_ind << "--" << t_ind << "[color=\"black\",style=\"dashed\"]\n";
	}
	dot_file << "}";
	dot_file.close();
	system("dot -Tpdf ../test/graph.dot -o ../test/graph.pdf");
}



template<typename GraphType>
void LPColoring<GraphType>::write_graph_color() const
{
#ifdef ASSERT_LPCOLORING
	//  assert(m_graph_ptr);
#endif
	//if(m_vertex_map.empty() || m_inverse_vertex_map.empty()) this->setMap();
	ofstream dot_file("../test/color_graph.dot");
	dot_file << "graph D { \n"
		<< "  randir = LR\n"
		<< "  size=\"4, 3\"\n"
		<< "  ratio=\"fill\"\n"
		<< "  edge[style=\"bold\"]\n" 
		<< "  node[shape=\"circle\"]\n";

	//output nodes 
	uint32_t vertex_num = num_vertices(m_graph);
	//check cycles
	bool inCycle[vertex_num];
	for(uint32_t k = 0; k < vertex_num; k++) inCycle[k] = false;
	uint32_t cycle_cnt = m_odd_cycles.size();
	for(uint32_t k = 0; k < cycle_cnt; k++) 
	{
		uint32_t cycle_len = m_odd_cycles[k].size();
		for(uint32_t m = 0; m < cycle_len; m++) 
		{
			uint32_t index = m_vertex_map.at(m_odd_cycles[k][m]);
			inCycle[index] = true;
		}
	}//end for k

	for(uint32_t k = 0; k < vertex_num; k++) 
	{
		dot_file << "  " << k << "[shape=\"circle\"";
		//output coloring label
		dot_file << ",label=\"" << m_coloring.at(m_inverse_vertex_map.at(k)) << "\"";
		if(inCycle[k]) dot_file << ",color=\"red\"]\n";
		else dot_file << "]\n";
	}//end for

	//output edges
	pair<typename graph_type::edge_iterator, typename graph_type::edge_iterator> edge_range = edges(m_graph);
	for(BOOST_AUTO(itr, edge_range.first); itr != edge_range.second; ++itr) 
	{
		BOOST_AUTO(from, source(*itr, m_graph));
		uint32_t f_ind = m_vertex_map.at(from);
		BOOST_AUTO(to, target(*itr, m_graph));
		uint32_t t_ind = m_vertex_map.at(to);

		if (m_edge_weight_map[*itr] >= 0) // conflict edge 
		{
			if(m_coloring.at(from) != m_coloring.at(to)) 
				dot_file << "  " << f_ind << "--" << t_ind << "[color=\"black\",style=\"solid\"]\n";
			else 
				dot_file << "  " << f_ind << "--" << t_ind << "[color=\"blue\",style=\"solid\"]\n";
		}
		else // stitch edge 
		{
			if(m_coloring.at(from) == m_coloring.at(to)) 
				dot_file << "  " << f_ind << "--" << t_ind << "[color=\"black\",style=\"dashed\"]\n";
			else 
				dot_file << "  " << f_ind << "--" << t_ind << "[color=\"blue\",style=\"dashed\"]\n";
		}
	}
	dot_file << "}";
	dot_file.close();
	system("dot -Tpdf ../test/color_graph.dot -o ../test/color_graph.pdf");
}

}//end namespace coloring

}//end namespace algorithms

}//end namespace limbo

#endif
