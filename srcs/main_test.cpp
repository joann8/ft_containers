/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:15:20 by lsoulier          #+#    #+#             */
/*   Updated: 2021/09/16 14:29:55 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "test_vector.hpp"
#include "test_map.hpp"
#include "test_stack.hpp"

int main(int argc, char **argv) 
{
	std::string containers[3] = {"vector", "map", "stack"};
	void (*test_functions[3])(void) = {&test_vector, &test_map, &test_stack};

	if(argc != 2) 
	{
		std::cout << "Usage ./ft_containers <container_name>" << std::endl;
	} 
	else 
	{
		for(size_t i = 0; i < 3; i++) 
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
/*
int main(int argc, char **argv) {
	std::string containers[5] = {"list", "vector", "map", "stack", "queue"};
	void (*test_functions[5])(void) = {&test_list, &test_vector, &test_map,
		&test_stack, &test_queue};

	if(argc != 2) {
		std::cout << "Usage ./ft_containers <container_name>" << std::endl;
	} else {
		for(size_t i = 0; i < 5; i++) {
			if (argv[1] == containers[i]) {
				test_functions[i]();
				return 0;
			}
		}
		std::cout << "This container is unknown" << std::endl;
	}
	return (0);
}*/
