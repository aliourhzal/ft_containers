#pragma once

#include "vector/pair.hpp"
#include <iostream>
#include "iterators.hpp"

# define RED 1
# define BLACK 0

namespace ft
{
	template<typename T>
	class Node
	{
		public:
			T		data;
			Node*	parent;
			Node*	left;
			Node*	right;
			int     color;
			Node(T obj) : data(obj){}
	};

	template <class T, class Compare, class _Alloc>
	class   _Rb_tree
	{
		public:
			typedef T						value_type;
			typedef Compare					key_compare;
			typedef value_type* 			pointer;
			typedef const value_type* 		const_pointer;
			typedef value_type& 			reference;
			typedef const value_type& 		const_reference;
			typedef size_t 					size_type;
			typedef ptrdiff_t 				difference_type;
			typedef _Alloc 					allocator_type;
		private:
			typedef typename    _Alloc::template rebind<Node<T>>::other		node_allocator;
			typedef Node<value_type>										node_type;
			typedef node_type*												nodePtr;
			typedef typename	value_type::first_type						key_type;
			typedef typename	value_type::second_type						mapped_type;
		public:
			typedef ft::mapIterator<pointer, nodePtr>						iterator;
			typedef ft::mapIterator<const_pointer, nodePtr>					const_iterator;
			typedef ft::mapRevIterator<pointer, nodePtr>					reverse_iterator;
			typedef ft::mapRevIterator<const_pointer, nodePtr>				const_reverse_iterator;
		private:
			size_type	_size;
			nodePtr root;
			key_compare	_cmp;
			node_allocator _alloc;

			void    _left_Rotation(nodePtr   x)
			{
				nodePtr child = x->right;
				x->right = child->left;
				if (child->left != this->NIL)
					child->left->parent = x;
				child->parent = x->parent;
				if(x->parent == nullptr)
					this->root = child;
				else if (x == x->parent->left)
					x->parent->left = child;
				else
					x->parent->right = child;
				child->left = x;
				x->parent = child;
			}
			void	_right_Rotation(nodePtr	x)
			{
				nodePtr child = x->left;
				x->left = child->right;
				if (child->right != this->NIL)
					child->right->parent = x;
				child->parent = x->parent;
				if (x->parent == nullptr)
					this->root = child;
				else if (x == x->parent->right)
					x->parent->right = child;
				else
					x->parent->left = child;
				child->right = x;
				x->parent = child;
			}

			void	_maintain_Insert(nodePtr	new_Node)
			{
				nodePtr	u;
				while(new_Node->parent->color == RED)
				{
					if (new_Node->parent == new_Node->parent->parent->right)
					{
						u = new_Node->parent->parent->left;
						if (u->color == RED)
						{
							u->color = BLACK;
							new_Node->parent->color = BLACK;
							new_Node->parent->parent->color = RED;
							new_Node = new_Node->parent->parent;
						}
						else
						{
							if (new_Node == new_Node->parent->left)
							{
								new_Node = new_Node->parent;
								this->_right_Rotation(new_Node);
							}
							new_Node->parent->color = BLACK;
							new_Node->parent->parent->color = RED;
							this->_left_Rotation(new_Node->parent->parent);
						}
					}
					else
					{
						u = new_Node->parent->parent->right;
						if (u->color == RED)
						{
							u->color = BLACK;
							new_Node->parent->color = BLACK;
							new_Node->parent->parent->color = RED;
							new_Node = new_Node->parent->parent;
						}
						else
						{
							if (new_Node == new_Node->parent->right)
							{
								new_Node = new_Node->parent;
								this->_left_Rotation(new_Node);
							}
							new_Node->parent->color = BLACK;
							new_Node->parent->parent->color = RED;
							this->_right_Rotation(new_Node->parent->parent);
						}
					}
					if (new_Node == this->root)
						break;
				}
				this->root->color = BLACK;
			}

