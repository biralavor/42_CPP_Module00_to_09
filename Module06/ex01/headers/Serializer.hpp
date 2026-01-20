/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:13:47 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/19 20:25:24 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <iostream>
#include <stdint.h>  // for uintptr_t
#include "Data.hpp"


class Serializer {
    
    Serializer();
    ~Serializer();
    Serializer(const Serializer &rightSide);
    Serializer &operator=(const Serializer &rightSide);
    
    
public:
    static uintptr_t serialize(Data *ptr);
    static Data *deserialize(uintptr_t raw);

};