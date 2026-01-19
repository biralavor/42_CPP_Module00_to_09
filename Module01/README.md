# Module 01 - Memory Allocation, Pointers & References

Memory allocation, pointers to members, references, and switch statements.

## Overview

This module dives deeper into C++ memory management, exploring the differences between stack and heap allocation, and introducing references as a safer alternative to pointers in certain contexts.

## Exercises

### Exercise 00: BraiiiiiiinnnzzzZ

Learn when to allocate objects on stack vs heap.

**Key concepts:**
- `new` / `delete` for heap allocation
- Stack allocation (automatic storage)
- Object lifetime and scope

**Functions implemented:**
- `Zombie* newZombie(std::string name)` - creates zombie on **heap** (survives scope)
- `void randomChump(std::string name)` - creates zombie on **stack** (destroyed at scope end)

**When to use which:**
| Allocation | Use when... |
|------------|-------------|
| Stack | Object only needed in current scope |
| Heap | Object needs to outlive the function |

### Exercise 01: Moar brainz!

Allocate multiple objects in a single allocation.

**Key concepts:**
- `new[]` / `delete[]` for array allocation
- Single allocation for N objects
- Contiguous memory

```cpp
Zombie* zombieHorde(int N, std::string name);
// Allocates N zombies in ONE new[] call
// Must use delete[] to free
```

### Exercise 02: HI THIS IS BRAIN

Demystify references - they're just another syntax for addresses.

**Key concepts:**
- Pointer: `std::string* ptr = &str;`
- Reference: `std::string& ref = str;`
- Both point to the same memory address

```cpp
std::string str = "HI THIS IS BRAIN";
std::string* stringPTR = &str;   // Pointer
std::string& stringREF = str;    // Reference

// All print the SAME address:
&str, stringPTR, &stringREF

// All print the SAME value:
str, *stringPTR, stringREF
```

### Exercise 03: Unnecessary violence

When to use references vs pointers.

**Key concepts:**
- Reference: must be initialized, cannot be NULL, cannot be reassigned
- Pointer: can be NULL, can be reassigned

| Class | Weapon storage | Why |
|-------|---------------|-----|
| HumanA | `Weapon& weapon` (reference) | Always armed, weapon set at construction |
| HumanB | `Weapon* weapon` (pointer) | May be unarmed, weapon set later |

```cpp
// HumanA - MUST have weapon (reference)
HumanA(std::string name, Weapon& weapon);

// HumanB - MAY have weapon (pointer)
HumanB(std::string name);
void setWeapon(Weapon& weapon);
```

### Exercise 04: Sed is for losers

File I/O and string manipulation without `std::string::replace`.

**Key concepts:**
- `std::ifstream` for reading files
- `std::ofstream` for writing files
- String searching with `find()`
- Building output with `substr()` and concatenation

**Forbidden:** `std::string::replace`

### Exercise 05: Harl 2.0

Pointers to member functions - avoiding if/else chains.

**Key concepts:**
- Pointer to member function syntax: `void (Harl::*funcPtr)(void)`
- Calling: `(this->*funcPtr)()`
- Array of function pointers for dispatch

```cpp
typedef void (Harl::*ActionPtr)(void);
ActionPtr actions[4] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

// Call by index:
(this->*actions[idx])();
```

### Exercise 06: Harl filter (Bonus)

Filter log levels using switch statement with fall-through.

**Key concepts:**
- `switch` statement
- Fall-through behavior (no `break`)

```cpp
switch (level) {
    case DEBUG:
        debug();
        // fall through
    case INFO:
        info();
        // fall through
    // ...
}
```

## C++ Concepts Introduced

| Concept | Description |
|---------|-------------|
| `new` / `delete` | Heap allocation/deallocation for single objects |
| `new[]` / `delete[]` | Heap allocation/deallocation for arrays |
| Reference (`&`) | Alias to existing variable, must be initialized |
| Pointer (`*`) | Stores memory address, can be NULL |
| `std::ifstream` | Input file stream |
| `std::ofstream` | Output file stream |
| Pointer to member function | Function pointer for class methods |
| `switch` | Multi-way branch statement |

## Building and Testing

### Build Everything
```bash
cd Module01
make              # Build exercises + run tests
```

### Run Tests
```bash
make test                                    # Run all tests
cd build && ctest --output-on-failure        # Verbose output
cd build && ./TestModule01Ex00               # Run specific test
cd build && ./TestModule01Ex03               # Run ex03 tests
cd build && ./TestModule01Ex05               # Run ex05 tests
```

### Build Individual Exercise
```bash
cd ex00 && make    # Build zombie
cd ex03 && make    # Build violence
cd ex05 && make    # Build harl
```

### Clean
```bash
make clean        # Remove object files
make fclean       # Remove objects + binaries
```

## Project Structure

```
Module01/
├── ex00/                    # BraiiiiiiinnnzzzZ (Stack vs Heap)
│   ├── headers/Zombie.hpp
│   └── src/Zombie.cpp, newZombie.cpp, randomChump.cpp
├── ex01/                    # Moar brainz! (Array allocation)
│   ├── headers/Zombie.hpp, ZombieHorde.hpp
│   └── src/Zombie.cpp, zombieHorde.cpp
├── ex02/                    # HI THIS IS BRAIN (References intro)
│   └── src/main.cpp
├── ex03/                    # Unnecessary violence (Ref vs Ptr)
│   ├── headers/Weapon.hpp, HumanA.hpp, HumanB.hpp
│   └── src/Weapon.cpp, HumanA.cpp, HumanB.cpp
├── ex04/                    # Sed is for losers (File I/O)
│   ├── headers/Database.hpp, ReplaceThisWithThat.hpp
│   └── src/Database.cpp, ReplaceThisWithThat.cpp
├── ex05/                    # Harl 2.0 (Ptr to member func)
│   ├── headers/Harl.hpp
│   └── src/Harl.cpp
├── ex06/                    # Harl filter (switch statement)
│   ├── headers/Harl.hpp
│   └── src/Harl.cpp
├── tests/
│   ├── TestModule01Ex00.cpp
│   ├── TestModule01Ex01.cpp
│   ├── TestModule01Ex03.cpp
│   ├── TestModule01Ex05.cpp
│   └── CMakeLists.txt
├── CMakeLists.txt
└── Makefile
```

## Test Coverage

| Exercise | Tests | Description |
|----------|-------|-------------|
| ex00 | 12 | Zombie creation, newZombie (heap), randomChump (stack) |
| ex01 | 11 | Zombie horde creation, array allocation, memory |
| ex03 | 14 | Weapon, HumanA (reference), HumanB (pointer) |
| ex05 | 14 | Harl log levels, pointer to member functions |

## Key Takeaways

1. **Stack vs Heap**: Use stack for local, temporary objects. Use heap when objects need to outlive their scope.

2. **References vs Pointers**:
   - Reference: safer, cleaner syntax, cannot be NULL
   - Pointer: flexible, can be NULL, can be reassigned

3. **Pointers to Member Functions**: Enable dynamic dispatch without virtual functions or if/else chains.

4. **Memory Management**: Every `new` needs a `delete`. Every `new[]` needs a `delete[]`.
