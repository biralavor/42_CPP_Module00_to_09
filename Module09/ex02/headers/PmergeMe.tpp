/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 10:04:46 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/16 16:54:40 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

PmergeMe::PmergeMe(std::string input) : 
    _userInput(input), _vec(), _deq(), _vectorTime(0), _dequeTime(0) {
    this->inputValidation(input);
    this->inputParser(input);
}

PmergeMe::PmergeMe(const PmergeMe &rightSide) {
    this->_userInput = rightSide._userInput;
    this->_vec = rightSide._vec;
    this->_deq = rightSide._deq;
    this->_vectorTime = rightSide._vectorTime;
    this->_dequeTime = rightSide._dequeTime;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rightSide) {
    if (this != &rightSide) {
        this->_userInput = rightSide._userInput;
        this->_vec = rightSide._vec;
        this->_deq = rightSide._deq;
        this->_vectorTime = rightSide._vectorTime;
        this->_dequeTime = rightSide._dequeTime;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::inputValidation(const std::string &input) {
    if (input.empty())
        throw std::invalid_argument("Empty input is not allowed.");
    bool hasDigit = false;
    for (size_t idx = 0; idx < input.size(); idx++) {
        if (std::isspace(input[idx]))
            continue;
        if (std::isdigit(input[idx])) {
            hasDigit = true;
            continue;
        }
        throw std::invalid_argument("Non positive integer detected in input.");
    }
    if (!hasDigit)
        throw std::invalid_argument("No numbers found in input.");
    return true;
}

void PmergeMe::inputParser(const std::string &input) {
    std::istringstream iss(input);
    std::string token;
    while (std::getline(iss, token, ' ')) {
        if (token.empty())
            continue;
        int num = std::atoi(token.c_str());
        this->_vec.push_back(num);
        this->_deq.push_back(num);
    }
}

template <typename Container>
void PmergeMe::printSort(const std::string title, const Container &containerType) const {
    std::cout << title;
    if (containerType.size() <= 10) {
        for (typename Container::const_iterator smallIter = containerType.begin();
             smallIter != containerType.end(); smallIter++)
            std::cout << *smallIter << " ";
    } else {
        typename Container::const_iterator beginOfBigIter = containerType.begin();
        for (int idx = 0; idx < 5; idx++, beginOfBigIter++)
            std::cout << *beginOfBigIter << " ";
        std::cout << "[...] ";
        typename Container::const_iterator endOfBigIter = containerType.end();
        for (int idx = 0; idx < 5; idx++)
            --endOfBigIter;
        for (; endOfBigIter != containerType.end(); endOfBigIter++)
            std::cout << *endOfBigIter << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::displayVectorCronometer() const {
    std::cout << "Time to process a range of " << this->_vec.size()
            << " elements with std::vector => "
            << std::fixed << std::setprecision(FLOAT_PRECISION)
            << this->_vectorTime << " us" << std::endl;
}

void PmergeMe::displayDequeCronometer() const {
    std::cout << "Time to process a range of " << this->_deq.size()
            << " elements with std::deque  => "
            << std::fixed << std::setprecision(FLOAT_PRECISION)
            << this->_dequeTime << " us" << std::endl;
}

std::vector<size_t> PmergeMe::getJacobsthalOrder(size_t pendingCount) {
    std::vector<size_t> order;
    if (pendingCount <= 1)
        return order;
    std::vector<size_t> jac;
    jac.push_back(0);
    jac.push_back(1);
    jac.push_back(1);
    while (jac.back() < pendingCount) {
        size_t next = jac[jac.size() - 1] + 2 * jac[jac.size() - 2];
        jac.push_back(next);
    }
    for (size_t k = 3; k < jac.size(); k++) {
        size_t upper = jac[k];
        size_t lower = jac[k - 1] + 1;
        if (upper > pendingCount)
            upper = pendingCount;
        if (lower > pendingCount)
            break;
        for (size_t i = upper; i >= lower; i--)
            order.push_back(i - 1);
    }
    return order;
}

template <typename Container>
Container PmergeMe::startSorting(Container &containerType) {
    if (containerType.size() <= 1)
        return containerType;

    bool hasStraggler = (containerType.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler)
        straggler = containerType.back();

    Container winners;
    Container losers;
    std::vector<std::pair<int, int> > pairs;
    size_t pairEnd = containerType.size() - (containerType.size() % 2);
    for (size_t idx = 0; idx < pairEnd; idx += 2) {
        int a = containerType[idx];
        int b = containerType[idx + 1];
        if (a > b) {
            winners.push_back(a);
            losers.push_back(b);
            pairs.push_back(std::make_pair(a, b));
        } else {
            winners.push_back(b);
            losers.push_back(a);
            pairs.push_back(std::make_pair(b, a));
        }
    }

    Container sortedWinners = this->startSorting(winners);
    Container sortedLosers;
    this->reorderLosers(sortedWinners, pairs, sortedLosers);
    return this->buildMainChain(sortedWinners, sortedLosers,
                                hasStraggler, straggler);
}

template <typename Container>
void PmergeMe::reorderLosers(const Container &sortedWinners,
                             const std::vector<std::pair<int, int> > &pairs,
                             Container &sortedLosers) {
    std::vector<std::pair<int, int> > pairsCopy(pairs.begin(), pairs.end());
    for (size_t i = 0; i < sortedWinners.size(); i++) {
        for (size_t j = 0; j < pairsCopy.size(); j++) {
            if (pairsCopy[j].first == sortedWinners[i]) {
                sortedLosers.push_back(pairsCopy[j].second);
                pairsCopy.erase(pairsCopy.begin() + j);
                break;
            }
        }
    }
}

template <typename Container>
Container PmergeMe::buildMainChain(const Container &sortedWinners,
                                   const Container &sortedLosers,
                                   bool hasStraggler, int straggler) {
    Container mainChain;
    mainChain.push_back(sortedLosers[0]);
    for (size_t i = 0; i < sortedWinners.size(); i++)
        mainChain.push_back(sortedWinners[i]);

    std::vector<size_t> insertOrder = this->getJacobsthalOrder(sortedLosers.size());
    for (size_t i = 0; i < insertOrder.size(); i++) {
        size_t idx = insertOrder[i];
        if (idx >= sortedLosers.size())
            continue;
        int value = sortedLosers[idx];
        typename Container::iterator pos = std::lower_bound(
            mainChain.begin(), mainChain.end(), value);
        mainChain.insert(pos, value);
    }

    if (hasStraggler) {
        typename Container::iterator pos = std::lower_bound(
            mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }
    return mainChain;
}


void PmergeMe::sortManager() {
    this->printSort("Before : ", this->_vec);

    std::clock_t vectorStart = std::clock();
    this->_vec = this->startSorting(this->_vec);
    std::clock_t vectorEnd = std::clock();
    
    std::clock_t dequeStart = std::clock();
    this->_deq = this->startSorting(this->_deq);
    std::clock_t dequeEnd = std::clock();
    
    this->printSort("After  : ", this->_deq);
    
    this->_vectorTime = static_cast<double>(vectorEnd - vectorStart) / CLOCKS_PER_SEC;
    this->displayVectorCronometer();
    this->_dequeTime = static_cast<double>(dequeEnd - dequeStart) / CLOCKS_PER_SEC;
    this->displayDequeCronometer();
}

const std::vector<int>& PmergeMe::getVector() const { return this->_vec; }
const std::deque<int>& PmergeMe::getDeque() const { return this->_deq; }
