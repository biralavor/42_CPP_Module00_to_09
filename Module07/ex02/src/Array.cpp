/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 21:45:29 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/23 22:02:17 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

Array::Array() {};

Array::~Array() {};

Array::Array(unsigned int n) {
    for(unsigned int idx = 0; idx < n; idx++) {
        this->data = new T();
    }
};

Array::Array(const Array &rightSide) {
    *this = rightSide;
};

void swap(Array &rightSide) {
    std::swap(this->size, rightSide.size);
    std::swap(this->data, rightSide.data);
};

Array &Array::operator=(const Array &rightSide) {
    Array temp(rightSide);
    this->swap(temp);
    return *this;
};