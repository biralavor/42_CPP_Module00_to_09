# Module 05 - Exceptions

C++ exception handling with try/catch and custom exception classes.

## Overview

This module introduces exception handling in C++. You'll learn to create custom exceptions, throw and catch them properly, and design classes that validate their state.

## Exercises

### Exercise 00: Bureaucrat

Create a Bureaucrat class with grade validation (1-150).

**Key concepts:**
- Custom exception classes inheriting from `std::exception`
- `what()` virtual function
- Exception throwing on invalid states

```cpp
class Bureaucrat {
    class GradeTooHighException : public std::exception {
        const char* what() const throw();
    };
    class GradeTooLowException : public std::exception {
        const char* what() const throw();
    };
};
```

### Exercise 01: Form

Add Form class that requires specific grades to sign.

**Key concepts:**
- Multiple exception types
- Form/Bureaucrat interaction
- `signForm()` method

```cpp
try {
    bureaucrat.signForm(form);
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
}
```

### Exercise 02: Concrete Forms

Abstract `AForm` with three implementations:
- `ShrubberyCreationForm` (145/137)
- `RobotomyRequestForm` (72/45)
- `PresidentialPardonForm` (25/5)

**Key concepts:**
- Abstract base class
- Pure virtual `execute()`
- `FormNotSignedException`

### Exercise 03: Intern

`Intern` class creates forms by name.

```cpp
Intern intern;
AForm* form = intern.makeForm("robotomy request", "Bender");
```

## Exception Handling Concepts

| Concept | Description |
|---------|-------------|
| `throw` | Raise an exception |
| `try/catch` | Handle exceptions |
| `std::exception` | Base exception class |
| `what()` | Return error message |
| `throw()` | Exception specification (C++98) |

## Building and Testing

```bash
cd Module05
make              # Build + run tests
make test         # Run all tests
make test-ex00    # Run ex00 tests only
make test-ex01    # Run ex01 tests only
make test-ex02    # Run ex02 tests only
make test-ex03    # Run ex03 tests only
make help         # Show all available targets
```

## Test Coverage

| Exercise | Tests | Description |
|----------|-------|-------------|
| ex00 | 10 | Constructor validation, increment/decrement, exceptions |
| ex01 | 12 | Form signing, grade checking, stream operator |
| ex02 | 22 | All three form types, execution, exceptions |
| ex03 | 18 | Intern form creation, invalid names, integration |

## Key Takeaways

1. **Custom exceptions** should inherit from `std::exception`
2. **Never let exceptions escape** constructors without cleanup
3. **Use RAII** for exception-safe resource management
4. **Validate early** - throw exceptions as soon as invalid state is detected
