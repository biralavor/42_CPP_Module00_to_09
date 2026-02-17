/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 10:04:28 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/17 17:32:32 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <fstream>

int main(int ac, char **av) {
    std::cout << "Ford-Johnson sort with performance "
              << "comparison between std::vector and std::deque" << std::endl;

    if (ac == 2) {
        try {
            PmergeMe pmergeMe(av[1]);
            pmergeMe.sortManager();
        } catch (const std::exception &error) {
            std::cerr << "Error: " << error.what() << std::endl;
            return 1;
        }
        return 0;
    }

    std::ifstream inputFile("data/input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Usage: " << av[0] << " <space-separated integers to sort>" << std::endl;
        std::cerr << "Or create data/input.txt with test cases (one per line)" << std::endl;
        return 1;
    }

    std::string line;
    int testNum = 1;
    while (std::getline(inputFile, line)) {
        if (line.empty())
            continue;
        
        std::cout << "\n=== Test " << testNum++ << " ===" << std::endl;
        try {
            PmergeMe pmergeMe(line);
            pmergeMe.sortManager();
        } catch (const std::exception &error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }
    inputFile.close();
    return 0;
}
