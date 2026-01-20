# Module 04 - Subtype Polymorphism, Abstract Classes, Interfaces

Runtime polymorphism, virtual functions, and abstract classes in C++.

## Overview

This module covers subtype polymorphism - the ability to use derived class objects through base class pointers. You'll implement virtual functions, understand the importance of virtual destructors, and create abstract classes.

## Exercises

### Exercise 00: Polymorphism

Create `Animal`, `Dog`, and `Cat` classes demonstrating virtual functions.

**Key concepts:**
- Virtual functions (`virtual void makeSound()`)
- Virtual destructors
- Base pointer to derived object

```cpp
Animal* ptr = new Dog();
ptr->makeSound();  // Calls Dog::makeSound (polymorphic)
delete ptr;        // Calls ~Dog then ~Animal (virtual destructor)
```

**Wrong classes** demonstrate what happens without `virtual`:
```cpp
WrongAnimal* ptr = new WrongCat();
ptr->makeSound();  // Calls WrongAnimal::makeSound (not polymorphic!)
```

### Exercise 01: Deep Copy with Brain

Add a `Brain` class (100 ideas/strings) to Dog and Cat.

**Key concepts:**
- Deep copy vs shallow copy
- Memory management with pointers
- Copy constructor and assignment operator

```cpp
Dog original;
Dog copy(original);  // Deep copy - separate Brain
delete &original;    // copy's Brain is still valid
```

**Brain class:**
- `std::string ideas[100]`
- Properly copy all 100 ideas in copy constructor

### Exercise 02: Abstract Class

Make `Animal` abstract by making `makeSound()` pure virtual.

**Key concepts:**
- Pure virtual functions (`virtual void makeSound() = 0`)
- Abstract classes (cannot be instantiated)
- Interface design

```cpp
class AAnimal {
    virtual void makeSound() const = 0;  // Pure virtual
};

AAnimal animal;        // ERROR: cannot instantiate abstract class
AAnimal* ptr = new Dog();  // OK: Dog implements makeSound()
```

## C++ Concepts

| Concept | Description |
|---------|-------------|
| `virtual` | Enables runtime polymorphism |
| Pure virtual (`= 0`) | Makes class abstract |
| Virtual destructor | Ensures proper cleanup |
| Deep copy | Copies pointed-to data, not just pointer |

## Building and Testing

```bash
cd Module04
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
| ex00 | 16 | Polymorphic calls, virtual destructor, WrongAnimal |
| ex01 | 16 | Brain class, deep copy, memory independence |
| ex02 | 16 | Abstract class, pure virtual, derived classes |

## Key Takeaways

1. **Always use virtual destructor** in base classes intended for polymorphism
2. **Virtual functions** enable runtime dispatch based on actual object type
3. **Deep copy** is essential when class has pointer members
4. **Abstract classes** define interfaces that derived classes must implement
