#include "tests.hpp"

namespace tests { namespace set
{
	void member_types()
	{
		std::cout << "Member Types tests : OK if you see this" << std::endl;
		NAMESPACE::set<int>::key_type kt;
		static_cast<void>(kt);
		NAMESPACE::set<int>::value_type vt;
		static_cast<void>(vt);
		NAMESPACE::set<int>::key_compare kc;
		static_cast<void>(kc);
		NAMESPACE::set<int>::value_compare vc;
		static_cast<void>(vc);
		NAMESPACE::set<int>::allocator_type at;
		static_cast<void>(at);
		NAMESPACE::set<int>::reference ref = vt;
		static_cast<void>(ref);
		NAMESPACE::set<int>::const_reference cref = vt;
		static_cast<void>(cref);
		NAMESPACE::set<int>::pointer ptr;
		static_cast<void>(ptr);
		NAMESPACE::set<int>::const_pointer cptr;
		static_cast<void>(cptr);
		NAMESPACE::set<int>::iterator it;
		NAMESPACE::set<int>::const_iterator cit;
		NAMESPACE::set<int>::reverse_iterator rit;
		NAMESPACE::set<int>::const_reverse_iterator crit;
		NAMESPACE::set<int>::difference_type dt;
		static_cast<void>(dt);
		NAMESPACE::set<int>::size_type st;
		static_cast<void>(st);
	}

