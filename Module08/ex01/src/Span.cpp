/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:55:46 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/03 22:09:21 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int quantity) : _maxSize(quantity) {
    _numbers.reserve(quantity);
}

Span::Span(const Span &rightSide) : _numbers(rightSide._numbers), _maxSize(rightSide._maxSize) {}

Span &Span::operator=(const Span &rightSide) {
    if (this != &rightSide) {
        this->_numbers = rightSide._numbers;
        this->_maxSize = rightSide._maxSize;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int nbr) {
    if (_numbers.size() >= _maxSize) {
        throw std::overflow_error("Error. Span is full. Cannot add more numbers.");
    }
    _numbers.push_back(nbr);
}

unsigned int Span::shortestSpan() {
    if (_numbers.size() < 2) {
        throw std::logic_error("Error. Not enough numbers to find the shortest span.");
    }
    long minSpan = std::numeric_limits<long>::max();
    std::vector<int> sortedNumbers = _numbers;
    std::sort(sortedNumbers.begin(), sortedNumbers.end());
    for (size_t idx = 1; idx < sortedNumbers.size(); ++idx)
    {
        long span = static_cast<long>(sortedNumbers[idx]) - static_cast<long>(sortedNumbers[idx - 1]);
        if (span < minSpan) {
            minSpan = span;
        }
    }
    return static_cast<unsigned int>(minSpan);
}

unsigned int Span::longestSpan() {
    if (_numbers.size() < 2) {
        throw std::logic_error("Error. Not enough numbers to find the longest span.");
    }
    long minValue = static_cast<long>(*std::min_element(_numbers.begin(), _numbers.end()));
    long maxValue = static_cast<long>(*std::max_element(_numbers.begin(), _numbers.end()));
    return static_cast<unsigned int>(maxValue - minValue);
}
