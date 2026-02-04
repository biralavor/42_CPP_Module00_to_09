/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 11:06:26 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/03 22:01:13 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "Easyfind.hpp"

int main()
{
    std::cout << "----- EASYFIND TEST -----" << std::endl;
    std::cout << "Creating a vector of integers and searching for a value" << std::endl;
    std::vector<int> vec;
    for (int idx = 0; idx < 10; idx++)
        vec.push_back(idx * 10);
    std::cout << "Vector contents: ";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "\n#1A TEST: Searching for value 50" << std::endl;
    try {
        std::vector<int>::iterator iter = easyfind(vec, 50);
        std::cout << "Found: " << *iter << std::endl;
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    std::cout << "\n#2A TEST: Searching for a value that does not exist" << std::endl;
    try {
        std::vector<int>::iterator iter = easyfind(vec, 55);
        std::cout << "Found: " << *iter << std::endl;
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    std::cout << "///// END EASYFIND TEST /////" << std::endl;

    std::cout << "\n----- EASYFIND TEST WITH DIFFERENT CONTAINERS -----" << std::endl;
    std::cout << "Creating a list of integers and searching for a value" << std::endl;
    std::list<int> lst;
    for (int idx = 0; idx < 10; idx++)
        lst.push_back(idx * 5);
    std::cout << "List contents: ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "\n#1B TEST: Searching for value 25" << std::endl;
    try {
        std::list<int>::iterator iter = easyfind(lst, 25);
        std::cout << "Found: " << *iter << std::endl;
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    std::cout << "\n#2B TEST: Searching for a value that does not exist (26)" << std::endl;
    try {
        std::list<int>::iterator iter = easyfind(lst, 26);
        std::cout << "Found: " << *iter << std::endl;
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    std::cout << "///// END EASYFIND TEST WITH DIFFERENT CONTAINERS /////" << std::endl;
    return 0;
}
