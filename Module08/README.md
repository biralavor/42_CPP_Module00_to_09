# Module 08 - STL Containers, Iterators, Algorithms

Templated containers, iterators, and STL algorithms.

## Overview

This module introduces the Standard Template Library (STL). The goal here is to use containers like `vector`, `list`, and `deque`, along with algorithms from `<algorithm>`.

## Exercises

### Exercise 00: Easy find
Function template to find an integer in any STL container.

```cpp
template<typename T>
typename T::iterator easyfind(T& container, int value);
// Throws exception if not found
```

### Exercise 01: Span
Class to store N integers with span calculations.

```cpp
class Span {
    Span(unsigned int n);
    void addNumber(int n);               // Single add
    void addRange(It begin, It end);     // Range add
    unsigned int shortestSpan();         // Min distance between any two
    unsigned int longestSpan();          // Max - Min
};
```

**Example output:**
```
shortestSpan: 2   (between 9 and 11)
longestSpan: 14   (17 - 3)
```

### Exercise 02: MutantStack
Make `std::stack` iterable by exposing underlying container's iterators.

```cpp
template<typename T>
class MutantStack : public std::stack<T> {
    typedef typename std::stack<T>::container_type::iterator iterator;
    iterator begin();
    iterator end();
};
```

## Key STL Concepts

| Component | Purpose |
|-----------|---------|
| Containers | Store collections (vector, list, deque, stack, map) |
| Iterators | Traverse containers uniformly |
| Algorithms | Operations on ranges (find, sort, transform) |

## Building and Testing

```bash
cd Module08
make              # Build + run tests
make test         # Run all tests
make test-ex00    # Run ex00 tests only
make test-ex01    # Run ex01 tests only
make test-ex02    # Run ex02 tests only
make help         # Show all available targets
```

## Test Coverage

| Exercise | Tests | Description |
|----------|-------|-------------|
| ex00 | 22 | easyfind with vector/list/deque, not found, edge cases |
| ex01 | 28 | Span add, shortest/longest, range add, 10K+ numbers |
| ex02 | 20 | MutantStack iteration, copy, types, std::stack compat |
