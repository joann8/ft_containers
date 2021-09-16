#ifndef TESTS_HPP
#define TESTS_HPP

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

#include <sys/time.h>

#include <iostream>
#include <string>
#include <climits>
#include <list>
#include <vector>
#include <map>
#include <stack>
#include <set>

#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "set.hpp"

namespace tests
{
	namespace vector
	{
		void launch();
	}

	namespace map
	{
		void launch();
	}

	namespace stack
	{
		void launch();
	}

	namespace set
	{
		void launch();
	}
}

#endif
