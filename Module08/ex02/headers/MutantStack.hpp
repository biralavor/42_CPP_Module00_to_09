/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 11:47:40 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/08 13:04:27 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stack>
#include <iterator>

template <typename T>
class MutantStack : public std::stack<T> {
    public:
        typedef typename std::stack<T>::container_type::iterator iterator;
        typedef typename std::stack<T>::container_type::const_iterator const_iterator;
        
        MutantStack();
        MutantStack(const MutantStack &rightSide);
        MutantStack &operator=(const MutantStack &rightSide);
        ~MutantStack();
        
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;    
};

#include "MutantStack.tpp"
