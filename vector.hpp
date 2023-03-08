#pragma once

#include <iostream>
#include "utility.hpp"
#include "reverse_iterator.hpp"

namespace ft 
{

	template <typename T>
	class __wrap_iter
	{
		public:
			typedef T													iterator_type;
			typedef typename iterator_traits<T>::iterator_category		iterator_category;
			typedef typename iterator_traits<T>::value_type				value_type;
			typedef typename iterator_traits<T>::difference_type		difference_type;
			typedef typename iterator_traits<T>::pointer				pointer;
			typedef typename iterator_traits<T>::reference				reference;
		private:
			T _current;
		public:
			__wrap_iter(){}
			__wrap_iter(T x) : _current(x) {}

			template <typename It>
			__wrap_iter(const __wrap_iter<It>& x) : _current(x.base()){}
		
			T				base()							const	{ return (this->_current);}
			reference 		operator*()						const	{ return (*_current);}
			pointer 		operator->()					const	{ return (_current);}
			__wrap_iter& 	operator++()							{ ++_current; return (*this);}
			__wrap_iter 	operator++(int)							{ __wrap_iter _tmp(*this); ++_current; return (_tmp); }
			__wrap_iter& 	operator--()							{ --_current; return (*this);}
			__wrap_iter 	operator--(int)							{ __wrap_iter _tmp(*this); --_current; return (_tmp); }
			__wrap_iter  	operator+ (difference_type _n)	const	{ __wrap_iter _tmp(*this); _tmp += _n; return (_tmp); }
			__wrap_iter&  	operator+= (difference_type _n)			{ _current += _n; return (*this); }
			__wrap_iter  	operator- (difference_type _n)	const	{ __wrap_iter _tmp(*this); _tmp -= _n; return (_tmp); }
			__wrap_iter&  	operator-= (difference_type _n)			{ _current -= _n; return (*this); }
			reference    	operator[](difference_type _n)	const	{ return (_current[_n]); }
			difference_type operator- ( __wrap_iter _n)		const	{ return (_current - _n._current); }

			bool operator==(const __wrap_iter& _y)	{ return (_current == _y._current); }
			bool operator!=(const __wrap_iter& _y)	{ return !(_current == _y._current); }
			bool operator>(const __wrap_iter& _y)	{ return (_current > _y._current); }
			bool operator<(const __wrap_iter& _y)	{ return (_current < _y._current); }
			bool operator>=(const __wrap_iter& _y)	{ return !(_current < _y._current); }
			bool operator<=(const __wrap_iter& _y)	{ return !(_current > _y._current); }
	};

	template <typename T, class _Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef _Alloc									allocator_type;
			typedef typename _Alloc::size_type				size_type;
			typedef typename _Alloc::difference_type		difference_type;
			typedef typename _Alloc::pointer				pointer;
			typedef typename _Alloc::const_pointer			const_pointer;
			typedef typename _Alloc::reference				reference;
			typedef typename _Alloc::const_reference		const_reference;
			typedef T										value_type;
			typedef	__wrap_iter<pointer>					iterator;
			typedef __wrap_iter<const_pointer>				const_iterator;
			typedef	ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		private:
			allocator_type	_alloc;
			pointer			_m_data;
			size_type		_size;
			size_type		_capacity;

