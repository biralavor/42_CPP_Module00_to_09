/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 11:06:26 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/01 11:51:25 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Easyfind.hpp"

int main()
{
    std::vector<int> vec;
    for (int idx = 0; idx < 10; idx++)
        vec.push_back(idx * 10);
    
    try {
        std::vector<int>interator = easyfind(vec, 50);
        std::cout << "Found: " << *interator << std::endl;
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
}
