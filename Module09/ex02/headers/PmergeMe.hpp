/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 10:02:36 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/16 16:46:44 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <utility>

#define FLOAT_PRECISION 7

class PmergeMe {
    private:
        std::string _userInput;
        std::vector<int> _vec;
        std::deque<int> _deq;
        double _vectorTime;
        double _dequeTime;
        
        PmergeMe(const PmergeMe &rightSide);
        PmergeMe &operator=(const PmergeMe &rightSide);
    
        bool inputValidation(const std::string &input);
        void inputParser(const std::string &input);
        
        template <typename Container>
        Container startSorting(Container &containerType);

        template <typename Container>
        void reorderLosers(const Container &sortedWinners,
                           const std::vector<std::pair<int, int> > &pairs,
                           Container &sortedLosers);

        template <typename Container>
        Container buildMainChain(const Container &sortedWinners,
                                 const Container &sortedLosers,
                                 bool hasStraggler, int straggler);

        template <typename Container>
        void printSort(const std::string title, const Container &containerType) const;

        static std::vector<size_t> getJacobsthalOrder(size_t pendingCount);

        void displayVectorCronometer() const;
        void displayDequeCronometer() const;
    
        public:
        PmergeMe(std::string input);
        ~PmergeMe();
        
        void sortManager();
        const std::vector<int>& getVector() const;
        const std::deque<int>& getDeque() const;
};

#include "PmergeMe.tpp"
