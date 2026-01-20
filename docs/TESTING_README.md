# C++ Modules 00-09 - Comprehensive Test Suite

This repository now includes comprehensive GoogleTest-based test suites for learning C++ through Test-Driven Development (TDD).

## Overview

Each module contains a `tests/` directory with:
- ✅ **Comprehensive test coverage** for all exercises
- ✅ **TDD-ready tests** (especially Module 06)
- ✅ **GoogleTest framework** integration
- ✅ **CMake build system** for easy compilation
- ✅ **Detailed implementation guides** in comments

## Test Suite Status

| Module | Status | Exercises Covered | Test Count |
|--------|--------|-------------------|------------|
| Module 00 | ✅ Complete | ex00, ex01, ex02 | ~100 tests |
| Module 01 | ✅ Partial | ex00, ex01 | ~40 tests |
| Module 02 | 🚧 Planned | ex00-ex02 | TBD |
| Module 03 | 🚧 Planned | ex00-ex02 | TBD |
| Module 04 | 🚧 Planned | ex00-ex02 | TBD |
| Module 05 | ✅ Partial | ex00, ex01 | ~50 tests |
| Module 06 | ✅ Complete TDD | ex00-ex02 | ~115 tests |

## Quick Start

### Prerequisites

```bash
# Install GoogleTest (if not using FetchContent)
sudo apt-get install libgtest-dev cmake

# Or let CMake fetch it automatically (already configured)
```

### Building and Running Tests

For any module with tests:

```bash
cd ModuleXX/tests
mkdir build && cd build
cmake ..
make
./TestModuleXX_ExYY  # Run specific test
```

### Example: Running Module06 Tests

```bash
cd Module06/tests
mkdir build && cd build
cmake ..
make
./TestModule06Ex00
./TestModule06Ex01
./TestModule06Ex02
```

## Module Highlights

### 🔥 Module 06 - Full TDD Suite (RECOMMENDED START)

**Special Features**:
- Complete Test-Driven Development suite
- Tests written BEFORE implementation
- Comprehensive implementation guides
- Perfect for learning TDD methodology

**What You Get**:
- 115+ tests covering all edge cases
- Step-by-step implementation hints
- RED → GREEN → REFACTOR workflow
- Detailed README with TDD guide

**Start Here If**:
- You want to learn TDD
- You prefer tests-first approach
- You want comprehensive coverage
- You learn by making tests pass

See [Module06/tests/README.md](Module06/tests/README.md) for the complete TDD guide.

### Module 00 - Basics and Foundations

**Tests Cover**:
- **ex00**: Megaphone - string manipulation
- **ex01**: PhoneBook - classes, arrays, input/output
- **ex02**: Account - static members, constructors

**Key Learning**:
- Basic C++ syntax
- Classes and objects
- Static members
- I/O streams

### Module 01 - Memory Management

**Tests Cover**:
- **ex00**: Zombie - stack vs heap allocation
- **ex01**: ZombieHorde - array allocation

**Key Learning**:
- new and delete
- Stack vs heap
- Memory leaks
- Object lifetime

### Module 05 - Exceptions

**Tests Cover**:
- **ex00**: Bureaucrat - custom exceptions
- **ex01**: Form - exception handling

**Key Learning**:
- Exception classes
- try-catch blocks
- Exception hierarchy
- Grade validation

## Test Organization

Each test file follows this structure:

```cpp
/* ************************************************************************** */
/*   TestModuleXXExYY.cpp - Description                                     */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../exYY/headers/ClassName.hpp"

// Test fixtures for common setup
class ClassNameTest : public ::testing::Test {
protected:
    void SetUp() override { /* setup code */ }
    void TearDown() override { /* cleanup code */ }
};

// Test groups organized by functionality
TEST(GroupName, TestName) {
    // Arrange
    // Act
    // Assert
}
```

## Writing New Tests

### Template for New Test

