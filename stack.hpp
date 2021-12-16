/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 08:05:37 by fcoudert          #+#    #+#             */
/*   Updated: 2021/08/19 12:38:21 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"
#include <deque>

/** SRC = http://www.cplusplus.com/reference/stack/stack/ **/

namespace ft {

	template <class T, class Container = std::deque<T> >
	class stack 
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

		protected:
			container_type c;

		public:

		/** (constructor) **/
		explicit stack (const container_type& ctnr = container_type()):
		c(ctnr)
		{	
		}
		
		/** empty **/
		/** This member function effectively calls member empty of the underlying container object. **/
		bool empty() const
		{
			return(c.empty());
		}

		/** size **/
		/** This member function effectively calls member size of the underlying container object. **/
		size_type size() const
		{
			return(c.size());
		}

		/** top **/
		/** Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
		This member function effectively calls member back of the underlying container object. **/
		value_type& top()
		{
			return(c.back());
		}
		
		const value_type& top() const
		{
			return(c.back());
		}

		/** push **/
		/** This member function effectively calls the member function push_back of the underlying container object. **/
		void push (const value_type& val)
		{
			return(c.push_back(val));
		}

		/** pop **/
		/** This member function effectively calls the member function pop_back of the underlying container object. **/
		void pop()
		{
			return(c.pop_back());
		}
		
		/** NON-MEMBER FUNCTION OVERLOADS **/

		/** relational operators **/
		template <class TA, class ContainerA>
		friend bool operator== (const stack<TA,ContainerA>& lhs, const stack<TA,ContainerA>& rhs);

		template <class TA, class ContainerA>
		friend bool operator<  (const stack<TA,ContainerA>& lhs, const stack<TA,ContainerA>& rhs);

	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(!(rhs < lhs));
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return(!(lhs < rhs));
	}
}

#endif