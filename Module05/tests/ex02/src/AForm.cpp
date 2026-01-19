/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:18:16 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 16:51:12 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(void)
    : _type("Default Abstract Form"),
    _target("Default Target"),
    _isSigned(false),
    _gradeToSign(MIN_GRADE),
    _gradeToExecute(MIN_GRADE)
{
}

AForm::AForm(const std::string type, int gradeToSign, int gradeToExecute,
    const std::string target)
    : _type(type),
    _target(target),
    _isSigned(false),
    _gradeToSign(gradeToSign),
    _gradeToExecute(gradeToExecute)
{
    if (gradeToSign < MAX_GRADE || gradeToExecute < MAX_GRADE)
        throw GradeTooHighException();
    if (gradeToSign > MIN_GRADE || gradeToExecute > MIN_GRADE)
        throw GradeTooLowException();
}

AForm::~AForm(void)
{
}

AForm::AForm(AForm const &src)
    : _type(src.getType()),
    _target(src.getTarget()),
    _isSigned(src.getSignature()),
    _gradeToSign(src.getGradeToSign()),
    _gradeToExecute(src.getGradeToExecute())
{
}

AForm &AForm::operator=(AForm const &rightSide)
{
    if (this != &rightSide)
    {
        this->_isSigned = rightSide.getSignature();
    }
    return *this;
}

std::string AForm::getType(void) const
{
    return this->_type;
}

bool AForm::getSignature(void) const
{
    return this->_isSigned;
}

int AForm::getGradeToSign(void) const
{
    return this->_gradeToSign;
}

int AForm::getGradeToExecute(void) const
{
    return this->_gradeToExecute;
}

void AForm::setSignature(bool status)
{
    this->_isSigned = status;
}

const std::string &AForm::getTarget(void) const
{
    return this->_target;
}

const char* AForm::GradeTooHighException::what() const throw()
{
    return "Grade is too high. Must be between 1 and 150.";
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return "Grade is too low. Must be between 1 and 150.";
}

const char* AForm::FormNotSignedException::what() const throw()
{
    return "Form is not signed!";
}

const char* AForm::FormAlreadySignedException::what() const throw()
{
    return "Form is already signed!";
}

bool AForm::beSigned(Bureaucrat &bureaucrat)
{
    if (this->getSignature())
        throw AForm::FormAlreadySignedException();
    else if (bureaucrat.getGrade() > this->_gradeToSign)
        throw AForm::GradeTooLowException();
    else
        this->setSignature(true);
    return true;
}

void AForm::requirementsController(const Bureaucrat &bureaucrat) const
{
    if (!this->getSignature())
        throw AForm::FormNotSignedException();
    if (bureaucrat.getGrade() > this->getGradeToExecute())
        throw AForm::GradeTooLowException();
}

void AForm::execute(const Bureaucrat &bureaucrat) const
{
    this->requirementsController(bureaucrat);
    action(bureaucrat);
}

std::ostream &operator<<(std::ostream &out, const AForm &absForm)
{
    out
    << "\n:: AForm '" << absForm.getType() << "' ::\n"
    << "Target: " << absForm.getTarget() << "\n"
    << "Status: "
    << (absForm.getSignature() ? "\e[32m signed" : "\e[31m not signed")
    << "\n\e[0m"
    << "Grade to sign: " << absForm.getGradeToSign() << "\n"
    << "Grade to execute: " << absForm.getGradeToExecute();
    return out;
}
