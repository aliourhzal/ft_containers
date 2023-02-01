#pragma once

#include "vector/pair.hpp"
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
			typedef Compare													key_compare;
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
			typedef typename	value_type::first_type						key_type;
			typedef typename	value_type::second_type						mapped_type;
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
			nodePtr STR;
			_Rb_tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _cmp(comp), _alloc(alloc), _size(0)
			{
				this->NIL = this->_alloc.allocate(1);
				this->NIL->color = BLACK;
				this->NIL->left = nullptr;
				this->NIL->right = nullptr;
				this->root = this->NIL;
			}
			/* nodePtrs */

			nodePtr		begin()			{return (minimum(this->root));}
			nodePtr		begin() const 	{return (minimum(this->root));}
			nodePtr		end()			{return (this->NIL);}
			nodePtr		end() const		{return (this->NIL);}
			
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
				while(root->left != this->NIL)
					root = root->left;
				return (root);
			}

			nodePtr	maximum(nodePtr	root) const
			{
				while(root->right != this->NIL)
					root = root->right;
				return (root);
			}

			nodePtr	search(key_type k) const
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

			int	insert(value_type	data)
			{
				nodePtr last;
				nodePtr	new_Node = this->_alloc.allocate(1);
				this->_alloc.construct(new_Node, data);
				new_Node->color = RED;
				new_Node->left = this->NIL;
				new_Node->right = this->NIL;
				new_Node->parent = nullptr;
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
				last = maximum(this->root);
				last->right->parent = last;
				return 0;
			}

			void	delete_node(key_type	key)
			{
				nodePtr node;
				nodePtr	x;
				nodePtr	y;
				nodePtr	last;
				node = this->search(key);
				if (node == this->NIL)
					return;
				int origrinalColor = node->color;
				y = node;
				if (node->left == this->NIL)
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
				{
					last = maximum(this->root);
					last->right->parent = last;
				}
			}

			/* Capacity */

			bool		empty()		const { return (this->_size == 0); }
			size_type	size()		const { return (this->_size); }
			size_type	max_size()	const { return (this->_alloc.max_size()); }

			/* Modifiers */

			void clear()
			{
				while (this->_size > 0)
					delete_node(this->root->data.first);
			}

			void	swap(_Rb_tree& other)
			{
				_Rb_tree tmp;

				for (nodePtr i = other.begin(); i != other.end(); i++)
					tmp.insert(*i);
				other.clear();
				for (nodePtr i = this->begin(); i != this->end(); i++)
					other.insert(*i);
				this->clear();
				for (nodePtr i = tmp.begin(); i != tmp.end(); i++)
					this->insert(*i);
			}

			/*-------- Operations --------*/
			
			nodePtr	find(const key_type& k) 		{ return (nodePtr(this->search(k))); }
			nodePtr	find(const key_type& k)	const	{ return (nodePtr(this->search(k))); }

			size_type	count_unique(const key_type& k) const
			{
				nodePtr i;

				i = this->search(k);
				if (i != this->NIL)
					return (1);
				return (0);
			}

			nodePtr	lower_bound(const key_type& k)
			{
				nodePtr i;
			
				i = this->begin();
				while(this->_cmp(i->first, k) && i != this->end())
					i++;
				return (i);
			}

			nodePtr lower_bound(const key_type& k) const
			{
				nodePtr i;
				
				i = this->begin();
				while(this->_comp(i->first, k) && i != this->end())
					i++;
				return (i);
			}

			nodePtr upper_bound(const key_type& k)
			{
				nodePtr i;

				i = this->begin();
				while(this->_comp(i->first, k) && i != this->end())
					i++;
				if (i->first == k)
					i++;
				return (i);
			}

			nodePtr upper_bound (const key_type& key) const
			{
				nodePtr i;
				
				i = this->begin();
				while(this->_comp(i->first, key) && i != this->end())
					i++;
				if (i->first == key)
					i++;
				return (i);
			}

			ft::pair<nodePtr,nodePtr>	equal_range_unique (const key_type& k)
			{
				return (ft::make_pair<nodePtr,nodePtr>(this->lower_bound(k), this->upper_bound(k)));
			}

			ft::pair<nodePtr,nodePtr> equal_range_unique (const key_type& k) const
			{
				return (ft::make_pair<nodePtr,nodePtr>(this->lower_bound(k), this->upper_bound(k)));
			}
	};
	
	template <class NodePtr>
	NodePtr	minimum(NodePtr	root)
	{
		while(root->left->left)
			root = root->left;
		return (root);
	}

	template <class NodePtr>
	NodePtr	maximum(NodePtr	root)
	{
		while(root->right->right)
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
		while (temp && node == temp->right) {
			node = temp;
			temp = temp->parent;
		}
		if (!temp)
			return (last->right);
		return temp;
	};

	template <class NodePtr>
	NodePtr	_getPredecessor(NodePtr node) {
		if (node->left && node->left->left)
			return maximum(node->left);
		NodePtr	temp = node->parent;
		while (temp && node == temp->left) {
			node = temp;
			temp = temp->parent;
		}
		return temp;
	};
};

/*
	maintain tree after insertion (maintainInsert(x)):
		4 scenarios of red black tree insertion violations:
			1- Z is root;
			2- Z.uncle is RED;
			3- Z.uncle is BLACK(triangle)
			4- Z.uncle is BLACK(line)

			SOLUTIONS:
				1- color Z black;
				2- recolor Z.parent, Z.uncle, Z.GP, Z = Z.GP;
				3- rotate Z.parent in the opposite direction of Z
				4- rotate Z.GP in the opposite direction of Z and recolor the original parent and GP of Z  
	
	maintain tree after deletion (maintainDelete(x)):
		let w = x.sibling;
		4 scenarios of red black tree deletion violations:
			1- w is RED;
			2- w is BLACK and w.left and w.right are BLACK;
			3- w is BLACK and w.left is RED and w.right is BLACK;
			4- w is BLACK and w.right is RED;

			SOLUTIONS:
				1- recolor w and w.parent and rotate w.parent in the opposite direction of w then w = x.sibling;
				2- w.color = RED and x = x.p
				3- recolor w.left and w, rotate w in the same direction, w = x.sibling;
				4- recolor w and w.parent and w.(the same direction of w) then rotate x.parent in the opposite direction of w
		
*/