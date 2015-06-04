/*************************************************************************
    > File Name: GraphSimplification.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Mon May 18 15:55:09 2015
 ************************************************************************/

#ifndef LIMBO_ALGORITHMS_GRAPHSIMPLIFICATION_H
#define LIMBO_ALGORITHMS_GRAPHSIMPLIFICATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include <set>
#include <deque>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/property_map/property_map.hpp>

namespace limbo { namespace algorithms { namespace coloring {

using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::string;
using std::map;
using std::set;
using std::deque;
using std::pair;
using std::make_pair;

template <typename GraphType>
class GraphSimplification
{
	public:
		typedef GraphType graph_type;
		typedef typename boost::graph_traits<graph_type>::vertex_descriptor graph_vertex_type;
		typedef typename boost::graph_traits<graph_type>::edge_descriptor graph_edge_type;
		typedef typename boost::graph_traits<graph_type>::vertex_iterator vertex_iterator;
		typedef typename boost::graph_traits<graph_type>::adjacency_iterator adjacency_iterator;
		typedef typename boost::graph_traits<graph_type>::edge_iterator edge_iterator;

		enum vertex_status_type {
			GOOD, // still in graph 
			HIDDEN, // vertex is hidden by simplification  
			MERGED // vertex is merged to other vertex 
		};
		/// constructor 
		GraphSimplification(graph_type const& g) 
			: m_graph (g)
			, m_vStatus(boost::num_vertices(g), GOOD)
			, m_vParent(boost::num_vertices(g))
			, m_vChildren(boost::num_vertices(g))
			, m_vHiddenVertex()
			, m_vComponent(boost::num_vertices(g), std::numeric_limits<uint32_t>::max())
			, m_sBridgeEdge()
			, m_vPrecolor(boost::num_vertices(g), -1)
		{
			graph_vertex_type v = 0; 
			for (typename vector<graph_vertex_type>::iterator it = m_vParent.begin(); it != m_vParent.end(); ++it, ++v)
				(*it) = v;
			v = 0;
			for (typename vector<vector<graph_vertex_type> >::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it, ++v)
				it->push_back(v);
#ifdef DEBUG_GRAPHSIMPLIFICATION
			assert(m_vParent.size() == boost::num_vertices(m_graph));
			assert(m_vChildren.size() == boost::num_vertices(m_graph));
#endif
		}
		/// copy constructor is not allowed 
		GraphSimplification(GraphSimplification const& rhs);

		template <typename Iterator>
		void precolor(Iterator first, Iterator last)
		{
			m_vPrecolor.assign(first, last);
#ifdef DEBUG_GRAPHSIMPLIFICATION
			assert(m_vPrecolor.size() == boost::num_vertices(m_graph));
#endif
		}

		vector<vertex_status_type> const& status() const {return m_vStatus;}
		vector<graph_vertex_type> const& parents() const {return m_vParent;}
		vector<vector<graph_vertex_type> > const& children() const {return m_vChildren;}
		stack<graph_vertex_type> const& hidden_vertices() const {return m_vHiddenVertex;}

		/// \return simplified graph and a map from merged graph vertices to original graph vertices 
		pair<graph_type, map<graph_vertex_type, graph_vertex_type> > simplified_graph() const; 

		/// for a structure of K4 with one fewer edge 
		/// suppose we have 4 vertices 1, 2, 3, 4
		/// 1--2, 1--3, 2--3, 2--4, 3--4, vertex 4 is merged to 1 
		/// this strategy only works for 3-coloring 
		/// it cannot guarantee minimal conflicts 
		/// but it can be used in a native conflict checker 
		void merge_subK4();

		/// \param color_num number of colors available 
		/// hide vertices whose degree is no larger than color_num-1
		void hide_small_degree(size_t color_num);
		/// find all bridge edges and divided graph into components  
		void remove_bridge();
		/// compute connected components 
		void connected_component();

		void write_graph_dot(string const& filename) const; 
		void write_simplified_graph_dot(string const& filename) const;
		