			pointer	_reallocate(size_type	n)
			{
				pointer tmp;

				tmp = this->_alloc.allocate(n);
				for (size_t i = 0; i < this->size(); i++)
					this->_alloc.construct(tmp + i, this->_m_data[i]);
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_m_data + i);
				if (this->_m_data)
					this->_alloc.deallocate(this->_m_data, this->capacity());
				return (tmp);
			}
			void	appendObjects(size_t n, value_type value)
			{
				for (size_t i = this->_size; i < n; i++)
				{
					this->_alloc.construct(this->_m_data + i, value);
				}
			}
			void	creatObjects(size_t count, value_type value)
			{
				for (size_t i = 0; i < count; i++)
				{
					this->_alloc.construct(this->_m_data + i, value);
				}
			}

			void	position_check(size_type n)
			{
				if (n >= this->size())
				{
					std::string execption = "vector::_M_range_check: __n (which is ";
					execption.append(std::to_string(n));
					execption.append(") >= this->size() (which is ");
					execption.append(std::to_string(this->size()));
					execption.append(")");
					throw std::out_of_range(execption);
				}
			}
		public:
		/* Constructors */

			explicit vector(const _Alloc& alloc = allocator_type()) : _alloc(alloc), _m_data(), _size(0), _capacity(0){}
			explicit vector(size_type count, const value_type& value = value_type(), const _Alloc& alloc = allocator_type()) : _alloc(alloc), _size(count), _m_data(), _capacity(count)
			{
				if (count)
				{
					this->_m_data = _alloc.allocate(count);
					creatObjects(count, value);
				}
			}
			template <class InputIterator>
        	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type = 1)
			{
				difference_type n = last - first;
				if (n > 0)
				{
					this->_m_data = this->_alloc.allocate(n);
					for (size_t i = 0; i < n && first != last ; i++)
					{
						this->_alloc.construct(this->_m_data + i, *first);
						first++;
					}
					this->_size = n;
					this->_capacity = n;
				}
				else
				{
					this->_size = 0;
					this->_capacity = 0;
				}
			}
			vector (const vector& x) : _m_data(), _size(0), _capacity(0)
			{
				*this = x;
			}
			~vector()
			{
				if (this->_capacity)
				{
					for (size_t i = 0; i < this->size(); i++)
						this->_alloc.destroy(this->_m_data + i);
					if (this->capacity())
						this->_alloc.deallocate(this->_m_data, this->capacity());
				}
				this->_size = 0;
				this->_capacity = 0;
			}
			vector& operator= (const vector& x)
			{
				this->clear();
				this->_alloc.deallocate(this->_m_data, this->_capacity);
				if (x.capacity())
					this->_m_data = this->_alloc.allocate(x.capacity());
				for (size_t i = 0; i < x.size(); i++)
					this->_alloc.construct(this->_m_data + i, x[i]);
				this->_size = x.size();
				this->_capacity = x.capacity();
				return (*this);
			}
		/* Iterators */

			iterator					begin()				{
				if (this->_size)
					return (iterator(this->_m_data));
				return (iterator(nullptr));
			}
			iterator					end()				{return (iterator(this->begin() + this->_size));}
			const_iterator				begin()		const	{return (const_iterator(this->_m_data));}
			const_iterator				end()		const	{return (const_iterator(this->begin() + this->_size));}
			reverse_iterator			rbegin()			{return (reverse_iterator(end()));}
			reverse_iterator			rend()				{return (reverse_iterator(begin()));}
			const_reverse_iterator		rbegin()	const	{return (const_reverse_iterator(end()));}
			const_reverse_iterator		rend()		const	{return (const_reverse_iterator(begin()));}

		/* Capacity */
			size_type	size() 		const _NOEXCEPT { return (this->_size);}
			size_type	max_size() 	const _NOEXCEPT { return (this->_alloc.max_size());}
			size_type	capacity() 	const _NOEXCEPT { return (this->_capacity); }
			bool		empty() 	const _NOEXCEPT { return (this->_size == 0);}

			void resize(size_type count, value_type value = value_type())
			{
				if (count < this->size())
				{
					for (size_t i = count; i < this->_size; i++)
					{
						this->_alloc.destroy(this->_m_data + i);
					}
				}
				else if (count > this->size())
				{
					if (count > this->_capacity)
						(count < (this->capacity() * 2) ? this->reserve(this->capacity() * 2) : this->reserve(count));
					appendObjects(count, value);
				}
				this->_size = count;
			}
			void reserve( size_type new_cap )
			{
				if (new_cap > this->max_size())
					throw (std::length_error("the new size exceeds the max size of the container"));
				if (new_cap > this->capacity() * 2)
				{
					this->_m_data = _reallocate(new_cap);
					this->_capacity = new_cap;
				}
				else if (new_cap > this->capacity())
				{
					this->_m_data = _reallocate(this->_capacity * 2);
					this->_capacity = this->_capacity * 2;
				}
			}
			/* Access Elements */

			reference		operator[](size_type i) {return *(this->_m_data + i);}
			const_reference	operator[](size_type i) const {return *(this->_m_data + i);}
			reference		at(size_type i)
			{
				if (i >= this->_size)
					throw std::out_of_range("vector");
				return *(this->_m_data + i);
			}
			const_reference	at(size_type i) const
			{
				if (i >= this->_size)
					throw std::out_of_range("vector");
				return *(this->_m_data + i);
			}
			reference 		front(){return *(this->begin());}
			const_reference front() const{return *(this->begin());}
			reference 		back(){return *(this->end() - 1);}
			const_reference back() const{return *(this->end() - 1);}
			pointer			data() {return (this->_m_data);}
			/* Modifiers */

			void push_back( const value_type& value )
			{
				if (this->_size + 1 > this->_capacity)
					(this->_capacity > 0) ? this->reserve(this->_capacity * 2) : this->reserve(1);
				this->_alloc.construct(this->_m_data + this->_size, value);
				this->_size++;
			}

			void	pop_back()
			{
				if (this->_size)
				{
					this->_alloc.destroy(this->_m_data + this->_size - 1);
					this->_size--;
				}
			}

			void	clear()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_m_data + i);
				this->_size = 0;
			}

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type = 0)
			{
				difference_type	n = last - first;
				this->clear();
				this->reserve(n);
				for (size_t i = 0; i < n; i++)
				{
					this->_alloc.construct(this->_m_data + i, *first);
					first++;
				}
				this->_size = n;
			}

			void assign (size_type n, const value_type& val)
			{
				this->clear();
				this->reserve(n);
				creatObjects(n, val);
				this->_size = n;
			}

			iterator insert (iterator position, const value_type& val)
			{
				difference_type n = position - this->begin();
				
				if (this->_size + 1 >= this->_capacity)
					this->reserve(this->size() + 1);
				if (n >= this->size())
				{
					this->_size++;
					return this->end();	
				}
				for (size_t i = this->_size - 1; i >= n; i--)
				{
					this->_m_data[i + 1] = this->_m_data[i];
					if (i == 0)
						break;
				}
				this->_m_data[n] = val;
				this->_size++;
				return (this->begin() + n);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				difference_type ip = position - this->begin();

				this->reserve(this->_size + n);
				for (size_t i = this->_size - 1; i >= ip; i--)
				{

					this->_m_data[i + n] = this->_m_data[i];
					if (i == 0)
						break;
				}
				for (size_t i = ip; i < ip + n; i++)
					this->_m_data[i] = val;
				this->_size += n;
			}

			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
			{
				difference_type len = last - first;
				if (len <= 0)
					return ;
				difference_type n = position - this->begin();
				vector tmp(this->begin(), this->end());
				try
				{
					this->reserve(this->_size + len);
					for (int i = this->_size - 1; i >= n; i--)
						this->_alloc.construct(this->_m_data + i + len, this->_m_data[i]);
					for (int i = n; i < n + len && first != last; i++)
					{
						this->_alloc.construct(this->_m_data + i, *first);
						this->_size++;
						first++;
					}
				}
				catch (...)
				{
					*this = tmp;
					throw ;
				}
			}

			iterator erase (iterator position)
			{
				difference_type n = position - this->begin();
				for (size_t i = n; i < this->_size; i++)
					this->_m_data[i] = this->_m_data[i + 1];
				this->_alloc.destroy(this->_m_data + (this->_size - 1));
				this->_size--;
				return (position);
			}

			iterator erase (iterator first, iterator last)
			{
				difference_type n = first - this->begin();
				difference_type diff = last - first;
				for (size_t i = n; i + diff < this->_size; i++)
				{
					this->_alloc.destroy(this->_m_data + i);
					this->_alloc.construct(this->_m_data + i, this->_m_data[i + diff]);
				}
				for (size_t i = this->_size - 1; i >= this->_size - diff; i--)
				{
					this->_alloc.destroy(this->_m_data + i);
					if (i == 0)
						break;
				}
				this->_size -= diff;
				return (first);
			}

			void swap (vector& x)
			{
				pointer	tmp = x._m_data;
				int xSize = x._size;
				int xCapacity = x._capacity;

				x._m_data = this->_m_data;
				x._capacity = this->_capacity;
				x._size = this->_size;
				this->_m_data = tmp;
				this->_capacity = xCapacity;
				this->_size = xSize;
			}

			allocator_type  get_allocator() const { return (_alloc); }

			bool operator==(const vector& rhs) const
			{
				if (this->size() == rhs.size())
					return ft::equal(this->begin(), this->end(), rhs.begin());
				return false;
			}
			bool operator!=(const vector& rhs) const
			{
				return !(*this == rhs);
			}
			bool operator<(const vector& rhs) const 
			{
				return ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end());
			}
			bool operator<=(const vector& rhs) const
			{
				return !(rhs < *this);
			}
			bool operator>(const vector& rhs) const
			{
				return (rhs < *this);
			}
			bool operator>=(const vector& rhs) const
			{
				return !(*this < rhs);
			}
	};

	template <class T, class Alloc>
	void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}