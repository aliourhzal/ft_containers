#pragma once

#include <iostream>
#include "iterator_traits.hpp"

namespace ft
{
	template<class T>
	class VectorIterator : public std::iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef T                                                   iterator_type;
			typedef typename    iterator_traits<T>::value_type          value_type;
			typedef typename    iterator_traits<T>::difference_type     difference_type;
			typedef typename    iterator_traits<T>::pointer             pointer;
			typedef typename    iterator_traits<T>::reference           reference;
		private:
			iterator_type it;
		public:
			VectorIterator(){};
			explicit    VectorIterator(iterator_type i) : it(i){}

			
			iterator_type   base() const {return (this->it);}
			reference       operator*(){return (*this->it);}
			VectorIterator  operator+(difference_type n)
			{
				return VectorIterator(this->it + n);
			}
			VectorIterator&  operator++()
			{
				++this->it;
				return (*this);
			}
			VectorIterator  operator++(int)
			{
				return VectorIterator(this->it++);
			}
			VectorIterator&  operator+=(difference_type n)
			{
				this->it += n;
				return (*this);
			}
			VectorIterator  operator-(difference_type n)
			{
				return VectorIterator(this->it - n);
			}
			VectorIterator&  operator--()
			{
				--this->it;
				return (*this);
			}
			VectorIterator  operator--(int)
			{
				return VectorIterator(this->it--);
			}
			VectorIterator  operator-=(difference_type n)
			{
				this->it -= n;
				return (*this);
			}
			pointer	 operator->() const {return (this->it);}
			const	reference operator[](difference_type n) const {return *(this->it + n);}
	};

	template <class Iterator1, class Iterator2>
	bool operator== (const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!= (const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator< (const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() < rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator<= (const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() <= rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator> (const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() > rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>= (const VectorIterator<Iterator1>& lhs, const VectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() >= rhs.base());
	}
	template <class Iterator>
	VectorIterator<Iterator> operator+ (typename VectorIterator<Iterator>::difference_type n, const VectorIterator<Iterator>& m_it)
	{
		return VectorIterator<Iterator>(m_it.base() + n);
	}
	template <class Iterator>
	typename VectorIterator<Iterator>::difference_type operator- (const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	}


	template<class T>
	class RevectorIterator :  public std::iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef T                                                   iterator_type;
			typedef typename    iterator_traits<T>::value_type          value_type;
			typedef typename    iterator_traits<T>::difference_type     difference_type;
			typedef typename    iterator_traits<T>::pointer             pointer;
			typedef typename    iterator_traits<T>::reference           reference;
		private:
			iterator_type	it;
		public:
			RevectorIterator(){}
			explicit	RevectorIterator(iterator_type i) : it(i){}

			iterator_type   base() const {return (this->it);}
			reference       operator*(){return (*(this->it - 1));}
			RevectorIterator  operator+(difference_type n)
			{
				return RevectorIterator(this->it - n);
			}
			RevectorIterator&  operator++()
			{
				--this->it;
				return (*this);
			}
			RevectorIterator  operator++(int)
			{
				return RevectorIterator(this->it--);
			}
			RevectorIterator&  operator+=(difference_type n)
			{
				this->it -= n;
				return (*this);
			}
			RevectorIterator  operator-(difference_type n)
			{
				return RevectorIterator(this->it + n);
			}
			RevectorIterator&  operator--()
			{
				++this->it;
				return (*this);
			}
			RevectorIterator&  operator--(int)
			{
				return RevectorIterator(this->it++);
			}
			RevectorIterator  operator-=(difference_type n)
			{
				this->it += n;
				return (*this);
			}
			pointer	 operator->() const {return (this->it - 1);}
			const	reference operator[](difference_type n) const {return *(this->it + n);}
	};
	template <class Iterator1, class Iterator2>
	bool operator== (const RevectorIterator<Iterator1>& lhs, const RevectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!= (const RevectorIterator<Iterator1>& lhs, const RevectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator< (const RevectorIterator<Iterator1>& lhs, const RevectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() < rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator<= (const RevectorIterator<Iterator1>& lhs, const RevectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() <= rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator> (const RevectorIterator<Iterator1>& lhs, const RevectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() > rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>= (const RevectorIterator<Iterator1>& lhs, const RevectorIterator<Iterator2>& rhs)
	{
		return(lhs.base() >= rhs.base());
	}
	template <class Iterator>
	RevectorIterator<Iterator> operator+ (typename RevectorIterator<Iterator>::difference_type n, const RevectorIterator<Iterator>& m_it)
	{
		return RevectorIterator<Iterator>(m_it.base() + n);
	}
	template <class Iterator>
	typename RevectorIterator<Iterator>::difference_type operator- (const RevectorIterator<Iterator>& lhs, const RevectorIterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	}
};