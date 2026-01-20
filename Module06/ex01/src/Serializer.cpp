/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:13:04 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/19 20:43:46 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer() {}

Serializer::~Serializer() {}

Serializer::Serializer(const Serializer &rightSide) {
    *this = rightSide;
}

Serializer &Serializer::operator=(const Serializer &rightSide) {
    if (this != &rightSide) {
        // No member variables to copy
    }
    return *this;
}

uintptr_t Serializer::serialize(Data *ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data *>(raw);
}