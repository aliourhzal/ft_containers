#pragma once

#include <iostream>

namespace ft
{

	template< class T, T v >
	struct integral_constant
	{
		typedef T	value_type;
		typedef integral_constant<T,v>	type;
		static const T	value = v;
		operator value_type() { return (value); }
	};
	
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <bool Cond, class T = void> struct enable_if {};
	template <class T>	struct	enable_if<true, T> { typedef T type; };
	template <class T>	struct	is_integral								: public false_type {};
	template <> 		struct	is_integral<bool> 						: public true_type {};
	template <> 		struct	is_integral<char>						: public true_type {};
	template <> 		struct	is_integral<char16_t>					: public true_type {};
	template <> 		struct	is_integral<char32_t>					: public true_type {};
	template <> 		struct	is_integral<wchar_t>					: public true_type {};
	template <> 		struct	is_integral<signed char>				: public true_type {};
	template <> 		struct	is_integral<short int>					: public true_type {};
	template <> 		struct	is_integral<int>						: public true_type {};
	template <> 		struct	is_integral<long int>					: public true_type {};
	template <> 		struct	is_integral<long long int>				: public true_type {};
	template <> 		struct	is_integral<unsigned char>				: public true_type {};
	template <> 		struct	is_integral<unsigned short int>			: public true_type {};
	template <> 		struct	is_integral<unsigned int>				: public true_type {};
	template <> 		struct	is_integral<unsigned long int>			: public true_type {};
	template <> 		struct	is_integral<unsigned long long int>		: public true_type {};

	template <class _Iterator>
	struct iterator_traits
	{
		typedef typename _Iterator::iterator_category iterator_category;
		typedef typename _Iterator::value_type        value_type;
		typedef typename _Iterator::difference_type   difference_type;
		typedef typename _Iterator::pointer           pointer;
		typedef typename _Iterator::reference         reference;
	};

	template<typename _Tp>
	struct iterator_traits<_Tp*>
	{
		typedef std::random_access_iterator_tag iterator_category;
		typedef _Tp                         	value_type;
		typedef ptrdiff_t                   	difference_type;
		typedef _Tp*                        	pointer;
		typedef _Tp&                        	reference;
	};

	template<typename _Tp>
	struct iterator_traits<const _Tp*>
	{
		typedef std::random_access_iterator_tag iterator_category;
		typedef _Tp								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const _Tp*						pointer;
		typedef const _Tp&						reference;
	};

		template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return false;
			++first1; ++first2;
		}
		return true;
	}


};