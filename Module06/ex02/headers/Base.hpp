/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:27:53 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/20 19:13:02 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Base {
    public:
        virtual ~Base();
};

Base *generate(void);
void identify(Base *p);
void identify(Base &p);
