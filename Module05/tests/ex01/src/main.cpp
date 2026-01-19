/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:57:24 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 14:38:48 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

const std::string RESET = "\e[0m";
const std::string RED = "\e[31m";
const std::string GREEN = "\e[32m";
const std::string YELLOW = "\e[33m";
const std::string BLUE = "\e[34m";

int main(void)
{
    std::cout << YELLOW
    << "#1 Bureaucrat and Form VALID test"
    << RESET << std::endl;
    try
    {
        Bureaucrat bureaucrat("Odin", 42);
        Form form("Form A", 50, 100);
        
        std::cout << bureaucrat << std::endl;
        std::cout << form << std::endl;
        bureaucrat.signForm(form);
        std::cout << form << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr
        << RED << e.what() << '\n' << RESET;
    }

    std::cout << YELLOW
    << "\n#2 VALID Bureaucrat with Too High Form Grade test"
    << RESET << std::endl;
    try
    {
        Bureaucrat bureaucrat("Aphrodite", 42);
        Form form("Form A", 40, 100);
        
        std::cout << bureaucrat << std::endl;
        std::cout << form << std::endl;
        bureaucrat.signForm(form);
        std::cout << form << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr
        << RED << e.what() << '\n' << RESET;
    }

    std::cout << YELLOW
    << "\n#3 VALID Bureaucrat trying to Sign a already signed Form test"
    << RESET << std::endl;
    try
    {
        Bureaucrat bAphrodite("Aphrodite", 42);
        Bureaucrat bPoseidon("Poseidon", 30);
        Form form("Form A", 50, 100);
        
        std::cout << bAphrodite << std::endl;
        std::cout << bPoseidon << std::endl;
        std::cout << form << std::endl;
        bAphrodite.signForm(form);
        std::cout << form << std::endl;
        
        bPoseidon.signForm(form);
    }
    catch (const std::exception &e) {
        std::cerr
        << RED << e.what() << '\n' << RESET;
    }
    std::cout << YELLOW
    << "\n#4 INVALID Bureaucrat (GradeTooLow) for Signing Forms test"
    << RESET << std::endl;
    try
    {
        Bureaucrat bureaucrat("Thor", 42);
        Form form("Form B", 30, 60);

        std::cout << bureaucrat << std::endl;
        std::cout << form << std::endl;
        bureaucrat.signForm(form);
        std::cout << form << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr
        << RED << e.what() << '\n' << RESET;
    }
    
    std::cout << YELLOW
    << "\n#5 INVALID Bureaucrat (GradeTooHigh) for Signing Forms test"
    << RESET << std::endl;
    try
    {
        Bureaucrat bureaucrat("Zeus", 0);
        Form form("Form C", 30, 60);
        
        std::cout << bureaucrat << std::endl;
        std::cout << form << std::endl;
        bureaucrat.signForm(form);
        std::cout << form << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr
        << RED << e.what() << '\n' << RESET;
    }
    return 0;
}