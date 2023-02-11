#pragma once
#include <iostream>

namespace ft
{
	template<typename _T1, typename _T2>
	struct pair
	{
		typedef _T1 first_type;
		typedef _T2 second_type;
		
		_T1 first;
		_T2 second;
		pair(){}
		pair(first_type f, second_type s = second_type()) : first(f), second(s){}
		template<class _A1, class _A2>
		pair(pair<_A1, _A2> pr) : first(pr.first), second(pr.second){}
		pair& operator= (const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);	
		}
	};
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first==rhs.first && lhs.second==rhs.second;
	}
	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs==rhs);
	}
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	}
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs<lhs);
	}
	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return rhs<lhs;
	}
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs<rhs);
	}
	template <class T1, class T2>
  	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}
};