	protected:
		/// \return the root parent 
		/// i.e. the vertex that is not merged 
		graph_vertex_type parent(graph_vertex_type v) const 
		{
#ifdef DEBUG_GRAPHSIMPLIFICATION
			assert(!this->hidden(v));
#endif
			while (v != m_vParent.at(v))
				v = m_vParent.at(v);
			return v;
		}
		/// \return true if two vertices (parents) are connected by conflict edges 
		bool connected_conflict(graph_vertex_type v1, graph_vertex_type v2) const 
		{
			graph_vertex_type vp1 = this->parent(v1);
			graph_vertex_type vp2 = this->parent(v2);
			vector<graph_vertex_type> const& vChildren1 = m_vChildren.at(vp1);
			vector<graph_vertex_type> const& vChildren2 = m_vChildren.at(vp2);
			for (typename vector<graph_vertex_type>::const_iterator vic1 = vChildren1.begin(); vic1 != vChildren1.end(); ++vic1)
				for (typename vector<graph_vertex_type>::const_iterator vic2 = vChildren2.begin(); vic2 != vChildren2.end(); ++vic2)
				{
					pair<graph_edge_type, bool> e12 = boost::edge(*vic1, *vic2, m_graph);
					// only count conflict edge 
					if (e12.second && boost::get(boost::edge_weight, m_graph, e12.first) >= 0) return true;
				}
			return false;
		}
		/// \return true if two vertices (parents) are connected by stitch edges 
		bool connected_stitch(graph_vertex_type v1, graph_vertex_type v2) const 
		{
			graph_vertex_type vp1 = this->parent(v1);
			graph_vertex_type vp2 = this->parent(v2);
			vector<graph_vertex_type> const& vChildren1 = m_vChildren.at(vp1);
			vector<graph_vertex_type> const& vChildren2 = m_vChildren.at(vp2);
			for (typename vector<graph_vertex_type>::const_iterator vic1 = vChildren1.begin(); vic1 != vChildren1.end(); ++vic1)
				for (typename vector<graph_vertex_type>::const_iterator vic2 = vChildren2.begin(); vic2 != vChildren2.end(); ++vic2)
				{
					pair<graph_edge_type, bool> e12 = boost::edge(*vic1, *vic2, m_graph);
					// only count conflict edge 
					if (e12.second && boost::get(boost::edge_weight, m_graph, e12.first) < 0) return true;
				}
			return false;
		}
		/// \return the edge of two vertices (parents)
		pair<graph_edge_type, bool> connected_edge(graph_vertex_type v1, graph_vertex_type v2) const 
		{
			graph_vertex_type vp1 = this->parent(v1);
			graph_vertex_type vp2 = this->parent(v2);
			vector<graph_vertex_type> const& vChildren1 = m_vChildren.at(vp1);
			vector<graph_vertex_type> const& vChildren2 = m_vChildren.at(vp2);
			for (typename vector<graph_vertex_type>::const_iterator vic1 = vChildren1.begin(); vic1 != vChildren1.end(); ++vic1)
				for (typename vector<graph_vertex_type>::const_iterator vic2 = vChildren2.begin(); vic2 != vChildren2.end(); ++vic2)
				{
					pair<graph_edge_type, bool> e12 = boost::edge(*vic1, *vic2, m_graph);
					if (e12.second) return e12;
				}
			return make_pair(graph_edge_type(), false);
		}
		/// \return true if current vertex is merged 
		bool merged(graph_vertex_type v1) const 
		{
			bool flag = (m_vStatus.at(v1) == MERGED);
#ifdef DEBUG_GRAPHSIMPLIFICATION
			assert(flag == m_vChildren.at(v1).empty());
			if (!flag) assert(v1 == m_vParent.at(v1));
			else assert(v1 != m_vParent.at(v1));
#endif
			return flag;
		}
		/// \return true if current vertex is still in graph 
		bool good(graph_vertex_type v1) const 
		{
			return (m_vStatus.at(v1) == GOOD);
		}
		/// \return true if current vertex is hidden  
		bool hidden(graph_vertex_type v1) const 
		{
			return (m_vStatus.at(v1) == HIDDEN);
		}
		/// \return true if current vertex is precolored
		bool precolored(graph_vertex_type v1) const 
		{
			return (m_vPrecolor.at(v1) >= 0);
		}
		/// \return true if the edge is a bridge edge 
		bool bridge(graph_edge_type e) const 
		{
			return m_sBridgeEdge.count(e);
		}
		graph_type const& m_graph;
		vector<vertex_status_type> m_vStatus; ///< status of each vertex 
		vector<graph_vertex_type> m_vParent; ///< parent vertex of current vertex 
		vector<vector<graph_vertex_type> > m_vChildren; ///< children verices of current vertex, a vertex is the child of itself if it is not merged  
		stack<graph_vertex_type> m_vHiddenVertex; ///< a stack that keeps a reverse order of vertices hidden, useful for color recovery 
		vector<uint32_t> m_vComponent; ///< connected component id for each vertex 
		set<graph_edge_type> m_sBridgeEdge; ///< bridge edges that are removed during graph division 

