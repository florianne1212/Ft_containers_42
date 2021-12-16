/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:05:37 by fcoudert          #+#    #+#             */
/*   Updated: 2021/09/20 11:45:41 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <cstddef>
#include "reverse_iterator.hpp"
#include "mandatory.hpp"





/** SRC = https://www.cplusplus.com/reference/vector/vector/ **/

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector 
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef pointer iterator;
			typedef const_pointer const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


		private:
		
			allocator_type v_allocator;
			value_type *v_array;
			size_type v_size;
			size_type v_capacity;


		public:
		
			/** (constructor) **/
			explicit vector (const allocator_type& alloc = allocator_type()):
			v_allocator(alloc),
			v_array(NULL),
			v_size(0),
			v_capacity(0)
			{}

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
			v_allocator(alloc),
			v_array(NULL),
			v_size(0),
			v_capacity(0)
			{
					assign(n, val);
			}

			template <class InputIterator>
			vector (InputIterator first, typename enable_if<InputIterator::It, InputIterator>::type last, const allocator_type& alloc = allocator_type()) :
				v_allocator(alloc),
				v_array(NULL),
				v_size(0),
				v_capacity(0)
			{
				assign(first, last);
			}
			
			template <class InputIterator>
			vector (InputIterator first, typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type &alloc = allocator_type()):
			v_allocator(alloc),
			v_array(NULL),
			v_size(0),
			v_capacity(0)
			{
				assign(first, last);
			}


			vector (const vector& x):
			v_allocator(x.v_allocator),
			v_array(x.v_array),
			v_size(x.v_size),
			v_capacity(x.v_capacity)
			{
				v_array = v_allocator.allocate(v_capacity);
                
				const_iterator it = x.begin();
				int i = 0;
				while (it!=x.end())
				{
					v_allocator.construct(&v_array[i], *it);
					i++;
					it++;
				}
			}

			/** (destructor) **/
			~vector()
			{
				if(v_array)
				{
					for (iterator i = begin(); i != end(); i++)
						v_allocator.destroy(&(*i));
					
					v_allocator.deallocate(v_array, v_size);
				}
				
			}

			/** operator= **/
			vector& operator= (const vector& x)
			{
				vector tmp(x);
                swap(tmp);
                return *this;
			}

			/** ITERATORS **/

			/** begin **/
			iterator begin()
			{
				return(iterator(&v_array[0]));
			}

			const_iterator begin() const
			{
				return(const_iterator(&v_array[0]));
			}

			/** end **/
			iterator end()
			{
				return(iterator(&v_array[v_size]));
			}

			const_iterator end() const
			{
				return(const_iterator(&v_array[v_size]));
			}

			/** rbegin **/
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const
			{
				return(const_reverse_iterator(&v_array[v_size]));
			}

			/** rend **/
			reverse_iterator rend()
			{
				return reverse_iterator(begin()); 
			}

			const_reverse_iterator rend() const
			{
				return(const_reverse_iterator(&v_array[0]));
			}

			/** CAPACITY **/

			/** size **/
			size_type size() const
			{
				return(this->v_size);
			}

			/** max_size **/
			size_type max_size() const
			{
				size_type max_size = 0;
				try
				{
					max_size = v_allocator.max_size();
				}
				catch (std::exception &e)
				{
					std::cout << "Error in vector.max_size() :" << e.what() << std::endl;
				}
				return (max_size);
			}

			/** resize **/
			void resize (size_type n, value_type val = value_type())
			{
				while (n > v_size)
				{
					push_back(val);
				}	
				if (n < v_size)
				{
					while (v_size != n)
						pop_back();
				}
			}

			/** capacity **/
			size_type capacity() const
			{
				return(v_capacity);
			}

			/** empty **/
			bool empty() const
			{
				return (v_size == 0);	
			}

			/** reserve **/
			void reserve (size_type n)
			{
				int to_allocate;
				if (n <= v_size * 2)
					to_allocate = v_size * 2;
				else
					to_allocate = n;
				
				if (n > max_size())
					throw (std::length_error("the size requested is greater than the maximum size"));
				if (n > capacity())
				{
					if (v_capacity)
					{
						value_type *copy;
						copy = v_allocator.allocate(to_allocate);
						for (size_t i = 0; i < v_size; i++)
							v_allocator.construct(copy + i, v_array[i]);
						v_allocator.deallocate(v_array, v_capacity);
						v_allocator.destroy(v_array);
						v_array = copy;
						v_capacity = to_allocate;
						
					}
					else
					{
						v_array = v_allocator.allocate(to_allocate);
						v_capacity = to_allocate;
					}
				}
			}

			/** ELEMENT ACCESS **/

			/** operator[] **/
			reference operator[] (size_type n)
			{
				return(v_array[n]);
			}

			const_reference operator[] (size_type n) const
			{
				return(v_array[n]);
			}

			/** at **/
			reference at (size_type n)
			{
				if(n >= v_size || n < 0 || v_size == 0)
					throw (std::out_of_range("the element is out of range"));
				else 
					return(v_array[n]);
			}

			const_reference at (size_type n) const
			{
				if(n >= v_size || n < 0 || v_size == 0)
					throw (std::out_of_range("the element is out of range"));
				else 
					return(v_array[n]);
			}

			/** front **/
			reference front()
			{
				return(v_array[0]);
			}

			const_reference front() const
			{
				return(v_array[0]);
			}

			/** back **/
			reference back()
			{
				return(v_array[v_size - 1]);
			}

			const_reference back() const
			{
				return(v_array[v_size - 1]);
			}

			// /** MODIFIERS **/

			/** assign **/
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
			{
				clear();
				insert(begin(), first, last);
			}

			void assign (size_type n, const value_type& val)
			{
				clear();
				resize(n, val);
			}

			/** push_back **/
			void push_back (const value_type& val)
			{
				if((v_size + 1) > capacity())
					reserve(v_size + 1);
				v_allocator.construct(v_array + v_size, val);
				v_size++;
	
			}

			/** pop_back **/
			void pop_back()
			{
				if(v_size > 0)
				{
					v_allocator.destroy(v_array + (v_size - 1));
					v_size --;
				}
			}

			/** insert **/
			iterator insert (iterator position, const value_type& val)
			{
				size_t dist = position - begin();
				insert(position, 1, val);
				return (&v_array[dist]);

			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n)
				{
					vector tmp;
					tmp.reserve(n + v_size);
					int i = 0;
					iterator it = begin();	
					while (it != position)
					{
						tmp.push_back(*it);
						it++;
						i++;
					}
					while (n--)
					{
						tmp.push_back(val);
						i++;
					}
					while (it != end())
					{
						tmp.push_back(*it);
						it++;
						i++;
					}
					swap(tmp);
				}
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, 
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				vector tmp;
				iterator it = begin();
				if(begin() != NULL)
				{
					while (it != position)
					{
						tmp.push_back(*it);
						it++;
					}
				}
				while (first != last)
				{
					tmp.push_back(*first);
					first++;
				}
				while (it != end())
				{
					tmp.push_back(*it);
					it++;
				}
				swap(tmp);
			}

			/** erase **/
			iterator erase (iterator position)
			{
				iterator it = position;

                v_allocator.destroy(position);     
                for (pointer tmp = position; tmp != end(); tmp++) 
                {
                    v_allocator.construct(tmp, *(tmp + 1));
                }
                v_size--;
                return (it);

				
				
			}

			iterator erase (iterator first, iterator last)
			{
				for (; first != last; --last)
					first = erase(first);
				return last;
			}

			/** swap **/
			void swap (vector& x)
			{
				swap(v_size, x.v_size);
				swap(v_array, x.v_array);
				swap(v_capacity, x.v_capacity);
				swap(v_allocator, x.v_allocator);
			}

			/** clear **/
			void clear()
			{
				for (size_type i = 0; i < v_size; ++i)
					v_allocator.destroy(&v_array[i]);
				v_size = 0;
			}

			allocator_type get_allocator() const
			{
				return(v_allocator);
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
	}
	;

	/** NON-MEMBER FUNCTION OVERLOADS **/

	/** relational operators **/
	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			if(lhs.size() != rhs.size())
				return(false);
			for (typename ft::vector<T>::size_type i = 0; i < lhs.size(); i++)
			{
				if(lhs[i] != rhs[i])
					return(false);
			}
			return(true);
		}

	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return(!(lhs == rhs));
		}

	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			typename ft::vector<T>::const_iterator first1 = lhs.begin();
			typename ft::vector<T>::const_iterator last1 = lhs.end();
			typename ft::vector<T>::const_iterator first2 = rhs.begin();
			typename ft::vector<T>::const_iterator last2 = rhs.end();
			
			while (first1!=last1)
			{
				if (first2==last2 || *first2<*first1) return false;
				else if (*first1<*first2) return true;
				++first1; ++first2;
			}
			return (first2!=last2);
		}

	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return(!(rhs < lhs));
		}

	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return(rhs < lhs);
		}

	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return(!(lhs < rhs));
		}

	/** swap **/
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}
}

#endif