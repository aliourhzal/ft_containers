#pragma once

#include "pair.hpp"
#include <iostream>

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
			typedef T														value_type;
			typedef Compare													value_compare;
			typedef value_type* 											pointer;
			typedef const value_type* 										const_pointer;
			typedef value_type& 											reference;
			typedef const value_type& 										const_reference;
			typedef size_t 													size_type;
			typedef ptrdiff_t 												difference_type;
			typedef _Alloc 													allocator_type;
		private:
			typedef typename    _Alloc::template rebind<Node<T> >::other	node_allocator;
			typedef Node<value_type>										node_type;
			typedef node_type*												nodePtr;
		private:
			size_type	_size;
			value_compare	_comp;
			node_allocator _alloc;

			void updateEdges()
			{
				nodePtr last;
				nodePtr first;

				last = maximum(this->root);
				last->right->parent = last;
				first = minimum(this->root);
				first->left = this->STR;
				this->STR->parent = first;
			}

			nodePtr newNode(value_type &data)
			{
				nodePtr	new_Node = this->_alloc.allocate(1);
				this->_alloc.construct(new_Node, data);
				new_Node->color = RED;
				new_Node->left = this->NIL;
				new_Node->right = this->NIL;
				new_Node->parent = nullptr;
				return (new_Node);
			}

			void    _left_Rotation(nodePtr   x)
			{
				nodePtr child = x->right;
				x->right = child->left;
				if (child->left != this->NIL && child->left != this->STR)
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

			nodePtr	_getSuccessor(nodePtr node)
			{
				nodePtr	last;

				last = node;
				if (node->right && node->right->right)
					return minimum(node->right);
				nodePtr	temp = node->parent;
				while (temp && node == temp->right && node != temp->left) {
					node = temp;
					temp = temp->parent;
				}
				if (!temp)
					return (last->right);
				return temp;
			};
		
		public:
			nodePtr NIL;
			nodePtr STR;
			nodePtr root;
			_Rb_tree(const value_compare& comp, const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _size(0)
			{
				this->NIL = this->_alloc.allocate(1);
				this->NIL->color = BLACK;
				this->NIL->left = nullptr;
				this->NIL->right = nullptr;
				this->STR = this->_alloc.allocate(1);
				this->STR->color = BLACK;
				this->STR->left = this->STR;
				this->STR->right = nullptr;
				this->root = this->NIL;
			}
			_Rb_tree(nodePtr root)
			{
				this->root = root;
			}
			~_Rb_tree() {
				this->clear();
				this->_alloc.destroy(this->NIL);
				this->_alloc.deallocate(this->NIL, 1);
				this->_alloc.destroy(this->STR);
				this->_alloc.deallocate(this->STR, 1);
				//also deallocate STR
			}
			/* nodePtrs */

			nodePtr		begin()			{return (minimum(this->root));}
			nodePtr		begin() const 	{return (minimum(this->root));}
			nodePtr		end()			{return (this->NIL);}
			nodePtr		end() const		{return (this->NIL);}
			
			void printHelper(nodePtr root, std::string indent, bool last)
			{
				if (root != this->NIL && root != this->	STR) {
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

			void	switchPositions(nodePtr	_P, nodePtr	child) //move subtree within he tree
			{
				if (_P->parent == nullptr)
					this->root = child;
				else if (_P == _P->parent->left)
					_P->parent->left = child;
				else
					_P->parent->right = child;
				child->parent = _P->parent;
			}

			nodePtr	minimum(nodePtr	root) const
			{
				while((root != this->NIL && root->left != this->NIL)
						&& (root != this->STR && root->left != this->STR))
					root = root->left;
				return (root);
			}

			nodePtr	maximum(nodePtr	root) const
			{
				while((root != this->NIL && root->right != this->NIL)
						&& (root != this->STR && root->right != this->STR))
					root = root->right;
				return (root);
			}

			nodePtr	search(value_type k) const
			{
				nodePtr	r = this->root;
				while (r != this->NIL && r != this->STR)
				{
					if (_comp(k, r->data))
						r = r->left;
					else if (_comp(r->data, k))
						r = r->right;
					else
						break;
				}
				return (r);
			}

			int	insert(value_type	data)
			{
				nodePtr	new_Node = newNode(data);
				if (this->root == this->NIL)
				{
					new_Node->color = BLACK;
					this->root = new_Node;
				}
				else
				{
					nodePtr	x = this->root;
					nodePtr	y;
					while(x != this->NIL && x != this->STR)
					{
						y = x;
						if (this->_comp(new_Node->data, x->data))
							x = x->left;
						else if (this->_comp(x->data, new_Node->data))
							x = x->right;
						else
						{
							this->_alloc.destroy(new_Node);
							this->_alloc.deallocate(new_Node, 1);
							return 1;
						}
					}
					new_Node->parent = y;
					if (this->_comp(new_Node->data, y->data))
						y->left = new_Node;
					else
						y->right = new_Node;
					this->_maintain_Insert(new_Node);
				}
				this->_size++;
				updateEdges();
				return 0;
			}

			int	insertHint(value_type	data, nodePtr	y)
			{
				nodePtr	new_Node = newNode(data);
				if (this->root == this->NIL)
				{
					new_Node->color = BLACK;
					this->root = new_Node;
				}
				else
				{
					new_Node->parent = y;
					if (this->_comp(new_Node->data, y->data))
						y->left = new_Node;
					else
						y->right = new_Node;
					this->_maintain_Insert(new_Node);
				}
				this->_size++;
				updateEdges();
				return 0;
			}

			int	delete_node(const value_type&	key)
			{
				nodePtr node;
				nodePtr	x;
				nodePtr	y;
				nodePtr	last;
				node = this->search(key);
				if (node == this->NIL || node == this->STR)
					return (0);
				int origrinalColor = node->color;
				y = node;
				if (node->left == this->NIL || node->left == this->STR)
				{
					x = node->right;
					switchPositions(node, x);
				}
				else if (node->right == this->NIL)
				{
					x = node->left;
					switchPositions(node, x);
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
				this->_size--;
				if (this->_size > 0)
					updateEdges();
				return (1);
			}

			/* Capacity */

			bool		empty()		const { return (this->_size == 0); }
			size_type	size()		const { return (this->_size); }
			size_type	max_size()	const { return (this->_alloc.max_size()); }

			/* Modifiers */

			void destroyTree(nodePtr node)
			{
				if (node->left != this->NIL && node->left != this->STR)
					destroyTree(node->left);
				if (node->right != this->NIL && node->right != this->STR)
					destroyTree(node->right);
				if (node != this->NIL)
				{
					if (node != this->root && node == node->parent->right)
						node->parent->right = this->NIL;
					if (node != this->root && node == node->parent->left)
						node->parent->left = this->NIL;
					if (node == this->root)
						this->root = this->NIL;
					this->_alloc.destroy(node);
					this->_alloc.deallocate(node, 1);
				}
			}

			void	clear()
			{
				if (this->root != this->NIL)
					destroyTree(this->root);
				this->_size = 0;
			}

			void	swap(_Rb_tree &other)
			{
				nodePtr thisRoot = this->root;
				nodePtr thisNIL = this->NIL;
				nodePtr thisSTR = this->STR;
				int thisSize =	this->_size;
				
				this->root = other.root;
				this->NIL = other.NIL;
				this->STR = other.STR;
				this->_size = other._size;
				other.root = thisRoot;
				other.NIL = thisNIL;
				other.STR = thisSTR;
				other._size = thisSize;
			}

			/*-------- Operations --------*/
			
			nodePtr	find(const value_type& k) 		{ return (nodePtr(this->search(k))); }
			nodePtr	find(const value_type& k)	const	{ return (nodePtr(this->search(k))); }

			size_type	count_unique(const value_type& k) const
			{
				nodePtr i;

				i = this->search(k);
				if (i != this->NIL)
					return (1);
				return (0);
			}

			nodePtr	lower_bound(const value_type& k)
			{
				nodePtr i;
			
				i = this->begin();
				while(this->_comp(i->data, k) && i != this->end())
					i = this->_getSuccessor(i);
				return (i);
			}

			nodePtr lower_bound(const value_type& k) const
			{
				nodePtr i;
				
				i = this->begin();
				while(this->_comp(i->data, k) && i != this->end())
					i = this->_getSuccessor(i);
				return (i);
			}

			nodePtr upper_bound(const value_type& key)
			{
				nodePtr i;

				i = this->begin();
				while(this->_comp(i->data, key) && i != this->end())
					i = this->_getSuccessor(i);
				if (!this->_comp(key, i->data) && i != this->NIL)
					i = this->_getSuccessor(i);
				return (i);
			}

			nodePtr upper_bound (const value_type& key) const
			{
				nodePtr i;
				
				i = this->begin();
				while(this->_comp(i->data, key) && i != this->end())
					i = this->_getSuccessor(i);
				if (!this->_comp(key, i->data))
					i = this->_getSuccessor(i);
				return (i);
			}

			ft::pair<nodePtr,nodePtr>	equal_range_unique (const value_type& k)
			{
				return (ft::make_pair<nodePtr,nodePtr>(this->lower_bound(k), this->upper_bound(k)));
			}

			ft::pair<nodePtr,nodePtr> equal_range_unique (const value_type& k) const
			{
				return (ft::make_pair<nodePtr,nodePtr>(this->lower_bound(k), this->upper_bound(k)));
			}
	};
	
	template <class NodePtr>
	NodePtr	minimum(NodePtr	root)
	{
		while(root->left && root->left->left)
			root = root->left;
		return (root);
	}

	template <class NodePtr>
	NodePtr	maximum(NodePtr	root)
	{
		while(root->right && root->right->right)
			root = root->right;
		return (root);
	}

	template <class NodePtr>
	NodePtr	_getSuccessor(NodePtr node) {
		NodePtr	last;

		last = node;
		if (node->right && node->right->right)
			return minimum(node->right);
		NodePtr	temp = node->parent;
		while (temp && node == temp->right && node != temp->left) {
			node = temp;
			temp = temp->parent;
		}
		if (!temp)
			return (last->right);
		return temp;
	};

	template <class NodePtr>
	NodePtr	_getPredecessor(NodePtr node) {
		// std::cout << "hello" << std::endl;
		if (node->left && node->left->left)
			return maximum(node->left);
		NodePtr	temp = node->parent;
		while (temp && node == temp->left && node != temp->right) {
			node = temp;
			temp = temp->parent;
		}
		return temp;
	};
};
