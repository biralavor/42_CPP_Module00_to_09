/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 21:14:55 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/03 22:02:09 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include "Span.hpp"

int main()
{
	std::cout << "----- SUBJECT TESTS -----" << std::endl;
	std::cout << "Creating a Span of size 5 and adding numbers 6, 3, 17, 9, 11" << std::endl;
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	std::cout << "///// END SUBJECT TESTS /////" << std::endl;
	
	std::cout << "\n----- SPAN TEST WITH RANGE -----" << std::endl;
	std::cout << "Creating a Span of size 10000 and adding a range of numbers from a list" << std::endl;
	Span sp2 = Span(10000);
	std::list<int> numbers;
	for (int i = 0; i < 10000; ++i) {
		numbers.push_back(i * 2);
	}
	sp2.addRange(numbers.begin(), numbers.end());
	std::cout << "Shortest Span: ";
	std::cout << sp2.shortestSpan() << std::endl;
	std::cout << "Longest Span: ";
	std::cout << sp2.longestSpan() << std::endl;
	std::cout << "////// END SPAN TEST WITH RANGE /////" << std::endl;

	std::cout << "\n----- SPAN TEST WITH EXCEPTIONS -----" << std::endl;
	std::cout << "Creating a Span of size 3 and trying to add 4 numbers" << std::endl;
	Span sp3 = Span(3);
	try {
		sp3.addNumber(1);
		sp3.addNumber(2);
		sp3.addNumber(3);
		sp3.addNumber(4); // This should throw an exception
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "///// END SPAN TEST WITH EXCEPTIONS /////" << std::endl;
	
	std::cout << "\n----- SPAN TEST WITH INSUFFICIENT NUMBERS -----" << std::endl;
	std::cout << "Creating a Span of size 2 and adding only 1 number" << std::endl;
	Span sp4 = Span(2);
	try {
		sp4.addNumber(10);
		std::cout << "Shortest Span: " << sp4.shortestSpan() << std::endl; // This should throw an exception
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "///// END SPAN TEST WITH INSUFFICIENT NUMBERS /////" << std::endl;

	std::cout << "\n----- SPAN TEST WITH LARGE NUMBERS -----" << std::endl;
	std::cout << "Creating a Span of size 3 and adding large numbers" << std::endl;
	Span sp5 = Span(3);
	sp5.addNumber(2147483647);
	sp5.addNumber(-2147483648);
	sp5.addNumber(0);
	std::cout << "Shortest Span: " << sp5.shortestSpan() << std::endl;
	std::cout << "Longest Span: " << sp5.longestSpan() << std::endl;
	std::cout << "///// END SPAN TEST WITH LARGE NUMBERS /////" << std::endl;
	return 0;
}
