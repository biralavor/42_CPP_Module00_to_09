# Module 07 - C++ Templates

Generic programming with function and class templates.

## Overview

This module introduces templates, enabling you to write generic, type-independent code. You'll implement function templates and a class template, learning how the compiler generates type-specific code at compile time.

## Exercises

### Exercise 00: Start with a few functions

Implement three function templates: `swap`, `min`, and `max`.

**Key concepts:**
- Function template syntax
- Type deduction
- Reference parameters
- Template instantiation

**Implementation:**
```cpp
template<typename T>
void swap(T& a, T& b);

template<typename T>
T const& min(T const& a, T const& b);  // Returns b if equal

template<typename T>
T const& max(T const& a, T const& b);  // Returns b if equal
```

**Usage:**
```cpp
int a = 2, b = 3;
::swap(a, b);           // a=3, b=2
std::cout << ::min(a, b);  // 2
std::cout << ::max(a, b);  // 3

std::string c = "abc", d = "xyz";
::swap(c, d);           // c="xyz", d="abc"
```

### Exercise 01: Iter

Create a function template that applies a function to each array element.

**Key concepts:**
- Function pointers as template parameters
- Array iteration
- Generic algorithms

**Implementation:**
```cpp
template<typename T>
void iter(T* array, size_t length, void (*func)(T&));

// Also works with const:
template<typename T>
void iter(T* array, size_t length, void (*func)(T const&));
```

**Usage:**
```cpp
void print(int const& n) { std::cout << n << " "; }
void doubleIt(int& n) { n *= 2; }

int arr[] = {1, 2, 3, 4, 5};
iter(arr, 5, print);      // Output: 1 2 3 4 5
iter(arr, 5, doubleIt);   // arr is now {2, 4, 6, 8, 10}
```

### Exercise 02: Array

Implement a class template for a dynamic array container.

**Key concepts:**
- Class template syntax
- Orthodox Canonical Form with templates
- Operator overloading
- Exception handling
- `new[]` with default initialization

**Implementation:**
```cpp
template<typename T>
class Array {
public:
    Array();                        // Empty array
    Array(unsigned int n);          // Array of n elements (default-initialized)
    Array(Array const& src);        // Deep copy
    ~Array();
    Array& operator=(Array const& rhs);

    T& operator[](unsigned int index);            // Throws on out-of-bounds
    T const& operator[](unsigned int index) const;
    unsigned int size() const;

private:
    T* _data;
    unsigned int _size;
};
```

**Usage:**
```cpp
Array<int> numbers(5);     // [0, 0, 0, 0, 0]
numbers[0] = 42;
numbers[10] = 1;           // Throws std::exception

Array<std::string> words(3);
words[0] = "hello";
```

## Template Concepts

### Function Templates
```cpp
// Template declaration
template<typename T>
T add(T a, T b) {
    return a + b;
}

// Usage - compiler deduces T
int sum = add(1, 2);           // T = int
double result = add(1.5, 2.5); // T = double
```

### Class Templates
```cpp
template<typename T>
class Container {
    T _data;
public:
    Container(T val) : _data(val) {}
    T getData() const { return _data; }
};

Container<int> intBox(42);
Container<std::string> strBox("hello");
```

### Template Instantiation
- **Implicit**: Compiler deduces type from arguments
- **Explicit**: Programmer specifies type `func<int>(args)`

### Template vs Macro
| Feature | Template | Macro |
|---------|----------|-------|
| Type safety | Yes | No |
| Debugging | Yes | Difficult |
| Scope | Respects | Textual replacement |
| Overloading | Yes | No |

## Building and Testing

```bash
cd Module07
make              # Build exercises + run tests
make test         # Run all tests
make test-ex00    # Run ex00 tests only
make test-ex01    # Run ex01 tests only
make test-ex02    # Run ex02 tests only
make help         # Show all available targets
```

## Test Coverage

| Exercise | Tests | Description |
|----------|-------|-------------|
| ex00 | 28 | swap/min/max with int, double, string, char; reference returns |
| ex01 | 18 | iter with various types, edge cases, template functions |
| ex02 | 40 | Array constructors, copy, assignment, exceptions, types |

## Common Pitfalls

1. **Forgetting `typename`**: Use `typename` for dependent types
   ```cpp
   template<typename T>
   typename T::value_type get(T& container);  // Need typename
   ```

2. **Template in .cpp file**: Template definitions must be in headers (or .tpp included in header)

3. **Comparison operators**: Ensure types used with `min`/`max` have `operator<`

4. **Exception safety**: Array assignment should be exception-safe

## Key Takeaways

1. **Templates enable generic programming** - write once, use with any type
2. **Type deduction** reduces boilerplate but can be explicitly overridden
3. **Class templates** follow the same Orthodox Canonical Form
4. **Compilation** generates separate code for each type instantiation
5. **Header-only** templates because compiler needs full definition at instantiation

## Files Structure

```
Module07/
├── ex00/                    # Function Templates
│   ├── whatever.hpp         # swap, min, max templates
│   ├── main.cpp
│   └── Makefile
├── ex01/                    # iter Template
│   ├── iter.hpp             # iter function template
│   ├── main.cpp
│   └── Makefile
├── ex02/                    # Array Class Template
│   ├── Array.hpp            # Array template declaration
│   ├── Array.tpp            # Array template implementation (optional)
│   ├── main.cpp
│   └── Makefile
├── tests/
│   ├── TestModule07Ex00.cpp
│   ├── TestModule07Ex01.cpp
│   ├── TestModule07Ex02.cpp
│   └── CMakeLists.txt
├── CMakeLists.txt
└── Makefile
```
