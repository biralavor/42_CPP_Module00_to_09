/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 11:44:19 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/08 13:15:59 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>() {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &rightSide) : std::stack<T>(rightSide) {}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack &rightSide) {
    if (this != &rightSide)
        std::stack<T>::operator=(rightSide);
    return *this;
}

template <typename T>
MutantStack<T>::~MutantStack() {}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
    return this->c.begin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
    return this->c.end();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin() const {
    return this->c.begin();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end() const {
    return this->c.end();
}
