/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:24:30 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/18 17:03:22 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
    std::cout << "Input: -4.2f" << std::endl;
    ScalarConverter::convert("-4.2f");
    std::cout << "----------------" << std::endl;
    
    std::cout << "SUBJECT EXAMPLES" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Input: 0" << std::endl;
    ScalarConverter::convert("0");
    std::cout << "----------------" << std::endl;
    std::cout << "Input: nan" << std::endl;
    ScalarConverter::convert("nan");
    std::cout << "----------------" << std::endl;
    std::cout << "Input: 42.0f" << std::endl;
    ScalarConverter::convert("42.0f");
    std::cout << "----------------" << std::endl;
    std::cout << "### end of SUBJECT EXAMPLES ###" << std::endl;
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <literal>" << std::endl;
        return 1;
    }
    ScalarConverter::convert(argv[1]);
    return 0;
}
