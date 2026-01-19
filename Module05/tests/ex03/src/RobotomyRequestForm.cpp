/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:11:56 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 16:33:34 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void)
	: AForm("Default Robotomy Request",
		_minGradeToSign,
		_minGradeToExecute,
		"Default Target")
{
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm("Robotomy Request Form",
		_minGradeToSign,
		_minGradeToExecute,
		target)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &src)
	: AForm(src)
{
}

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &rightSide)
{
	if (this != &rightSide)
		AForm::operator=(rightSide);
	return *this;
}

void RobotomyRequestForm::drillingNoise(void) const
{
	std::cout
	<< "\e[33m"
	<< "Bzzzzzzzz... Vrrrrrrrrr... Bzzzzzzzz..."
	<< "\e[0m" <<std::endl;
}

void RobotomyRequestForm::successAnnouncement(void) const
{
	std::cout
	<< this->getTarget()
	<< "\e[32m" << " has been robotomized successfully."
	<< "\e[0m" <<std::endl;
}

void RobotomyRequestForm::failureAnnouncement(void) const
{
	std::cout
	<< "The robotomy on " << this->getTarget()
	<< "\e[31m" << " has failed."
	<< "\e[0m" <<std::endl;
}

void RobotomyRequestForm::randomOutcome(void) const
{
	drillingNoise();
	if (std::rand() % 2)
		successAnnouncement();
	else
		failureAnnouncement();
}

void RobotomyRequestForm::action(Bureaucrat const &executor) const
{
	std::cout
	<< "\e[34m" << executor.getName()
	<< "\e[32m is running the form \e[36m"
	<< this->getType() << "\e[0m" <<std::endl;
	randomOutcome();
}
