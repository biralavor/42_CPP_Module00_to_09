/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:11:42 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/20 19:58:49 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(void) {
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    std::cout << "--- Manual Instantiation Tests ---" << std::endl;

    Base *a = new A();
    std::cout << "Object 'a' created from class A (derived from Base)."
            << std::endl;
    std::cout << "Pointer: " << a << std::endl;
    std::cout << "Real type (ptr): ";
    identify(a);
    std::cout << "Real type (ref): ";
    identify(*a);
    std::cout << std::endl;

    Base *b = new B();
    std::cout << "Object 'b' created from class B (derived from Base)."
    << std::endl;
    std::cout << "Pointer: " << b << std::endl;
    std::cout << "Real type (ptr): ";
    identify(b);
    std::cout << "Real type (ref): ";
    identify(*b);
    std::cout << std::endl;

    Base *c = new C();
    std::cout << "Object 'c' created from class C (derived from Base)."
    << std::endl;
    std::cout << "Pointer: " << c << std::endl;
    std::cout << "Real type (ptr): ";
    identify(c);
    std::cout << "Real type (ref): ";
    identify(*c);
    std::cout << std::endl;

    std::cout << "--- Random Generation Tests ---" << std::endl;
    for (int i = 0; i < 5; i++) {
        Base *random = generate();
        std::cout << "Random object " << i + 1 << " (" << random << "): ";
        identify(random);
        delete random;
    }
    delete a;
    delete b;
    delete c;
    return 0;
}
