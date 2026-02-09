/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Easyfind.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 11:11:01 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/01 11:56:22 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T>
typename T::iterator easyfind(T &container, int value) {
    typename T::iterator iter = std::find(container.begin(), container.end(), value);
    if (iter == container.end()) {
        throw std::runtime_error("Value not found in container");
    }
    return iter;
}

template <typename T>
typename T::const_iterator easyfind(const T &container, int value) {
    typename T::const_iterator iter = std::find(container.begin(), container.end(), value);
    if (iter == container.end()) {
        throw std::runtime_error("Value not found in container");
    }
    return iter;
}
/* ************************************************************************** */