	void constructors()
	{
		std::cout << "Constructors tests :\n";

		NAMESPACE::set<int> default_set;
		std::cout << "- default constructor, empty() : " << std::boolalpha
			<< default_set.empty() << "\n";

		NAMESPACE::set<int> util;
		util.insert(1);
		util.insert(2);
		util.insert(3);
		util.insert(4);
		util.insert(5);

		NAMESPACE::set<int> range(++util.begin(), --util.end());
		std::cout << "- range constructor, values :";
		for (NAMESPACE::set<int>::const_iterator cit = range.begin(),
				cite = range.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		NAMESPACE::set<int> copy(util);
		std::cout << "- copy constructor, values :";
		for (NAMESPACE::set<int>::const_iterator cit = copy.begin(),
				cite = copy.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void assignment_operator()
	{
		std::cout << "Assignment operator tests :\n";

		NAMESPACE::set<int> util;
		util.insert(1);
		util.insert(2);
		util.insert(3);
		util.insert(4);
		util.insert(5);

		NAMESPACE::set<int> copy;
		copy.insert(42);

		copy = util;
		std::cout << "- after assignment operator values :";
		for (NAMESPACE::set<int>::const_iterator cit = copy.begin(),
				cite = copy.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void begin()
	{
		std::cout << "begin tests :\n";

		NAMESPACE::set<std::string> set;
		set.insert("1 first");
		set.insert("2 second");
		set.insert("3 last");

		std::cout << "- *begin() : " << *set.begin() << "\n";

		std::cout << std::flush;
	}

	void end()
	{
		std::cout << "end tests :\n";

		NAMESPACE::set<std::string> set;
		set.insert("1 first");
		set.insert("2 second");
		set.insert("3 last");

		std::cout << "- *(--end()) : " << *(--set.end()) << "\n";

		std::cout << std::flush;
	}

	void rbegin()
	{
		std::cout << "rbegin tests :\n";

		NAMESPACE::set<std::string> set;
		set.insert("1 first");
		set.insert("2 second");
		set.insert("3 last");

		std::cout << "- *rbegin() : " << *set.rbegin() << "\n";

		std::cout << std::flush;
	}

	void rend()
	{
		std::cout << "rend tests :\n";

		NAMESPACE::set<std::string> set;
		set.insert("1 first");
		set.insert("2 second");
		set.insert("3 last");

		std::cout << "- *(--rend()) : " << *(--set.rend()) << "\n";

		std::cout << std::flush;
	}

	void empty()
	{
		std::cout << "empty tests :\n";

		NAMESPACE::set<int> set;

		std::cout << "- empty set, empty() : " << std::boolalpha
			<< set.empty() << "\n";

		set.insert(false);
		std::cout << "- non empty set, empty() : " << std::boolalpha
			<< set.empty() << "\n";

		set.clear();
		std::cout << "- clear set, empty() : " << std::boolalpha
			<< set.empty() << "\n";

		std::cout << std::flush;
	}
	
	void size()
	{
		std::cout << "size tests :\n";

		NAMESPACE::set<float> set;

		std::cout << "- empty set, size() : " << set.size() << "\n";

		set.insert(42.42);
		std::cout << "- 1 elem set, size() : " << set.size() << "\n";

		NAMESPACE::set<float> util;
		util.insert(1.1);
		util.insert(2.2);
		util.insert(3.3);
		util.insert(4.4);
		util.insert(5.5);
		set.insert(util.begin(), util.end());
		std::cout << "- 6 elems set, size() : " << set.size() << "\n";

		set.clear();
		std::cout << "- clear set, size() : " << set.size() << "\n";

		std::cout << std::flush;
	}

	void max_size()
	{
		std::cout << "max_size tests :\n";

		NAMESPACE::set<std::string> string_set;
		std::cout << "- set<std::string>, max_size() : "
			<< string_set.max_size() << "\n";

		NAMESPACE::set<int> int_set;
		std::cout << "- set<int>, max_size() : "
			<< int_set.max_size() << "\n";

		NAMESPACE::set<char> char_set;
		std::cout << "- set<char>, max_size() : "
			<< char_set.max_size() << "\n";

		std::cout << std::flush;
	}

	void insert()
	{
		std::cout << "insert tests :\n";

		NAMESPACE::set<int> set;
		NAMESPACE::pair<NAMESPACE::set<int>::iterator, bool> pair;
		NAMESPACE::set<int>::iterator it;

		pair = set.insert(21);
		std::cout << "- new single element insert return : "
			<< *pair.first << ", " << std::boolalpha << pair.second << "\n";
		pair = set.insert(21);
		std::cout << "- single element already insert return : "
			<< *pair.first << ", " << std::boolalpha << pair.second << "\n";
		std::cout << "- after single element insert, values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		it = set.insert(set.begin(), 42);
		std::cout << "- hint insert return : " << *it << "\n";
		std::cout << "- after hint insert, values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		NAMESPACE::set<float> util;
		util.insert(1.1);
		util.insert(2.2);
		util.insert(3.3);
		util.insert(4.4);
		util.insert(5.5);

		set.insert(++util.begin(), --util.end());
		std::cout << "- after range insert, values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void erase()
	{
		std::cout << "erase tests :\n";

		NAMESPACE::set<int> set;
		set.insert(1);
		set.insert(2);
		set.insert(3);
		set.insert(4);
		set.insert(5);

		set.erase(++(++set.begin()));
		std::cout << "- after iterator erase, values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		NAMESPACE::set<int>::size_type st;
		st = set.erase(42);
		std::cout << "- unknown key erase return : " << st << "\n";
		st = set.erase(5);
		std::cout << "- known key erase return : " << st << "\n";
		std::cout << "- after key erase, values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		set.erase(++set.begin(), set.end());
		std::cout << "- after range erase, values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void swap()
	{
		std::cout << "swap tests :\n";

		NAMESPACE::set<int> set;
		set.insert(1);
		set.insert(2);
		set.insert(3);
		set.insert(4);
		set.insert(5);
		NAMESPACE::set<int> set2;
		set2.insert(1);
		set2.insert(2);
		set2.insert(3);

		std::cout << "- before swap, set values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";
		std::cout << "- before swap, set2 values :";
		for (NAMESPACE::set<int>::const_iterator cit = set2.begin(),
				cite = set2.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		set.swap(set2);
		std::cout << "- after member function swap, set values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";
		std::cout << "- after member function swap, set2 values :";
		for (NAMESPACE::set<int>::const_iterator cit = set2.begin(),
				cite = set2.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		swap(set, set2);
		std::cout << "- after non member function swap, set values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";
		std::cout << "- after non member function swap, set2 values :";
		for (NAMESPACE::set<int>::const_iterator cit = set2.begin(),
				cite = set2.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void clear()
	{
		std::cout << "clear tests :\n";

		NAMESPACE::set<int> set;
		set.insert(1);
		set.insert(2);
		set.insert(3);

		set.clear();
		std::cout << "- after clear, values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	template <class T>
	struct comp_util
	{
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;

		bool operator()(T const& x, T const& y) const
		{
			std::cout << "OK if you see this";
			return x < y;
		}
	};

	void key_comp()
	{
		std::cout << "key_comp tests : ";

		NAMESPACE::set< int, comp_util<int> > set;
		NAMESPACE::set< int, comp_util<int> >::key_compare key_compare;

		key_compare = set.key_comp();
		key_compare(1, 2);

		std::cout << std::endl;
	}

	void value_comp()
	{
		std::cout << "value_comp tests : ";

		NAMESPACE::set< int, comp_util<int> > set;
		set.insert(0);
		set.value_comp()(*set.begin(), *set.begin());

		std::cout << std::endl;
	}

	void find()
	{
		std::cout << "find tests :\n";

		NAMESPACE::set<int> set;
		set.insert(42);

		NAMESPACE::set<int>::iterator it;
		it = set.find(42);
		std::cout << "- present key find return : " << *it << "\n";
		it = set.find(21);
		std::cout << "- non present key find return == set::end() : "
			<< std::boolalpha << (it == set.end()) << "\n";

		std::cout << std::flush;
	}

	void count()
	{
		std::cout << "count tests :\n";

		NAMESPACE::set<int> set;
		set.insert(42);

		NAMESPACE::set<int>::size_type st;
		st = set.count(42);
		std::cout << "- present key count return : " << st << "\n";
		st = set.count(21);
		std::cout << "- non present key count return : " << st << "\n";

		std::cout << std::flush;
	}

	void lower_bound()
	{
		std::cout << "lower_bound tests :\n";

		NAMESPACE::set<int> set;
		NAMESPACE::set<int>::iterator it;
		set.insert(2);
		set.insert(4);
		set.insert(8);

		std::cout << "  set values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		it = set.lower_bound(3);
		std::cout << "- lower_bound(3) : " << *it << "\n";

		it = set.lower_bound(4);
		std::cout << "- lower_bound(4) : " << *it << "\n";

		it = set.lower_bound(5);
		std::cout << "- lower_bound(5) : " << *it << "\n";

		std::cout << std::flush;
	}

	void upper_bound()
	{
		std::cout << "upper_bound tests :\n";

		NAMESPACE::set<int> set;
		NAMESPACE::set<int>::iterator it;
		set.insert(2);
		set.insert(4);
		set.insert(8);

		std::cout << "  set values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		it = set.upper_bound(3);
		std::cout << "- upper_bound(3) : " << *it << "\n";

		it = set.upper_bound(4);
		std::cout << "- upper_bound(4) : " << *it << "\n";

		it = set.upper_bound(5);
		std::cout << "- upper_bound(5) : " << *it << "\n";

		std::cout << std::flush;
	}

	void equal_range()
	{
		std::cout << "equal_range tests :\n";

		NAMESPACE::set<int> set;
		NAMESPACE::pair<NAMESPACE::set<int>::const_iterator,
			NAMESPACE::set<int>::const_iterator> it_pair;
		set.insert(1);

		std::cout << "  set values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		it_pair = set.equal_range(1);
		std::cout << "- equal_range(1) values :";
		for (NAMESPACE::set<int>::const_iterator cit = it_pair.first,
				cite = it_pair.second; cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		it_pair = set.equal_range(42);
		std::cout << "- equal_range(42) values :";
		for (NAMESPACE::set<int>::const_iterator cit = it_pair.first,
				cite = it_pair.second; cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";

		std::cout << std::flush;
	}

	void get_allocator()
	{
		std::cout << "get_allocator tests : ";

		NAMESPACE::set<std::string> set;
		NAMESPACE::set<std::string>::allocator_type at = set.get_allocator();

		NAMESPACE::set<std::string>::value_type *vt = at.allocate(1);
		at.construct(vt, "OK if you see this\n");

		std::cout << *vt;

		at.destroy(vt);
		at.deallocate(vt, 1);

		std::cout << std::flush;
	}

	static void print_sets_comparaison(NAMESPACE::set<int> const& set,
			NAMESPACE::set<int> const& set2)
	{
		std::cout << "  set values :";
		for (NAMESPACE::set<int>::const_iterator cit = set.begin(),
				cite = set.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";
		std::cout << "  set2 values :";
		for (NAMESPACE::set<int>::const_iterator cit = set2.begin(),
				cite = set2.end(); cit != cite; ++cit) {
			std::cout << " " << *cit;
		}
		std::cout << "\n";
		std::cout << "- set == set2 : " << std::boolalpha << (set == set2)
			<< "\n";
		std::cout << "- set < set2 : " << std::boolalpha << (set < set2)
			<< "\n";
		std::cout << "- set >= set2 : " << std::boolalpha << (set >= set2)
			<< "\n";
	}

	void relational_operators()
	{
		std::cout << "Relational operators tests :\n";

		NAMESPACE::set<int> set;
		set.insert(1);
		set.insert(2);
		NAMESPACE::set<int> set2;
		set2.insert(1);
		set2.insert(2);
		set2.insert(3);

		print_sets_comparaison(set, set2);

		std::cout << "\n";
		set.insert(4);
		print_sets_comparaison(set, set2);

		std::cout << "\n";
		set.erase(4);
		set.insert(0);
		print_sets_comparaison(set, set2);

		std::cout << "\n";
		set.erase(0);
		set.insert(3);
		print_sets_comparaison(set, set2);

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
		empty();
		std::cout << "\n";
		size();
		std::cout << "\n";
		max_size();
		std::cout << "\n";
		insert();
		std::cout << "\n";
		erase();
		std::cout << "\n";
		swap();
		std::cout << "\n";
		clear();
		std::cout << "\n";
		key_comp();
		std::cout << "\n";
		value_comp();
		std::cout << "\n";
		find();
		std::cout << "\n";
		count();
		std::cout << "\n";
		lower_bound();
		std::cout << "\n";
		upper_bound();
		std::cout << "\n";
		equal_range();
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
