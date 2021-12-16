/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 08:05:37 by fcoudert          #+#    #+#             */
/*   Updated: 2021/08/09 17:50:40 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATORY_HPP
# define MANDATORY_HPP

#include "pair.hpp"
#include <cstddef>
#include <typeinfo>


/** MAKE_PAIR / INTEGRAL CONSTANT / IS_INTEGRAL /  LEXICOGRAPHICAL_COMPARE / EQUAL **/

/** SRC = http://www.cplusplus.com/reference/utility/make_pair/												**/
/** SRC = https://www.cplusplus.com/reference/type_traits/integral_constant/								**/
/** SRC = https://www.cplusplus.com/reference/type_traits/is_integral/?kw=is_integral						**/
/** SRC = https://www.cplusplus.com/reference/algorithm/lexicographical_compare/?kw=lexicographical_compare	**/
/** SRC = https://www.cplusplus.com/reference/algorithm/equal/?kw=equal										**/


namespace ft {

	/** make_pair **/
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}

	/** integral_constant **/
	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		operator T() { return v; }
	};

	//Instantiations
	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	/** enable_if **/

	template <bool Cond, class T = void>
	struct enable_if
	{};

	template<class T> 
	struct enable_if<true, T>
	{ typedef T type; };

	/** is_integral **/
	template <class T>
	struct is_integral : ft::false_type
	{};
	
	template <>
	struct is_integral<bool> : ft::true_type
	{};

	template <>
	struct is_integral<char> : ft::true_type
	{};

	template <>
	struct is_integral<wchar_t> : ft::true_type
	{};

	template <>
	struct is_integral<signed char> : ft::true_type
	{};

	template <>
	struct is_integral<short int> : ft::true_type
	{};

	template <>
	struct is_integral<int> : ft::true_type
	{};

	template <>
	struct is_integral<long int> : ft::true_type
	{};

	template <>
	struct is_integral<long long int> : ft::true_type
	{};
	
	template <>
	struct is_integral<unsigned char> : ft::true_type
	{};
	
	template <>
	struct is_integral<unsigned short int> : ft::true_type
	{};


	template <>
	struct is_integral<unsigned int> : ft::true_type
	{};

	template <>
	struct is_integral<unsigned long int> : ft::true_type
	{};
	
	template <>
	struct is_integral<unsigned long long int> : ft::true_type
	{};
	
	/** lexicographical_compare **/  
	 
	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	template <class InputIterator1, class InputIterator2, class Compare>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (comp(*first1,*first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	/** equal **/

	template <class InputIterator1, class InputIterator2>
  	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1) {
			if (!(*first1 == *first2))
			return false;
			++first1;
			++first2;
		}
		return true;
	};

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1) {
			if (!pred(*first1,*first2))
			return false;
			++first1;
			++first2;
		}
		return true;
	};

}
#endif