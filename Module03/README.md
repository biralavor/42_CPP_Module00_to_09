# Module 03 - Inheritance

Inheritance in C++: base classes, derived classes, and the diamond problem.

## Overview

This module introduces inheritance, one of the core concepts of Object-Oriented Programming. You'll create a class hierarchy of "trap" robots, each with different stats and abilities, learning how derived classes inherit and override behavior from base classes.

## Exercises

### Exercise 00: Aaaaand... OPEN!

Create the `ClapTrap` base class with basic combat capabilities.

**Key concepts:**
- Base class design
- Member attributes (name, hit points, energy, attack damage)
- Combat methods (attack, takeDamage, beRepaired)

**ClapTrap Stats:**
| Attribute | Value |
|-----------|-------|
| Hit Points | 10 |
| Energy Points | 10 |
| Attack Damage | 0 |

**Methods:**
```cpp
void attack(const std::string &target);   // Costs 1 energy
void takeDamage(unsigned int amount);     // Reduces hit points
void beRepaired(unsigned int amount);     // Costs 1 energy, adds hit points
```

**Rules:**
- Attacking and repairing cost 1 energy point each
- No action possible with 0 energy or 0 hit points
- Display messages for each action

### Exercise 01: Serena, my love!

Create `ScavTrap`, a derived class of `ClapTrap` with enhanced stats.

**Key concepts:**
- Public inheritance (`class ScavTrap : public ClapTrap`)
- Constructor/destructor chaining
- Method overriding

**ScavTrap Stats:**
| Attribute | Value |
|-----------|-------|
| Hit Points | 100 |
| Energy Points | 50 |
| Attack Damage | 20 |

**New method:**
```cpp
void guardGate();  // ScavTrap-specific ability
```

**Constructor/Destructor Order:**
```
Creating ScavTrap "Bob":
1. ClapTrap constructor called (base class first)
2. ScavTrap constructor called (derived class second)

Destroying ScavTrap "Bob":
1. ScavTrap destructor called (derived class first)
2. ClapTrap destructor called (base class second)
```

### Exercise 02: Repetitive work

Create `FragTrap`, another derived class with different stats.

**Key concepts:**
- Multiple derived classes from same base
- Different default values in constructors
- Unique special abilities

**FragTrap Stats:**
| Attribute | Value |
|-----------|-------|
| Hit Points | 100 |
| Energy Points | 100 |
| Attack Damage | 30 |

**New method:**
```cpp
void highFivesGuys(void);  // FragTrap-specific ability
```

### Exercise 03: Now it's weird! (Bonus)

Create `DiamondTrap`, inheriting from both `ScavTrap` and `FragTrap`.

**Key concepts:**
- Multiple inheritance
- The Diamond Problem
- Virtual inheritance
- Name shadowing

**The Diamond Problem:**
```
        ClapTrap
       /        \
  ScavTrap    FragTrap
       \        /
      DiamondTrap
```

Without virtual inheritance, DiamondTrap would have TWO copies of ClapTrap members.

**Solution - Virtual Inheritance:**
```cpp
class ScavTrap : virtual public ClapTrap { ... };
class FragTrap : virtual public ClapTrap { ... };
class DiamondTrap : public ScavTrap, public FragTrap { ... };
```

**DiamondTrap Stats:**
| Attribute | From |
|-----------|------|
| Hit Points | FragTrap (100) |
| Energy Points | ScavTrap (50) |
| Attack Damage | FragTrap (30) |
| Name | Own `_name` + ClapTrap's `_name = name + "_clap_name"` |

**Special method:**
```cpp
void whoAmI();  // Displays both DiamondTrap name and ClapTrap name
```

## C++ Concepts Introduced

| Concept | Description |
|---------|-------------|
| Inheritance | Derived class acquires properties of base class |
| `public` inheritance | Public members remain public in derived class |
| `protected` | Accessible by class and derived classes |
| `virtual` destructor | Ensures proper cleanup through base pointer |
| Virtual inheritance | Solves diamond problem by sharing base instance |
| Constructor chaining | Base constructor called before derived |
| Method overriding | Derived class replaces base class method |

## Inheritance Access Specifiers

```cpp
class Base {
public:    int pub;     // Everyone
protected: int prot;    // Base + Derived
private:   int priv;    // Base only
};

class Derived : public Base {
    // pub → public
    // prot → protected
    // priv → not accessible
};
```

