#pragma once

#include "vector/iterator_traits.hpp"
#include "_Rb_tree.hpp"

namespace ft
{
	template<typename T, class NodePtr>
	class mapIterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::reference			reference;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef std::bidirectional_iterator_tag 				iterator_category;
			typedef	NodePtr											nodePtr;
		private:
			nodePtr	it;
		public:
			mapIterator() : it(){};
			explicit mapIterator(nodePtr	i) : it(i){};
			template<typename It>
				mapIterator(mapIterator<It, nodePtr>	&i) : it(i.base()){};

			nodePtr			base()						{return (this->it);}
			reference		operator*() const  	{return (this->it->data);}
			pointer			operator->() const 	{return &(this->it->data);}
			mapIterator		operator++()  		{it = _getSuccessor(it); return mapIterator(it);}
			mapIterator		operator++(int)  	{ mapIterator tmp = *this; it = _getSuccessor(it); return (tmp);}
			mapIterator		operator--()  		{it = _getPredecessor(it); return mapIterator(it);}
			mapIterator		operator--(int)  	{ mapIterator tmp = *this; it = _getPredecessor(it); return (tmp);}

			friend	bool	operator==(const mapIterator x, const mapIterator y) {return (x.it == y.it);}
			friend	bool	operator!=(const mapIterator x, const mapIterator y) {return (x.it != y.it);}
	};

	template <class T, class NodePtr>
	class mapRevIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		typedef T												iterator_type;
		typedef typename std::bidirectional_iterator_tag		iterator_category;
		typedef typename iterator_traits<T>::difference_type	difference_type;
		typedef typename iterator_traits<T>::value_type			value_type;
		typedef typename iterator_traits<T>::reference			reference;
		typedef typename iterator_traits<T>::pointer			pointer;
		typedef NodePtr											node_pointer;

	private:
		node_pointer	_it;

	public:
		mapRevIterator() : _it() {};
		explicit mapRevIterator(node_pointer _p) : _it(_p) {};
		template <class Iter>
		mapRevIterator(const mapRevIterator<Iter, node_pointer>& _i) : _it(_i.base()) {};

		node_pointer		base() const				{ return this->_it; };
		reference			operator*() const	{ return _getPredecessor(this->_it)->data; };
		pointer				operator->() const	{ return &(this->_it->data); };
		mapRevIterator&		operator++()		{ this->_it = _getPredecessor(this->_it); return (*this); };
		mapRevIterator		operator++(int)	{ mapRevIterator temp(*this); ++(*this); return (temp); };
		mapRevIterator&		operator--()	{ this->_it = _getSuccessor(this->_it); return (*this); };
		mapRevIterator		operator--(int)	{ mapRevIterator temp(*this); this->_it = _getSuccessor(this->_it); return (temp); };
		
		friend bool			operator==(const mapRevIterator& x, const mapRevIterator& y) { return (x._it == y._it); };
		friend bool			operator!=(const mapRevIterator& x, const mapRevIterator& y) { return (x._it != y._it); };
	};
};