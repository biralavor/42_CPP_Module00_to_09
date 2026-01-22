/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:27:02 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/21 21:41:56 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Whatever.hpp"
#include <iostream>

int main(void) {
    int a = 42;
    int b = 200;
    std::cout << "a = " << a << ", b = " << b << std::endl;
    
    std::cout << "\n::::::: SWAP :::::" << std::endl;
    ::swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    
    std::cout << "\n::::::: MIN :::::" << std::endl;
    std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
    
    std::cout << "\n::::::: MAX :::::" << std::endl;
    std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
    
    std::cout << "\n\n::::::: TEST WITH STRINGS :::::" << std::endl;
    std::string c = "chaine1";
    std::string d = "chaine2";
    std::cout << "c = " << c << ", d = " << d << std::endl;
    ::swap(c, d);
    std::cout << "After swap -> c = " << c << ", d = " << d << std::endl;
    
    std::cout << "\n::::::: MIN :::::" << std::endl;
    std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
    
    std::cout << "\n::::::: MAX :::::" << std::endl;
    std::cout << "max(c, d) = " << ::max(c, d) << std::endl;
    
    return 0;
}