		vector<int8_t> m_vPrecolor; ///< precolor information, if uncolored, set to -1
};

/// \return simplified graph and a map from merged graph vertices to original graph vertices 
template <typename GraphType>
pair<typename GraphSimplification<GraphType>::graph_type, map<typename GraphSimplification<GraphType>::graph_vertex_type, typename GraphSimplification<GraphType>::graph_vertex_type> > 
GraphSimplification<GraphType>::simplified_graph() const 
{
	size_t vertex_cnt = 0;
	map<graph_vertex_type, graph_vertex_type> mG2MG;
	map<graph_vertex_type, graph_vertex_type> mMG2G;
	vertex_iterator vi1, vie1;
	for (boost::tie(vi1, vie1) = boost::vertices(m_graph); vi1 != vie1; ++vi1)
	{
		graph_vertex_type v1 = *vi1;
		if (this->good(v1))
		{
			mG2MG[*vi1] = vertex_cnt;
			mMG2G[vertex_cnt] = v1;
			vertex_cnt += 1;
		}
	}
	graph_type mg (vertex_cnt);

	edge_iterator ei, eie;
	for (boost::tie(ei, eie) = boost::edges(m_graph); ei != eie; ++ei)
	{
		graph_edge_type e = *ei;
		graph_vertex_type s = boost::source(e, m_graph);
		graph_vertex_type t = boost::target(e, m_graph);
		// skip edge with hidden vertices  
		if (this->hidden(s) || this->hidden(t)) continue;

		graph_vertex_type sp = this->parent(s);
		graph_vertex_type tp = this->parent(t);

#ifdef DEBUG_GRAPHSIMPLIFICATION
		assert(mG2MG.count(sp));
		assert(mG2MG.count(tp));
#endif
		graph_vertex_type msp = mG2MG[sp];
		graph_vertex_type mtp = mG2MG[tp];
		pair<graph_edge_type, bool> emg = boost::edge(msp, mtp, mg);
		if (!emg.second)
		{
			emg = boost::add_edge(msp, mtp, mg);
			assert(emg.second);
			boost::put(boost::edge_weight, mg, emg.first, boost::get(boost::edge_weight, m_graph, e));
		}
		else 
		{
			// use cumulative weight 
			// this is to make sure we can still achieve small conflict number in the simplified graph 
			// no longer optimal if merge_subK4() is called 
			boost::put(
					boost::edge_weight, mg, emg.first, 
					boost::get(boost::edge_weight, mg, emg.first) + boost::get(boost::edge_weight, m_graph, e)
					);
		}
	}

	return make_pair(mg, mMG2G);
}

/// for a structure of K4 with one fewer edge 
/// suppose we have 4 vertices 1, 2, 3, 4
/// 1--2, 1--3, 2--3, 2--4, 3--4, vertex 4 is merged to 1 
/// this strategy only works for 3-coloring 
/// it cannot guarantee minimal conflicts 
/// but it can be used in a native conflict checker 
template <typename GraphType>
void GraphSimplification<GraphType>::merge_subK4()
{
	// when applying this function, be aware that other merging strategies may have already been applied 
	// so m_vParent is valid 
	//
	// merge iteratively 
	bool merge_flag; // true if merge occurs
	do 
	{
		merge_flag = false;
		// traverse the neighbors of vertex 1 to find connected vertex 2 and 3 
		vertex_iterator vi1, vie1;
		for (boost::tie(vi1, vie1) = boost::vertices(m_graph); vi1 != vie1; ++vi1)
		{
			graph_vertex_type v1 = *vi1;
			// only track good vertices 
			if (!this->good(v1)) continue;
			// find vertex 2 by searching the neighbors of vertex 1
			vector<graph_vertex_type> const& vChildren1 = m_vChildren.at(v1);
			for (typename vector<graph_vertex_type>::const_iterator vic1 = vChildren1.begin(); vic1 != vChildren1.end(); ++vic1)
			{
#ifdef DEBUG_GRAPHSIMPLIFICATION
				assert(vic1-vChildren1.begin() >= 0);
#endif
				graph_vertex_type vc1 = *vic1;
				adjacency_iterator vi2, vie2;
				for (boost::tie(vi2, vie2) = boost::adjacent_vertices(vc1, m_graph); vi2 != vie2; ++vi2)
				{
					// skip hidden vertex 
					if (this->hidden(*vi2)) continue;
					// skip stitch edges 
					pair<graph_edge_type, bool> e12 = boost::edge(vc1, *vi2, m_graph);
					assert(e12.second);
					if (boost::get(boost::edge_weight, m_graph, e12.first) < 0) continue;

					graph_vertex_type v2 = this->parent(*vi2);
					// find vertex 3 by searching the neighbors of vertex 2 
					vector<graph_vertex_type> const& vChildren2 = m_vChildren.at(v2);
					for (typename vector<graph_vertex_type>::const_iterator vic2 = vChildren2.begin(); vic2 != vChildren2.end(); ++vic2)
					{
						graph_vertex_type vc2 = *vic2;
						adjacency_iterator vi3, vie3;
						for (boost::tie(vi3, vie3) = boost::adjacent_vertices(vc2, m_graph); vi3 != vie3; ++vi3)
						{
							// skip hidden vertex 
							if (this->hidden(*vi3)) continue;
							// skip stitch edges 
							pair<graph_edge_type, bool> e23 = boost::edge(vc2, *vi3, m_graph);
							assert(e23.second);
							if (boost::get(boost::edge_weight, m_graph, e23.first) < 0) continue;

							graph_vertex_type v3 = this->parent(*vi3);
							// skip v1, v1 must be a parent  
							if (v3 == v1) continue;
							// only connected 1 and 3 are considered 
							if (!this->connected_conflict(v1, v3)) continue;

							// find vertex 4 by searching the neighbors of vertex 3  
							vector<graph_vertex_type> const& vChildren3 = m_vChildren.at(v3);
							for (typename vector<graph_vertex_type>::const_iterator vic3 = vChildren3.begin(); vic3 != vChildren3.end(); ++vic3)
							{
								graph_vertex_type vc3 = *vic3;
								adjacency_iterator vi4, vie4;
								for (boost::tie(vi4, vie4) = boost::adjacent_vertices(vc3, m_graph); vi4 != vie4; ++vi4)
								{
									// skip hidden vertex and skip precolored vertex  
									if (this->hidden(*vi4) || this->precolored(*vi4)) continue;
									// skip stitch edges 
									pair<graph_edge_type, bool> e34 = boost::edge(vc3, *vi4, m_graph);
									assert(e34.second);
									if (boost::get(boost::edge_weight, m_graph, e34.first) < 0) continue;

									graph_vertex_type v4 = this->parent(*vi4);
									// skip v1 or v2, v1 and v2 must be parent, and v4 must not be precolored
									if (v4 == v1 || v4 == v2 || this->precolored(v4)) continue;
									// vertex 2 and vertex 4 must be connected 
									// vertex 1 and vertex 4 must not be connected (K4)
									if (!this->connected_conflict(v2, v4) || this->connected_conflict(v1, v4)) continue;
									// merge vertex 4 to vertex 1 
									m_vStatus[v4] = MERGED;
									m_vChildren[v1].insert(m_vChildren[v1].end(), m_vChildren[v4].begin(), m_vChildren[v4].end());
									m_vChildren[v4].resize(0); // clear and shrink to fit 
									m_vParent[v4] = v1;
									merge_flag = true;
#ifdef DEBUG_GRAPHSIMPLIFICATION
									assert(m_vStatus[v1] == GOOD);
									//this->write_graph_dot("graph_simpl");
#endif
									break;
								}
								if (merge_flag) break;
							}
							if (merge_flag) break;
						}
						if (merge_flag) break;
					}
					if (merge_flag) break;
				}
				if (merge_flag) break;
			}
			if (merge_flag) break;
		}
	} while (merge_flag);
}

/// \param color_num number of colors available 
/// hide vertices whose degree is no larger than color_num-1
template <typename GraphType>
void GraphSimplification<GraphType>::hide_small_degree(size_t color_num)
{
	// when applying this function, be aware that other strategies may have already been applied 
	// make sure it is compatible 

	bool hide_flag;
	do 
	{
		hide_flag = false;
		// traverse the neighbors of vertex 1 to find connected vertex 2 and 3 
		vertex_iterator vi1, vie1;
		for (boost::tie(vi1, vie1) = boost::vertices(m_graph); vi1 != vie1; ++vi1)
		{
			graph_vertex_type v1 = *vi1;
			// only track good and uncolored vertices  
			if (!this->good(v1) || this->precolored(v1)) continue;
			size_t conflict_degree = 0;
			// find vertex 2 by searching the neighbors of vertex 1
			vector<graph_vertex_type> const& vChildren1 = m_vChildren.at(v1);
			for (typename vector<graph_vertex_type>::const_iterator vic1 = vChildren1.begin(); vic1 != vChildren1.end(); ++vic1)
			{
#ifdef DEBUG_GRAPHSIMPLIFICATION
				assert(vic1-vChildren1.begin() >= 0);
#endif
				graph_vertex_type vc1 = *vic1;
				adjacency_iterator vi2, vie2;
				for (boost::tie(vi2, vie2) = boost::adjacent_vertices(vc1, m_graph); vi2 != vie2; ++vi2)
				{
					// skip hidden vertex 
					if (this->hidden(*vi2)) continue;
					// skip stitch edges 
					pair<graph_edge_type, bool> e12 = boost::edge(vc1, *vi2, m_graph);
					assert(e12.second);
					if (boost::get(boost::edge_weight, m_graph, e12.first) < 0) continue;

					conflict_degree += 1;
				}
			}
			if (conflict_degree < color_num) // hide v1 
			{
				//m_vStatus[v1] = HIDDEN;
				m_vHiddenVertex.push(v1);
				hide_flag = true;
				// hide all the children of v1 
				// but no need to push them to the stack m_vHiddenVertex
				// v1 is also in its children 
				vector<graph_vertex_type> const& vChildren1 = m_vChildren.at(v1);
				for (typename vector<graph_vertex_type>::const_iterator vic1 = vChildren1.begin(); vic1 != vChildren1.end(); ++vic1)
					m_vStatus[*vic1] = HIDDEN;
#ifdef DEBUG_GRAPHSIMPLIFICATION
				cout << "stack +" << v1 << endl;
				assert(m_vStatus[v1] == HIDDEN);
#endif
				break;
			}
		}
	} while (hide_flag);
}

// refer to http://www.geeksforgeeks.org/bridge-in-a-graph/
// for the recursive implementation 
template <typename GraphType>
void GraphSimplification<GraphType>::remove_bridge()
{
	m_sBridgeEdge.clear();

	uint32_t vertex_num = boost::num_vertices(m_graph);
	stack<graph_vertex_type> vStack; // stack for dfs 
	// for speed instead of memory (no bool)
	deque<bool> vVisited (vertex_num, false); 
	vector<graph_vertex_type> vParent (vertex_num); 
	// vLow[u] = min(vDisc[u], vDisc[w]), where w is an ancestor of u
	// there is a back edge from some descendant of u to w
	vector<uint32_t> vLow (vertex_num, std::numeric_limits<uint32_t>::max()); // lowest vertex reachable from subtree under v  
	vector<uint32_t> vDisc(vertex_num, std::numeric_limits<uint32_t>::max()); // discovery time 
	uint32_t visit_time = 0;

	// set initial parent of current vertex to itself 
	vertex_iterator vi, vie;
	for (boost::tie(vi, vie) = boost::vertices(m_graph); vi != vie; ++vi)
		vParent[*vi] = *vi;

	// similar to pre-order dfs  
	for (boost::tie(vi, vie) = boost::vertices(m_graph); vi != vie; ++vi)
	{
		graph_vertex_type source = *vi;
		// only consider good vertex 
		if (!this->good(source)) continue;
		// skip visited vertex 
		if (vVisited[source]) continue; 
		vStack.push(source);
		vVisited[source] = true;
		while (!vStack.empty())
		{
			graph_vertex_type v = vStack.top();
			vStack.pop();
			assert(this->good(v));

			vLow[v] = vDisc[v] = visit_time++;

#ifdef DEBUG_GRAPHSIMPLIFICATION
			cout << v << " ";
#endif

			// find neighbors of all merged vertices
			vector<graph_vertex_type> const& vChildren = m_vChildren.at(v);
			for (typename vector<graph_vertex_type>::const_iterator vic = vChildren.begin(); vic != vChildren.end(); ++vic)
			{
				graph_vertex_type vc = *vic;
				// skip hidden vertex 
				if (this->hidden(vc)) continue;
				adjacency_iterator ui, uie;
				for (boost::tie(ui, uie) = boost::adjacent_vertices(vc, m_graph); ui != uie; ++ui)
				{
					graph_vertex_type uc = *ui;
					// skip hidden vertex 
					if (this->hidden(uc)) continue;

					graph_vertex_type u = this->parent(uc);
					assert(this->good(u));

					// visited vertex and popped vertex to find parent vertex 
					// in order to keep the same parent as recursive implementation 
					if (vVisited[u] && vDisc[u] < std::numeric_limits<uint32_t>::max()) 
					{
						if (vParent[v] == v || vDisc[u] > vDisc[vParent[v]])
							vParent[v] = u;
					}
				}
			}
			// find neighbors of all merged vertices
			for (typename vector<graph_vertex_type>::const_iterator vic = vChildren.begin(); vic != vChildren.end(); ++vic)
			{
				graph_vertex_type vc = *vic;
				// skip hidden vertex 
				if (this->hidden(vc)) continue;
				adjacency_iterator ui, uie;
				for (boost::tie(ui, uie) = boost::adjacent_vertices(vc, m_graph); ui != uie; ++ui)
				{
					graph_vertex_type uc = *ui;
					// skip hidden vertex 
					if (this->hidden(uc)) continue;

					graph_vertex_type u = this->parent(uc);
					assert(this->good(u));

					if (!vVisited[u]) // non-visited vertex 
					{
						vStack.push(u);
						vVisited[u] = true;
					}
					else if (u != vParent[v]) // Update low value of v for parent function calls.
						vLow[v] = std::min(vLow[v], vDisc[u]);
				}
			}
		}
	}
#ifdef DEBUG_GRAPHSIMPLIFICATION
	cout << endl;
	for (boost::tie(vi, vie) = boost::vertices(m_graph); vi != vie; ++vi)
		if (vParent[*vi] != *vi)
			assert(vDisc[vParent[*vi]] < vDisc[*vi]);
#endif
	// similar to post-order dfs traversal (a little bit different from the order of tree post-order traversal)
	std::fill(vVisited.begin(), vVisited.end(), false);
	vector<graph_vertex_type> vDiscOrder (vertex_num, std::numeric_limits<uint32_t>::max());
	for (boost::tie(vi, vie) = boost::vertices(m_graph); vi != vie; ++vi)
		if (this->good(*vi))
			vDiscOrder[vDisc[*vi]] = *vi;
	for (typename vector<graph_vertex_type>::const_reverse_iterator it = vDiscOrder.rbegin(); it != vDiscOrder.rend(); ++it)
	{
		graph_vertex_type v = *it;
		if (v >= std::numeric_limits<uint32_t>::max()) continue;
		if (!this->good(v)) continue;

		// find neighbors of all merged vertices
		vector<graph_vertex_type> const& vChildren = m_vChildren.at(v);
		for (typename vector<graph_vertex_type>::const_iterator vic = vChildren.begin(); vic != vChildren.end(); ++vic)
		{
			graph_vertex_type vc = *vic;
			// skip hidden vertex 
			if (this->hidden(vc)) continue;

			adjacency_iterator ui, uie;
			for (boost::tie(ui, uie) = boost::adjacent_vertices(vc, m_graph); ui != uie; ++ui)
			{
				graph_vertex_type uc = *ui;
				// skip hidden vertex 
				if (this->hidden(uc)) continue;

				graph_vertex_type u = this->parent(uc);
				assert(this->good(u));

//				if (!vVisited[u]) // non-visited vertex 
				{
					vVisited[u] = true;
					if (vParent[v] != u)
						vLow[v] = std::min(vLow[v], vLow[u]);
					// If the lowest vertex reachable from subtree under u is 
					// below v in DFS tree, then v-u is a bridge
					if (vLow[u] > vDisc[v])
					{
						assert(this->good(v) && this->good(u));
						pair<graph_edge_type, bool> e = this->connected_edge(v, u);
						assert(e.second);
						assert(m_sBridgeEdge.insert(e.first).second);
#ifdef DEBUG_GRAPHSIMPLIFICATION
						//							if (std::min(v, u) == 5 && std::max(v, u) == 86)
						//								cout << "stop" << endl;
						//							cout << "+ bridge (" << boost::source(e.first, m_graph) << ", " << boost::target(e.first, m_graph) << ")" << endl;
#endif
					}
				}
			}
		}
#ifdef DEBUG_GRAPHSIMPLIFICATION
		cout << v << " ";
#endif
	}
#if 0
	// similar to post-order dfs traversal (a little bit different from the order of tree post-order traversal)
	std::fill(vVisited.begin(), vVisited.end(), false);
	for (boost::tie(vi, vie) = boost::vertices(m_graph); vi != vie; ++vi)
	{
		graph_vertex_type source = *vi;
		// only consider good vertex 
		if (!this->good(source)) continue;
		// skip visited vertex 
		if (vVisited[source]) continue; 
		vStack.push(source);
		vVisited[source] = true;
		while (!vStack.empty())
		{
			graph_vertex_type v = vStack.top();
			//vStack.pop();

			bool hasUnvisitedChild = false;
			// find neighbors of all merged vertices
			vector<graph_vertex_type> const& vChildren = m_vChildren.at(v);
			for (typename vector<graph_vertex_type>::const_iterator vic = vChildren.begin(); vic != vChildren.end(); ++vic)
			{
				graph_vertex_type vc = *vic;
				// skip hidden vertex 
				if (this->hidden(vc)) continue;

				adjacency_iterator ui, uie;
				for (boost::tie(ui, uie) = boost::adjacent_vertices(vc, m_graph); ui != uie; ++ui)
				{
					graph_vertex_type uc = *ui;
					// skip hidden vertex 
					if (this->hidden(uc)) continue;

					graph_vertex_type u = this->parent(uc);
					assert(this->good(u));

					if (!vVisited[u]) // non-visited vertex 
					{
						vStack.push(u);
						vVisited[u] = true;
						hasUnvisitedChild = true;
						vLow[v] = std::min(vLow[v], vLow[u]);
						// If the lowest vertex reachable from subtree under u is 
						// below v in DFS tree, then v-u is a bridge
						if (vLow[u] > vDisc[v])
						{
							assert(this->good(v) && this->good(u));
							pair<graph_edge_type, bool> e = this->connected_edge(v, u);
							assert(e.second);
							assert(m_sBridgeEdge.insert(e.first).second);
#ifdef DEBUG_GRAPHSIMPLIFICATION
//							if (std::min(v, u) == 5 && std::max(v, u) == 86)
//								cout << "stop" << endl;
//							cout << "+ bridge (" << boost::source(e.first, m_graph) << ", " << boost::target(e.first, m_graph) << ")" << endl;
#endif
						}
					}
				}
			}
			if (!hasUnvisitedChild)
			{
#ifdef DEBUG_GRAPHSIMPLIFICATION
				cout << v << " ";
#endif
				vStack.pop();
			}
		}
	}
#endif
#ifdef DEBUG_GRAPHSIMPLIFICATION
	cout << endl;
	for (typename set<graph_edge_type>::const_iterator it = m_sBridgeEdge.begin(); it != m_sBridgeEdge.end(); ++it)
	{
		graph_edge_type e = *it;
		cout << "+ bridge (" << boost::source(e, m_graph) << ", " << boost::target(e, m_graph) << ")" << endl;
	}
#endif
}

template <typename GraphType>
void GraphSimplification<GraphType>::connected_component() 
{
	// we only need to filter out hidden vertices and bridges 
	// merged vertices are not a problem because they are initially connected with their parents 

	uint32_t vertex_num = boost::num_vertices(m_graph);
	stack<graph_vertex_type> vStack; // stack for dfs 
	// for speed instead of memory (no bool)
	deque<bool> vVisited (vertex_num, false); 
	uint32_t comp_id = 0;

	assert(m_vComponent.size() == vertex_num);
	std::fill(m_vComponent.begin(), m_vComponent.end(), 0);

	// set initial parent of current vertex to itself 
	vertex_iterator vi, vie;
	for (boost::tie(vi, vie) = boost::vertices(m_graph); vi != vie; ++vi)
	{
		graph_vertex_type source = *vi;
		// skip visited vertex 
		if (vVisited[source]) continue; 
		if (this->hidden(source)) continue;
		vStack.push(source);
		vVisited[source] = true;
		while (!vStack.empty())
		{
			graph_vertex_type v = vStack.top();
			vStack.pop();

			m_vComponent[v] = comp_id; // set component id 

			adjacency_iterator ui, uie;
			for (boost::tie(ui, uie) = boost::adjacent_vertices(v, m_graph); ui != uie; ++ui)
			{
				graph_vertex_type u = *ui;
				if (this->hidden(u)) continue;
				pair<graph_edge_type, bool> e = boost::edge(u, v, m_graph);
				assert(e.second);
				// skip bridge edges 
				if (this->bridge(e.first)) continue;

				if (!vVisited[u]) // non-visited vertex 
				{
					vStack.push(u);
					vVisited[u] = true;
				}
			}
		}
		comp_id += 1;
	}
}

template <typename GraphType>
void GraphSimplification<GraphType>::write_graph_dot(string const& filename) const 
{
	std::ofstream dot_file((filename+".dot").c_str());
	dot_file << "graph D { \n"
		<< "  randir = LR\n"
		<< "  size=\"4, 3\"\n"
		<< "  ratio=\"fill\"\n"
		<< "  edge[style=\"bold\",fontsize=200]\n" 
		<< "  node[shape=\"circle\",fontsize=200]\n";

	//output nodes 
	vertex_iterator vi1, vie1;
	for (boost::tie(vi1, vie1) = boost::vertices(m_graph); vi1 != vie1; ++vi1)
	{
		graph_vertex_type v1 = *vi1;
		if (!this->good(v1)) continue;

		dot_file << "  " << v1 << "[shape=\"circle\"";
		//output coloring label
		dot_file << ",label=\"" << v1 << ":(";
		for (typename vector<graph_vertex_type>::const_iterator it1 = m_vChildren[v1].begin(); it1 != m_vChildren[v1].end(); ++it1)
		{
			if (it1 != m_vChildren[v1].begin())
				dot_file << ",";
			dot_file << *it1;
		}
		dot_file << ")";
		if (this->good(v1) && m_vComponent[v1] < std::numeric_limits<uint32_t>::max())
			dot_file << ":" << m_vComponent[v1];
		dot_file << "\"";
		dot_file << "]\n";
	}

	//output edges
	for (boost::tie(vi1, vie1) = boost::vertices(m_graph); vi1 != vie1; ++vi1)
	{
		graph_vertex_type v1 = *vi1;
		if (!this->good(v1)) continue;

		vertex_iterator vi2, vie2;
		for (boost::tie(vi2, vie2) = boost::vertices(m_graph); vi2 != vie2; ++vi2)
		{
			graph_vertex_type v2 = *vi2;
			if (!this->good(v2)) continue;
			if (v1 >= v2) continue;

			pair<graph_edge_type, bool> e = this->connected_edge(v1, v2);
			if (e.second)
			{
#ifdef DEBUG_GRAPHSIMPLIFICATION
//				if (v1 == uint32_t(3)) 
//					cout << "stop\n";
#endif
				// if two hyper vertices are connected by conflict edges, 
				// there is no need to consider stitch edges 
				if (this->connected_conflict(v1, v2)) 
					dot_file << "  " << v1 << "--" << v2 << "[color=\"black\",style=\"solid\",penwidth=3]\n";
				else if (this->connected_stitch(v1, v2))
					dot_file << "  " << v1 << "--" << v2 << "[color=\"black\",style=\"dashed\",penwidth=3]\n";
				// virtual connection showing that a bridge exists
				dot_file << " " << v1 << "--" << v2 << "[color=\"black\",style=\"dotted\",penwidth=1]\n";
			}
		}
	}
	dot_file << "}";
	dot_file.close();

	char buf[256];
	sprintf(buf, "dot -Tpdf %s.dot -o %s.pdf", filename.c_str(), filename.c_str());
	system(buf);
}
template <typename GraphType>
void GraphSimplification<GraphType>::write_simplified_graph_dot(string const& filename) const
{
	std::ofstream dot_file((filename+".dot").c_str());
	dot_file << "graph D { \n"
		<< "  randir = LR\n"
		<< "  size=\"4, 3\"\n"
		<< "  ratio=\"fill\"\n"
		<< "  edge[style=\"bold\",fontsize=200]\n" 
		<< "  node[shape=\"circle\",fontsize=200]\n";

	// get merged graph 
	pair<graph_type, map<graph_vertex_type, graph_vertex_type> > mg = this->simplified_graph();
	//output nodes 
	vertex_iterator vi1, vie1;
	for (boost::tie(vi1, vie1) = boost::vertices(mg.first); vi1 != vie1; ++vi1)
	{
		graph_vertex_type mv1 = *vi1;
		graph_vertex_type v1 = mg.second[mv1];
		if (m_vChildren[v1].empty()) continue;

		dot_file << "  " << mv1 << "[shape=\"circle\"";
		//output coloring label
		dot_file << ",label=\"" << mv1 << ":(";
		for (typename vector<graph_vertex_type>::const_iterator it1 = m_vChildren[v1].begin(); it1 != m_vChildren[v1].end(); ++it1)
		{
			if (it1 != m_vChildren[v1].begin())
				dot_file << ",";
			dot_file << *it1;
		}
		dot_file << ")\"";
		dot_file << "]\n";
	}

	//output edges
	edge_iterator ei, eie;
	for (boost::tie(ei, eie) = boost::edges(mg.first); ei != eie; ++ei)
	{
		graph_edge_type e = *ei;
		graph_vertex_type mv1 = boost::source(e, mg.first);
		graph_vertex_type mv2 = boost::target(e, mg.first);
		int32_t w = boost::get(boost::edge_weight, mg.first, e);

		char buf[256];
		if (w >= 0)
			sprintf(buf, "  %lu--%lu[label=%d,color=\"black\",style=\"solid\",penwidth=3]", mv1, mv2, w);
		else 
			sprintf(buf, "  %lu--%lu[label=%d,color=\"black\",style=\"dashed\",penwidth=3]", mv1, mv2, w);
		dot_file << buf << endl;
	}
	dot_file << "}";
	dot_file.close();

	char buf[256];
	sprintf(buf, "dot -Tpdf %s.dot -o %s.pdf", filename.c_str(), filename.c_str());
	system(buf);
}

}}} // namespace limbo // namespace algorithms // namespace coloring 

#endif
