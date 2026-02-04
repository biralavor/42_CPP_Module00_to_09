/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 21:45:29 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/25 10:51:24 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <cstdlib>
#include <stdexcept>

template <typename T>
Array<T>::Array() : _data(NULL), _size(0){};

template <typename T>
Array<T>::~Array() {
  if (this->_data)
    delete[] this->_data;
};

template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n){};

template <typename T>
Array<T>::Array(const Array &rightSide) : _data(NULL), _size(rightSide._size) {
  if (this->_size > 0) {
    this->_data = new T[this->_size];
    for (unsigned int idx = 0; idx < this->_size; idx++) {
      this->_data[idx] = rightSide._data[idx];
    }
  }
};

template <typename T>
void Array<T>::swap(Array &rightSide) {
  unsigned int tempSize = this->_size;
  this->_size = rightSide._size;
  rightSide._size = tempSize;

  T *tempData = this->_data;
  this->_data = rightSide._data;
  rightSide._data = tempData;
};

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &rightSide) {
  if (this == &rightSide)
    return *this;
  Array<T> temp(rightSide);
  this->swap(temp);
  return *this;
};

template <typename T>
unsigned int Array<T>::size() const {
  return this->_size;
};

template <typename T>
T &Array<T>::operator[](unsigned int idx) {
  if (idx >= this->_size) {
    throw std::out_of_range("Index out of bounds");
  }
  return this->_data[idx];
};

template <typename T>
T const &Array<T>::operator[](unsigned int idx) const {
  if (idx >= this->_size) {
    throw std::out_of_range("Index out of range");
  }
  return this->_data[idx];
};
