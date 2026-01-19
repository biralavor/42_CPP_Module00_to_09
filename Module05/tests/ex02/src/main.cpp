/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:43:08 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 15:12:35 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

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
	
	// std::cout << "\e[33m"
	// << "\n#6 ----- TESTING ABSTRACT FORM CLASSES -----"
	// << "\e[0m" << std::endl;
	// try
	// {
	// 	AForm shouldNotExistForm("Weird and Abstract Form");

	// 	std::cout << shouldNotExistForm << std::endl;
	// }
	// catch (const std::exception &err)
	// {
	// 	std::cerr << "\e[31m" << err.what() << "\e[0m" << std::endl;
	// }
	return 0;
}
