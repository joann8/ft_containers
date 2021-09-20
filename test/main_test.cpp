#include <iostream>
#include <string>
#include "common.hpp"
#include "test_vector.hpp"
#include "test_map.hpp"
#include "test_stack.hpp"
#include "test_set.hpp"

int main(int argc, char **argv) 
{
	std::string containers[4] = {"vector", "map", "stack", "set"};
	void (*test_functions[4])(void) = {&test_vector, &test_map, &test_stack, &test_set};

	if(argc != 2) 
	{
		std::cout << "Usage ./ft_containers <container_name>" << std::endl;
	} 
	else 
	{
		for(size_t i = 0; i < 4; i++) 
		{
			if (argv[1] == containers[i]) 
			{
				test_functions[i]();
				return 0;
			}
		}
		std::cout << "This container is unknown" << std::endl;
	}
	return (0);
}
