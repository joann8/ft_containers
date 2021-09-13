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
/*
	template< class T >
	struct equal_to {
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;

		bool operator()( const T& lhs, const T& rhs ) const {
			return lhs == rhs;
		}
	};

	template< class T >
	struct equal_to_unary {
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;

		explicit equal_to_unary(const T& ref) : _ref(ref) {}

		bool operator()(const T& other) const {
			return other == _ref;
		}

		const T& _ref;
	};*/
}

#endif