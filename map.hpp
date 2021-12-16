#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include <cstddef>
#include <functional>
#include <iostream>

// #include "Iterator.hpp"
// #include "Reverse_Iterator.hpp"
// #include "needed.hpp"
#include "mandatory.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "map_iterator.hpp"

/** SRC = https://www.cplusplus.com/reference/map/map/ **/
/** SRC = https://www.cplusplus.com/reference/utility/pair/ **/

namespace ft {

	template <class T> 
	struct less : std::binary_function <T,T,bool> 
	{
  		bool operator() (const T& x, const T& y) const 
		{
			return x<y;
		}
	};


	
	template< 
		class Key,
		class T,
		class Compare = ft::less<Key>,
		class Alloc = std::allocator<ft::pair<const Key,T> > 
		>
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef pair< Key, T> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef ft::BSTNode<Key, T> BSTNode;
			typedef typename Alloc::template rebind<ft::BSTNode<Key, T> >::other bst_node_alloc;
			typedef typename bst_node_alloc::reference reference;
			typedef typename bst_node_alloc::const_reference const_reference;
			typedef typename bst_node_alloc::pointer pointer;
			typedef typename bst_node_alloc::const_pointer const_pointer;
			typedef mapIterator<Key, T> iterator;
			typedef mapConstIterator< Key, T> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		private:
			bst_node_alloc m_allocator;
			key_compare	m_comp;
			size_type 	m_size;
			BSTNode		*m_root;
			BSTNode		*m_last;
			BSTNode		*m_first;

		
		public:

		
		class value_compare
		{
			friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		};


		public:
		
