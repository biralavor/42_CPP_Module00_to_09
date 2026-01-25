/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:29:31 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/21 21:33:32 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Whatever {
    public:
        Whatever();
        ~Whatever();
        Whatever(const Whatever &rightSide);
        Whatever &operator=(const Whatever &rightSide);
};

template <typename T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
T &min(T &a, T &b) {
    return a < b ? a : b;
}

template <typename T>
T &max (T &a, T &b) {
    return a > b ? a : b;
}
