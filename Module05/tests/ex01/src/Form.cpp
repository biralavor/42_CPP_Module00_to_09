/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:18:16 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 16:51:17 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(void)
    : _name("Default"),
    _isSigned(false),
    _gradeToSign(MIN_GRADE),
    _gradeToExecute(MIN_GRADE)
{
}

Form::Form(const std::string name, int gradeToSign, int gradeToExecute)
    : _name(name),
    _isSigned(false),
    _gradeToSign(gradeToSign),
    _gradeToExecute(gradeToExecute)
{
    if (gradeToSign < MAX_GRADE || gradeToExecute < MAX_GRADE)
        throw GradeTooHighException();
    if (gradeToSign > MIN_GRADE || gradeToExecute > MIN_GRADE)
        throw GradeTooLowException();
}

Form::~Form(void)
{
}

Form::Form(Form const &src)
    : _name(src.getName()),
    _isSigned(src.getSignature()),
    _gradeToSign(src.getGradeToSign()),
    _gradeToExecute(src.getGradeToExecute())
{
}

Form &Form::operator=(Form const &rightSide)
{
    if (this != &rightSide)
    {
        this->_isSigned = rightSide.getSignature();
    }
    return *this;
}

std::string Form::getName(void) const
{
    return this->_name;
}

bool Form::getSignature(void) const
{
    return this->_isSigned;
}

int Form::getGradeToSign(void) const
{
    return this->_gradeToSign;
}

int Form::getGradeToExecute(void) const
{
    return this->_gradeToExecute;
}

const char* Form::GradeTooHighException::what() const throw()
{
    return "Grade is too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "Grade is too low";
}

const char* Form::AlreadySignedForm::what() const throw()
{
    return "Form is already signed!";
}

void Form::setSignature(Form &paper, bool status)
{
    paper._isSigned = status;
}

bool Form::beSigned(Bureaucrat &bureaucrat)
{
    if (getSignature())
        throw Form::AlreadySignedForm();
    else if (bureaucrat.getGrade() > this->_gradeToSign)
        throw Form::GradeTooLowException();
    this->setSignature(*this, true);
    return true;
}

std::ostream &operator<<(std::ostream &out, const Form &form)
{
    out << "\n:: AForm '" << form.getName() << "' ::\n"
    << "Status: "
    << (form.getSignature() ? "\e[32m signed" : "\e[31m not signed")
    << "\n\e[0m"
    << "Grade to sign: " << form.getGradeToSign() << "\n"
    << "Grade to execute: " << form.getGradeToExecute();
    return out;
}
