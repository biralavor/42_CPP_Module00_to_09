/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:47:47 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/03 21:09:45 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <limits>

class Span {
    private:
        std::vector<int> _numbers;
        unsigned int _maxSize;
    
    public:
        Span(unsigned int quantity);
        Span(const Span &rightSide);
        Span &operator=(const Span &rightSide);
        ~Span();

        void addNumber(int nbr);
        template <typename InputIterator>
        void addRange(InputIterator start, InputIterator end);
        unsigned int shortestSpan();
        unsigned int longestSpan();
};

template <typename InputIterator>
void Span::addRange(InputIterator start, InputIterator end) {
    size_t rangeSize = std::distance(start, end);
    if (rangeSize + _numbers.size() > _maxSize) {
        throw std::overflow_error("Error. Range exceeds Span capacity.");
    }
    _numbers.insert(_numbers.end(), start, end);
}
