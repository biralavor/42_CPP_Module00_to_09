/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 11:44:25 by umeneses          #+#    #+#             */
/*   Updated: 2026/02/09 19:49:37 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <list>
#include <string>

/**
 * MutantStack Demo - Making std::stack Iterable
 *
 * Problem: std::stack is a container adapter that restricts access to LIFO
 * operations only (push, pop, top). It deliberately hides the underlying
 * container's iterators to enforce stack semantics.
 *
 * Solution: MutantStack inherits from std::stack and exposes the protected
 * member 'c' (the underlying container) through iterator methods, allowing
 * traversal while maintaining all standard stack operations.
 */

static void printSeparator(const std::string& title) {
    std::cout << "\n========== " << title << " ==========" << std::endl;
}

static void printResult(bool passed, const std::string& test) {
    std::cout << (passed ? "[✅  OK  ✅] " : "[❌  KO  ❌] ") << test << std::endl;
}

/**
 * Test 1: Subject Example
 */
static void testSubjectExample() {
    printSeparator("1. SUBJECT EXAMPLE");
    std::cout << "Reproducing the exact subject PDF example:\n" << std::endl;

    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);

    std::cout << "After push(5), push(17):" << std::endl;
    std::cout << "  top() = " << mstack.top() << " (expected: 17)" << std::endl;
    bool expected1 = (mstack.top() == 17);
    printResult(expected1, "top() returns last pushed element");

    mstack.pop();
    std::cout << "\nAfter pop():" << std::endl;
    std::cout << "  size() = " << mstack.size() << " (expected: 1)" << std::endl;
    bool expected2 = (mstack.size() == 1);
    printResult(expected2, "size() decremented after pop");

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    std::cout << "\nAfter push(3), push(5), push(737), push(0):" << std::endl;
    std::cout << "  Iterating with begin()/end(): ";

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator itend = mstack.end();

    // Subject shows ++it then --it to demonstrate bidirectional iteration
    ++it;
    --it;

    while (it != itend) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << "(expected: 5 3 5 737 0)" << std::endl;

    std::stack<int> std_stack(mstack);
    bool expected3 = (std_stack.size() == 5);
    printResult(expected3, "MutantStack convertible to std::stack");
}

/**
 * Test 2: Comparison with std::list
 */
static void testListComparison() {
    printSeparator("2. LIST COMPARISON");
    std::cout << "Subject requirement: MutantStack and std::list must produce\n"
              << "identical iteration output when used the same way.\n" << std::endl;

    MutantStack<int> mstack;
    std::list<int> lst;

    mstack.push(5);    lst.push_back(5);
    mstack.push(17);   lst.push_back(17);
    mstack.pop();      lst.pop_back();
    mstack.push(3);    lst.push_back(3);
    mstack.push(5);    lst.push_back(5);
    mstack.push(737);  lst.push_back(737);
    mstack.push(0);    lst.push_back(0);

    std::cout << "MutantStack: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "std::list:   ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    bool match = true;
    MutantStack<int>::iterator mutant_it = mstack.begin();
    std::list<int>::iterator list_it = lst.begin();
    while (mutant_it != mstack.end() && list_it != lst.end()) {
        if (*mutant_it != *list_it)
            match = false;
        ++mutant_it;
        ++list_it;
    }
    if (mutant_it != mstack.end() || list_it != lst.end())
        match = false;

    printResult(match, "Iteration order matches std::list");
}

/**
 * Test 3: Orthodox Canonical Form
 */
static void testOrthodoxCanonicalForm() {
    printSeparator("3. ORTHODOX CANONICAL FORM");
    std::cout << "Testing deep copy semantics:\n" << std::endl;

    MutantStack<int> original;
    original.push(100);
    original.push(200);
    original.push(300);

    MutantStack<int> copied(original);
    std::cout << "After copy construction:" << std::endl;
    std::cout << "  Original size: " << original.size() << std::endl;
    std::cout << "  Copy size:     " << copied.size() << std::endl;
    bool expected1 = (original.size() == copied.size());
    printResult(expected1, "Copy has same size");

    // Modify copy - original should be unaffected
    copied.push(400);
    copied.pop();
    copied.pop();

    std::cout << "\nAfter modifying copy (push 400, pop twice):" << std::endl;
    std::cout << "  Original size: " << original.size() << " (expected: 3)" << std::endl;
    std::cout << "  Copy size:     " << copied.size() << " (expected: 2)" << std::endl;
    bool expected2 = (original.size() == 3);
    printResult(expected2, "Original unchanged after modifying copy");

    // Assignment operator
    MutantStack<int> assigned;
    assigned.push(999);
    assigned = original;
    std::cout << "\nAfter assignment (assigned = original):" << std::endl;
    std::cout << "  Assigned top: " << assigned.top() << " (expected: 300)" << std::endl;
    bool expected3 = (assigned.top() == 300);
    printResult(expected3, "Assignment copies content");
}

/**
 * Test 4: Iterator modification with non-const iterators
 */
static void testIteratorModification() {
    printSeparator("4. ITERATOR MODIFICATION");
    std::cout << "Iterators should allow modifying stack contents:\n" << std::endl;

    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);

    std::cout << "Before: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    // Double each element through iterator
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        *it *= 2;

    std::cout << "After doubling each element: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << " ";
    std::cout << "(expected: 2 4 6)" << std::endl;

    bool correct = true;
    MutantStack<int>::iterator it = mstack.begin();
    if (*it++ != 2)
        correct = false;
    if (*it++ != 4)
        correct = false;
    if (*it != 6)
        correct = false;
    printResult(correct, "Iterator modification works");
}

