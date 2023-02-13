#pragma once

#include "utility.hpp"
#include "_Rb_tree.hpp"

namespace ft
{
	template<typename T, class NodePtr>
	class mapIterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename iterator_traits<T*>::difference_type	difference_type;
			typedef typename iterator_traits<T*>::value_type		value_type;
			typedef typename iterator_traits<T*>::reference			reference;
			typedef typename iterator_traits<T*>::pointer			pointer;
			typedef std::bidirectional_iterator_tag 				iterator_category;
			typedef	NodePtr											nodePtr;
		private:
			nodePtr	it;
		public:
			mapIterator() : it(){};
			mapIterator(nodePtr	i) : it(i){};
			template<typename It>
				mapIterator(const mapIterator<It, nodePtr>	&i) : it(i.base()){};

			nodePtr			base()	const		{return (this->it);}
			T&				operator*() const  	{return (this->it->data);}
			T*				operator->() const 	{return &(this->it->data);}
			mapIterator		operator++()  		{it = _getSuccessor(it); return mapIterator(it);}
			mapIterator		operator++(int)  	{ mapIterator tmp = *this; it = _getSuccessor(it); return (tmp);}
			mapIterator		operator--()  		{it = _getPredecessor(it); return mapIterator(it);}
			mapIterator		operator--(int)  	{ mapIterator tmp = *this; it = _getPredecessor(it); return (tmp);}

			bool	operator==(const mapIterator &y) {return (this->it == y.it);}
			bool	operator!=(const mapIterator &y) {return (this->it != y.it);}
	};
};