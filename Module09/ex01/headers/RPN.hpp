/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:00:11 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/15 22:33:59 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stack>
#include <string>
#include <stdexcept>
#include <iostream>

class RPN {
private:
    std::string _userInput;
    std::stack<int> _stack;
    RPN();
    RPN(const RPN &rightSide);
    RPN &operator=(const RPN &rightSide);
    
    bool inputValidation(const std::string &expression);
    int executeOperation(const int number1, const int number2, const char operation);
    
public:
    RPN(const std::string &userInput);
    ~RPN();

    int evaluate();
};
