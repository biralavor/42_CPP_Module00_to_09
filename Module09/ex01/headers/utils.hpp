/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:16:52 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/15 22:41:29 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

bool isDoubleDigit(const std::string &expression);
bool isOperator(char c);
bool areOperationsValid(const std::string &expression, char &badChar);
bool areTotalOperationsValid(const std::string &expression);
