/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 08:05:37 by fcoudert          #+#    #+#             */
/*   Updated: 2021/08/09 16:22:17 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP



/** SRC = https://www.cplusplus.com/reference/utility/pair/ **/

namespace ft {

	template <class T1, class T2> 
	struct pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

		public:

		/** (constructor) **/
		pair() : first(first_type()), second(second_type())
		{}

		template<class U, class V> pair (const pair<U,V>& pr)
		{
			first = pr.first;
			second = pr.second;
		}
		
		pair (const first_type& a, const second_type& b):first(a), second(b)
		{}

		/** pair::operator= **/

		pair& operator= (const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return(*this);
		}

	
	};
	/** NON-MEMBER FUNCTION OVERLOADS **/

	/** relational operators **/
	template <class T1, class T2>
  	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first==rhs.first && lhs.second==rhs.second;
	}

	template <class T1, class T2>
 	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs==rhs);
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs<lhs);
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return rhs<lhs;
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs<rhs);
	}
}

#endif