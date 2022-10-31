#pragma once

#include <iostream>
#include "iterators.hpp"
#include "is_integral.hpp"
#include "lexi_equal.hpp"

namespace ft 
{
	template<typename T, class _Alloc = std::allocator<T>>
	class vector
	{
		public:
			typedef _Alloc								allocator_type;
			typedef T									value_type;
			typedef typename _Alloc::size_type			size_type;
			typedef typename _Alloc::difference_type	difference_type;
			typedef typename _Alloc::pointer			pointer;
			typedef typename _Alloc::const_pointer		const_pointer;
			typedef typename _Alloc::reference			reference;
			typedef typename _Alloc::const_reference	const_reference;
			typedef	VectorIterator<pointer>				iterator;
			typedef VectorIterator<const_pointer>		const_iterator;
			typedef	RevectorIterator<pointer>			reverse_iterator;
			typedef RevectorIterator<const_iterator>	const_reverse_iterator;
		private:
			allocator_type	_alloc;
			value_type*		_m_data;
			size_type		_size;
			size_type		_capacity;

			value_type*	_reallocate(size_type	n)
			{
				value_type* tmp;

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
				this->_m_data = this->_alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
				{
					this->_alloc.construct(this->_m_data + i, *first);
					first++;
				}
				this->_size = n;
				this->_capacity = n;
			}
			vector (const vector& x)
			{
				*this = x;
			}
			~vector()
			{
				for (size_t i = 0; i < this->size(); i++)
					this->_alloc.destroy(this->_m_data + i);
				if (this->capacity())
				this->_alloc.deallocate(this->_m_data, this->capacity());
			}
			vector& operator= (const vector& x)
			{
				this->clear();
				this->reserve(x.size());
				for (size_t i = 0; i < x.size(); i++)/* code */
				{
					this->_alloc.construct(this->_m_data + i, x[i]);
				}
				this->_size = x.size();
				return (*this);
			}
		/* Iterators */

			iterator				begin(){return (iterator(this->_m_data));}
			iterator				end(){return (iterator(this->begin() + this->_size));}
			const_iterator			begin() const{return (const_iterator(this->_m_data));}
			const_iterator			end() const{return (const_Iterator(this->begin() + this->_size));}
			reverse_iterator			rbegin() {return (RevectorIterator(this->_m_data + this->size()));}
			reverse_iterator			rend() {return (RevectorIterator(this->_m_data));}
			const_reverse_iterator	rbegin() const{return (RevectorIterator(this->_m_data + this->size()));}
			const_reverse_iterator	rend() const{return (RevectorIterator(this->_m_data));}
		/* Capacity */
			size_type	size() const noexcept
			{
				return (this->_size);
			}

			size_type	max_size() const noexcept
			{
				return (this->_alloc.max_size());
			}

			size_type	capacity() const noexcept
			{
				return (this->_capacity);
			}

			bool	empty() const noexcept
			{
				return (this->_size == 0);
			}

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
				if (new_cap > this->capacity())
				{
					this->_m_data = _reallocate(new_cap);
					this->_capacity = new_cap;
				}
			}
			/* Access Elements */

			reference		operator[](size_type i) {return *(this->_m_data + i);}
			const_reference	operator[](size_type i) const {return *(this->_m_data + i);}
			reference		at(size_type i) {position_check(i); return *(this->_m_data + i);}
			const_reference	at(size_type i) const {position_check(i); return *(this->_m_data + i);}
			reference 		front(){return *(this->begin());}
			const_reference front() const{return *(this->begin());};
			reference 		back(){return *(this->end() - 1);}
			const_reference back() const{return *(this->end() - 1);};
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
				this->_alloc.destroy(this->_m_data + this->_size - 1);
				this->_size--;
			}

			void	clear()
			{
				for (size_t i = 0; i < this->_size; i++)
					_alloc.destroy(this->_m_data + i);
				this->_size = 0;
			}

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type = 0)
			{
				difference_type	n = std::distance(first, last);
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
				
				if (this->size() + 1 > this->capacity())
					this->reserve(this->_capacity * 2);
				if (n >= this->size())
				{
					this->_size++;
					return this->end();	
				}
				for (size_t i = this->_size - 1; i >= n; i--)
					this->_m_data[i + 1] = this->_m_data[i];
				this->_m_data[n] = val;
				this->_size++;
				return (this->begin() + n);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				difference_type ip = position - this->begin();iterator erase (iterator first, iterator last);iterator erase (iterator first, iterator last);iterator erase (iterator first, iterator last);
				
				while (this->size() + n > this->capacity())
					this->reserve(this->_capacity * 2);
				for (size_t i = this->_size - 1; i >= ip; i--)
					this->_m_data[i + n] = this->_m_data[i];
				for (size_t i = ip; i < ip + n; i++)
					this->_m_data[i] = val;
				this->_size += n;
			}

			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
			{
				difference_type len = last - first;
				difference_type n = position - this->begin();
				if (this->_size + len > this->_capacity)
					(this->_size + len) > (this->_capacity * 2) ? this->reserve(this->_size + len) : this->reserve(this->_capacity * 2);
				for (size_t i = this->_size - 1; i >= n; i--)
					this->_m_data[i + len] = this->_m_data[i];
				for (size_t i = n; i < n + len; i++)
				{ 
					this->_m_data[i] = *first;
					first++;
				}
				this->_size += len;
			}

			iterator erase (iterator position)
			{
				difference_type n = position - this->begin();
				for (size_t i = n; i < this->_size; i++)
				{
					this->_m_data[i] = this->_m_data[i + 1];
				}
				this->_alloc.destroy(this->_m_data + (this->_size - 1));
				this->_size--;
				return (position);
			}

			iterator erase (iterator first, iterator last)
			{
				difference_type n = first - this->begin();
				difference_type diff = last - first;
				for (size_t i = n; i + diff < this->_size; i++)
					this->_m_data[i] = this->_m_data[i + diff];
				for (size_t i = this->_size - 1; i > this->_size - diff; i--)
					this->_alloc.destroy(this->_m_data + i);
				this->_size -= diff;
				return (first);
			}

			void swap (vector& x)
			{
				vector	tmp(x);
				x = *(this);
				x._capacity = this->_capacity;
				*(this) = tmp;
				this->_capacity = tmp._capacity;
			}

			allocator_type  get_allocator() const
			{
				return (_alloc);
			}
	};
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}