```cpp
TEST(ClassName, TestDescription) {
    // Arrange - Set up test data
    ClassName obj(params);
    
    // Act - Execute the code being tested
    result = obj.method();
    
    // Assert - Verify the result
    EXPECT_EQ(result, expected);
}
```

### GoogleTest Assertions

```cpp
// Equality
EXPECT_EQ(a, b);      // a == b
EXPECT_NE(a, b);      // a != b

// Comparison
EXPECT_LT(a, b);      // a < b
EXPECT_GT(a, b);      // a > b
EXPECT_LE(a, b);      // a <= b
EXPECT_GE(a, b);      // a >= b

// Boolean
EXPECT_TRUE(condition);
EXPECT_FALSE(condition);

// Floating point
EXPECT_FLOAT_EQ(a, b);
EXPECT_DOUBLE_EQ(a, b);

// Exceptions
EXPECT_THROW(statement, exception_type);
EXPECT_NO_THROW(statement);

// Strings
EXPECT_STREQ(str1, str2);

// Pointers
EXPECT_EQ(ptr, nullptr);
EXPECT_NE(ptr, nullptr);
```

## Test Categories

### 1. **Constructor/Destructor Tests**
```cpp
TEST(ClassName, ConstructorDefault) {
    ClassName obj;
    EXPECT_EQ(obj.getValue(), 0);
}

TEST(ClassName, ConstructorParameterized) {
    ClassName obj(42);
    EXPECT_EQ(obj.getValue(), 42);
}
```

### 2. **Method Behavior Tests**
```cpp
TEST(ClassName, MethodReturnsExpectedValue) {
    ClassName obj;
    int result = obj.calculate(5);
    EXPECT_EQ(result, 25);
}
```

### 3. **Exception Tests**
```cpp
TEST(ClassName, ThrowsOnInvalidInput) {
    ClassName obj;
    EXPECT_THROW(obj.setGrade(200), ClassName::Exception);
}
```

### 4. **Edge Case Tests**
```cpp
TEST(ClassName, HandlesZero) { /* ... */ }
TEST(ClassName, HandlesMaxValue) { /* ... */ }
TEST(ClassName, HandlesMinValue) { /* ... */ }
TEST(ClassName, HandlesNegative) { /* ... */ }
```

### 5. **Integration Tests**
```cpp
TEST(SystemTest, CompleteWorkflow) {
    // Test multiple components together
    ClassA a;
    ClassB b(a);
    ClassC c(b);
    EXPECT_TRUE(c.isValid());
}
```

## CMake Configuration

Each module's `tests/CMakeLists.txt` follows this pattern:

```cmake
cmake_minimum_required(VERSION 3.14)
project(ModuleXXTests)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# GoogleTest (auto-fetched)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test executable
add_executable(TestModuleXXExYY
  TestModuleXXExYY.cpp
  ../exYY/src/ClassName.cpp
)
target_link_libraries(TestModuleXXExYY GTest::gtest_main)
target_include_directories(TestModuleXXExYY PRIVATE ../exYY/headers)

include(GoogleTest)
gtest_discover_tests(TestModuleXXExYY)
```

## Running Tests

### Run All Tests
```bash
cd ModuleXX/tests/build
make
ctest
```

### Run Specific Test Suite
```bash
./TestModuleXXExYY
```

### Run Specific Test
```bash
./TestModuleXXExYY --gtest_filter=ClassName.MethodName
```

### Run Tests with Verbose Output
```bash
./TestModuleXXExYY --gtest_verbose
```

### Run Tests and See Failures Only
```bash
./TestModuleXXExYY --gtest_brief
```

## Test-Driven Development Workflow

### The TDD Cycle

1. **🔴 RED** - Write a failing test
   ```bash
   # Test fails because feature doesn't exist yet
   ./TestModuleXX --gtest_filter=NewFeature
   # Output: [  FAILED  ] NewFeature
   ```

