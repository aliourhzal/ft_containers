#pragma once

#include <iostream>

namespace ft {

	template <typename _Iter>
	class reverse_iterator {
		public:
			typedef _Iter												iterator_type;
			typedef typename iterator_traits<_Iter>::difference_type	difference_type;
			typedef typename iterator_traits<_Iter>::reference			reference;
			typedef typename iterator_traits<_Iter>::pointer			pointer;
		private:
			_Iter _current;
		public:
			reverse_iterator() : _current(_Iter()) {}
			explicit reverse_iterator (_Iter it) : _current(it) {}
			template <class Iter>
				reverse_iterator (const reverse_iterator<Iter>& rev_it) : _current(rev_it.base()) {}
			
			iterator_type		base()			const	{return (this->_current);}
			reference			operator*()		const	{iterator_type tmp(this->_current); return (*--tmp);}
			pointer				operator->()	const	{return (&operator*());}
			reverse_iterator&	operator++()			{--this->_current; return (*this);}
			reverse_iterator	operator++(int)			{reverse_iterator tmp(this->_current); --this->_current; return (tmp);}
			reverse_iterator&	operator--()			{++this->_current; return (*this);}
			reverse_iterator	operator--(int)			{reverse_iterator tmp(this->_current); ++this->_current; return (tmp);}

			bool	operator!=(const reverse_iterator& y) {return (this->_current != y._current);}
			bool	operator==(const reverse_iterator& y) {return (this->_current == y._current);}
	};

}