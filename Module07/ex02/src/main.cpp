/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:49:48 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/25 10:55:25 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <iostream>

int main(void) {
    std::cout << ":::::::: Creating an Array of integers with 5 elements. :::::::" << std::endl;
    Array<int> arr(5);
    for (unsigned int i = 0; i < arr.size(); i++) {
        arr[i] = i * 10;
    }
    std::cout << "Array contents:" << std::endl;
    for (unsigned int idx = 0; idx < arr.size(); idx++) {
        std::cout << "arr[" << idx << "] = " << arr[idx] << std::endl;
    }

    std::cout << "\n ::::::: Creating a copy of the Array using the copy constructor. :::::::" << std::endl;
    Array<int> copy(arr);
    std::cout << "Copy contents:" << std::endl;
    for (unsigned int idx = 0; idx < copy.size(); idx++) {
        std::cout << "copy[" << idx << "] = " << copy[idx] << std::endl;
    }

    std::cout << "\n ::::::: Modifying the original array. :::::::" << std::endl;
    arr[0] = 999;
    std::cout << "Original arr[0]: " << arr[0] << std::endl;
    std::cout << "Copy copy[0]: " << copy[0] << std::endl;

    std::cout << "\n ::::::: Assigning the original array to the copy using the assignment operator. :::::::" << std::endl;
    copy = arr;
    std::cout << "Copy contents after assignment:" << std::endl;
    for (unsigned int idx = 0; idx < copy.size(); idx++) {
        std::cout << "copy[" << idx << "] = " << copy[idx] << std::endl;
    }

    std::cout << "\n ::::::: Attempting to access out-of-bounds index. :::::::" << std::endl;
    try {
        std::cout << "Accessing arr[10]...." << arr[10] << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Caught exception: " <<e.what() << std::endl;
    }
    return 0;
}
/* ************************************************************************** */