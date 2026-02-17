/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:13:44 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/15 23:09:08 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void printHeader(const std::string &header) {
    std::cout << "::::: " << header << " :::::" << std::endl;
}

void subjectTest1() {
    printHeader("#1 SUBJECT TEST");
    std::string subjectTest1 = "8 9 * 9 - 9 - 9 - 4 - 1 +";
    try {
        RPN rpn(subjectTest1);
        std::cout << "Operation: " << subjectTest1 << std::endl;
        std::cout << "Result: " << rpn.evaluate() << std::endl;
    } catch (const std::exception &error) {
        std::cerr << "Error: " << error.what() << std::endl;
    }
    std::cout << std::endl;
}

void subjectTest2() {
    printHeader("#2 SUBJECT TEST");
    std::string subjectTest2 = "7 7 * 7 -";
    try {
        RPN rpn(subjectTest2);
        std::cout << "Operation: " << subjectTest2 << std::endl;
        std::cout << "Result: " << rpn.evaluate() << std::endl;
    } catch (const std::exception &error) {
        std::cerr << "Error: " << error.what() << std::endl;
    }
    std::cout << std::endl;
}

void subjectTest3() {
    printHeader("#3 SUBJECT TEST");
    std::string subjectTest3 = "1 2 * 2 / 2 * 2 4 - +";
    try {
        RPN rpn(subjectTest3);
        std::cout << "Operation: " << subjectTest3 << std::endl;
        std::cout << "Result: " << rpn.evaluate() << std::endl;
    } catch (const std::exception &error) {
        std::cerr << "Error: " << error.what() << std::endl;
    }
    std::cout << std::endl;
}

void subjectTest4() {
    printHeader("#4 SUBJECT TEST");
    std::string subjectTest4 = "(1 + 1)";
    try {
        RPN rpn(subjectTest4);
        std::cout << "Operation: " << subjectTest4 << std::endl;
        std::cout << "Result: " << rpn.evaluate() << std::endl;
    } catch (const std::exception &error) {
        std::cerr << "Error: " << error.what() << std::endl;
    }
    std::cout << std::endl;
}
    
int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Error. Usage: " << av[0] << " <RPN expression>" << std::endl;
        return 1;
    }

    subjectTest1();
    subjectTest2();
    subjectTest3();
    subjectTest4();
    
    try {
        RPN rpn(av[1]);
        printHeader("USER INPUT TEST");
        std::cout << "Operation: " << av[1] << std::endl;
        std::cout << "Result: " << rpn.evaluate() << std::endl;
    } catch (const std::exception &error) {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}
