# Module 02 - Ad-hoc Polymorphism, Operator Overloading & Orthodox Canonical Form

Fixed-point numbers, operator overloading, and the Orthodox Canonical Class Form.

## Overview

This module introduces operator overloading and the Orthodox Canonical Form (OCF), a standard way to define classes in C++98. You'll implement a fixed-point number class that progressively gains more features through operator overloading.

## Exercises

### Exercise 00: My First Class in Orthodox Canonical Form

Create a basic `Fixed` class following the Orthodox Canonical Form.

**Key concepts:**
- Orthodox Canonical Form (Rule of Three in C++98)
- Fixed-point number representation
- `getRawBits()` and `setRawBits()` member functions

**Orthodox Canonical Form requires:**
```cpp
class Fixed {
public:
    Fixed(void);                           // Default constructor
    Fixed(Fixed const &src);               // Copy constructor
    Fixed &operator=(Fixed const &rhs);    // Copy assignment operator
    ~Fixed(void);                          // Destructor
};
```

**Fixed-point representation:**
- Uses 8 fractional bits (stored in static const)
- Integer part stored in remaining bits
- Value = raw_bits / 256 (2^8)

### Exercise 01: Towards a More Useful Fixed-Point Number Class

Add constructors for int and float, plus conversion functions.

**Key concepts:**
- Constructor overloading
- Type conversion (int ↔ float ↔ fixed-point)
- Stream insertion operator overloading (`operator<<`)

**New members:**
```cpp
Fixed(int const n);           // Int constructor
Fixed(float const n);         // Float constructor
float toFloat(void) const;    // Convert to float
int toInt(void) const;        // Convert to int
```

**Conversion formulas:**
```cpp
// Int to fixed-point: multiply by 256 (1 << 8)
_fixedPointValue = n << _fractionalBits;

// Float to fixed-point: multiply by 256 and round
_fixedPointValue = roundf(n * (1 << _fractionalBits));

// Fixed-point to int: divide by 256
return _fixedPointValue >> _fractionalBits;

// Fixed-point to float: divide by 256.0
return (float)_fixedPointValue / (1 << _fractionalBits);
```

**Stream operator (global function):**
```cpp
std::ostream &operator<<(std::ostream &out, Fixed const &fixed);
```

### Exercise 02: Now We're Talking

Add comparison, arithmetic, and increment/decrement operators.

**Key concepts:**
- Operator overloading (all types)
- Pre-increment vs Post-increment
- Static member functions
- Function overloading for const/non-const

**Comparison operators (return bool):**
```cpp
bool operator>(Fixed const &rhs) const;
bool operator<(Fixed const &rhs) const;
bool operator>=(Fixed const &rhs) const;
bool operator<=(Fixed const &rhs) const;
bool operator==(Fixed const &rhs) const;
bool operator!=(Fixed const &rhs) const;
```

**Arithmetic operators (return new Fixed):**
```cpp
Fixed operator+(Fixed const &rhs) const;
Fixed operator-(Fixed const &rhs) const;
Fixed operator*(Fixed const &rhs) const;
Fixed operator/(Fixed const &rhs) const;
```

**Increment/Decrement operators:**
```cpp
Fixed &operator++(void);    // Pre-increment: ++a
Fixed operator++(int);      // Post-increment: a++
Fixed &operator--(void);    // Pre-decrement: --a
Fixed operator--(int);      // Post-decrement: a--
```

**Pre vs Post increment:**
| Type | Returns | Behavior |
|------|---------|----------|
| Pre (`++a`) | Reference to modified object | Increment first, then return |
| Post (`a++`) | Copy of original value | Return copy, then increment |

**Static min/max functions (overloaded for const and non-const):**
```cpp
static Fixed &min(Fixed &a, Fixed &b);
static Fixed const &min(Fixed const &a, Fixed const &b);
static Fixed &max(Fixed &a, Fixed &b);
static Fixed const &max(Fixed const &a, Fixed const &b);
```

### Exercise 03: BSP (Bonus)

Implement a function to check if a point is inside a triangle using the Binary Space Partitioning algorithm.

