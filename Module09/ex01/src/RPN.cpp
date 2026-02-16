/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:14:29 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/15 23:26:53 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "utils.hpp"

RPN::RPN() : _userInput(""), _stack() {}

RPN::RPN(const std::string &userInput) : _userInput(userInput), _stack() {
    this->inputValidation(userInput);
}

RPN::RPN(const RPN &rightSide) {
    *this = rightSide;
}

RPN &RPN::operator=(const RPN &rightSide) {
    if (this != &rightSide) {
        this->_userInput = rightSide._userInput;
        this->_stack = rightSide._stack;
    }
    return *this;
}

RPN::~RPN() {}

bool RPN::inputValidation(const std::string &expression) {
    if (expression.empty())
        throw std::invalid_argument("Empty expression is not allowed.");
    else if (isDoubleDigit(expression))
        throw std::invalid_argument("Double digit numbers are not allowed.");
    char badChar = '\0';
    if (!areOperationsValid(expression, badChar))
        throw std::invalid_argument("Invalid character '" + std::string(1, badChar) + "' in expression.");
    else if (!areTotalOperationsValid(expression))
        throw std::invalid_argument("Invalid number of operations.");
    this->_userInput = expression;
    return true;
}

int RPN::executeOperation(const int number1, const int number2, const char operation) {
    switch  (operation) {
        case '+':
            return number1 + number2;
        case '-':
            return number1 - number2;
        case '*':
            return number1 * number2;
        case '/':
            if (number2 == 0)
                throw std::runtime_error("Division by zero is not allowed.");
            return number1 / number2;
        default:
            throw std::invalid_argument("Invalid operator.");
    }
}

int RPN::evaluate() {
    std::string::iterator iter = this->_userInput.begin();
    std::size_t idx = 0;
    while (idx < this->_userInput.size()) {
        if (std::isdigit(*iter))
            this->_stack.push(*iter - '0');
        else if (isOperator(*iter) && this->_userInput.size() > 1) {
            if (this->_stack.size() < 2)
                throw std::runtime_error("Not enough operands for operator.");
            int number2 = this->_stack.top();
            this->_stack.pop();
            int number1 = this->_stack.top();
            this->_stack.pop();
            int result = this->executeOperation(number1, number2, *iter);
            this->_stack.push(result);
        }
        idx++;
        iter++;
    }
    if (this->_stack.empty())
        throw std::runtime_error("Invalid expression.");
    return this->_stack.top();
}
