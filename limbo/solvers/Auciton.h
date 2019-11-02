#ifndef LIMBO_SOLVERS_MINCOSTFLOW_AUCTION_H
#define LIMBO_SOLVERS_MINCOSTFLOW_AUCTION_H
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <lemon/core.h>
//#include <lemon/list_graph.h>
#include <lemon/math.h>
//#include <lemon/concepts/digraph.h>
//#include <lemon/smart_graph.h>
//#include <lemon/cost_scaling.h>
//#include <lemon/capacity_scaling.h>
//#include <lemon/cycle_canceling.h>
#include <lemon/lgf_writer.h>
#ifndef AUCTION_DEBUG
#define AUCTION_DEBUG 1	

#endif
namespace MyAuction {
	template <typename GR, typename V = int, typename C = V>
	class AuctionAlgrithm
	{
		public:
			typedef V Value;
			typedef C Cost;
			const Value MAX;
			const Value INF;
		    enum ProblemType {
				INFEASIBLE,
        	    OPTIMAL,
				UNBOUNDED
		    };
			
			/// \brief construction algorithm

			AuctionAlgrithm(const GR& graph, int epsilon = 1)
				:_graph(graph), _node_id(graph), _arc_id(graph),
				_epsilon(epsilon), 
				MAX(std::numeric_limits<Value>::max()),
				INF(std::numeric_limits<Value>::has_infinity ?
						std::numeric_limits<Value>::infinity() : MAX)
			{
				// Check the number types
				LEMON_ASSERT(std::numeric_limits<Value>::is_signed,
						"The flow type of NetworkSimplex must be signed");
				LEMON_ASSERT(std::numeric_limits<Cost>::is_signed,
						"The cost type of NetworkSimplex must be signed");

				// Reset data structures
				reset();
			}

			/// \brief reset private variable with __graph
			/// set _node_num with number of node
			/// set 

			AuctionAlgrithm& reset(){
				_node_num = countNodes(_graph);
				_arc_num = countArcs(_graph);
				int max_arc_num = _node_num*_node_num;
		
				_source.resize(_arc_num);
				_target.resize(_arc_num);

				_supply.resize(_node_num);
				_price.resize(_node_num);
				_flow.resize(max_arc_num);
				_lower.resize(max_arc_num);
				_upper.resize(max_arc_num);
				_cost.resize(max_arc_num);

				int i = 0;
				for(typename GR::NodeIt n(_graph); n !=	lemon::INVALID; ++n, ++i){
					_node_id[n] = i;
				}
		
				i = 0;
				for(typename GR ::ArcIt a(_graph); a != lemon::INVALID; ++a, ++i){
					_arc_id[a] = i;
					_source[i] = _node_id[_graph.source(a)];
					_target[i] = _node_id[_graph.target(a)];
				}

				resetParams();
				return *this;
			}
			AuctionAlgrithm& resetParams(){      
				#ifndef AUCTION_DEBUG
				std::cout << "Auction ResetParams\n";
				#endif

				for (int i = 0; i != _node_num; ++i) {
					_supply[i] = 0;
				}
				for (int j = 0; j != _arc_num; ++j) {
			        _lower[j] = 0;
			        _upper[j] = INF;
			        _cost[j] = -1;
				}
			    return *this;
			}
			
			template <typename LowerMap>
			AuctionAlgrithm& lowerMap(const LowerMap& map){
				for(typename GR::ArcIt a(_graph); a != lemon::INVALID; ++a){
					_lower[_arc_id[a]] = map[a];
				}
				return *this;
			}

			template <typename UpperMap>
			AuctionAlgrithm& upperMap(const UpperMap& map){
				for(typename GR::ArcIt a(_graph); a != lemon::INVALID; ++a){
					_upper[_arc_id[a]] = map[a];
				}
				return *this;
			}

			template <typename CostMap>
			AuctionAlgrithm& costMap(const CostMap& map){
				for(typename GR::ArcIt a(_graph); a != lemon::INVALID; ++a){
					_cost[_arc_id[a]] = map[a];
				}
				return *this;
			}

			template <typename SupplyMap>
			AuctionAlgrithm& supplyMap(const SupplyMap& map){
				for(typename GR::NodeIt n(_graph); n != lemon::INVALID; ++n){
					_supply[_node_id[n]] = map[n];
				}
				return *this;
			}

			
			void myaprintGraph(){
				int* fgraph = new int[_node_num*_node_num];
				memset(fgraph,0,sizeof(int)*_node_num*_node_num);
				//print cost of edge;
				for(int i = 0; i < _arc_num; i++){
					fgraph[_source[i]*_node_num + _target[i]] = _cost[i];
				}
				std::cout << "*************************\n"
					<< "cost of Edge, sourse to target\n"
					<< "*************************\n";
				for(int i = 0; i < _node_num; i++){
					for(int j = 0; j < _node_num; j++){
						std::cout << fgraph[i*_node_num + j] << "  \t";
					}
					std::cout << std::endl;
				}
				//print bound of edge;
				//memset(fgraph,0,sizeof(int)*_node_num*_node_num);
				for(int i = 0; i < _arc_num; i++){
					fgraph[_source[i]*_node_num + _target[i]] = _upper[i];
				}
				std::cout << "*************************\n"
					<< "bound of Edge, sourse to target\n"
					<< "*************************\n";
				for(int i = 0; i < _node_num; i++){
					for(int j = 0; j < _node_num; j++){
						std::cout << fgraph[i*_node_num + j] << "  \t";
					}
					std::cout << std::endl;
				}



			}



			ProblemType run(int m_epsilon){
				_epsilon = m_epsilon;
				std::cout << "***************" << "some varible:\n" 
					<< "* num of node: " << _node_num << std::endl
					<< "* num of edge: " << _arc_num << std::endl
					<< "***********************";
				std::cout << "print cost graph!!\n";
				
				myaprintGraph();


				std::cout << "run_ not success!!\n";
				return OPTIMAL;
			}


			Cost totalCost() const {
				return totalCost<Cost>();
			}

			/// \brief Return the total cost of the found flow
			///
			/// Its complexity is O(Edge)

			template <typename Number>
			Number totalCost() const {
				Number c = 0;
				for(typename GR::ArcIt a(_graph); a != lemon::INVALID; ++a){
					int i = _arc_id[a];
					c += Number(_flow[i]) * Number(_cost[i]);
				}
				return c;
			}


		private:
			/// \brief
			/// 

			TEMPLATE_DIGRAPH_TYPEDEFS(GR);

			typedef std::vector<Value> ValueVector;
			typedef std::vector<Cost> CostVector;
			typedef std::vector<int> IntVector;

			const GR & _graph;

			int _node_num;
			int _arc_num;

			/// _node

			IntNodeMap _node_id;
			IntArcMap _arc_id;

			IntVector _source;
			IntVector _target;

			ValueVector _supply;	//1
			CostVector _price;			//1
			ValueVector _flow;			//2
			ValueVector _lower;			//2
			ValueVector _upper;			//2
			CostVector _cost;			//2
			

			int _epsilon;
	};

}
#endif
