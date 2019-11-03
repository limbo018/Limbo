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
		
				_source.resize(_arc_num, 0);
				_target.resize(_arc_num, 0);

				_supply.resize(_node_num, 0);
				_grow.resize(_node_num, 0);
				_price.resize(_node_num, 0);
				_flow.resize(max_arc_num, 0);
				_lower.resize(max_arc_num, 0);
				_upper.resize(max_arc_num, 0);
				_cost.resize(max_arc_num, 0);

				int i = 0;
#if AUCTION_DEBUG
				std::cout << "********in function Auction.h/reset()*********\n";
#endif
				for(typename GR::NodeIt n(_graph); n !=	lemon::INVALID; ++n, ++i){
					_node_id[n] = i;
#if AUCTION_DEBUG
					std::cout << "node_id: " << i << std::endl;
#endif
				}
#if AUCTION_DEBUG
				std::cout << "*****************\n";
#endif
		
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
				#if AUCTION_DEBUG
				std::cout << "Auction ResetParams\n";
				#endif

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
					_cost[_arc_id[a]] = map[a]*(_node_num-1);
				}
				return *this;
			}

			template <typename SupplyMap>
			AuctionAlgrithm& supplyMap(const SupplyMap& map){
				for(typename GR::NodeIt n(_graph); n != lemon::INVALID; ++n){
					_supply[_node_id[n]] = map[n];
					_grow[_node_id[n]] = map[n];
				}
				return *this;
			}

			
			void myaprintGraph(){
				int* fgraph = new int[_node_num*_node_num];
				memset(fgraph,0,sizeof(int)*_node_num*_node_num);
				//print cost of edge;
				std::cout << "******************\n"
					<< "node_num:" << _node_num << "*  edge_num" << _arc_num
					<< "******************\n";
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

		private:
			int pushEdge(){
				int fpoCount = 0;
				int fnaCount = 0;
				//edge id
				IntVector pushListPo;
				IntVector pushListNa;
				//遍历 edge
				for(int i = 0; i < _arc_num; i++){
					if(_price[_source[i]] == _price[_target[i]] + _cost[i] + _epsilon){
						pushListPo.push_back(i);
						continue;
					}
					if(_price[_target[i]] == _price[_source[i]] - _cost[i] + _epsilon){
						pushListNa.push_back(i);
					}				
				}
				int fId;//edge id
				Value fdelta;
				int fpoSize = pushListPo.size();
				int fnaSize = pushListNa.size();
				for(int i = 0;i < fpoSize; i++){
					fId = pushListPo[i];
					fdelta = std::min(_grow[_source[fId]], _upper[fId] - _flow[fId]);
					_flow[fId] += fdelta;
					_grow[_source[fId]] -= fdelta;
					_grow[_target[fId]] += fdelta;
				}

				for(int i = 0; i < fnaSize; i++){
					fId = pushListNa[i];
					fdelta = std::min(_grow[_target[fId]], _flow[fId] - _lower[fId]);
					_flow[fId] -= fdelta;
					_grow[_target[fId]] -= fdelta;
					_grow[_source[fId]] += fdelta;
				}

				return 0;
			}

			int priceRise(){
				//node id
				std::vector<bool> frisePriceId;
				frisePriceId.resize(_node_num, false);
				Cost minRise = INF;
				for(int i = 0; i < _node_num; i++){
					if(_grow[i] > 0){
						frisePriceId[i] = true;
					}
				}

				for(int i = 0; i < _arc_num; i++){
					if(frisePriceId[_source[i]]&&(!frisePriceId[_target[i]])){
						if(_flow[i] < _upper[i]){
							minRise = std::min(_price[_target[i]] + _cost[i] + _epsilon - _price[_source[i]], minRise);
						}
					}
					if(frisePriceId[_target[i]]&&(!frisePriceId[_source[i]])){
						if(_flow[i] > _lower[i]){
							minRise = std::min(_price[_source[i]] - _cost[i] + _epsilon -_price[_target[i]], minRise);
						}
					}
				}

				for(int i = 0; i < _node_num; i++){
					if(frisePriceId[i]){
						_price[i] += minRise;
					}
				}
				return 0;
			}
			
			bool iterateEnd(){
				bool fflag = true;
				for(int i = 0; i < _node_num; i++){
					if(_grow[i] != 0){
						fflag = false;
						break;
					}
				}
				return fflag;
			}
					




		public:
#if AUCTION_DEBUG
			void printFlow(){
				int* fgraph = new int[_node_num*_node_num];
				memset(fgraph,0,sizeof(int)*_node_num*_node_num);

				for(int i = 0; i < _arc_num; i++){
					fgraph[_source[i]*_node_num + _target[i]] = _flow[i];
				}
				for(int i = 0; i < _node_num; i++){
					for(int j = 0; j < _node_num; j++){
						std::cout << fgraph[i*_node_num + j] << "  \t";
					}
					std::cout << std::endl;
				}
			}
			void printPrice(){
				int* fgraph = new int[_node_num*_node_num];
				memset(fgraph,0,sizeof(int)*_node_num*_node_num);

				std::cout << "***********************\n"
					<< "printPrice\n";
				for(int i = 0; i < _node_num; i++){
					fgraph[i] = _price[i];
				}
				for(int i = 0; i < _node_num; i++){
						std::cout << fgraph[i] << "  \t";
				}
				std::cout << std::endl
					<< "***********************\n";
			}
			void printGrow(){
				int* fgraph = new int[_node_num*_node_num];
				memset(fgraph,0,sizeof(int)*_node_num*_node_num);

				std::cout << "***********************\n"
					<< "printGrow\n";
				for(int i = 0; i < _node_num; i++){
					fgraph[i] = _grow[i];
				}
				for(int i = 0; i < _node_num; i++){
						std::cout << fgraph[i] << "  \t";
				}
				std::cout << std::endl
					<< "***********************\n";
			}
	
#endif


			template <typename Cost>
			ProblemType run(Cost m_epsilon){
				_epsilon = m_epsilon;
				//for debug
				/*
				 * std::cout << "***************" << "some varible:\n" 
					<< "* num of node: " << _node_num << std::endl
					<< "* num of edge: " << _arc_num << std::endl
					<< "***********************";
				std::cout << "print cost graph!!\n";
				myaprintGraph();
				*
				*/
				myaprintGraph();	
				while(!iterateEnd()){
#if AUCTION_DEBUG
					printFlow();
					printPrice();
					printGrow();
#endif
					pushEdge();
					priceRise();
				}
				return OPTIMAL;
			}

			template <typename FlowMap>
			void flowMap(FlowMap &map) const{
				for(typename GR::ArcIt a(_graph); a != lemon::INVALID; ++a){
					map.set(a, _flow[_arc_id[a]]);
				}
			}
/*
			template <typename Number>
			Number totalCost() const {
				Number c = 0;
				for(typename GR::ArcIt a(_graph); a!= lemon::INVALID; ++a){
					int i = _arc_id[a];
					c += static_cast<Number>(_flow[i] * _cost[i]);
				}
				return c;
			}
*/

#ifndef DOXYGEN
			Cost totalCost() const {
				return totalCost<Cost>();
			}
#endif

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
			ValueVector _grow;		//1
			CostVector _price;			//1
			ValueVector _flow;			//2
			ValueVector _lower;			//2
			ValueVector _upper;			//2
			CostVector _cost;			//2
			

			Cost _epsilon;
	};

}
#endif
