/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 11:44:25 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/08 11:47:35 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>

int main() {
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << "Top element: " << mstack.top() << std::endl; // Should print 17

    mstack.pop();
    std::cout << "Size after pop: " << mstack.size() << std::endl; // Should print 1

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    std::cout << "Iterating through MutantStack:" << std::endl;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << std::endl; // Should print all elements in order
    }

    return 0;
}