			void	_maintain_Delete(nodePtr	x)
			{
				nodePtr	w;
				while(x != this->root && x->color == BLACK)
				{
					if (x == x->parent->left)
					{
						w = x->parent->right;
						if (w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							_left_Rotation(x->parent);
							w = x->parent->right;
						}
						if (w->left->color == BLACK && w->right->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else 
						{
							if (w->right->color == BLACK)
							{
								w->left->color = BLACK;
								w->color = RED;
								_right_Rotation(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right->color = BLACK;
							_left_Rotation(x->parent);
							x = this->root;
						}
					}
					else
					{
						w = x->parent->left;
						if (w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							_right_Rotation(x->parent);
							w = x->parent->left;
						}
						if (w->right->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else 
						{
							if (w->left->color == BLACK)
							{
								w->right->color = BLACK;
								w->color = RED;
								_left_Rotation(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left->color = BLACK;
							_right_Rotation(x->parent);
							x = this->root;
						}
					}
				}
				x->color = BLACK;
			}

		public:
			nodePtr NIL;
			_Rb_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _cmp(comp), _alloc(alloc), _size(0)
			{
				this->NIL = this->_alloc.allocate(1);
				this->NIL->color = BLACK;
				this->NIL->left = nullptr;
				this->NIL->right = nullptr;
				this->root = this->NIL;
			}
			/* Iterators */

			iterator				begin()			{return iterator(minimum(this->root));}
			const_iterator			begin() const 	{return const_iterator(minimum(this->root));}
			iterator				end()			{return iterator(this->NIL);}
			const_iterator			end() const		{return const_iterator(this->NIL);}
			reverse_iterator		rbegin()		{return reverse_iterator(this->NIL);}
			const_reverse_iterator	rbegin() const	{return const_reverse_iterator(this->NIL);}
			reverse_iterator		rend()			{return reverse_iterator(this->minimum(this->root));}
			const_reverse_iterator	rend() const	{return const_reverse_iterator(this->minimum(this->root));}
			
			void printHelper(nodePtr root, std::string indent, bool last)
			{
				if (root != this->NIL) {
				std::cout << indent;
				if (last) {
					std::cout << "R----";
					indent += "   ";
				} else {
					std::cout << "L----";
					indent += "|  ";
				}

				std::string sColor = root->color ? "RED" : "BLACK";
				std::cout << root->data.first << "(" << sColor << ")" << std::endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
				}
			}
			void printTree() {
				if (root) {
					printHelper(this->root, "", true);
				}
			}
			int	insert(value_type	data)
			{
				static int i = 0;
				nodePtr	new_Node = this->_alloc.allocate(1);
				this->_alloc.construct(new_Node, data);
				new_Node->color = RED;
				new_Node->left = this->NIL;
				new_Node->right = this->NIL;
				if (this->root == this->NIL)
				{
					new_Node->color = BLACK;
					this->root = new_Node;
				}
				else
				{
					nodePtr	x = this->root;
					nodePtr	y;
					while(x != this->NIL)
					{
						y = x;
						if (this->_cmp(new_Node->data.first, x->data.first))
							x = x->left;
						else if (this->_cmp(x->data.first, new_Node->data.first))
							x = x->right;
						else
							return 1;
					}
					new_Node->parent = y;
					if (this->_cmp(new_Node->data.first, y->data.first))
						y->left = new_Node;
					else
						y->right = new_Node;
					this->_maintain_Insert(new_Node);
				}
				this->_size++;
				return 0;
			}

			void	switchPositions(nodePtr	_P, nodePtr	child)
			{
				if (_P->parent == nullptr)
					this->root = child;
				else if (_P == _P->parent->left)
					_P->parent->left = child;
				else
					_P->parent->right = child;
				child->parent = _P->parent;
			}

			nodePtr	minimum(nodePtr	root)
			{
				while(root->left != this->NIL)
					root = root->left;
				return (root);
			}

			nodePtr	maximum(nodePtr	root)
			{
				while(root->right != this->NIL)
					root = root->right;
				return (root);
			}

			nodePtr	search(key_type k)
			{
				nodePtr	r = this->root;
				while (r->data.first != k && r != this->NIL)
				{
					if (k < r->data.first)
						r = r->left;
					else if (k > r->data.first)
						r = r->right;
				}
				return (r);
			}

			void	delete_node(key_type	key)
			{
				nodePtr node = this->root;
				nodePtr	x;
				nodePtr	y;
				node = this->search(key);
				if (node == this->NIL)
					return;
				int origrinalColor = node->color;
				y = node;
				if (node->left == this->NIL)
				{
					x = node->right;
					switchPositions(node, node->right);
				}
				else if (node->right == this->NIL)
				{
					x = node->left;
					switchPositions(node, node->left);
				}
				else
				{
					y = minimum(node->right);
					origrinalColor = y->color;
					x = y->right;
					if (y->parent == node)
						x->parent = y;
					else
					{
						switchPositions(y, y->right);
						y->right = node->right;
						y->right->parent = y;
					}
					switchPositions(node, y);
					y->left = node->left;
					y->left->parent = y;
					y->color = node->color;
				}
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
				if (origrinalColor == BLACK)
					_maintain_Delete(x);
			}

			/* Capacity */

			bool empty() const
			{
				return (this->_size == 0);
			}

			size_type size() const
			{
				return (this->_size);
			}

			size_type max_size() const
			{
				return (this->_alloc.max_size());
			}

			/* Modifiers */

			void clear()
			{
				while (this->_size > 0)
				{
					delete_node(this->root->data.first);
					this->_size--;
				}
			}
	};
	
	template <class NodePtr>
	NodePtr	_getSuccessor(NodePtr node) {
		if (node->right)
			return _getMin(node->right);
		NodePtr	temp = node->parent;
		while (temp && node == temp->right) {
			node = temp;
			temp = temp->parent;
		}
		return temp;
	};

	template <class NodePtr>
	NodePtr	_getPredecessor(NodePtr node) {
		if (node->left)
			return _getMax(node->left);
		NodePtr	temp = node->parent;
		while (temp && node == temp->left) {
			node = temp;
			temp = temp->parent;
		}
		return temp;
	};
};