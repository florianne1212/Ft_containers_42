#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include <iostream>
#include "iterator.hpp"


// template < class T >
// struct Iterator;

namespace ft {
    template <typename Iterator>
    class reverse_iterator
    {
        public:
           // typedef Iterator							Iterator;
			typedef typename ft::iterator_traits<Iterator>::value_type		    value_type;
			typedef typename ft::iterator_traits<Iterator>::pointer			pointer;
            typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::reference		reference;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;

		private:
			Iterator _ptr;

        public:
            reverse_iterator()
            {}

            reverse_iterator(Iterator it) : _ptr(it)
            {}

			template <typename Iter>
            reverse_iterator(const reverse_iterator<Iter>& rev_it) : _ptr(rev_it.base())
            {}

            template <typename Iter>	reverse_iterator&	operator=(const reverse_iterator<Iter> &u) {
				_ptr = u.base();
				return *this;
			}

            ~reverse_iterator()
            {}


            Iterator
            base() const
            {
                return (_ptr);
            }
            
            reference operator*() const
			{
				Iterator	tmp = _ptr;
				return *(--tmp);
			}


            reverse_iterator operator+(difference_type n)
            {
				return(reverse_iterator(_ptr - n));
            }
            
            reverse_iterator& operator++()
            {
                this->_ptr--;
				return(*this);
            }

            reverse_iterator operator++(int)
            {
                reverse_iterator	tmp(*this);
				operator++();
				return tmp;
            }

            reverse_iterator& operator+= (difference_type n)
            {
                _ptr -= n;
				return *this;
            }
            
            reverse_iterator operator- (difference_type n)
            {
				return(reverse_iterator(_ptr + n));
            }

            reverse_iterator &
            operator--()
            {
                this->_ptr++;
				return(*this);
            }
                
            reverse_iterator
            operator--(int)
            {
                reverse_iterator tmp = *this;
				this->_ptr++;
				return(tmp);
            }

            reverse_iterator& operator-= (difference_type n)
            {
                _ptr += n;
				return *this;
            }
            
            pointer operator->() const
            {
                return &(operator*());
            }
            

            reference operator[] (difference_type n)
            {
                return this->_ptr[-n - 1];
            }

    };

	template <typename U, typename V>
	bool	operator==(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <typename U, typename V>
	bool	operator!=(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <typename U, typename V>
	bool		operator>(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() < rhs.base();
	}

	template <typename U, typename V>
	bool		operator<(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <typename U, typename V>
	bool		operator>=(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <typename U, typename V>
	bool		operator<=(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <typename U, typename V>
	ptrdiff_t		operator-(const reverse_iterator<U>& lhs, const reverse_iterator<V>& rhs) {
		return rhs.base() - lhs.base();
	}

	template <typename U>
	reverse_iterator<U>		operator+(typename reverse_iterator<U>::difference_type n, const reverse_iterator<U>& rhs) {
		return (reverse_iterator<U>)(rhs.base() - n);
	}

}
#endif