			/** (constructor) **/
			explicit map (const key_compare& comp = key_compare(),
			  const allocator_type& alloc = allocator_type()):
			  m_allocator(alloc),
			  m_comp(comp),
			  m_size(0)
			  {
                  first_creation_node();
              }


			
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0):
				m_allocator(alloc),
				m_comp(comp),
				m_size(0)
				{
                    first_creation_node();
					while (first != last)
					{
						insert(*first);
						first++;
					}
				}
			
			map (const map& x)
			{
				m_comp = x.m_comp;
				m_allocator = x.m_allocator;
				m_size = 0;
				first_creation_node();
				const_iterator it = x.begin();
				const_iterator ite = x.end();
				while (it != ite)
				{
					insert(*it);
					it++;
				}
			}

			/** (destructor) **/
			~map()
			{
				erase(begin(), end());
				if(m_first)
					m_allocator.destroy(m_first);
					m_allocator.deallocate(m_first, 1);
				if(m_last)
					m_allocator.destroy(m_last);
					m_allocator.deallocate(m_last, 1);
			}

			/** operator= **/
			map& operator= (const map& x)
			{
				clear();
				const_iterator it = x.begin();
				const_iterator ite = x.end();

				while (it != ite)
				{
					insert(*it);
					it++;
				}
				return(*this);
			}

			// /** ITERATORS **/
			
			/** begin **/
			iterator begin()
			{
				if(m_root != m_last)
				{
					iterator it = iterator(m_first);
					it++;
					return(it);
				}
				else
					return(end());
			}

			const_iterator begin() const
			{
				if(m_root != m_last)
				{
					const_iterator it = const_iterator(m_first);
					it++;
					return(it);
				}
				else
					return(end());
			}

			/** end **/
			iterator end()
			{
				return(iterator(m_last));
			}

			const_iterator end() const
			{
				return(const_iterator(m_last));
			}

			/** rbegin **/
			reverse_iterator rbegin()
			{
				return(reverse_iterator(end()));
			}

			const_reverse_iterator rbegin() const
			{
				return(reverse_iterator(end()));
			}

			/** rend **/
			reverse_iterator rend()
			{
				return(reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const
			{
				return(const_reverse_iterator(begin()));
			}

			// /** CAPACITY **/

			/** empty **/
			bool empty() const
			{
				return(m_size == 0);
			}

			/** size **/
			size_type size() const
            {
				return(m_size);
			}

			/** max_size **/
			size_type max_size() const
			{
				return(bst_node_alloc().max_size());
			}

			// /** ELEMENT ACCESS **/

			/** operator[] **/
			mapped_type& operator[] (const key_type& k)
			{
				BSTNode *found;
				if((found = find_node(k)))
					return(found->_data.second);

				value_type val = ft::make_pair<key_type, mapped_type>(k,mapped_type());
				pair<iterator,bool> ret = insert(val);
				iterator finder = ret.first;
				return(finder.get_node()->_data.second);

			}
			// /** MODIFIERS **/

			/** insert **/
		    pair<iterator,bool>
			insert (const value_type& val)
			{
                if (m_root == m_last)
                {
                    m_root = creation_node(val);
                    m_size += 1;
					add_end();

                    return (ft::pair<iterator,bool>(iterator(m_root), true));
                }

				BSTNode *node;

				if(do_compare(m_last->_parent->_data.first, val.first))
					node = m_last->_parent;
				else if (do_compare(val.first, m_first->_parent->_data.first))
					node = m_first->_parent;
				else
					node = m_root;

				while(true) {
					if (do_compare(val.first, node->_data.first)) {
						if (node->_left && node->_left != m_first) {
							node = node->_left;
						} else {
							BSTNode *new_node = creation_node(val);
							new_node->_parent = node;
							node->_left = new_node;
							if (m_first->_parent == node) {
								m_first->_parent = new_node;
								new_node->_left = m_first;
							}
							m_size++;
                    		return (ft::pair<iterator,bool>(iterator(new_node), true));
						}
					}
					else if (are_keys_equal(val.first, node->_data.first)) {
                    	return (ft::pair<iterator,bool>(iterator(node), false));
					} 
					
					else {
						if (node->_right && node->_right != m_last) {
							node = node->_right;
						} else {
							BSTNode *new_node = creation_node(val);
							new_node->_parent = node;
							node->_right = new_node;
							if (m_last->_parent == node) {
								m_last->_parent = new_node;
								new_node->_right = m_last;
							}
							m_size++;
                    		return (ft::pair<iterator,bool>(iterator(new_node), true));
						}
					}
				}
			}

			iterator insert (iterator position, const value_type& val)
			{
				(void) position;
				insert(val);
				return(iterator(find_node(val.first)));
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{		
				for ( InputIterator it = first; it != last; it++)
					insert(*it);
			}

			/** erase **/
			void erase (iterator position)
			{
				if(m_first->_parent)
				{
					m_first->_parent->_left = NULL;
					if (m_first->_parent == m_root && position.get_node() == m_root)
					{
						m_first->_parent =  m_first->_parent->_right;
					}
					if (m_first->_parent == position.get_node()) {
						m_first->_parent = m_first->_parent->_parent;
					}
				}

				if(m_last->_parent)
				{
					m_last->_parent->_right = NULL;
					if (m_last->_parent == position.get_node()) {
						m_last->_parent = m_last->_parent->_parent;
					}
				}
				delete_into_tree(position.get_node());
				m_size--;
				if(m_root && m_root != m_last)
				{
					if(m_first->_parent)
					{
						BSTNode *node = as_left_as_you_can(m_first->_parent);
						if (node)
							m_first->_parent = node;
						m_first->_parent->_left = m_first;
					}
					if(m_last->_parent)
					{
						BSTNode *node = as_right_as_you_can(m_last->_parent);
						if (node) 
							m_last->_parent = node;

						m_last->_parent->_right = m_last;
					}
				}
			}

			size_t erase (const key_type& k)
			{
				BSTNode *to_delete = find_node(k);
				if(to_delete && to_delete != m_last)
				{
					remove_end();		
					delete_into_tree(to_delete);
					m_size--;
					add_end();
					return(1);	
				}
				return(0);
			}

			void erase (iterator first, iterator last)
			{
				while (first != last )
				{
					iterator it = first;
					first++;	
					erase(it);
				}
			}

			/** swap **/
			void swap (map& x)
			{
				swap(m_size, x.m_size);
				swap(m_allocator, x.m_allocator);
				swap(m_comp, x.m_comp);
				swap(m_root, x.m_root);
				swap(m_last, x.m_last);
				swap(m_first, x.m_first);
			}

			/** clear **/
			void clear()
			{
				erase(begin(), end());
			}

			// /** OBSERVERS **/

			/** key_comp **/
			key_compare key_comp() const
			{
				return(m_comp);
			}

			/** value_comp **/
			value_compare value_comp() const
			{
				return value_compare(m_comp);
			}
			
			
			/** OPERATIONS **/
			
			/** find **/
			iterator find (const key_type& k)
			{
				if(find_node(k))
				{
					return(iterator(find_node(k)));
				}
				return(m_last);
				
			}

			const_iterator find (const key_type& k) const
			{
				if(find_node(k))
				{
					return(iterator(find_node(k)));
				}
				return(m_last);
			}
			
			/** count **/
			size_type count (const key_type& k) const
			{
				if(find_node(k))
					return(1);
				return(0);		
			}

			/** lower_bound **/
			iterator lower_bound (const key_type& k)
			{
				iterator first = begin();
				iterator last = end();
				while (first != last && m_comp(first.get_node()->_data.first,k))
				{
					first++;
				}
				return(first);
			}
			
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator first = begin();
				const_iterator last = end();
				while (first != last && m_comp(first.get_node()->_data.first,k))
				{
					first++;
				}
				return(first);
			}

			/** upper_bound **/
			iterator upper_bound (const key_type& k)
			{
				iterator first = lower_bound(k);
				iterator last = end();
				while (first != last && !m_comp(k, first.get_node()->_data.first))
				{
					first++;
				}
				return(first);
			}
			
			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator first = lower_bound(k);
				const_iterator last = end();
				while (first != last && !m_comp(k, first.get_node()->_data.first))
				{
					first++;
				}
				return(first);
			}

			// /** equal_range **/

			pair<const_iterator,const_iterator> 
			equal_range (const key_type& k) const
			{
				const_iterator ite = upper_bound(k);
				const_iterator it = lower_bound(k);
					
				return(make_pair(it, ite));
			}
			
			pair<iterator,iterator>
			equal_range (const key_type& k)
			{	
				iterator ite = upper_bound(k);
				iterator it = lower_bound(k);
					
				return(make_pair(it, ite));
			}

			/** ALLOCATOR **/
			allocator_type get_allocator() const
			{
				return(m_allocator);
			}

		private:
			template <typename F>
			void swap(F& a, F& b)
			{
				F tmp;
				tmp = a;
				a = b;
				b = tmp;
            }

			BSTNode * _get(key_type k, BSTNode *root) const
			{
				while (true) {
					if (!root || root == m_last)
					{
						return NULL;
					}

					if (!m_comp(k, root->_data.first) && !m_comp(root->_data.first, k))
					{
						return root;
					}

					if (m_comp(k, root->_data.first))
					{
						root = root->_left;
						continue;
					}

					else if (m_comp(root->_data.first, k))
					{
						root = root->_right;
						continue;
					}
				}
				return(NULL);
			}

			BSTNode * _get(key_type k, BSTNode *root)
			{
				while (true) {
					if (!root || root == m_last)
					{
						return NULL;
					}

					if (!m_comp(k, root->_data.first) && !m_comp(root->_data.first, k))
					{
						return root;
					}

					if (m_comp(k, root->_data.first))
					{
						root = root->_left;
						continue;
					}

					else if (m_comp(root->_data.first, k))
					{
						root = root->_right;
						continue;
					}
				}
				return(NULL);
			}

			BSTNode *find_node(const key_type& k) const
			{
				if (m_root && m_root != m_last){
					BSTNode *res = _get(k, m_root);
					if (res)
						return res;
				}
				return NULL;
			}

			BSTNode *find_node(const key_type& k)
			{
				if (m_root && m_root != m_last){
					BSTNode *res = _get(k, m_root);
					if (res)
						return res;
				}
				return NULL;
			}

			BSTNode *delete_leaf(BSTNode *to_delete)
			{
				if(to_delete == m_root)
				{
					destroy_node(to_delete);
					m_root = m_last;
					return NULL;
				}
				
				if(to_delete == to_delete->_parent->_right)
					to_delete->_parent->_right = NULL;
				else
					to_delete->_parent->_left = NULL;

				destroy_node(to_delete);
				
				return NULL; 
			}

			BSTNode *delete_left_or_right(BSTNode *to_delete)
			{
				BSTNode *tmp = NULL; 
				if(to_delete->_left == NULL )
				{
					tmp =  to_delete->_right;
					if(to_delete == m_root)
					{
						m_root = to_delete->_right;
						destroy_node(to_delete);
						return(tmp);
					}
					if(to_delete == to_delete->_parent->_right)
					{
						to_delete->_right->_parent = to_delete->_parent;
						to_delete->_parent->_right = to_delete->_right;
					}
					else
					{
						to_delete->_right->_parent = to_delete->_parent;
						to_delete->_parent->_left = to_delete->_right;
					}					
					destroy_node(to_delete);
					return(tmp);
				}
				else if(to_delete->_right == NULL)
				{
					tmp =  to_delete->_left;
					if(to_delete == m_root)
					{
						m_root = to_delete->_left;
						destroy_node(to_delete);
						return(tmp);
					}
					if(to_delete == to_delete->_parent->_right)
					{
						to_delete->_left->_parent = to_delete->_parent;
						to_delete->_parent->_right = to_delete->_left;
					}
					else
					{
						to_delete->_left->_parent = to_delete->_parent;
						to_delete->_parent->_left = to_delete->_left;
					}					
					destroy_node(to_delete);
					return(tmp);
				}
				return(tmp);
			}

			BSTNode *delete_into_tree(BSTNode *to_delete)
			{
				while(true)
				{
					if(to_delete == NULL || to_delete == m_last)
						return NULL;
					if(to_delete != NULL)
					{
						if(to_delete->_left == NULL && to_delete->_right == NULL)
						{
							return(delete_leaf(to_delete));
						}
						else if(to_delete->_left == NULL )
						{
							return(delete_left_or_right(to_delete));
						}
						else if(to_delete->_right == NULL)
						{
							return(delete_left_or_right(to_delete));
						}
						else 
						{
							BSTNode *as_right = as_left_as_you_can(to_delete->_right);
							swap(to_delete->_data,as_right->_data);
							to_delete  = as_right;
							continue;
						}
					}
					return to_delete;
				}

			}

			BSTNode *insert_into_tree(BSTNode *root,const value_type& val)
			{
				BSTNode *new_node = NULL;
				while(true) {
					if(m_comp(val.first, root->_data.first))
					{
						if(root->_left != NULL)
						{
							root = root->_left;
							continue;
						}
						else
						{
							new_node = creation_node(val);
							new_node->_parent = root;
							root->_left = new_node;
							break;
						}
					}
					else
					{
						if(root->_right)
						{
							root = root->_right;
							continue;
						}
						else
						{
							new_node = creation_node(val);
							new_node->_parent = root;
							root->_right = new_node;
							break;
						}
					}
				}

				return (new_node);

			}

            void first_creation_node()
            {
                m_last = m_allocator.allocate(1);
                m_allocator.construct(m_last, BSTNode());
                m_last->_left = NULL;
                m_last->_right = NULL;
                m_last->_parent = NULL;
                m_root = m_last;
				m_first = m_allocator.allocate(1);
                m_allocator.construct(m_first, BSTNode());
                m_first->_left = NULL;
                m_first->_right = NULL;
                m_first->_parent = NULL;
            }

            BSTNode *creation_node(value_type val)
            {
                BSTNode *new_node;
                new_node = m_allocator.allocate(1);
                m_allocator.construct(new_node, BSTNode());
                new_node->_left = NULL;
                new_node->_right = NULL;
                new_node->_parent = NULL;
                new_node->_data = val;
                return(new_node);
            }

			void destroy_node(BSTNode *node)
			{
				if (node == m_last || node == m_first)
					return ;
				m_allocator.destroy(node);
				m_allocator.deallocate(node, 1);
			}

			void remove_end()
			{
				if(m_last->_parent)
				{
					m_last->_parent->_right = NULL;
					m_last->_parent = NULL;
				}

				if(m_first->_parent)
				{
					m_first->_parent->_left = NULL;
					m_first->_parent = NULL;
				}
			}

			void add_end()
			{
				if(m_root && m_root != m_last)
				{
					m_last->_parent = as_right_as_you_can(m_root);
					if(m_last->_parent)
						m_last->_parent->_right = m_last;

					m_first->_parent = as_left_as_you_can(m_root);
					if(m_first->_parent)
						m_first->_parent->_left = m_first;
				}
				
			}

			BSTNode *as_left_as_you_can(BSTNode *node) 
			{
				while (node && node->_left)
				{
					node = node->_left;
				}
				return(node);
			}

			BSTNode *as_left_as_you_can(BSTNode *node) const
			{
				while (node && node->_left)
				{
					node = node->_left;
				}
				return(node);
			}

			BSTNode *as_right_as_you_can(BSTNode *node)
			{
				while (node->_right)
				{
					node = node->_right;
				}
				return(node);
			}

			BSTNode *as_right_as_you_can(BSTNode *node) const
			{
				while (node->_right)
				{
					node = node->_right;
				}
				return(node);
			}

			inline bool
			are_keys_equal(const key_type &a, const key_type &b)
			{
				return (!m_comp(a, b) && !m_comp(b, a));
			}

			inline bool
			do_compare(const key_type &a, const key_type &b) const
			{
				return (m_comp(a, b));
			}

	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		if(lhs.size() != rhs.size())
			return(false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return(!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		typename ft::map<Key, T>::const_iterator first1 = lhs.begin();
		typename ft::map<Key, T>::const_iterator last1 = lhs.end();
		typename ft::map<Key, T>::const_iterator first2 = rhs.begin();
		typename ft::map<Key, T>::const_iterator last2 = rhs.end();
			
			while (first1!=last1)
			{
				if (first2==last2 || *first2<*first1) return false;
				else if (*first1<*first2) return true;
				++first1; ++first2;
			}
			return (first2!=last2);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return(!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return(!(lhs < rhs));
	}
};

#endif
