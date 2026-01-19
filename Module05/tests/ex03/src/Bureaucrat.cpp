/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:59:45 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 16:31:48 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat(void)
    : _name("Default"), _grade(LOWEST_GRADE)
{
}

Bureaucrat::Bureaucrat(const std::string name, int grade)
    : _name(name)
{
    if (grade < HIGHEST_GRADE)
        throw Bureaucrat::GradeTooHighException();
    if (grade > LOWEST_GRADE)
        throw Bureaucrat::GradeTooLowException();
    _grade = grade;
}

Bureaucrat::~Bureaucrat(void)
{
}

Bureaucrat::Bureaucrat(Bureaucrat const &src)
    : _name(src._name)
{
    *this = src;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &rightSide)
{
    if (this != &rightSide)
        this->_grade = rightSide.getGrade();
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
    return "Grade is too high. Must be between 1 and 150.";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Grade is too low. Must be between 1 and 150.";
}

void Bureaucrat::signForm(AForm &paper)
{
    try
    {
        paper.beSigned(*this);
        std::cout
        << "\e[34m" << this->getName() << " signed "
        << paper.getType() << "\e[0m" << std::endl;
    }
    catch(const std::exception &err)
    {
        std::cerr
        << "\e[34m" << _name << " couldn't sign " << paper.getType()
        << " because \e[31m" << err.what() << "\e[0m\n";
    }
}

void Bureaucrat::executeForm(AForm const &paper) const
{
    try
    {
        paper.execute(*this);
        std::cout
        << "\e[34m" << this->getName() << " executed "
        << paper.getType() << "\e[0m" << std::endl;
    }
    catch(const std::exception &err)
    {
        std::cerr
        << "\e[34m" << _name << " couldn't execute " << paper.getType()
        << " because \e[31m" << err.what() << "\e[0m\n";
    }
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat)
{
    out << bureaucrat.getName() << ", bureaucrat grade "
    << bureaucrat.getGrade();
    return out;
}
