/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iter.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:02:36 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/22 19:03:51 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Iter.hpp"

Iter::Iter() {}

Iter::~Iter() {}

Iter::Iter(const Iter &rightSide) {
    *this = rightSide;
}

Iter &Iter::operator=(const Iter &rightSide) {
    (void)rightSide;
    return *this;
}
