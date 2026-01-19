/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:10:25 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 16:14:54 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void)
	: AForm("Default Shrubbery Creation Form",
		_minGradeToSign,
		_minGradeToExecute,
		"Default Target")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("Shrubbery Creation Form",
		_minGradeToSign,
		_minGradeToExecute,
		target)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &src)
	: AForm(src)
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &rightSide)
{
	if (this != &rightSide)
		AForm::operator=(rightSide);
	return *this;
}

const char * ShrubberyCreationForm::FileOperationException::what() const throw()
{
	return "Error creating or writing to the shrubbery file.";
}

void ShrubberyCreationForm::writeShrubberyArt(std::ofstream &ofs) const
{
	ofs << "       _-_" << std::endl;
	ofs << "    /~~   ~~\\" << std::endl;
	ofs << " /~~         ~~\\" << std::endl;
	ofs << "{               }" << std::endl;
	ofs << " \\  _-     -_  /" << std::endl;
	ofs << "   ~  \\\\ //  ~" << std::endl;
	ofs << "_- -   | | _- _" << std::endl;
	ofs << "  _ -  | |   -_" << std::endl;
	ofs << "      // \\\\" << std::endl;
}

void ShrubberyCreationForm::createShrubberyFile(void) const
{
	std::string filename = this->getTarget() + "_shrubbery";
	std::ofstream ofs(filename.c_str());

	if (!ofs.is_open())
		throw ShrubberyCreationForm::FileOperationException();
	else
		writeShrubberyArt(ofs);
	ofs << std::endl;
	std::cout << "Shrubbery created in file: " << filename << std::endl;
	ofs.close();
}

void ShrubberyCreationForm::action(Bureaucrat const &executor) const
{
	std::cout
	<< "\e[34m" << executor.getName()
	<< "\e[32m is running the form \e[36m"
	<< this->getType() << "\e[0m" <<std::endl;
	this->createShrubberyFile();
}
