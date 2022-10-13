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
			reference		operator*() const noexcept 	{return (this->it->data);}
			pointer			operator->() const noexcept	{return &(this->it->data);}
			mapIterator&	operator++() noexcept 		{it = _getSuccessor(it); return (*it);}
			mapIterator		operator++(int) noexcept 	{ mapIterator tmp = *this; it = _getSuccessor(it); return (tmp);}
			mapIterator&	operator--() noexcept 		{it = _getPredecessor(it); return (*it);}
			mapIterator		operator--(int) noexcept 	{ mapIterator tmp = *this; it = _getPredecessor(it); return (tmp);}

			friend	bool	operator==(const mapIterator x, const mapIterator y) noexcept {return (x.it == y.it);}
			friend	bool	operator!=(const mapIterator x, const mapIterator y) noexcept {return (x.it != y.it);}
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
		node_pointer	it;

	public:
		mapRevIterator() : it() {};
		explicit mapRevIterator(node_pointer _p) : it(_p) {};
		template <class Iter>
		mapRevIterator(const mapRevIterator<Iter, node_pointer>& _i) : it(_i.base()) {};

		node_pointer		base() const				{ return this->_it; };
		reference			operator*() const noexcept	{ return _getPredecessor(this->_it)->data; };
		pointer				operator->() const noexcept	{ return &(this->it->data); };
		mapRevIterator&		operator++() noexcept		{ this->_it = _getPredecessor(this->_it); return (*this); };
		mapRevIterator		operator++(int)	noexcept	{ mapRevIterator temp(*this); ++(*this); return (temp); };
		mapRevIterator&		operator--()	noexcept	{ this->_it = _getSuccessor(this->_it); return (*this); };
		mapRevIterator		operator--(int)	noexcept	{ mapRevIterator temp(*this); this->_it = _getSuccessor(this->_it); return (temp); };
		
		friend bool			operator==(const mapRevIterator& x, const mapRevIterator& y) noexcept { return (x.it == y.it); };
		friend bool			operator!=(const mapRevIterator& x, const mapRevIterator& y) noexcept { return (x.it != y.it); };
	};
};