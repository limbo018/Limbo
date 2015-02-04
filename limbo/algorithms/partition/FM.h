/*************************************************************************
    > File Name: FM.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Tue 03 Feb 2015 03:56:27 PM CST
 ************************************************************************/

#ifndef _LIMBO_ALGORITHMS_PARTITION_FM_H
#define _LIMBO_ALGORITHMS_PARTITION_FM_H

/// ===================================================================
///    class          : FM
///
///  Refer to Fiduccia and Mattheyses,
///  "A Linear-time Heuristics for Improving Network Partitions", DAC 1982
///  
/// ===================================================================

#include <iostream>
#include <vector>
#include <limbo/containers/FastMultiSet.h>
#include <limbo/math/Math.h>
using std::cout;
using std::endl;
using std::vector;

namespace limbo { namespace algorithms { namespace partition {

/// \param NodeType, type of nodes in the graph
template <typename NodeType>
struct FM_node_traits
{
	typedef NodeType node_type;
	typedef typename node_type::tie_id_type tie_id_type;
	typedef typename node_type::weight_type node_weight_type;
	
	/// \return id of a node to sort nodes in each bucket
	static tie_id_type tie_id(node_type const& val)
	{return val.tie_id();}
	/// \return weight of a node for balancing constraint, e.g. area 
	static node_weight_type weight(node_type const& n)
	{return n.weight();}
};

/// \param NodeType indicates type of nodes in the graph 
/// Only support two partitions 
template <typename NodeType, typename NetWeightType = double>
class FM
{
	public:
		typedef NodeType node_type;
		typedef NetWeightType net_weight_type;
		typedef typename node_traits<node_type>::node_weight_type node_weight_type;

		struct FM_node_type;
		struct FM_net_type;

		struct FM_node_type
		{
			node_type* pNode;
			vector<FM_net_type*> vNet;
			bool locked; ///< locked or not
			int partition; ///< partition id: 0 or 1, -1 for uninitialized
			node_weight_type weight; ///< node weight for balancing constraint, like area

			FM_node_type()
			{
				pNode = NULL;
				locked = false;
				partition = -1;
				weight = 0;
			}
			net_weight_type gain() const
			{
				net_weight_type g = 0;
				for (vector<FM_net_type*>::const_iterator itNet = vNet.begin(); 
						itNet != vNet.end(); ++itNet)
				{
					for (vector<FM_node_type*>::const_iterator itNode = (*itNet)->begin();
							itNode != (*itNet)->end(); ++itNode)
					{
						assert((*itNode)->partition == 0 || (*itNode)->partition == 1);

						if (this == *itNode) continue;
						else if (this->partition == (*itNode)->partition) // internal node 
							g -= (*itNet)->weight;
						else // external node
							g += (*itNet)->weight;
					}
				}
				return g;
			}
		};
		struct FM_net_type
		{
			vector<FM_node_type*> vNode;
			net_weight_type weight; ///< net weight
		};

		/// largest gain comes first
		struct compare_type1
		{
			bool operator()(FM_node_type* pFMNode1, FM_node_type* pFMNode2) const 
			{
				return pFMNode1->gain() > pFMNode2->gain();
			}
		};
		/// smallest tie_id comes first
		struct compare_type2
		{
			bool operator()(FM_node_type* pFMNode1, FM_node_type* pFMNode2) const 
			{
				return node_traits<node_type>::tie_id(*(pFMNode1->pNode)) < node_traits<node_type>::tie_id(*(pFMNode2->pNode));
			}
		};

		typedef containers::FastMultiSet<FM_node_type*, compare_type1, compare_type2> gain_bucket_type;

		/// \param initialPartition, 0 or 1
		/// \return whehter insertion is successful
		bool add_node(node_type* pNode, int initialPartition)
		{
			assert(initialPartition == 0 || initialPartition == 1);

			FM_node_type* pFMNode = new FM_node_type;
			pFMNode->pNode = pNode;
			pFMNode->partition = initialPartition;
			pFMNode->weight = node_traits<node_type>::weight(*pNode);
			return m_hNode.insert(std::make_pair(pNode, pFMNode)).second;
		}
		/// \param Iterator, dereference of which must be type of node
		/// \return whehter a net is successfully added
		/// this function must be called after all nodes are inserted
		template <typename Iterator>
		bool add_net(Iterator first, Iterator last, net_weight_type const& weight)
		{
			FM_net_type* pFMNet = new FM_net_type;
			pFMNet->weight = weight;

			for (Iterator it = first; it != last; ++it)
			{
				unordered_map<node_type*, FM_node_type*>::const_iterator found = m_hNode.find(*it);
				// return false if failed
				if (found == m_hNode.end())
				{
					delete pFMNet;
					return false;
				}
				pFMNet->vNode.push_back(found->second);
			}
			m_vNet.push_back(pFMNet);

			return true;
		}
	protected:
		/// \param ratio1, minimum target ratio for partition 0 over partition 1
		/// \param ratio2, maximum target ratio for partition 0 over partition 1
		void run(double ratio1, double ratio2)
		{
			// initialize m_gain_bucket
			node_weight_type total_weight[2] = {0, 0};
			for (unordered_map<node_type*, FM_node_type*>::const_iterator it = m_hNode.begin();
					it != m_hNode.end(); ++it)
			{
				FM_node_type* const& pFMNode = it->second;
				assert(pFMNode->partition == 0 || pFMNode->partition == 1);
				total_weight[pFMNode->partition] += pFMNode->weight;
				m_gain_bucket.insert(pFMNode);
			}

			// perform iterations 
			while (!m_gain_bucket.empty())
			{
				gain_bucket_type tmp_gain_bucket (m_gain_bucket);

				FM_node_type* pFMNodeBest = NULL; // candidnate node to move
				for (gain_bucket_type::const_iterator it = tmp_gain_bucket.begin(); 
						it != tmp_gain_bucket.end(); ++it)
				{
					FM_node_type* pFMNode = *it;

					node_weight_type tmp_total_weight[2] = {
						total_weight[0],
						total_weight[1]
					};
					// move out from current partition
					tmp_total_weight[pFMNode->partition] -= pFMNode->weight;
					// move into the other partition
					tmp_total_weight[!pFMNode->partition] += pFMNode->weight;

					double cur_ratio = (double)total_weight[0]/total_weight[1];
					double tmp_ratio = (double)tmp_total_weight[0]/tmp_total_weight[1];

					// the ratio stays in the target range or get closer to the target range
					if (limbo::abs(tmp_ratio-ratio1)+limbo::abs(tmp_ratio-ratio2) 
							<= limbo::abs(cur_ratio-ratio1)+limbo::abs(cur_ratio-ratio2))
					{
						pFMNodeBest = pFMNode;
						break;
					}
				}
				// this is not exit condition yet
				if (!pFMNodeBest) break; 
				
				// move pFMNodeBest
				// move out from current partition
				total_weight[pFMNodeBest->partition] -= pFMNodeBest->weight;
				// move into the other partition
				total_weight[!pFMNodeBest->partition] += pFMNodeBest->weight;
				tmp_gain_bucket.erase(pFMNodeBest);
				pFMNodeBest->partition = !pFMNodeBest->partition;
			}
		}
		unordered_map<node_type*, FM_node_type*> m_hNode; ///< FM nodes
		vector<FM_net_type*> m_vNet; ///< FM nets 
		gain_bucket_type m_gain_bucket; ///< gain buckets
};

}}} // namespace limbo  // namespace algorithms // namespace partition

#endif
