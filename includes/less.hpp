#ifndef LESS_HPP
#define LESS_HPP

namespace ft
{
	template <class T>
	struct less
	{
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;

		bool operator()(T const& x, T const& y) const
		{
			return x < y;
		}
	};
}

#endif