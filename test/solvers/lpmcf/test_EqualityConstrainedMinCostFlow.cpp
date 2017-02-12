/**
 * @file   test_EqualityConstrainedMinCostFlow.cpp
 * @brief  test @ref limbo::solvers::lpmcf::EqualityConstrainedMinCostFlow
 * @author Yibo Lin
 * @date   Feb 2017
 */
#include <iostream>
#include <string>
#include <limbo/solvers/lpmcf/EqualityConstrainedMinCostFlow.h>

int main(int argc, char** argv)
{
    typedef int value_type;
    typedef float cost_type;
    typedef lemon::SmartDigraph graph_type;
    typedef graph_type::Node node_type;
    typedef graph_type::Arc arc_type;
    typedef graph_type::NodeMap<value_type> node_value_map_type;
    typedef graph_type::NodeMap<std::string> node_name_map_type;
    typedef graph_type::ArcMap<value_type> arc_value_map_type;
    typedef graph_type::ArcMap<value_type> arc_cost_map_type;
    typedef graph_type::ArcMap<value_type> arc_flow_map_type;
    typedef graph_type::NodeMap<value_type> node_pot_map_type; // potential of each node 

	if (argc > 1)
	{
        graph_type graph; 
        node_value_map_type mSupply (graph); 
        node_name_map_type mName (graph); 
        arc_value_map_type mLower (graph); 
        arc_value_map_type mUpper (graph); 
        arc_cost_map_type mCost (graph); 
        arc_value_map_type mArcId (graph); // help for mEquality
        arc_value_map_type mEquality (graph); // stores like adjacency list, 
                                      // in case there are multiple neighbors, we allow propagation through neighbors 
                                      // for example, arc 1 has neighbor arc 2, arc 2 has neighbor arc 3, 
                                      // it means arc 1, 2, 3 should have the same flow. 
                                      // one's neighbor is itself if it does not have equality constraints 

        // read input file in .lgf format and initialize graph 
        lemon::DigraphReader<graph_type>(graph, argv[1])
            .nodeMap("supply", mSupply)
            .nodeMap("name", mName)
            .arcMap("capacity_lower", mLower)
            .arcMap("capacity_upper", mUpper)
            .arcMap("cost", mCost)
            .arcMap("arc_id", mArcId)
            .arcMap("equality_neighbor", mEquality)
            .run();

        typedef limbo::solvers::lpmcf::EqualityConstrainedMinCostFlow<graph_type, value_type, cost_type> alg_type; 

        // construct equality map from mArcId and mEquality 
        std::vector<arc_type> mId2Arc (graph.maxArcId()+1); 
        alg_type::equality_map_type mEqualityMap; 

        // need first construct mapping from arc_id to arc 
        for (graph_type::ArcIt a(graph); a != lemon::INVALID; ++a)
            mId2Arc[mArcId[a]] = a; 
        // set equality map 
        for (graph_type::ArcIt a(graph); a != lemon::INVALID; ++a)
        {
            if (a != mId2Arc[mEquality[a]])
            {
                mEqualityMap.push_back(std::make_pair(a, mId2Arc[mEquality[a]]));
            }
        }

        alg_type eqcMcf(graph);
        alg_type::ProblemType pt = eqcMcf
            .equalityMap(mEqualityMap)
            .operator()(10, 1);
        limboAssert(pt == alg_type::base_type::OPTIMAL);
    }
	else 
		std::cout << "at least 1 argument required\n";

    return 0; 
}