/**
 * Test 5: Const iterator
 * Demonstrates const-correctness with const_iterator.
 */
static void testConstIterator() {
    printSeparator("5. CONST ITERATOR");
    std::cout << "Testing const_iterator on const reference:\n" << std::endl;

    MutantStack<int> mstack;
    mstack.push(10);
    mstack.push(20);
    mstack.push(30);

    const MutantStack<int>& constRef = mstack;

    std::cout << "Iterating const stack: ";
    int sum = 0;
    for (MutantStack<int>::const_iterator it = constRef.begin();
         it != constRef.end(); ++it) {
        std::cout << *it << " ";
        sum += *it;
    }
    std::cout << "(sum = " << sum << ", expected: 60)" << std::endl;
    bool expected = (sum == 60);
    printResult(expected, "const_iterator reads correctly");
}

/**
 * Test 6: Template with different types
 * MutantStack should work with any type, not just int.
 */
static void testDifferentTypes() {
    printSeparator("6. TEMPLATE TYPES");
    std::cout << "MutantStack works with any type:\n" << std::endl;

    MutantStack<std::string> strStack;
    strStack.push("Hello");
    strStack.push("World");
    strStack.push("!");

    std::cout << "String stack: ";
    for (MutantStack<std::string>::iterator it = strStack.begin();
         it != strStack.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    printResult(strStack.top() == "!", "String stack works");

    MutantStack<double> dblStack;
    dblStack.push(3.14);
    dblStack.push(2.71);
    dblStack.push(1.41);

    std::cout << "Double stack: ";
    double dsum = 0;
    for (MutantStack<double>::iterator it = dblStack.begin();
         it != dblStack.end(); ++it) {
        std::cout << *it << " ";
        dsum += *it;
    }
    std::cout << "(sum = " << dsum << ")" << std::endl;
    bool expected = (dsum > 7.2 && dsum < 7.3); // 3.14 + 2.71 + 1.41 = 7.26
    printResult(expected, "Double stack works");
}

/**
 * Test 7: Edge cases
 * Empty stack, single element, and extreme values.
 */
static void testEdgeCases() {
    printSeparator("7. EDGE CASES");

    // Empty stack
    std::cout << "Empty stack:" << std::endl;
    MutantStack<int> empty;
    bool emptyOk = (empty.begin() == empty.end()) && empty.empty();
    std::cout << "  begin() == end(): " << (empty.begin() == empty.end()) << std::endl;
    std::cout << "  empty(): " << empty.empty() << std::endl;
    printResult(emptyOk, "Empty stack has begin() == end()");

    // Single element
    std::cout << "\nSingle element stack:" << std::endl;
    MutantStack<int> single;
    single.push(42);
    MutantStack<int>::iterator sit = single.begin();
    bool singleOk = (*sit == 42);
    ++sit;
    singleOk = singleOk && (sit == single.end());
    std::cout << "  *begin() = " << *single.begin() << std::endl;
    printResult(singleOk, "Single element iterates once");

    // Extreme values
    std::cout << "\nExtreme values (INT_MAX, INT_MIN):" << std::endl;
    MutantStack<int> extreme;
    extreme.push(-2147483648);
    extreme.push(2147483647);
    std::cout << "  Contains: ";
    for (MutantStack<int>::iterator it = extreme.begin(); it != extreme.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    printResult(extreme.top() == 2147483647, "Handles extreme int values");
}

/**
 * Test 8: Reverse iterators
 * Demonstrates reverse iteration capability.
 */
static void testReverseIterators() {
    printSeparator("8. REVERSE ITERATORS");
    std::cout << "Testing reverse iterators:\n" << std::endl;
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);
    mstack.push(4);
    mstack.push(5);
    
    std::cout << "Mstack original contents: ";
    int *iterator_array[5];
    int *reversed_array[5];
    for (MutantStack<int>::iterator it = mstack.begin();
         it != mstack.end(); ++it) {
            iterator_array[it - mstack.begin()] = &(*it);
            std::cout << *it << " ";
         }
    std::cout << std::endl;

    std::cout << "Reverse iteration: ";
    for (MutantStack<int>::reverse_iterator rit = mstack.rbegin();
         rit != mstack.rend(); ++rit) {
            reversed_array[rit - mstack.rbegin()] = &(*rit);
            std::cout << *rit << " ";
         }
    std::cout << "(expected: 5 4 3 2 1)" << std::endl;
    int size = mstack.size();
    for (int i = 0; i < size; i++) {
        if (*iterator_array[i] != *reversed_array[size - 1 - i]) {
            printResult(false, "Reverse iteration order is correct");
            return;
        }
    }
    printResult(true, "Reverse iteration");
}

int main() {
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════════════════════════╗\n";
    std::cout << "║           MutantStack - Iterable Stack Container          ║\n";
    std::cout << "║     Making std::stack iterable by exposing 'c' member     ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════════╝\n";

    testSubjectExample();
    testListComparison();
    testOrthodoxCanonicalForm();
    testIteratorModification();
    testConstIterator();
    testDifferentTypes();
    testEdgeCases();
    testReverseIterators();

    printSeparator("SUMMARY");
    std::cout << "All mandatory tests completed.\n"
              << std::endl;

    return 0;
}
