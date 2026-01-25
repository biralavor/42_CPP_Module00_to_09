# Module 06 - C++ Casts

C++ type casting: static_cast, reinterpret_cast, dynamic_cast.

## Overview

This module introduces C++ casting operators, replacing C-style casts with safer, more explicit alternatives. The goal here is to implement type conversion, serialization, and runtime type identification.

## Exercises

### Exercise 00: ScalarConverter

Convert string literals to char, int, float, and double.

**Key concepts:**
- Type detection from string
- `static_cast` for safe conversions
- Handling special values (inf, nan)
- Non-instantiable class (private constructor)

**Usage:**
```bash
./convert 42       # Integer
./convert 4.2f     # Float
./convert 4.2      # Double
./convert 'c'      # Char
./convert nan      # Special value
```

**Output format:**
```
char: '*'
int: 42
float: 42.0f
double: 42.0
```

### Exercise 01: Serializer

Serialize pointers to integers and back.

**Key concepts:**
- `reinterpret_cast` for pointer ↔ integer
- `uintptr_t` type (pointer-sized integer)
- Data structure design

**Implementation:**
```cpp
class Serializer {
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};
```

### Exercise 02: Identify Real Type

Identify object types at runtime without typeinfo.

**Key concepts:**
- `dynamic_cast` for safe downcasting
- Polymorphism and RTTI
- Exception handling (std::bad_cast)

**Functions:**
```cpp
Base* generate(void);      // Randomly create A, B, or C
void identify(Base* p);    // Identify using pointer
void identify(Base& p);    // Identify using reference (no pointers!)
```

## C++ Casts

| Cast | Purpose | Safety |
|------|---------|--------|
| `static_cast` | Compile-time type conversion | Safe |
| `dynamic_cast` | Runtime polymorphic casting | Safe (returns NULL/throws) |
| `reinterpret_cast` | Bit-level reinterpretation | Unsafe |
| `const_cast` | Add/remove const | Unsafe |

```cpp
// C-style cast (avoid)
int i = (int)3.14;

// C++ casts (prefer)
int i = static_cast<int>(3.14);         // Explicit conversion
Data* d = reinterpret_cast<Data*>(raw); // Pointer from integer
A* a = dynamic_cast<A*>(basePtr);       // Safe downcast
```

## Building and Testing

```bash
cd Module06
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
| ex00 | 43 | Char/int/float/double conversion, special values |
| ex01 | 30 | Serialize/deserialize, pointer preservation |
| ex02 | 35 | Type identification with pointer and reference |

## Key Takeaways

1. **Use explicit C++ casts** instead of C-style casts
2. **static_cast** for conversions the compiler can verify
3. **dynamic_cast** for safe downcasting with virtual classes
4. **reinterpret_cast** only when absolutely necessary
