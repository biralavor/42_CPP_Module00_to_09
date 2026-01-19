/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:33:48 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/18 23:45:32 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void) {
  this->_convertTypes[0] = "char";
  this->_convertTypes[1] = "int";
  this->_convertTypes[2] = "float";
  this->_convertTypes[3] = "double";
}

ScalarConverter::~ScalarConverter(void) {}

ScalarConverter::ScalarConverter(const ScalarConverter &src) { *this = src; }

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rightSide) {
  if (this != &rightSide) {
    for (int idx = 0; idx < POSSIBLE_TYPES; idx++) {
      this->_convertTypes[idx] = rightSide._convertTypes[idx];
    }
  }
  return *this;
}

bool ScalarConverter::isInt(const std::string &literal) {
  if (literal.find('.') != std::string::npos
    || literal.find('e') != std::string::npos
    || literal.find('E') != std::string::npos)
    return false;
  if (isdigit(literal[0]) || (literal[0] == '-'
    && literal.length() > 1 && isdigit(literal[1])))
    return true;
  return false;
}

bool ScalarConverter::isChar(const std::string &literal) {
  if (literal.length() == 3 &&
      ((literal[0] == '\'' && literal[2] == '\'') ||
       (literal[0] == '\"' && literal[2] == '\"')) &&
      isprint(literal[1]) && !isdigit(literal[1]))
    return true;
  else if (literal.length() == 1 && isprint(literal[0]) && !isdigit(literal[0]))
    return true;
  return false;
}

bool ScalarConverter::isFloat(const std::string &literal) {
  size_t len = literal.length();
  if (literal == "-inff" || literal == "+inff" || literal == "inff"
    || literal == "nanf")
    return true;
  if (len > 1 && (literal[len -1] == 'f' || literal[len -1] == 'F')
    && literal.find('.') != std::string::npos)
      return true;
  return false;
}

bool ScalarConverter::isDouble(const std::string &literal) {
  if (literal == "-inf" || literal == "+inf" || literal == "inf"
    || literal == "nan")
    return true;
  if (literal.find('.') != std::string::npos
    && literal.find('f') == std::string::npos
    && literal.find('F') == std::string::npos)
    return true;
  return false;
}

void ScalarConverter::impossiblePrinter(const int idx) {
  int counter = 0;
  const char *typeNames[] = {"char", "int", "float", "double"};
  while (counter < idx) {
    std::cout << typeNames[counter] << ": impossible" << std::endl;
    counter++;
  }
}

void ScalarConverter::charPrinter(double converted, const std::string &literal) {
  double realValue = (literal[0] == '\'' || literal[0] == '"')                                                                                               
                       ? converted                                                                                                                             
                       : std::strtod(literal.c_str(), NULL);
  std::cout << "char: ";
  if (realValue < 0 || realValue > 127 ||
      (std::isnan(realValue) || std::isinf(realValue)))
    std::cout << "impossible" << std::endl;
  else if (std::iscntrl(static_cast<int>(realValue)))
    std::cout << "Non displayable" << std::endl;
  else
    std::cout << "'" << static_cast<char>(realValue) << "'" << std::endl;
  (void)converted;
}

void ScalarConverter::intPrinter(double converted, const std::string &literal) {
  double realValue = (literal[0] == '\'' || literal[0] == '"')                                                                                               
                       ? converted                                                                                                                             
                       : std::strtod(literal.c_str(), NULL);
  std::cout << "int: ";
  if ((std::isnan(realValue) || std::isinf(realValue)
    || realValue < static_cast<double>(INT_MIN)
    || realValue > static_cast<double>(INT_MAX)))
    std::cout << "impossible" << std::endl;
  else
    std::cout << static_cast<int>(realValue) << std::endl;
  (void)converted;
}

void ScalarConverter::floatPrinter(double converted, const std::string &literal) {
  std::cout << "float: ";
  if (static_cast<double>(atof(literal.c_str())) ==
      static_cast<int>(atoi(literal.c_str())))
    {
      std::cout << static_cast<int>(converted);
      std::cout << ".0f" << std::endl;
    }
  else
    std::cout << std::strtod(literal.c_str(), NULL) << "f" << std::endl;
}

void ScalarConverter::doublePrinter(double converted, const std::string &literal) {
  std::cout << "double: ";
  if (static_cast<double>(atof(literal.c_str())) ==
      static_cast<int>(atoi(literal.c_str()))) {
    std::cout << static_cast<int>(converted);
    std::cout << ".0" << std::endl;
  }
  else
    std::cout << std::strtod(literal.c_str(), NULL) << std::endl;
}

bool ScalarConverter::isRandomString(const std::string &literal) {
  if (literal.length() > 4 && !isInt(literal) && !isFloat(literal) &&
      !isDouble(literal)) {
    return true;
  }
  return false;
}

void ScalarConverter::convert(const std::string &literal) {
  char *end_ptr = NULL;
  double converted = std::strtod(literal.c_str(), &end_ptr);

  if (literal.empty() || isRandomString(literal)) {
    impossiblePrinter(POSSIBLE_TYPES);
    return;
  }

  if (isChar(literal)) {
    if (literal.length() == 3)
      converted = static_cast<double>(literal[1]);
    else if (literal.length() == 1)
      converted = static_cast<double>(literal[0]);
  } else if (isInt(literal))
    converted = static_cast<double>(atoi(literal.c_str()));
  else if (isFloat(literal) || isDouble(literal))
    converted = static_cast<double>(atof(literal.c_str()));
  else {
    std::cerr << "Error: Invalid input" << std::endl;
    return;
  }
  charPrinter(converted, literal);
  intPrinter(converted, literal);
  floatPrinter(converted, literal);
  doublePrinter(converted, literal);
}
