/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:43:08 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/28 15:15:40 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main(void)
{
	std::cout << "\e[33m"
	<< "#1 ----- TESTING BUREAUCRATS CREATION -----"
	<< "\e[0m" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 150);

		std::cout << intern << std::endl;
	}
	catch (const std::exception &err)
	{
		std::cerr << "\e[31m" << err.what() << "\e[0m" << std::endl;
	}

	std::cout << "\e[33m"
	<< "\n#2 ----- TESTING INVALID GRADE to Sign/Execute FORMS -----"
	<< "\e[0m" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 150);

		ShrubberyCreationForm shrub("Flowers In My Garden");
		RobotomyRequestForm robot("iRobot");
		PresidentialPardonForm president("Macron");

		std::cout << intern << std::endl;
		
		std::cout << shrub << std::endl;
		std::cout << robot << std::endl;
		std::cout << president << "\n" << std::endl;

		intern.signForm(shrub);
		intern.executeForm(shrub);

		intern.signForm(robot);
		intern.executeForm(robot);

		intern.signForm(president);
		intern.executeForm(president);

		std::cout << shrub << std::endl;
		std::cout << robot << std::endl;
		std::cout << president << std::endl;
	}
	catch (const std::exception &err)
	{
		std::cerr << "\e[31m" << err.what() << "\e[0m" << std::endl;
	}
	
	std::cout << "\e[33m"
	<< "\n#3 ----- TESTING VALID GRADE to Sign/Execute Forms -----"
	<< "\e[0m" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 4);

		ShrubberyCreationForm shrub("Flowers In My Garden");
		RobotomyRequestForm robot("iRobot");
		PresidentialPardonForm president("Macron");

		std::cout << intern << std::endl;
		
		std::cout << shrub << std::endl;
		std::cout << robot << std::endl;
		std::cout << president << "\n" << std::endl;

		intern.signForm(shrub);
		intern.executeForm(shrub);

		intern.signForm(robot);
		intern.executeForm(robot);

		intern.signForm(president);
		intern.executeForm(president);

		std::cout << shrub << std::endl;
		std::cout << robot << std::endl;
		std::cout << president << std::endl;
	}
	catch (const std::exception &err)
	{
		std::cerr << "\e[31m" << err.what() << "\e[0m" << std::endl;
	}

	std::cout << "\e[33m"
	<< "\n#4 ----- TESTING ALREADY SIGNED FORMS -----"
	<< "\e[0m" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 4);
		Bureaucrat boss("Boss", 1);

		ShrubberyCreationForm shrub("Flowers In My Garden");
		RobotomyRequestForm robot("iRobot");
		PresidentialPardonForm president("Macron");

		std::cout << boss << std::endl;
		std::cout << intern << std::endl;
		
		std::cout << shrub << std::endl;
		std::cout << robot << std::endl;
		std::cout << president << "\n" << std::endl;

		boss.signForm(shrub);
		boss.executeForm(shrub);

		intern.signForm(shrub);
		intern.executeForm(shrub);

		boss.signForm(robot);
		boss.executeForm(robot);

		intern.signForm(robot);
		intern.executeForm(robot);

		boss.signForm(president);
		boss.executeForm(president);

		intern.signForm(president);
		intern.executeForm(president);

		std::cout << shrub << std::endl;
		std::cout << robot << std::endl;
		std::cout << president << std::endl;
	}
	catch (const std::exception &err)
	{
		std::cerr << "\e[31m" << err.what() << "\e[0m" << std::endl;
	}

	std::cout << "\e[33m"
	<< "\n#5 ----- TESTING NOT SIGNED FORMS AND EXECUTE THEM -----"
	<< "\e[0m" << std::endl;
	try
	{
		Bureaucrat intern("Intern", 4);
		Bureaucrat boss("Boss", 1);

		ShrubberyCreationForm shrub("Flowers In My Garden");
		RobotomyRequestForm robot("iRobot");
		PresidentialPardonForm president("Macron");

		std::cout << boss << std::endl;
		std::cout << intern << std::endl;
		
		std::cout << shrub << std::endl;
		std::cout << robot << std::endl;
		std::cout << president << "\n" << std::endl;

		boss.executeForm(shrub);
		intern.executeForm(shrub);

		boss.executeForm(robot);
		intern.executeForm(robot);

		boss.executeForm(president);
		intern.executeForm(president);

		std::cout << shrub << std::endl;
		std::cout << robot << std::endl;
		std::cout << president << std::endl;
	}
	catch (const std::exception &err)
	{
		std::cerr << "\e[31m" << err.what() << "\e[0m" << std::endl;
	}

	std::cout << "\e[33m"
	<< "\n#6 ----- TESTING INTERN CLASS THAT MAKES FORMS -----"
	<< "\e[0m" << std::endl;
	try
	{
		Bureaucrat boss("Boss", 1);
		Intern intern;
		
		std::cout << boss << std::endl;
		
		AForm *rrf = intern.makeForm("Robotomy Request", "Bender");
		boss.signForm(*rrf);
		boss.executeForm(*rrf);
		delete rrf;

		AForm *scf = intern.makeForm("Shrubbery Creation", "Home");
		boss.signForm(*scf);
		boss.executeForm(*scf);
		delete scf;

		AForm *ppf = intern.makeForm("Presidential Pardon", "President");
		boss.signForm(*ppf);
		boss.executeForm(*ppf);
		delete ppf;
	}
	catch (const std::exception &err)
	{
		std::cerr << "\e[31m" << err.what() << "\e[0m" << std::endl;
	}

	std::cout << "\e[33m"
	<< "\n#6 ----- TESTING INTERN CLASS THAT TRY TO MAKE INVALID FORMS -----"
	<< "\e[0m" << std::endl;
	try
	{
		Bureaucrat boss("Boss", 1);
		Intern intern;
		
		std::cout << boss << std::endl;
		
		AForm *invalidForm28B = intern.makeForm("invalidForm28B", "Moulinette");
		boss.signForm(*invalidForm28B);
		boss.executeForm(*invalidForm28B);
		delete invalidForm28B;
	}
	catch (const std::exception &err)
	{
		std::cerr << "\e[31m" << err.what() << "\e[0m" << std::endl;
	}
	std::cout << std::endl;
	return 0;
}
