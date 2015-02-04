/*************************************************************************
    > File Name: FastMultiSet.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Tue 03 Feb 2015 04:10:43 PM CST
 ************************************************************************/

#ifndef LIMBO_CONTAINERS_FASTMULTISET_H
#define LIMBO_CONTAINERS_FASTMULTISET_H

/// ===================================================================
/// class       : FastMultiSet
/// Function    : Fast multiple set 
/// Description :
/// Use 2 level comparison 
/// Compare1 is for main multiset, it allows duplicate keys. 
/// Compare2 is for secondary map, it must have unique keys. 
/// In other words, keys to Compare1 can have duplicated compare results, 
/// while to Compare2, the compare results must be unique. 
/// The data structure is as follows 
/// multiset keeps the correct order that user wants
/// for duplicate keys, map can ensure fast access 
/// because map saves <key, iterator in multiset>
///
/// This data structure can provide O(logN) in insert, erase and update 
/// for even duplicate keys 
///
/// It is suitable to use pointers as key_type or value_type, which will not change during the operations.
/// But the data the pointers point to can change, so that no data race between the order of update data and update multiset.
/// ===================================================================

#include <iostream>
#include <map>
#include <multiset>
#include <cassert>
#include <boost/typeof.hpp>

using std::map;
using std::less;
using std::multiset;

/// \param KeyType, type of keys for comparison, also the type of values in the set 
/// \param Compare1, 1st level compare type, control multiset 
/// \param Compare2, 2nd level compare type, control map
template <typename KeyType, 
		 typename Compare1 = less<KeyType>, 
		 typename Compare2 = less<KeyType> >
class FastMultiSet : public multiset<KeyType, Compare1>
{
	public:
		/// for set concept, value_type is also key_type
		typedef KeyType key_type;
		/// for set concept, key_type is also value_type
		typedef KeyType value_type; 
		typedef Compare1 key_compare1;
		typedef Compare2 key_compare2;
		typedef multiset<key_type, key_compare1> base_type;
		typedef map<key_type, typename base_type::iterator, key_compare2> map_type;
		typedef typename map_type::value_type map_value_type;

		typedef typename base_type::reference reference;
		typedef typename base_type::const_reference const_reference;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::const_pointer const_pointer;
		typedef typename base_type::iterator iterator;
		typedef typename base_type::const_iterator const_iterator;
		typedef typename base_type::reverse_iterator reverse_iterator;
		typedef typename base_type::const_reverse_iterator const_reverse_iterator;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::size_type size_type;

		explicit FastMultiSet(key_compare1 const& comp1 = key_compare1(), 
				key_compare2 const& comp2 = key_compare2())
			: base_type(comp1), m_map(comp2) {}
		FastMultiSet(FastMultiSet const& rhs)
			: base_type(rhs) 
		{
			// O(2NlogN)
			// rhs may be in bad order 
			// so we have to reconstruct m_map
			m_map.clear();
			for (iterator it = this->begin();
					it != this->end(); ++it)
				m_map.insert(std::make_pair(*it, it));
		}

		virtual iterator insert(key_type const& val)
		{
			// for safty, take O(logN)
			BOOST_AUTO(found, m_map.find(val));
			assert(found == m_map.end());
			iterator it = this->base_type::insert(val); // no hint 
			m_map[val] = it;
			return it;
		}
		virtual iterator insert(iterator position, key_type const& val)
		{
			// for safty, take O(logN)
			BOOST_AUTO(found, m_map.find(val));
			assert(found == m_map.end());
			iterator it = this->base_type::insert(position, val); // with hint 
			m_map[val] = it;
			return it;
		}
		/// hide methods in base class
		template <typename InputIterator> void insert(InputIterator first, InputIterator last);

		virtual size_type erase(key_type const& val)
		{
			BOOST_AUTO(found, m_map.find(val));
			if (found == m_map.end()) return 0;
			this->base_type::erase(found->second);
			m_map.erase(found);
			return 1;
		}
		/// hide methods in base class
		void erase(iterator position);
		void erase(iterator first, iterator last);

		virtual iterator update(key_type const& val)
		{
			BOOST_AUTO(found, m_map.find(val)); // O(logN)
			//  it is possible in some applications  
			if (found == m_map.end()) return this->end();
			// update multiset 
			this->base_type::erase(found->second); // O(1)
			iterator it = this->base_type::insert(val); // O(logN)
			// update map 
			found->second = it; // O(1)
			return found->second;
		}

		/// use m_map.count rather than multiset::count to have faster access
		virtual size_type count(key_type const& val) const
		{
			return m_map.count(val); // O(logN)
		}
		/// use m_map.find rather than multiset::find to have faster access
		virtual iterator find(key_type const& val) const
		{
			BOOST_AUTO(found, m_map.find(val)); // O(logN)
			if (found == m_map.end()) // not found
				return this->end();
			else // found
				return found->second;
		}

		void print(std::ostream& os) const
		{
			os << "/////////// FastMultiSet ////////////\n";
			os << "<< set >>\n";
			for (const_iterator it = this->begin(); 
					it != this->end(); ++it)
				os << *it << endl;
			os << "<< map >>\n";
			for (BOOST_AUTO(it, m_map.begin()); 
					it != m_map.end(); ++it)
				os << it->first << " --> " << *(it->second) << endl;
		}
		friend std::ostream& operator<<(std::ostream& os, FastMultiSet const& rhs)
		{
			rhs.print(os);
			return os;
		}

	protected:
		map_type m_map;
};


#endif
