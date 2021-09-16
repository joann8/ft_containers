#include "tests.hpp"

namespace tests { namespace stack
{
	void member_types()
	{
		std::cout << "Member Types tests : OK if you see this" << std::endl;
		NAMESPACE::stack<int>::value_type vt;
		static_cast<void>(vt);
		NAMESPACE::stack<int>::container_type ct;
		NAMESPACE::stack<int>::size_type st;
		static_cast<void>(st);
	}

	void constructors()
	{
		std::cout << "Constructors tests :\n";

		NAMESPACE::stack<int> stack;
		std::cout << "- default constructor, empty() : " << std::boolalpha
			<< stack.empty() << "\n";

		std::vector<int> vector(3);
		NAMESPACE::stack< int, std::vector<int> > filled_stack(vector);
		std::cout << "- constructor with a filled underlying container, empty() : " << std::boolalpha
			<< filled_stack.empty() << "\n";

		std::cout << std::flush;
	}

	void size()
	{
		std::cout << "size tests :\n";

		NAMESPACE::stack<float> stack;

		std::cout << "- empty stack, size() : " << stack.size() << "\n";

		stack.push(42.42);
		std::cout << "- 1 elem stack, size() : " << stack.size() << "\n";

		for (int i = 0; i < 20; ++i) {
			stack.push(21.21);
		}
		std::cout << "- 21 elems stack, size() : " << stack.size() << "\n";

		stack.pop();
		std::cout << "- after pop, size() : " << stack.size() << "\n";

		std::cout << std::flush;
	}

	void empty()
	{
		std::cout << "empty tests :\n";

		NAMESPACE::stack<bool> stack;

		std::cout << "- empty stack, empty() : " << std::boolalpha
			<< stack.empty() << "\n";

		stack.push(false);
		std::cout << "- after push, empty() : " << std::boolalpha
			<< stack.empty() << "\n";

		stack.pop();
		std::cout << "- after pop, empty() : " << std::boolalpha
			<< stack.empty() << "\n";

		std::cout << std::flush;
	}

	void top()
	{
		std::cout << "top tests :\n";

		NAMESPACE::stack<std::string> stack;
		stack.push("first");
		stack.push("second");
		stack.push("last");

		std::cout << "- top() : " << stack.top() << "\n";

		std::cout << std::flush;
	}

	void push()
	{
		std::cout << "push tests :\n";

		NAMESPACE::stack<int> stack;
		stack.push(0);

		std::cout << "- actual top() : " << stack.top() << "\n";

		stack.push(1);
		std::cout << "- after push(1), top() : " << stack.top() << "\n";

		std::cout << std::flush;
	}

	void pop()
	{
		std::cout << "pop tests :\n";

		NAMESPACE::stack<int> stack;
		stack.push(0);
		stack.push(1);

		std::cout << "- actual top() : " << stack.top() << "\n";

		stack.pop();
		std::cout << "- after pop(), top() : " << stack.top() << "\n";

		std::cout << std::flush;
	}

	static void print_vectors_comparaison(NAMESPACE::stack<int> const& stack,
			NAMESPACE::stack<int> const& stack2)
	{
		std::cout << "- stack == stack2 : " << std::boolalpha << (stack == stack2)
			<< "\n";
		std::cout << "- stack < stack2 : " << std::boolalpha << (stack < stack2)
			<< "\n";
		std::cout << "- stack >= stack2 : " << std::boolalpha << (stack >= stack2)
			<< "\n";
	}

	void relational_operators()
	{
		std::cout << "Relational operators tests :\n";

		NAMESPACE::stack<int> stack;
		stack.push(0);
		stack.push(0);
		NAMESPACE::stack<int> stack2;
		stack2.push(0);
		stack2.push(0);
		stack2.push(0);

		print_vectors_comparaison(stack, stack2);

		std::cout << "\n";
		stack.push(1);
		print_vectors_comparaison(stack, stack2);

		std::cout << "\n";
		stack.top() = 0;
		print_vectors_comparaison(stack, stack2);

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
		size();
		std::cout << "\n";
		empty();
		std::cout << "\n";
		top();
		std::cout << "\n";
		push();
		std::cout << "\n";
		pop();
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
