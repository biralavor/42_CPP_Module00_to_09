/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:20:15 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 14:27:28 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <iostream>

class Bureaucrat;

class Form
{
    const std::string   _name;
    bool                _isSigned;
    const int           _gradeToSign;
    const int           _gradeToExecute;
    static const int    MAX_GRADE = 1;
    static const int    MIN_GRADE = 150;

public:
    Form(void);
    Form(const std::string name, int gradeToSign, int gradeToExecute);
    ~Form(void);
    Form(Form const &src);
    Form &operator=(Form const &rightSide);
    void beSigned(void);

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
    class AlreadySignedForm : public std::exception
    {
        public:
            virtual const char *what() const throw();
    };

    std::string getName(void) const;
    bool getSignature(void) const;
    int getGradeToSign(void) const;
    int getGradeToExecute(void) const;
    bool beSigned(Bureaucrat &bureaucrat);
    void setSignature(Form &paper, bool status);
};

std::ostream &operator<<(std::ostream &out, const Form &form);
