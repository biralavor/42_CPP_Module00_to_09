/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:16:02 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/17 17:55:36 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <cctype>
#include <iostream>

bool isDoubleDigit(const std::string &expression) {
    for (size_t idx = 0; idx < expression.size(); idx++) {
        if (idx + 1 < expression.size() && std::isdigit(expression[idx])
            && std::isdigit(expression[idx + 1])) {
            return true;
        }
    }
    return false;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool areOperationsValid(const std::string &expression, char &badChar) {
    for (size_t idx = 0; idx < expression.size(); idx++) {
        if (std::isdigit(expression[idx]) || std::isspace(expression[idx]))
            continue;
        if (!isOperator(expression[idx])) {
            badChar = expression[idx];
            return false;
        }
    }
    return true;
}

bool areTotalOperationsValid(const std::string &expression) {
    int totalOperations = 0;
    int totalNumbers = 0;
    if (expression.size() == 1)
        return false;
    for (size_t idx = 0; idx < expression.size(); idx++) {
        if (std::isdigit(expression[idx]))
            totalNumbers++;
        else if (isOperator(expression[idx]))
            totalOperations++;
    }
    if (totalOperations + 1 != totalNumbers) {
        return false;
    }
    return true;
}
