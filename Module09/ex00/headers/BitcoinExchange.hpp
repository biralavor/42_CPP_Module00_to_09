/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:42:45 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/15 13:10:48 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>

#define DATA_FILE "data/data.csv"

class BitcoinExchange {
private:
  std::map<std::string, double> data;

public:
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange &rightSide);
  BitcoinExchange &operator=(const BitcoinExchange &rightSide);
  ~BitcoinExchange();

  void loadDatabase(const std::string &filename);
  void processInput(const std::string &inputFile);
  std::map<std::string, double> findClosestDate(const std::string &date) const;
  bool inputValidation(std::istringstream &iss, std::string &date, std::string &valueStr) const;
};
