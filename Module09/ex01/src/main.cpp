/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:13:44 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/17 20:26:26 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <fstream>

int main(int ac, char **av) {
    std::cout << "Reverse Polish Notation Calculator" << std::endl;

    if (ac == 2) {
        try {
            RPN rpn(av[1]);
            std::cout << "Operation: " << av[1] << std::endl;
            std::cout << "Result: " << rpn.evaluate() << std::endl;
        } catch (const std::exception &error) {
            std::cerr << "Error: " << error.what() << std::endl;
            return 1;
        }
        return 0;
    }

    std::ifstream inputFile("data/input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Usage: " << av[0] << " \"<RPN expression>\"" << std::endl;
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
            RPN rpn(line);
            std::cout << "Operation: " << line << std::endl;
            std::cout << "Result: " << rpn.evaluate() << std::endl;
        } catch (const std::exception &error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }
    inputFile.close();
    return 0;
}
