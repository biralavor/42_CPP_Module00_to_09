/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:55:46 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/02 23:07:15 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int quantity) : maxSize(quantity) {
    numbers.reserve(quantity);
}

Span::Span(const Span &rightSide) {
    *this = rightSide;
}

Span &Span::operator=(const Span &rightSide) {
    if (this != &rightSide) {
        this->numbers = rightSide.numbers;
        this->maxSize = rightSide.maxSize;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int nbr) {
    if (numbers.size() >= maxSize) {
        throw std::exception();
    }
    numbers.push_back(nbr);
}

template <typename InputIterator>
void Span::addRange(InputIterator start, InputIterator end) {
    if (std::distance(start, end) + numbers.size() > maxSize) {
        throw std::exception();
    }
    numbers.insert(numbers.end(), start, end);
}

unsigned short int Span::shortestSpan() {
    if (numbers.size() < 2) {
        throw std::exception();
    }
}

unsigned int Span::longestSpan() {
    if (numbers.size() < 2) {
        throw std::exception();
    }
    int minValue = *std::min_element(numbers.begin(), numbers.end());
    int maxValue = *std::max_element(numbers.begin(), numbers.end());
    return maxValue - minValue;
}
