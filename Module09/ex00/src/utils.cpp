/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:31:10 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/17 17:55:36 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>

bool isValidDateFormat(const std::string &date) {
  if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
    std::cerr << RED("Error: ") << YELLOW("Invalid date format.") << std::endl;
    return false;
  }
  for (size_t i = 0; i < 10; i++) {
    if (i == 4 || i == 7)
      continue;
    if (!std::isdigit(date[i])) {
      std::cerr << RED("Error: ") << YELLOW("Date is not a digit.")
                << std::endl;
      return false;
    }
  }
  return true;
}

bool isValidDate(const std::string &date) {
  if (!isValidDateFormat(date))
    return false;
  int year = atoi(date.substr(0, 4).c_str());
  int month = atoi(date.substr(5, 2).c_str());
  int day = atoi(date.substr(8, 2).c_str());
  if (year < 1 || year > 9999 || month < 1 || month > 12 || day < 1 ||
      day > 31) {
    // std::cerr << RED("Error: ") << YELLOW("Invalid date format.") << std::endl;
    return false;
  }
  if (month == 2) {
    if ((!isLeapYear(year) && day > 28) || day > 29) {
      std::cerr << RED("Error: ") << YELLOW("February has 28 or 29 days.")
                << std::endl;
      return false;
    }
  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
    if (day > 30) {
      std::cerr << RED("Error: ") << YELLOW("This month has 30 days.")
                << std::endl;
      return false;
    }
  }
  return true;
}

bool isValidValue(const std::string &value) {
  if (value.empty())
    return false;
  size_t start = 0;
  if (value[0] == '-') {
    std::cerr << RED("Error: ") << YELLOW("not a positive number.") << std::endl;
    return false;
  }
  if (value[0] == '+')
    start = 1;

  for (size_t i = start; i < value.size(); i++) {
    if (!std::isdigit(value[i]) && value[i] != '.')
      return false;
  }
  double val = atof(value.c_str());
  if (val > 1000) {
    std::cerr << RED("Error: ") << YELLOW("too large a number.") << std::endl;
    return false;
  }
  return true;
}

bool isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

std::string skipSpaces(const std::string &str) {
  std::string::const_iterator start = str.begin();
  while (start != str.end() && std::isspace(*start)) {
    start++;
  }

  std::string::const_reverse_iterator end = str.rbegin();
  while (end.base() != start && std::isspace(*end)) {
    end++;
  }

  return std::string(start, end.base());
}

std::string skipPipe(const std::string &str) {
  std::string result;

  for (size_t idx = 0; idx < str.size(); idx++) {
    if (str[idx] != '|') {
      result += str[idx];
    }
  }
  return skipSpaces(result);
}
