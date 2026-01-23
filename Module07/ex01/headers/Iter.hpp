/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:51:53 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/22 21:28:39 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Colors.hpp"
#include <cstddef>
#include <iostream>
#include <string>

class Iter {
public:
  Iter();
  ~Iter();
  Iter(const Iter &rightSide);
  Iter &operator=(const Iter &rightSide);
};

template <typename T, typename F>
void iter(T *array, const size_t &lenght, F func) {
  if (!func || !array)
    return;
  for (size_t idx = 0; idx < lenght; idx++) {
    func(array[idx]);
  }
};

template <typename T> void basic_printer_as_template(const T &element) {
  std::cout << YELLOW << element << RESET << std::endl;
}

template <typename T> void incremental_printer_as_template(T &element) {
  element++;
  std::cout << GREEN << element << RESET << std::endl;
}

template <> inline void incremental_printer_as_template(std::string &element) {
  element += "_modified";
  std::cout << GREEN << element << RESET << std::endl;
}
