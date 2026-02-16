/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 10:04:28 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/16 13:14:26 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av) {
    std::cout << "Ford-Johnson sort with performance "
              << "comparison between std::vector and std::deque" << std::endl;
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <space-separated integers to sort>" << std::endl;
        return 1;
    }
    
    try {
        PmergeMe pmergeMe(av[1]);
        pmergeMe.sortManager();
    } catch (const std::exception &error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}
