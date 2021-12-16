  #ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iostream>


namespace ft {
	template < class Key, class T >
	class BSTNode
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef pair<Key, T> value_type;
			BSTNode *_left;
			BSTNode *_right;
			BSTNode *_parent;
			value_type _data;
		
		public:
			BSTNode():
			_left(NULL),
			_right(NULL),
			_parent(NULL)
			{}

			BSTNode(const pair<Key, T> p) : 
            _data(p),
			_left(NULL),
			_right(NULL),
			_parent(NULL)
			{}

			~BSTNode()
			{}

			BSTNode& operator= (const BSTNode& x)
			{ 
				_parent = x._parent;
				_data = x._data;
				_right = x._right;
				_left = x._left;

				return(*this);
			}

			BSTNode<Key, T> *as_left_as_you_can(BSTNode<Key, T> *node)
				{
					if(node)
					{
						while (node->_left)
							node=node->_left;
					}
					return(node);
				}

				BSTNode<Key, T> *as_right_as_you_can(BSTNode<Key, T> *node)
				{
					if(node)
					{
						while (node->_right)
							node=node->_right;
					}
					return(node);
				}

				BSTNode<Key, T> *as_upleft_as_you_can(BSTNode<Key, T> *node)
				{
					if(!node)
						return(NULL);
					while (node->_parent != NULL && node != node->_parent->_left)
						node = node->_parent;
						
					return(node->_parent);
				}

				BSTNode<Key, T> *as_upright_as_you_can(BSTNode<Key, T> *node)
				{
					if(!node)
						return(NULL);
					while (node->_parent != NULL && node != node->_parent->_right)
						node = node->_parent;
						
					return(node->_parent);
				}
	
        
		
	};

	

	template < class Key, class T >
		class mapIterator 
		{
			public :
				typedef pair<Key, T> value_type;
				typedef value_type &reference;
				typedef value_type *pointer;
				typedef std::ptrdiff_t			difference_type;
				typedef typename std::bidirectional_iterator_tag	iterator_category;

			private :
				BSTNode<Key, T> *_node;
		
			public:
				/** (constructor) **/
				mapIterator():
				_node(NULL)
				{}

				mapIterator(BSTNode<Key, T> *node):
				_node(node)
				{}

				mapIterator(const mapIterator& copy):
				_node(copy._node)
				{
				}
				/** (destructor) **/
				~mapIterator()
				{}

				mapIterator& operator= (const mapIterator& ope)
				{
					this->_node = ope._node;
					return(*this);
				}
				

			// 	/** getter **/
				BSTNode<Key, T> *get_node()const
				{
					return(this->_node);
				}


				const BSTNode<Key, T> *const_getnode() const
				{
					return(this->_node);
				}

			// 	/** ITERATORS **/

				/** a == b **/
				friend bool		operator==( const mapIterator& lhs, const mapIterator& rhs ) { return lhs._node == rhs._node; }

				/** a != b **/
				bool operator!=(const mapIterator &other) const
				{
					return(_node != other._node);
				}
				
				/** *a **/
				pair<Key, T> &operator*() const
				{
					return(_node->_data);
				}
				
				/** a->m **/
				pointer operator->() const
				{
					return(&(_node->_data));
				}

				/** --a **/
				mapIterator& operator--()
				{
					if (_node->_left != NULL)
						_node = _node->as_right_as_you_can(_node->_left);
					else
						_node = _node->as_upright_as_you_can(_node);
					return(*this);
				}
				
				/** a-- **/
				mapIterator operator--(int)
				{
					mapIterator copy= *this;
					operator--();
					return(copy);
				}

				/** ++a **/
				mapIterator operator++()
				{
					if(!_node)
						return NULL;
					if (_node->_right != NULL)
						_node = _node->as_left_as_you_can(_node->_right);
					else
						_node = _node->as_upleft_as_you_can(_node);
					return(*this);
				}
				
				/** a++ **/
				mapIterator operator++(int)
				{
					mapIterator copy= *this;
					operator++();
					return(copy);
				}
		
	};

	template < class Key, class T >
	class mapConstIterator 
	{
		public :
			typedef pair<Key, T> value_type;
			typedef const value_type &reference;
			typedef const value_type *pointer;
			typedef std::ptrdiff_t			difference_type;
			typedef typename std::bidirectional_iterator_tag	iterator_category;

		private :
			BSTNode<Key, T> *_node;
	
		public:
			/** (constructor) **/
			mapConstIterator ():
			_node(NULL)
			{}

			mapConstIterator (BSTNode<Key, T> *node):
			_node(node)
			{}

			mapConstIterator (const mapConstIterator& copy):
			_node(copy._node)
			{
			}

			mapConstIterator (const mapIterator<Key, T>& ite):
			_node(ite.get_node())
			{
			}

			

			/** (destructor) **/
			~mapConstIterator ()
			{}

			mapConstIterator& operator= (const mapConstIterator& ope)
			{
				this->_node = ope._node;
				return(*this);
			}
			

		// 	/** getter **/
			const BSTNode<Key, T> *get_node()
			{
				return(this->_node);
			}

			const BSTNode<Key, T> *const_getnode() const
			{
				return(this->_node);
			}

		// 	/** ITERATORS **/
			
			/** a == b **/
			friend bool	operator==( const mapConstIterator& lhs, const mapConstIterator& rhs ) { return lhs._node == rhs._node; }

			/** a != b **/
			bool operator!=(const mapConstIterator &other) const
			{
				return(_node != other._node);
			}
			
			/** *a **/
			const pair<Key, T> &operator*() const
			{
				return(_node->_data);
			}
			
			/** a->m **/
			pointer operator->() const
			{
				return(&(_node->_data));
			}

			/** --a **/
			mapConstIterator& operator--()
			{
				if (_node->_left != NULL)
					_node = _node->as_right_as_you_can(_node->_left);
				else
					_node = _node->as_upright_as_you_can(_node);
				return(*this);
			}
			
			/** a-- **/
			mapConstIterator operator--(int)
			{
				mapConstIterator copy= *this;
				operator--();
				return(copy);
			}

			/** ++a **/
			mapConstIterator operator++()
			{
				if(!_node)
					return NULL;
				if (_node->_right != NULL)
					_node = _node->as_left_as_you_can(_node->_right);
				else
					_node = _node->as_upleft_as_you_can(_node);
				return(*this);
			}
			
			/** a++ **/
			mapConstIterator operator++(int)
			{
				mapConstIterator copy= *this;
				operator++();
				return(copy);
			}

	};
}

#include "map.hpp"

#endif
