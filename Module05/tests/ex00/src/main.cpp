/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:06:13 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/25 13:38:01 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

const std::string RESET = "\e[0m";
const std::string RED = "\e[31m";
const std::string GREEN = "\e[32m";
const std::string YELLOW = "\e[33m";
const std::string BLUE = "\e[34m";

int main (void)
{
    std::cout
    << YELLOW << "#1 --- Testing Valid Bureaucrats ---"
    << RESET << std::endl;
    try
    {
        Bureaucrat b1;
        std::cout << GREEN << b1 << RESET << std::endl;
        b1.incrementGrade();
        std::cout << "After increment: " << GREEN << b1 << RESET << std::endl;
        b1.decrementGrade();
        std::cout << "After decrement: " << GREEN << b1 << RESET << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr
        << RED << "Caught exception: " << e.what()
        << RESET << std::endl;
    }

    try
    {
        Bureaucrat b2("Led", 2);
        std::cout << GREEN << b2 << RESET << std::endl;
        b2.incrementGrade();
        std::cout << "After increment: " << GREEN << b2 << RESET << std::endl;
        b2.decrementGrade();
        std::cout << "After decrement: " << GREEN << b2 << RESET << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr
        << RED << "Caught exception: " << e.what()
        << RESET << std::endl;
    }

    std::cout
    << YELLOW << "\n#2 --- Testing Grade Too Low ---"
    << RESET << std::endl;
    std::cout
    << BLUE << "::: trying grade as 151 :::" << RESET << std::endl;
    try
    {
        Bureaucrat b3("Zepplin", 151);
        std::cout << b3 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr
        << RED << "Caught exception: " << e.what()
        << RESET << std::endl;
    }
    std::cout
    << BLUE << "::: trying grade as 151, then incrementing :::"
    << RESET << std::endl;
    try
    {
        Bureaucrat b4("Again", 151);
        b4.incrementGrade();
        std::cout << b4 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr
        << RED << "Caught exception: " << e.what()
        << RESET << std::endl;
    }

    std::cout
    << YELLOW << "\n#3 --- Testing Grade Too High ---"
    << RESET << std::endl;
    std::cout
    << BLUE << "::: trying grade as 0 :::" << RESET << std::endl;
    try
    {
        Bureaucrat b5("Rock'n Roll", 0);
        std::cout << b5 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr
        << RED << "Caught exception: " << e.what()
        << RESET << std::endl;
    }
    std::cout
    << BLUE << "::: trying grade as 0, then decrementing :::"
    << RESET << std::endl;
    try
    {
        Bureaucrat b6("Rock'n Roll", 0);
        b6.decrementGrade();
        std::cout << b6 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr
        << RED << "Caught exception: " << e.what()
        << RESET << std::endl;
    }

    return 0;
}
