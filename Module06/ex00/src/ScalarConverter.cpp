/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:33:48 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/18 18:18:24 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void)
{
	this->_convertTypes[0] = "int";
	this->_convertTypes[1] = "char";
	this->_convertTypes[2] = "float";
	this->_convertTypes[3] = "double";
	std::cout
	<< "\e[35m"
	<< "Possible TYPES to be converted are:"
	<< "\e[0m" << std::endl;
	for (int idx = 0; idx < POSSIBLE_TYPES; idx++)
	{
		std::cout
		<< "\e[36m"
		<< "- " << this-> _convertTypes[idx]
		<< "\e[0m" << std::endl;
	}
}

ScalarConverter::~ScalarConverter(void)
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
	*this = src;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rightSide)
{
	if(this != &rightSide)
	{
		for (int idx = 0; idx < POSSIBLE_TYPES; idx++)
		{
			this->_convertTypes[idx] = rightSide._convertTypes[idx];
		}
	}
	return *this;
}

bool ScalarConverter::isInt(const std::string &literal)
{
	if (isdigit(literal[0]) || (literal[0] == '-' && isdigit(literal[1])))
		return true;
	return false;
}

bool ScalarConverter::isChar(const std::string &literal)
{
	if (literal.length() == 3 \
		&& ((literal[0] == '\'' && literal[2] == '\'') \
		|| (literal[0] == '\"' && literal[2] == '\"')) \
		&& isprint(literal[1]) && !isdigit(literal[1]))
		return true;
	else if (literal.length() == 1 && isprint(literal[0]) && !isdigit(literal[0]))
		return true;
	return false;
}

bool ScalarConverter::isFloat(const std::string &literal)
{
	float converted = static_cast<float>(atof(literal.c_str()));
	if (converted != 0.0f)
		return true;
	return false;
}

bool ScalarConverter::isDouble(const std::string &literal)
{
	double converted = static_cast<double>(atof(literal.c_str()));
	if (converted != 0.0)
		return true;
	return false;
}

bool ScalarConverter::isRandomString(const std::string &literal)
{
	if (literal.length() > 3
		&& !isInt(literal) && !isFloat(literal) && !isDouble(literal))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return true;
	}
	return false;
}

void ScalarConverter::convert(const std::string &literal)
{
	if (literal.empty())
	{
		std::cerr << "Error. String is empty." << std::endl;
		return ;
	}
	else if (isRandomString(literal))
		return ;
	
	double value = 0.0;
	if (isChar(literal))
	{
		if (literal.length() == 3)
			value = static_cast<double>(literal[1]);
		else if (literal.length() == 1)
			value = static_cast<double>(literal[0]);
	}
	else if (isInt(literal))
		value = static_cast<double>(atoi(literal.c_str()));
	else if (isFloat(literal) || isDouble(literal))
		value = static_cast<double>(atof(literal.c_str()));
	else
	{
		std::cerr << "Error: Invalid input" << std::endl;
		return;
	}
	
	std::cout << "char: ";
	if (value < 0 || value > 127 || (std::isnan(value) || std::isinf(value)))
		std::cout << "impossible" << std::endl;
	else if (iscntrl(static_cast<int>(value)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
	
	std::cout << "int: ";
	if (std::isnan(value) || std::isinf(value))
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(value) << std::endl;
	
	std::cout << "float: ";
	if (static_cast<double>(atof(literal.c_str())) == static_cast<int>(atoi(literal.c_str())))
	{
		std::cout << static_cast<int>(value);
		std::cout << ".0f" << std::endl;
	}
	else
		std::cout << std::strtod(literal.c_str(), NULL) << "f" << std::endl;

	std::cout << "double: ";
	if (static_cast<double>(atof(literal.c_str())) == static_cast<int>(atoi(literal.c_str())))
	{
		std::cout << static_cast<int>(value);
		std::cout << ".0" << std::endl;
	}
	else
		std::cout << std::strtod(literal.c_str(), NULL) << std::endl;
}
