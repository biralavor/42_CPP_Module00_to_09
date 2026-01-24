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
#include <cstdlib>
#include <stdexcept>

template <typename T>
Array<T>::Array() : _data(nullptr), _size(0) {};

template <typename T>
Array<T>::~Array() {};

template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n) {};

template <typename T>
Array<T>::Array(const Array &rightSide) : _data(nullptr), _size(0) {
    for (unsigned int idx = 0; rightSide._size > idx; idx++) {
        this->_data[idx] = rightSide._data[idx];
    }
    *this = rightSide;
};

template <typename T>
void Array<T>::swap(Array &rightSide) {
    unsigned int tempSize = this->_size;
    this->_size = rightSide._size;
    rightSide._size = tempSize;

    T* tempData = this->_data;
    this->_data = rightSide._data;
    rightSide._data = tempData;
};

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &rightSide) {
    Array<T> temp(rightSide);
    this->swap(temp);
    return *this;
};