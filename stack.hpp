#pragma once

#include "vector.hpp"
#include <stack>

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef	typename	Container::value_type	value_type;
			typedef	Container							container_type;
			typedef	typename	Container::size_type	size_type;
		private:
			Container c;
		public:
			explicit			stack (const container_type& ctnr = container_type()) : c(ctnr){}
			bool				empty() const {return (c.empty());}
			size_type			size() const {return (c.size());}
			value_type& 		top() {return (c.back());}
			const value_type&	top() const {return (c.back());}
			void				push(const value_type &val)	{ c.push_back(val); }
			void				pop() { c.pop_back(); }

			bool operator==(const stack &rhs) { return (this->c == rhs.c); }

			bool operator!=(const stack &rhs) { return (this->c != rhs.c); }

			bool operator<(const stack &rhs) { return (this->c < rhs.c); }

			bool operator<=(const stack &rhs) { return (this->c <= rhs.c); }

			bool operator>(const stack &rhs) { return (this->c > rhs.c); }

			bool operator>=(const stack &rhs) { return (this->c >= rhs.c); }
	};
};