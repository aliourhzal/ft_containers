#pragma once

# include <iostream>
# include <iterator>
namespace ft
{
	template <class _Iterator>
	struct iterator_traits
	{
		// typedef typename _Iterator::iterator_category iterator_category;
		typedef typename _Iterator::value_type        value_type;
		typedef typename _Iterator::difference_type   difference_type;
		typedef typename _Iterator::pointer           pointer;
		typedef typename _Iterator::reference         reference;
	};

	template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
		typedef _Tp                         value_type;
		typedef ptrdiff_t                   difference_type;
		typedef _Tp*                        pointer;
		typedef _Tp&                        reference;
    };

	template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef const _Tp*                  pointer;
      typedef const _Tp&                  reference;
    };
};