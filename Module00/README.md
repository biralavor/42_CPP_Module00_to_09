# Module 00 - C++ Basics

Introduction to C++ fundamentals: namespaces, classes, member functions, stdio streams, initialization lists, static, and const.

## Overview

This is the starting point of the C++ journey at 42. The module introduces Object-Oriented Programming concepts using C++98 standard, building on existing C knowledge.

## Exercises

### Exercise 00: Megaphone

A simple program that converts input to uppercase and outputs it.

**Key concepts:**
- Basic C++ I/O streams (`std::cout`)
- String manipulation with `std::string`
- Command-line argument handling
- Character transformation (`std::toupper`)

**Expected behavior:**
```bash
./megaphone "shhhhh... I think the students are asleep..."
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...

./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.

./megaphone
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```

### Exercise 01: My Awesome PhoneBook

An 80s-style phonebook application with ADD, SEARCH, and EXIT commands.

**Key concepts:**
- **Classes**: `PhoneBook` and `Contact`
- **Encapsulation**: private attributes, public methods (getters/setters)
- **Fixed-size arrays** (no dynamic allocation)
- **I/O manipulation**: `std::setw`, `std::right` for formatted output
- **Circular buffer logic**: oldest contact replacement when full

**Classes implemented:**
- `Contact`: stores first name, last name, nickname, phone number, darkest secret
- `PhoneBook`: manages array of 8 contacts, handles ADD/SEARCH/EXIT commands

**Display format:**
```
|     INDEX|FIRST NAME| LAST NAME|  NICKNAME|
|         0|      John|       Doe|        JD|
|         1| VeryLongF.|VeryLongL.|VeryLongN.|
```

### Exercise 02: The Job Of Your Dreams (Bonus)

Recreate a lost `Account.cpp` file based on the header and log file.

**Key concepts:**
- **Static members**: class-level variables shared across all instances
- **Static member functions**: `getNbAccounts()`, `getTotalAmount()`, etc.
- **Constructor/Destructor** with side effects (logging)
- **Timestamp display**
- **Reverse engineering** from header and expected output

**Static members:**
- `_nbAccounts`: total number of accounts created
- `_totalAmount`: sum of all account balances
- `_totalNbDeposits`: total deposits across all accounts
- `_totalNbWithdrawals`: total withdrawals across all accounts

## C++ Concepts Introduced

| Concept | Description |
|---------|-------------|
| `std::string` | C++ string class (replaces C char arrays) |
| `std::cout` / `std::cin` | Stream-based I/O (replaces printf/scanf) |
| `class` | User-defined types with data + behavior |
| `private` / `public` | Access specifiers for encapsulation |
| `static` | Class-level members shared by all instances |
| `const` | Immutable values and member functions |
| `std::setw` / `std::right` | I/O manipulators for formatting |

## Building and Testing

### Build Everything
```bash
cd Module00
make              # Build exercises + run tests
```

### Build Only Exercises
```bash
make build_exercises
```

### Run Tests
```bash
make test         # Run all tests
make test-ex00    # Run ex00 tests only
make test-ex01    # Run ex01 tests only
make test-ex02    # Run ex02 tests only
make help         # Show all available targets
```

### Build Individual Exercise
```bash
cd ex00 && make    # Build megaphone
cd ex01 && make    # Build phonebook
cd ex02 && make    # Build account
```

### Run Individual Exercise
```bash
cd ex00 && make go              # Build and run megaphone
cd ex00/bin && ./megaphone "hello world"
```

### Clean
```bash
make clean        # Remove object files
make fclean       # Remove objects + binaries
make re           # Full rebuild
```

## Project Structure

```
Module00/
├── ex00/                    # Megaphone
│   ├── headers/
│   │   └── Megaphone.hpp
│   ├── src/
│   │   ├── main.cpp
│   │   └── Megaphone.cpp
│   └── Makefile
├── ex01/                    # PhoneBook
│   ├── headers/
│   │   ├── Contact.hpp
│   │   ├── PhoneBook.hpp
│   │   └── Printers.hpp
│   ├── src/
│   │   ├── main.cpp
│   │   ├── Contact.cpp
│   │   └── PhoneBook.cpp
│   └── Makefile
├── ex02/                    # Account (bonus)
│   ├── headers/
│   │   └── Account.hpp
│   ├── src/
│   │   ├── tests.cpp
│   │   └── Account.cpp
│   └── Makefile
├── tests/                   # Google Test files
│   ├── TestModule00Ex00.cpp
│   ├── TestModule00Ex01.cpp
│   ├── TestModule00Ex02.cpp
│   └── CMakeLists.txt
├── CMakeLists.txt
└── Makefile
```

## Test Coverage

| Exercise | Tests | Description |
|----------|-------|-------------|
| ex00 | 5 | No args, single arg, multiple args, numbers |
| ex01 | 14 | Contact creation, PhoneBook capacity, truncation, display |
| ex02 | 14 | Account operations, deposits, withdrawals, static members |

## Resources

- [cplusplus.com/reference/string](http://www.cplusplus.com/reference/string/string/)
- [cplusplus.com/reference/iomanip](http://www.cplusplus.com/reference/iomanip/)
- [learncpp.com](https://www.learncpp.com/)
