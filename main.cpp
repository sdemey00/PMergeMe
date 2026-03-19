#include <iostream>
#include <sstream>	// std::stringstream

#include "PmergeMe.hpp"

int	main(int ac, char **av) {
	ac--;av++;
	if (ac < 1) {
		std::cerr << "Usage ./PmergeMe <positive_integer_sequence>" << std::endl;
		return (1);
	}
	try {
		if (ac == 1) {
			PmergeMe p(*av);
			std::cout << p << std::endl;
		}
		else {
			std::vector<int> vec;
			for (int i = 0; i < ac; ++i) {
				std::stringstream	ss(av[i]);
				int					nb;
				ss >> nb;
				if (!(ss.eof() && !ss.fail()) || nb < 0) {
					std::cerr << "Error: Invalid sequence." << std::endl;
					return (1);
				}
				vec.push_back(nb);
			}
			if (vec.empty())
				return (1);
			PmergeMe p(vec);
			std::cout << p << std::endl;
		}
	} catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
