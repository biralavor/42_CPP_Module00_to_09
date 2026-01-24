/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:48:23 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/23 22:01:51 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename T>
class Array {
private:
    T* _data;
    unsigned int _size;

public:
    Array();
    Array(unsigned int n);
    Array(const Array &rightSide);
    Array &operator=(const Array &rightSide);
    ~Array();

    void swap(Array &rightSide);
    unsigned int size() const;
    T &operator[](unsigned int idx);
    T const &operator[](unsigned int idx) const;
};

#include "Array.tpp"
/* ************************************************************************** */