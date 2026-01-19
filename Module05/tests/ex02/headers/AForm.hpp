/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:20:15 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 15:15:52 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <iostream>

class Bureaucrat;

class AForm
{
    const std::string   _type;
    const std::string   _target;
    bool                _isSigned;
    const int           _gradeToSign;
    const int           _gradeToExecute;
    static const int    MAX_GRADE = 1;
    static const int    MIN_GRADE = 150;

public:
    AForm(void);
    AForm(const std::string type, int gradeToSign, int gradeToExecute,
        const std::string target);
    virtual ~AForm(void);
    AForm(AForm const &src);
    AForm &operator=(AForm const &rightSide);

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
    class FormNotSignedException : public std::exception
    {
        public:
            virtual const char *what() const throw();
    };
    class FormAlreadySignedException : public std::exception
    {
        public:
            virtual const char *what() const throw();
    };

    std::string getType(void) const;
    bool getSignature(void) const;
    int getGradeToSign(void) const;
    int getGradeToExecute(void) const;
    bool beSigned(Bureaucrat &bureaucrat);
    void setSignature(bool status);

    const std::string &getTarget(void) const;
    void execute(const Bureaucrat &bureaucrat) const;
    void requirementsController(const Bureaucrat &executor) const;
    virtual void action(const Bureaucrat &executor) const = 0;
};

std::ostream &operator<<(std::ostream &out, const AForm &absForm);
