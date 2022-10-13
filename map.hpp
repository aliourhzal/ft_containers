#pragma once

#include <iostream>
#include "_Rb_tree.hpp"
#include "vector/pair.hpp"


namespace	ft
{
	template < class Key, class T, class Compare = std::less<Key>,class Alloc = std::allocator<std::pair<const Key,T> >>
	class map
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef	ft::pair<const key_type,mapped_type>			value_type;
			typedef	Compare											key_compare;
			typedef	Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::difference_type		difference_type;
			typedef typename allocator_type::size_type				size_type;
		private:
			typedef	Node<value_type>								Node_type;
			typedef	Node_type*										NodePtr;
			typedef	_Rb_tree<value_type, key_compare, Alloc>		Tree_type;

		public:
			typedef typename Tree_type::iterator					iterator;
			typedef typename Tree_type::const_iterator				const_iterator;
			typedef typename Tree_type::reverse_iterator			reverse_iterator;
			typedef typename Tree_type::const_reverse_iterator		const_reverse_iterator;

			class	value_compare
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
		private:
			Tree_type	_tree;
			key_compare	_comp;
			allocator_type	_alloc;
		public:

		/* Constructors */

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc), _comp(comp){}
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _tree(comp, alloc), _comp(comp) { this->insert(first, last); };
			map(const map& x) { *this = x; };
			~map() {this->clear();}

		/* Iterators */

		iterator 				begin() 		{return (this->_tree.begin());}
		const_iterator 			begin() const 	{return (this->_tree.begin());}
		iterator				end() 			{return (this->_tree.end());}
		const_iterator			end() const 	{return (this->_tree.end());}
		reverse_iterator		rbegin()		{return (this->_tree.rbegin());}
		const_reverse_iterator	rbegin() const	{return (this->_tree.rbegin());}
		reverse_iterator		rend()			{return (this->_tree.rend());}
		const_reverse_iterator	rend() const	{return (this->_tree.rend());}

		/* Capacity */

		bool		empty() const		{ return this->_tree.empty(); };
		size_type	size() const		{ return this->_tree.size(); };
		size_type	max_size() const	{ return this->_tree.max_size(); };

		/* Modifiers */
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				ft::pair<iterator, bool> r;
				if (this->_tree.insert(val))
					r.second = false;
				else
					r.second = true;
				NodePtr p = search(val.first);
				r.first = iterator(p);
				return (r);
			}
			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					this->_tree.insert(*first)				
			}

			void erase (iterator position)
			{
				this->_tree.delete_node(*position.first);
			}

			void erase (iterator first, iterator last)
			{
				for (; first != last; first++)
					this->erase(first);
			}

			size_type erase (const key_type& k){
				this->_tree.delete_node(k);
				return (1);
			}

			void clear() {this->_tree.clear();};

		/* Access Elements */

		mapped_type& operator[] (const key_type& k)
		{
			NodePtr	p;

			p = this->_tree.search(k);
			if (p != this->_tree.NIL)
				return (p->data.second);
			this->_tree.insert(std::pair<key_type, mapped_type>(k, mapped_type()));
			p = this->_tree.search(k);
			return (p->data.second);
		}

		/* Allocator */
		
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}

	};
};