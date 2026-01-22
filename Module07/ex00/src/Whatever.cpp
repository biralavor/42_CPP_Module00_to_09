/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whatever.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:27:57 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/21 21:38:32 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Whatever.hpp"
#include <iostream>

Whatever::Whatever() {}

Whatever::~Whatever() {}

Whatever::Whatever(const Whatever &rightSide) {
    *this = rightSide;
}

Whatever &Whatever::operator=(const Whatever &rightSide) {
    (void)rightSide;
    return *this;
}
