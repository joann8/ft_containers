#include <iostream>
#include <string>
#include <cstring>

#include "tests.hpp"

int main(int argc, char* argv[])
{
	if (argc == 1) {
		std::cout << "usage :" << std::endl
			<< "  " << argv[0] << " container_name" << std::endl;
		return 1;
	}
	std::string ft = "ft";
	std::string std = "std";
	std::cout << "Start tests with namespace : " << NAMESPACE << "\n";
	for (int i = 1; i < argc; ++i) {
		std::cout << std::endl;
		if (strcmp(argv[i], "vector") == 0) {
			tests::vector::launch();
		}
		else if (strcmp(argv[i], "map") == 0) {
			tests::map::launch();
		}
		else if (strcmp(argv[i], "stack") == 0) {
			tests::stack::launch();
		}
		else if (strcmp(argv[i], "set") == 0) {
			tests::set::launch();
		}
		else {
			std::cout << "Unknown container_name : " << argv[i] << std::endl;
		}
	}
	return 0;
}
