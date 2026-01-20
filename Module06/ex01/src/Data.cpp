/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:14:57 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/19 22:05:08 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data() {}

Data::Data(int i, std::string n, float v, bool a)
    : id(i), name(n), value(v), active(a) {}

Data::~Data() {}

Data::Data(const Data &rightSide) {
    *this = rightSide;
}

Data &Data::operator=(const Data &rightSide) {
    if (this != &rightSide) {
        id = rightSide.id;
        name = rightSide.name;
        value = rightSide.value;
        active = rightSide.active;
    }
    return *this;
}

bool Data::operator==(const Data& other) const {
    return id == other.id
        && name == other.name
        && value == other.value
        && active == other.active;
}