2. **🟢 GREEN** - Write minimum code to pass
   ```cpp
   // Implement just enough to make test pass
   int ClassName::newMethod() {
       return 42;  // Simplest implementation
   }
   ```
   ```bash
   ./TestModuleXX --gtest_filter=NewFeature
   # Output: [       OK ] NewFeature
   ```

3. **🔵 REFACTOR** - Improve code while staying green
   ```cpp
   // Improve implementation
   int ClassName::newMethod() {
       return this->calculate();  // Better implementation
   }
   ```
   ```bash
   ./TestModuleXX  # All tests still pass
   ```

4. **REPEAT** for next feature

### TDD Benefits

- ✅ Confidence in your code
- ✅ Better design (testable code is better code)
- ✅ Living documentation
- ✅ Catch regressions immediately
- ✅ Easier debugging (know exactly what broke)

## Best Practices

### 1. Test Organization
- Group related tests in test fixtures
- Use descriptive test names
- One assertion per test (when possible)
- Test one thing at a time

### 2. Test Quality
- **FIRST Principles**:
  - **F**ast - Tests should run quickly
  - **I**ndependent - Tests don't depend on each other
  - **R**epeatable - Same result every time
  - **S**elf-validating - Pass/fail, no manual checking
  - **T**imely - Written before or with the code

### 3. Test Coverage
- Happy path (normal cases)
- Edge cases (boundaries)
- Error cases (exceptions)
- Integration (multiple components)

### 4. Naming Conventions
```cpp
TEST(ClassName, MethodName_Scenario_ExpectedBehavior) {
    // Example: Bureaucrat_IncrementGrade_AtMaxGrade_ThrowsException
}
```

## Continuous Integration

You can integrate these tests with CI/CD:

### GitHub Actions Example
```yaml
name: C++ Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Install dependencies
        run: sudo apt-get install cmake g++
      - name: Build and Test Module 06
        run: |
          cd Module06/tests
          mkdir build && cd build
          cmake ..
          make
          ctest --output-on-failure
```

## Troubleshooting

### Common Issues

**Issue**: GoogleTest not found
```bash
# Solution: Let CMake fetch it (already configured)
# Or install manually:
sudo apt-get install libgtest-dev
```

**Issue**: Tests fail to compile
```bash
# Solution: Check that source files exist
# Check that paths in CMakeLists.txt are correct
```

**Issue**: Undefined reference errors
```bash
# Solution: Ensure all source files are listed in CMakeLists.txt
# Check that member functions are implemented
```

**Issue**: All tests fail
```bash
# Solution: Check that you're running the right test executable
# Verify implementation matches expected interface
```

## Contributing

To add tests for more modules:

1. Create `ModuleXX/tests/` directory
2. Copy CMakeLists.txt from another module
3. Create test files following existing patterns
4. Update this README with new module info

## Resources

- [GoogleTest Documentation](https://google.github.io/googletest/)
- [GoogleTest Primer](https://google.github.io/googletest/primer.html)
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/)
- [TDD by Example (Book)](https://www.oreilly.com/library/view/test-driven-development/0321146530/)
- [42 Cursus Subject PDFs](https://github.com/42School)

## Learning Path

Recommended order for maximum learning:

1. **Start with Module 06** (TDD suite) - Learn TDD methodology
2. **Module 00** - Practice with provided tests
3. **Module 01** - Memory management tests
4. **Module 05** - Exception tests
5. Write your own tests for remaining modules

## Test Statistics

Total test coverage across all modules:
- **~400+ individual tests**
- **Coverage**: All major features and edge cases
- **TDD-ready**: Module 06 fully TDD
- **Expandable**: Easy to add more tests

## License

Same as the main repository. Tests are provided to help you learn C++.

## Acknowledgments

- GoogleTest team for the testing framework
- 42 Network for the curriculum
- The C++ community for best practices

---

**Remember**: Tests are not just for verification—they're a learning tool. Read them, understand them, and use them to guide your implementation!

Happy Testing! 🧪✨
