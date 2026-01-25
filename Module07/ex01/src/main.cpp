/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:04:10 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/22 21:18:47 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Iter.hpp"
#include <iostream>
#include <string>

int main(void) {
    int nbr_arr[] = {1, 2, 3, 4, 5};
    int nbr_arr_dec[] = {10, 24, 41};
    std::string abc_arr[] = {"a", "b", "c"};
    std::string hello_arr[] = {"hello", "world", "iter", "function", "template"};

    std::cout << "Integer Array before iter: " << std::endl;
    iter(nbr_arr, 5, basic_printer_as_template<int>);
    std::cout << "Integer Array after iter with incremental printer: " << std::endl;
    iter(nbr_arr, 5, incremental_printer_as_template<int>);

    std::cout << "Integer Array with DECIMALS before iter: " << std::endl;
    iter(nbr_arr_dec, 3, basic_printer_as_template<int>);
    std::cout << "Integer Array with DECIMALS after iter with incremental printer: " << std::endl;
    iter(nbr_arr_dec, 3, incremental_printer_as_template<int>);

    std::cout << "\nString Array ABC before iter: " << std::endl;
    iter(abc_arr, 3, basic_printer_as_template<std::string>);
    std::cout << "String Array ABC after iter with incremental printer: " << std::endl;
    iter(abc_arr, 3, incremental_printer_as_template<std::string>);

    std::cout << "\nString Array Hello before iter: " << std::endl;
    iter(hello_arr, 5, basic_printer_as_template<std::string>);
    std::cout << "String Array Hello after iter with incremental printer: " << std::endl;
    iter(hello_arr, 5, incremental_printer_as_template<std::string>);
    return 0;
}
