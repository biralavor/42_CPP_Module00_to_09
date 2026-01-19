/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:07:25 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/27 16:08:51 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#define POSSIBLE_FORMS 3

class Intern
{
	std::string _formTypes[POSSIBLE_FORMS];

private:
	int getActualFormIndex(const std::string formName) const;
	AForm *createShrubberyForm(const std::string target) const;
	AForm *createRobotomyForm(const std::string target) const;
	AForm *createPresidentialForm(const std::string target) const;

public:
	Intern(void);
	~Intern(void);
	Intern(Intern const &src);
	Intern &operator=(Intern const &rightSide);

	class FormNotFoundException : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
	AForm *makeForm(const std::string formName, const std::string target) const;
};
