#pragma once

#include <iostream>
#include "_Rb_tree.hpp"
#include "vector/pair.hpp"
#include "vector/utility.hpp"
#include "iterators.hpp"
#include "reverse_iterator.hpp"

namespace	ft
{

	template < class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set
	{
		public:
			typedef Key												key_type;
			typedef	Key												value_type;
			typedef	Compare											key_compare;
			typedef	Compare											value_compare;
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
			typedef typename ft::mapIterator<value_type, NodePtr>			iterator;
			typedef typename ft::mapIterator<const value_type, NodePtr>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
			Tree_type	_tree;
			key_compare	_comp;
			allocator_type	_alloc;
		public:

		/* Constructors */

			set () : _tree(value_compare(), allocator_type()) {}
			explicit set( const Compare& comp, const allocator_type& alloc = allocator_type() ) : _tree(comp, alloc), _comp(comp), _alloc(alloc){}
			template <class InputIterator>
				set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: _tree(comp, alloc), _comp(comp), _alloc(alloc) { this->insert(first, last); };
			set (const set& other) : _tree(other._comp, other._alloc) { *this = other; };
			~set () {this->clear();}
			set& operator=( const set& other )
			{
				this->clear();
				for (iterator it = other.begin(); it != other.end(); it++)
					this->insert(*it);
				return (*this);
			}

		/* Iterators */

		iterator 					begin() 			{return iterator(this->_tree.begin());}
		const_iterator 				begin()		const 	{return const_iterator(this->_tree.begin());}
		iterator					end()				{return iterator(this->_tree.end());}
		const_iterator				end()		const 	{return const_iterator(this->_tree.end());}
		reverse_iterator			rbegin()			{return (reverse_iterator(end()));}
		reverse_iterator			rend()				{return (reverse_iterator(begin()));}
		const_reverse_iterator		rbegin()	const	{return (const_reverse_iterator(end()));}
		const_reverse_iterator		rend()		const	{return (const_reverse_iterator(begin()));}


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
			NodePtr p = this->_tree.search(val);
			r.first = iterator(p);
			return (r);
		}
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for (; first != last; first++)
				this->_tree.insert(*first);				
		}

		iterator insert (iterator position, const value_type& val) { return (insert(val).first);}

		void erase (iterator position) { this->_tree.delete_node(*position); }

		void erase (iterator first, iterator last)
		{
			iterator tmp;
			while (first != last)
			{
				tmp = first++;
				this->erase(tmp);
			}
		}

		size_type erase (const key_type& k){
			if (!this->_tree.delete_node(k))
				return (0);
			return (1);
		}

		void swap( set& other ) { this->_tree.swap(other._tree); }

		void clear() {this->_tree.clear();};
		
		/* Observers */

		key_compare key_comp() const		{ return (_comp); }
		value_compare value_comp() const	{ return (value_compare()); }

		/* Operations */

		iterator 								find(const key_type& k) 				{ return (this->_tree.find(k)); }
		const_iterator							find(const key_type& k)	const			{ return (this->_tree.find(k)); }
		size_type								count(const key_type& k) const			{ return (this->_tree.count_unique(k)); }
		iterator								lower_bound( const key_type& k) 		{ return (this->_tree.lower_bound(k)); }
		const_iterator							lower_bound( const key_type& k) const	{ return (this->_tree.lower_bound(k)); }
		iterator								upper_bound (const key_type& k)			{ return (this->_tree.upper_bound(k)); }
		const_iterator 							upper_bound (const key_type& k) const	{ return (this->_tree.upper_bound(k)); }
		ft::pair<iterator,iterator>				equal_range (const key_type& k)			{ return (this->_tree.equal_range_unique(k)); }
		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k)	const	{ return (this->_tree.equal_range_unique(k)); }

		/* Allocator */
		
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}
	};

	template< class Key, class Compare, class Alloc >
	bool operator==( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template< class Key, class Compare, class Alloc >
	bool operator!=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}
	template< class Key, class Compare, class Alloc >
	bool operator<( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template< class Key, class Compare, class Alloc >
	bool operator<=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (lhs < rhs || lhs == rhs);
	}
	template< class Key, class Compare, class Alloc >
	bool operator>( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (!(lhs <= rhs));
	}
	template< class Key, class Compare, class Alloc >
	bool operator>=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}
};