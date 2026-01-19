/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:09:57 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 15:46:06 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>
#include <fstream>

class ShrubberyCreationForm : public AForm
{
	static const int _minGradeToSign = 145;
	static const int _minGradeToExecute = 137;

private:
	void createShrubberyFile(void) const;
	void writeShrubberyArt(std::ofstream &ofs) const;

public:
	ShrubberyCreationForm(void);
	explicit ShrubberyCreationForm(const std::string &target);
	~ShrubberyCreationForm(void);
	ShrubberyCreationForm(ShrubberyCreationForm const &src);
	ShrubberyCreationForm &operator=(ShrubberyCreationForm const &rightSide);
	
	virtual void action(Bureaucrat const &executor) const;

	class FileOperationException : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
};
