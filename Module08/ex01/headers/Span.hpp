/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:47:47 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/02 22:50:02 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include <exception>

class Span {
    private:
        std::vector<int> numbers;
        unsigned int maxSize;
    
    public:
        Span(unsigned int quantity);
        Span(const Span &rightSide);
        Span &operator=(const Span &rightSide);
        ~Span();

        void addNumber(int nbr);
        template <typename InputIterator>
        void addRange(InputIterator start, InputIterator end);
        unsigned short int shortestSpan();
        unsigned int longestSpan();
};
