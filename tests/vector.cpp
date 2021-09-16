#include "tests.hpp"

namespace tests { namespace vector
{
	void member_types()
	{
		std::cout << "Member Types tests : OK if you see this" << std::endl;
		NAMESPACE::vector<int>::value_type vt;
		static_cast<void>(vt);
		NAMESPACE::vector<int>::allocator_type at;
		static_cast<void>(at);
		NAMESPACE::vector<int>::reference ref = vt;
		static_cast<void>(ref);
		NAMESPACE::vector<int>::const_reference cref = vt;
		static_cast<void>(cref);
		NAMESPACE::vector<int>::pointer ptr;
		static_cast<void>(ptr);
		NAMESPACE::vector<int>::const_pointer cptr;
		static_cast<void>(cptr);
		NAMESPACE::vector<int>::iterator it;
		NAMESPACE::vector<int>::const_iterator cit;
		NAMESPACE::vector<int>::reverse_iterator rit;
		NAMESPACE::vector<int>::const_reverse_iterator crit;
		NAMESPACE::vector<int>::difference_type dt;
		static_cast<void>(dt);
		NAMESPACE::vector<int>::size_type st;
		static_cast<void>(st);
	}

	void constructors()
	{
		std::cout << "Constructors tests :\n";

		NAMESPACE::vector<int> default_vec;
		std::cout << "- default constructor, empty() : " << std::boolalpha
			<< default_vec.empty() << "\n";

		NAMESPACE::vector<int> fill(4, 42);
		std::cout << "- fill constructor, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = fill.begin(),
				cite = fill.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		NAMESPACE::vector<int> util;
		util.push_back(1);
		util.push_back(2);
		util.push_back(3);
		util.push_back(4);
		util.push_back(5);

		NAMESPACE::vector<int> range(util.begin() + 1, util.end() - 1);
		std::cout << "- range constructor, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = range.begin(),
				cite = range.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		NAMESPACE::vector<int> copy(util);
		std::cout << "- copy constructor, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = copy.begin(),
				cite = copy.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void assignment_operator()
	{
		std::cout << "Assignment operator tests :\n";

		NAMESPACE::vector<int> util;
		util.push_back(1);
		util.push_back(2);
		util.push_back(3);
		util.push_back(4);
		util.push_back(5);

		NAMESPACE::vector<int> copy;
		copy.push_back(42);

		copy = util;
		std::cout << "- after assignment operator values :";
		for (NAMESPACE::vector<int>::const_iterator cit = copy.begin(),
				cite = copy.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void begin()
	{
		std::cout << "begin tests :\n";

		NAMESPACE::vector<std::string> vec;
		vec.push_back("first");
		vec.push_back("second");
		vec.push_back("last");

		std::cout << "- *begin() : " << *vec.begin() << "\n";

		std::cout << std::flush;
	}

	void end()
	{
		std::cout << "end tests :\n";

		NAMESPACE::vector<std::string> vec;
		vec.push_back("first");
		vec.push_back("second");
		vec.push_back("last");

		std::cout << "- *--end() : " << *--vec.end() << "\n";

		std::cout << std::flush;
	}

	void rbegin()
	{
		std::cout << "rbegin tests :\n";

		NAMESPACE::vector<std::string> vec;
		vec.push_back("first");
		vec.push_back("second");
		vec.push_back("last");

		std::cout << "- *rbegin() : " << *vec.rbegin() << "\n";

		std::cout << std::flush;
	}

	void rend()
	{
		std::cout << "rend tests :\n";

		NAMESPACE::vector<std::string> vec;
		vec.push_back("first");
		vec.push_back("second");
		vec.push_back("last");

		std::cout << "- *--rend() : " << *--vec.rend() << "\n";

		std::cout << std::flush;
	}
	
	void size()
	{
		std::cout << "size tests :\n";

		NAMESPACE::vector<float> vec;

		std::cout << "- empty vector, size() : " << vec.size() << "\n";

		vec.push_back(42.42);
		std::cout << "- 1 elem vector, size() : " << vec.size() << "\n";

		vec.insert(vec.end(), 20, 21.21);
		std::cout << "- 21 elems vector, size() : " << vec.size() << "\n";

		vec.clear();
		std::cout << "- clear vector, size() : " << vec.size() << "\n";

		std::cout << std::flush;
	}

	void max_size()
	{
		std::cout << "max_size tests :\n";

		NAMESPACE::vector<std::string> string_vector;
		std::cout << "- vector<std::string>, max_size() : "
			<< string_vector.max_size() << "\n";

		NAMESPACE::vector<int> int_vector;
		std::cout << "- vector<int>, max_size() : "
			<< int_vector.max_size() << "\n";

		NAMESPACE::vector<char> char_vector;
		std::cout << "- vector<char>, max_size() : "
			<< char_vector.max_size() << "\n";

		std::cout << std::flush;
	}
	void resize()
	{
		std::cout << "resize tests :\n";

		NAMESPACE::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);

		vec.resize(3, 42);
		std::cout << "- after smaller resize, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		vec.resize(5, 42);
		std::cout << "- after greater resize, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void capacity()
	{
		std::cout << "capacity tests :\n";

		NAMESPACE::vector<float> vec;

		std::cout << "- empty vector, capacity() : " << vec.capacity() << "\n";

		vec.push_back(42.42);
		std::cout << "- 1 elem vector, capacity() : " << vec.capacity() << "\n";

		vec.push_back(21.21);
		std::cout << "- 2 elem vector, capacity() : " << vec.capacity() << "\n";

		vec.push_back(105.105);
		std::cout << "- 3 elem vector, capacity() : " << vec.capacity() << "\n";

		vec.insert(vec.end(), 2, 525.525);
		std::cout << "- 5 elems vector, capacity() : " << vec.capacity() << "\n";

		vec.clear();
		std::cout << "- clear vector, capacity() : " << vec.capacity() << "\n";

		std::cout << std::flush;
	}

	void empty()
	{
		std::cout << "empty tests :\n";

		NAMESPACE::vector<bool> vec;

		std::cout << "- empty vector, empty() : " << std::boolalpha
			<< vec.empty() << "\n";

		vec.push_back(false);
		std::cout << "- non empty vector, empty() : " << std::boolalpha
			<< vec.empty() << "\n";

		vec.clear();
		std::cout << "- clear vector, empty() : " << std::boolalpha
			<< vec.empty() << "\n";

		std::cout << std::flush;
	}

	void reserve()
	{
		std::cout << "reserve tests :\n";

		NAMESPACE::vector<float> vec;

		std::cout << "- empty vector, capacity() : " << vec.capacity() << "\n";

		vec.reserve(42);
		std::cout << "- after reserve(42), capacity() : " << vec.capacity() << "\n";

		vec.reserve(21);
		std::cout << "- after reserve(21), capacity() : " << vec.capacity() << "\n";

		try {
			vec.reserve(ULONG_MAX);
		}
		catch (std::length_error const& e) {
			std::cout << "- execption catch in reserve(ULONG_MAX), e.what() : "
				<< e.what() << "\n";
		}

		std::cout << std::flush;
	}

	void subscript_operator()
	{
		std::cout << "operator[] tests :\n";

		NAMESPACE::vector<std::string> vec;
		vec.push_back("first");
		vec.push_back("second");
		vec.push_back("last");

		std::cout << "- values accessed with [] :";
		for (std::size_t i = 0, size = vec.size(); i < size; ++i) {
			std::cout << " " << vec[i];
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void at()
	{
		std::cout << "at tests :\n";

		NAMESPACE::vector<std::string> vec;
		vec.push_back("first");
		vec.push_back("second");
		vec.push_back("last");

		std::cout << "- values accessed with at :";
		for (std::size_t i = 0, size = vec.size(); i < size; ++i) {
			std::cout << " " << vec.at(i);
		}
		std::cout << "\n";

		try {
			vec.at(ULONG_MAX);
		}
		catch (std::out_of_range const& e) {
			std::cout << "- execption catch in at(ULONG_MAX), e.what() : "
				<< e.what() << "\n";
		}

		std::cout << std::flush;
	}

	void front()
	{
		std::cout << "front tests :\n";

		NAMESPACE::vector<std::string> vec;
		vec.push_back("first");
		vec.push_back("second");
		vec.push_back("last");

		std::cout << "- front() : " << vec.front() << "\n";

		std::cout << std::flush;
	}

	void back()
	{
		std::cout << "back tests :\n";

		NAMESPACE::vector<std::string> vec;
		vec.push_back("first");
		vec.push_back("second");
		vec.push_back("last");

		std::cout << "- back() : " << vec.back() << "\n";

		std::cout << std::flush;
	}

	void assign()
	{
		std::cout << "assign tests :\n";

		NAMESPACE::vector<int> util;
		util.push_back(1);
		util.push_back(2);
		util.push_back(3);
		util.push_back(4);
		util.push_back(5);

		NAMESPACE::vector<int> range(10);

		range.assign(++util.begin(), --util.end());
		std::cout << "- range assign, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = range.begin(),
				cite = range.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		NAMESPACE::vector<int> fill(4, 42);

		fill.assign(2, 21);
		std::cout << "- fill assign, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = fill.begin(),
				cite = fill.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void push_back()
	{
		std::cout << "push_back tests :\n";

		NAMESPACE::vector<int> vec(2);

		vec.push_back(42);
		std::cout << "- after push_back, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void pop_back()
	{
		std::cout << "pop_back tests :\n";

		NAMESPACE::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);

		vec.pop_back();
		std::cout << "- after pop_back, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void insert()
	{
		std::cout << "insert tests :\n";

		NAMESPACE::vector<int> vec;

		vec.insert(vec.end(), 42);
		std::cout << "- after single element insert, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		vec.insert(vec.begin(), 2, 21);
		std::cout << "- after fill insert, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		NAMESPACE::vector<int> util;
		util.push_back(1);
		util.push_back(2);
		util.push_back(3);
		util.push_back(4);
		util.push_back(5);

		vec.insert(--vec.end(), ++util.begin(), --util.end());
		std::cout << "- after range insert, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void erase()
	{
		std::cout << "erase tests :\n";

		NAMESPACE::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);

		vec.erase(++(++vec.begin()));
		std::cout << "- after single element erase, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		vec.erase(++vec.begin(), vec.end());
		std::cout << "- after range erase, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void swap()
	{
		std::cout << "swap tests :\n";

		NAMESPACE::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);
		NAMESPACE::vector<int> vec2(3, 42);

		std::cout << "- before swap, vec values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";
		std::cout << "- before swap, vec2 values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec2.begin(),
				cite = vec2.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		vec.swap(vec2);
		std::cout << "- after member function swap, vec values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";
		std::cout << "- after member function swap, vec2 values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec2.begin(),
				cite = vec2.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		swap(vec, vec2);
		std::cout << "- after non member function swap, vec values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";
		std::cout << "- after non member function swap, vec2 values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec2.begin(),
				cite = vec2.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void clear()
	{
		std::cout << "clear tests :\n";

		NAMESPACE::vector<int> vec(4, 42);

		vec.clear();
		std::cout << "- after clear, values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void get_allocator()
	{
		std::cout << "get_allocator tests : ";

		NAMESPACE::vector<std::string> vec;
		NAMESPACE::vector<std::string>::allocator_type at = vec.get_allocator();

		NAMESPACE::vector<std::string>::value_type *vt = at.allocate(1);
		at.construct(vt, "OK if you see this\n");

		std::cout << *vt;

		at.destroy(vt);
		at.deallocate(vt, 1);

		std::cout << std::flush;
	}

	static void print_vectors_comparaison(NAMESPACE::vector<int> const& vec,
			NAMESPACE::vector<int> const& vec2)
	{
		std::cout << "  vec values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec.begin(),
				cite = vec.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";
		std::cout << "  vec2 values :";
		for (NAMESPACE::vector<int>::const_iterator cit = vec2.begin(),
				cite = vec2.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";
		std::cout << "- vec == vec2 : " << std::boolalpha << (vec == vec2)
			<< "\n";
		std::cout << "- vec < vec2 : " << std::boolalpha << (vec < vec2)
			<< "\n";
		std::cout << "- vec >= vec2 : " << std::boolalpha << (vec >= vec2)
			<< "\n";
	}

	void relational_operators()
	{
		std::cout << "Relational operators tests :\n";

		NAMESPACE::vector<int> vec(2);
		NAMESPACE::vector<int> vec2(3);

		print_vectors_comparaison(vec, vec2);

		std::cout << "\n";
		vec.push_back(1);
		print_vectors_comparaison(vec, vec2);

		std::cout << "\n";
		vec.back() = 0;
		print_vectors_comparaison(vec, vec2);

		std::cout << std::flush;
	}

	void launch()
	{
		struct timeval	timeval;

		if (gettimeofday(&timeval, NULL) == -1) {
			std::cout << "gettimeofday failed" << std::endl;
			return;
		}
		unsigned long long time_start = timeval.tv_sec * 1000000 + timeval.tv_usec;

		member_types();
		std::cout << "\n";
		constructors();
		std::cout << "\n";
		assignment_operator();
		std::cout << "\n";
		begin();
		std::cout << "\n";
		end();
		std::cout << "\n";
		rbegin();
		std::cout << "\n";
		rend();
		std::cout << "\n";
		size();
		std::cout << "\n";
		max_size();
		std::cout << "\n";
		resize();
		std::cout << "\n";
		capacity();
		std::cout << "\n";
		empty();
		std::cout << "\n";
		reserve();
		std::cout << "\n";
		subscript_operator();
		std::cout << "\n";
		at();
		std::cout << "\n";
		front();
		std::cout << "\n";
		back();
		std::cout << "\n";
		assign();
		std::cout << "\n";
		push_back();
		std::cout << "\n";
		pop_back();
		std::cout << "\n";
		insert();
		std::cout << "\n";
		erase();
		std::cout << "\n";
		swap();
		std::cout << "\n";
		clear();
		std::cout << "\n";
		get_allocator();
		std::cout << "\n";
		relational_operators();

		if (gettimeofday(&timeval, NULL) == -1) {
			std::cout << "gettimeofday failed" << std::endl;
			return;
		}
		unsigned long long time_end = timeval.tv_sec * 1000000 + timeval.tv_usec;

		std::cout << "\nTests duration : " << time_end - time_start
			<< " microseconds" << std::endl;
	}
} }
