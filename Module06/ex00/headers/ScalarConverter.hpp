/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:40:36 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/18 23:14:12 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <iomanip>
#include <cerrno>

#define POSSIBLE_TYPES 4

class ScalarConverter
{
	std::string _convertTypes[POSSIBLE_TYPES];

	typedef bool (*PtrToMember)(const std::string &literal);

	ScalarConverter(void);
	~ScalarConverter(void);
	ScalarConverter(const ScalarConverter &src);
	ScalarConverter &operator=(const ScalarConverter &rightSide);

	static bool isInt(const std::string &literal);
	static bool isChar(const std::string &literal);
	static bool isFloat(const std::string &literal);
	static bool isDouble(const std::string &literal);
	static bool isRandomString(const std::string &literal);
	static void impossiblePrinter(const int idx);

	static void charPrinter(double converted, const std::string &literal);
	static void intPrinter(double converted, const std::string &literal);
	static void floatPrinter(double converted, const std::string &literal);
	static void doublePrinter(double converted, const std::string &literal);

public:
	static void convert(const std::string &literal);
};