**Key concepts:**
- Point class (using Fixed for coordinates)
- Geometric calculations with fixed-point
- Triangle area calculation

## C++ Concepts Introduced

| Concept | Description |
|---------|-------------|
| Orthodox Canonical Form | Default constructor, copy constructor, copy assignment, destructor |
| Operator Overloading | Custom behavior for operators (`+`, `-`, `<<`, etc.) |
| Fixed-point Numbers | Represent decimals using integer with implicit fractional bits |
| Static Member Functions | Class-level functions, called as `ClassName::function()` |
| Const Member Functions | Functions that don't modify object state |
| Function Overloading | Multiple functions with same name but different parameters |

## Fixed-Point Number Representation

With 8 fractional bits:
- Smallest increment: 1/256 ≈ 0.00390625
- Range: -(2^23) to (2^23 - 1) for 32-bit int
- Resolution: ~0.004 (good enough for many applications)

```
32-bit integer layout:
[Sign][Integer part (23 bits)][Fractional part (8 bits)]

Example: 42.5 in fixed-point
42.5 * 256 = 10880
Binary: 00000000 00000000 00101010 10000000
        └─────Integer─────┘└─Fraction─┘
```

## Building and Testing

### Build Everything
```bash
cd Module02
make              # Build exercises + run tests
```

### Run Tests
```bash
make test                                    # Run all tests
cd build && ctest --output-on-failure        # Verbose output
cd build && ./TestModule02Ex00               # Run specific test
cd build && ./TestModule02Ex01               # Run ex01 tests
cd build && ./TestModule02Ex02               # Run ex02 tests
```

### Build Individual Exercise
```bash
cd ex00 && make    # Build ex00
cd ex01 && make    # Build ex01
cd ex02 && make    # Build ex02
```

### Clean
```bash
make clean        # Remove object files
make fclean       # Remove objects + binaries
```

## Project Structure

```
Module02/
├── ex00/                    # Orthodox Canonical Form
│   ├── headers/Fixed.hpp
│   └── src/Fixed.cpp, main.cpp
├── ex01/                    # With conversions
│   ├── headers/Fixed.hpp
│   └── src/Fixed.cpp, main.cpp
├── ex02/                    # With operators
│   ├── headers/Fixed.hpp
│   └── src/Fixed.cpp, main.cpp
├── ex03/                    # BSP (bonus)
│   ├── headers/Fixed.hpp, Point.hpp
│   └── src/Fixed.cpp, Point.cpp, bsp.cpp
├── tests/
│   ├── TestModule02Ex00.cpp
│   ├── TestModule02Ex01.cpp
│   ├── TestModule02Ex02.cpp
│   └── CMakeLists.txt
├── CMakeLists.txt
└── Makefile
```

## Test Coverage

| Exercise | Tests | Description |
|----------|-------|-------------|
| ex00 | 16 | OCF compliance, getRawBits, setRawBits, copy semantics |
| ex01 | 18 | Int/float constructors, toInt, toFloat, operator<< |
| ex02 | 35 | All operators, min/max, pre/post increment |

## Key Takeaways

1. **Orthodox Canonical Form**: Always implement all four special members when your class manages resources.

2. **Operator Overloading Rules**:
   - Comparison operators return `bool`
   - Arithmetic operators return new object (by value)
   - Assignment operator returns reference to `*this`
   - Pre-increment returns reference, post-increment returns copy

3. **Fixed-Point Arithmetic**: Useful when floating-point isn't available or when you need deterministic behavior (same results on all platforms).

4. **const correctness**: Mark methods that don't modify state as `const`. Overload for const and non-const when returning references.

## Subject Expected Output

**Ex00:**
```
Default constructor called
Copy constructor called
Copy assignment operator called
getRawBits member function called
Default constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
```

**Ex01:**
```
Default constructor called
Int constructor called
Float constructor called
Copy constructor called
Copy assignment operator called
Float constructor called
Copy assignment operator called
Destructor called
a is 1234.43
b is 10
c is 42.4219
d is 10
a is 1234 as integer
Destructor called
Destructor called
Destructor called
Destructor called
```

**Ex02:**
```
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
```