## Virtual Destructor Importance

```cpp
class ClapTrap {
public:
    virtual ~ClapTrap();  // MUST be virtual for polymorphism!
};

// Without virtual destructor:
ClapTrap* ptr = new ScavTrap();
delete ptr;  // Only calls ClapTrap destructor! Memory leak!

// With virtual destructor:
delete ptr;  // Calls ScavTrap destructor, then ClapTrap destructor. Correct!
```

## Building and Testing

### Build Everything
```bash
cd Module03
make              # Build exercises + run tests
```

### Run Tests
```bash
make test         # Run all tests
make test-ex00    # Run ex00 tests only
make test-ex01    # Run ex01 tests only
make test-ex02    # Run ex02 tests only
make test-ex03    # Run ex03 tests only
make help         # Show all available targets
```

### Build Individual Exercise
```bash
cd ex00 && make    # Build ClapTrap
cd ex01 && make    # Build ScavTrap
cd ex02 && make    # Build FragTrap
cd ex03 && make    # Build DiamondTrap
```

### Clean
```bash
make clean        # Remove object files
make fclean       # Remove objects + binaries
```

## Project Structure

```
Module03/
├── ex00/                    # ClapTrap (Base Class)
│   ├── headers/
│   │   ├── ClapTrap.hpp
│   │   └── Utils.hpp
│   └── src/
│       ├── ClapTrap.cpp
│       ├── Utils.cpp
│       └── main.cpp
├── ex01/                    # ScavTrap (Derived)
│   ├── headers/
│   │   ├── ClapTrap.hpp
│   │   ├── ScavTrap.hpp
│   │   └── Utils.hpp
│   └── src/
│       ├── ClapTrap.cpp
│       ├── ScavTrap.cpp
│       ├── Utils.cpp
│       └── main.cpp
├── ex02/                    # FragTrap (Derived)
│   ├── headers/
│   │   ├── ClapTrap.hpp
│   │   ├── ScavTrap.hpp
│   │   ├── FragTrap.hpp
│   │   └── Utils.hpp
│   └── src/
│       ├── ClapTrap.cpp
│       ├── ScavTrap.cpp
│       ├── FragTrap.cpp
│       ├── Utils.cpp
│       └── main.cpp
├── ex03/                    # DiamondTrap (Multiple Inheritance)
│   ├── headers/
│   │   ├── ClapTrap.hpp
│   │   ├── ScavTrap.hpp
│   │   ├── FragTrap.hpp
│   │   ├── DiamondTrap.hpp
│   │   └── Utils.hpp
│   └── src/
│       ├── ClapTrap.cpp
│       ├── ScavTrap.cpp
│       ├── FragTrap.cpp
│       ├── DiamondTrap.cpp
│       ├── Utils.cpp
│       └── main.cpp
├── tests/
│   ├── TestModule03Ex00.cpp
│   ├── TestModule03Ex01.cpp
│   ├── TestModule03Ex02.cpp
│   └── CMakeLists.txt
├── CMakeLists.txt
└── Makefile
```

## Test Coverage

| Exercise | Tests | Description |
|----------|-------|-------------|
| ex00 | 20 | ClapTrap constructors, combat, energy management |
| ex01 | 18 | ScavTrap inheritance, guardGate, constructor order |
| ex02 | 18 | FragTrap inheritance, highFivesGuys, stat comparison |

## Class Comparison Table

| Feature | ClapTrap | ScavTrap | FragTrap | DiamondTrap |
|---------|----------|----------|----------|-------------|
| Hit Points | 10 | 100 | 100 | 100 (FragTrap) |
| Energy | 10 | 50 | 100 | 50 (ScavTrap) |
| Attack | 0 | 20 | 30 | 30 (FragTrap) |
| Special | - | guardGate() | highFivesGuys() | whoAmI() |

## Key Takeaways

1. **Inheritance Hierarchy**: Design base classes to be extensible. Use `protected` for members that derived classes need.

2. **Virtual Destructors**: Always make destructors virtual in base classes that will be inherited.

3. **Constructor Order**: Base class constructs first, destructs last. Initialize base in derived constructor's initialization list.

4. **Diamond Problem**: Use virtual inheritance when multiple inheritance paths lead to same base class.

5. **Method Overriding**: Derived classes can replace base class methods. Use `virtual` keyword if polymorphism is needed.
