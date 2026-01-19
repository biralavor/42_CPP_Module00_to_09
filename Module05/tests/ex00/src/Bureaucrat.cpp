/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:59:45 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/23 18:42:24 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

const int Bureaucrat::HIGHEST_GRADE;
const int Bureaucrat::LOWEST_GRADE;

Bureaucrat::Bureaucrat(void)
    : _name("Default"), _grade(LOWEST_GRADE)
{
    std::cout << "Default constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(const std::string name, int grade)
    : _name(name)
{
    std::cout << "Parameterized constructor called" << std::endl;
    if (grade < HIGHEST_GRADE)
        throw Bureaucrat::GradeTooHighException();
    if (grade > LOWEST_GRADE)
        throw Bureaucrat::GradeTooLowException();
    _grade = grade;
}

Bureaucrat::~Bureaucrat(void)
{
    std::cout << "Destructor called" << std::endl;
}

Bureaucrat::Bureaucrat(Bureaucrat const &src)
    : _name(src._name)
{
    std::cout << "Copy constructor called for: " << _name << std::endl;
    *this = src;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &rightSide)
{
    std::cout << "Assignment operator called for: "
    << rightSide.getName() << std::endl;
    if (this != &rightSide)
    {
        // _name is const, so it cannot be changed after construction.
        // Only non-const members can be assigned.
        this->_grade = rightSide.getGrade();
    }
    return *this;
}

std::string Bureaucrat::getName(void) const
{
    return this->_name;
}

int Bureaucrat::getGrade(void) const
{
    return this->_grade;
}

void Bureaucrat::incrementGrade(void)
{
    if (this->_grade - 1 < HIGHEST_GRADE)
        throw Bureaucrat::GradeTooHighException();
    else
        this->_grade--;
}

void Bureaucrat::decrementGrade(void)
{
    if (this->_grade + 1 > LOWEST_GRADE)
        throw Bureaucrat::GradeTooLowException();
    else
        this->_grade++;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Grade is too low";
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat)
{
    out << bureaucrat.getName() << ", bureaucrat grade "
    << bureaucrat.getGrade();
    return out;
}
