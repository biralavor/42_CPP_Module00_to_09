/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:06:59 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/27 10:42:00 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <exception>

class AForm;

class Bureaucrat
{
    const std::string   _name;
    int                 _grade;

public:
    static const int    HIGHEST_GRADE = 1;
    static const int    LOWEST_GRADE = 150;

public:
    Bureaucrat(void);
    Bureaucrat(const std::string name, int grade);
    Bureaucrat(Bureaucrat const &src);
    Bureaucrat &operator=(Bureaucrat const &rightSide);
    ~Bureaucrat(void);
    std::string getName(void) const;
    int getGrade(void) const;

    void incrementGrade(void);
    void decrementGrade(void);
    void signForm(AForm &paper);
    void executeForm(AForm const &paper) const;
    class GradeTooHighException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };

    class GradeTooLowException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat);
