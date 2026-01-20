# Module 09 - STL Applications

Real-world applications using STL containers and algorithms.

## Overview

This module applies STL knowledge to practical problems. Each exercise requires different containers (once used, can't be reused in subsequent exercises).

## Exercises

### Exercise 00: Bitcoin Exchange
Calculate Bitcoin value on specific dates using CSV price database.

**Container**: `std::map` (date → price lookup with lower_bound)

**Usage:**
```bash
./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
```

**Rules:**
- Input format: `date | value`
- Value: 0-1000 (float or int)
- Use closest lower date if exact date not in DB

### Exercise 01: RPN (Reverse Polish Notation)
Stack-based calculator for postfix expressions.

**Container**: `std::stack` (natural fit for RPN evaluation)

**Usage:**
```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"  # Output: 42
./RPN "7 7 * 7 -"                   # Output: 42
./RPN "(1 + 1)"                     # Error (no brackets)
```

**Operators:** `+ - * /`
**Numbers:** Single digits (0-9) only in input

### Exercise 02: PmergeMe
Ford-Johnson merge-insert sort with performance comparison.

**Containers**: Two different (e.g., `std::vector` and `std::deque`)

**Usage:**
```bash
./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process 5 elements with std::vector : 0.00031 us
Time to process 5 elements with std::deque  : 0.00014 us
```

**Requirements:**
- Handle 3000+ integers
- Display timing for both containers
- Implement Ford-Johnson algorithm

## Container Usage Rule

| Exercise | Container(s) | Cannot use after |
|----------|-------------|------------------|
| ex00 | map | ex01, ex02 |
| ex01 | stack | ex02 |
| ex02 | vector + deque | - |

## Building and Testing

```bash
cd Module09
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
| ex00 | 22 | Date/value parsing, DB lookup, error handling |
| ex01 | 25 | Operations, complex expressions, errors |
| ex02 | 18 | Sorting correctness, large inputs, timing |

## Key Algorithms

### RPN Evaluation
```
Input: "3 4 + 2 *"
Stack: [] → [3] → [3,4] → [7] → [7,2] → [14]
```

### Ford-Johnson (Merge-Insert)
1. Pair elements, sort pairs by larger element
2. Recursively sort larger elements
3. Insert smaller elements using binary search
4. Optimal comparison count for small n
