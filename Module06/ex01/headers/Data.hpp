/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:14:10 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/19 21:35:09 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
// #include <stdint.h>  // for uintptr_t

struct Data {
    int id;
    std::string name;
    float value;
    bool active;
    
    Data();
    Data(int i, std::string n, float v, bool a);
    ~Data();
    Data(const Data &rightSide);
    Data &operator=(const Data &rightSide);

    bool operator==(const Data& other) const;
};