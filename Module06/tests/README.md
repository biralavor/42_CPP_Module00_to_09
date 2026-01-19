# Module 06 - TDD Test Suite

## Test-Driven Development Guide

This directory contains comprehensive TDD (Test-Driven Development) tests for Module 06.
The tests are **already written** - your job is to implement the code to make them pass!

## What is TDD?

Test-Driven Development is a methodology where you:
1. **Read the failing tests** (they're already written!)
2. **Implement the code** to make tests pass
3. **Refactor** your code while keeping tests green
4. **Repeat** until all tests pass

## Structure

```
Module06/
├── ex00/           # Your ScalarConverter implementation goes here
│   ├── headers/
│   │   └── ScalarConverter.hpp
│   └── src/
│       └── ScalarConverter.cpp
├── ex01/           # Your Serializer implementation goes here
│   ├── headers/
│   │   ├── Serializer.hpp
│   │   └── Data.hpp
│   └── src/
│       ├── Serializer.cpp
│       └── Data.cpp
├── ex02/           # Your Type Identification implementation goes here
│   ├── headers/
│   │   ├── Base.hpp
│   │   ├── A.hpp
│   │   ├── B.hpp
│   │   └── C.hpp
│   └── src/
│       ├── Base.cpp
│       └── identify.cpp
└── tests/          # TDD Tests (already complete!)
    ├── TestModule06Ex00.cpp
    ├── TestModule06Ex01.cpp
    ├── TestModule06Ex02.cpp
    ├── CMakeLists.txt
    └── README.md (this file)
```

## How to Use This TDD Suite

### Step 1: Read the Test File

Before writing any code, read the test file for the exercise:
- `TestModule06Ex00.cpp` - ScalarConverter tests
- `TestModule06Ex01.cpp` - Serializer tests
- `TestModule06Ex02.cpp` - Type Identification tests

Each test file contains:
- **IMPLEMENTATION GUIDE** comments at the top
- Detailed test cases showing what your code should do
- **Hints** and explanations in comments

### Step 2: Set Up Your Build

```bash
cd Module06/tests
mkdir build
cd build
cmake ..
```

At first, this will fail because the source files don't exist. That's expected!

### Step 3: Create the Files

Start with **Exercise 00** (easiest):

1. Create the directory structure:
```bash
mkdir -p ../ex00/headers ../ex00/src
```

2. Create the header file: `ex00/headers/ScalarConverter.hpp`
3. Create the source file: `ex00/src/ScalarConverter.cpp`

### Step 4: Uncomment the Tests

In `tests/CMakeLists.txt`, uncomment the section for ex00:

```cmake
add_executable(
  TestModule06Ex00
  TestModule06Ex00.cpp
  ../ex00/src/ScalarConverter.cpp
)
target_link_libraries(TestModule06Ex00 GTest::gtest_main)
target_include_directories(TestModule06Ex00 PRIVATE ../ex00/headers)

include(GoogleTest)
gtest_discover_tests(TestModule06Ex00)
```

In `tests/TestModule06Ex00.cpp`, uncomment:
```cpp
#include "../ex00/headers/ScalarConverter.hpp"
```

And uncomment the `ScalarConverter::convert()` calls in the tests.

### Step 5: Build and Run Tests

```bash
cd Module06/tests/build
cmake ..
make
./TestModule06Ex00
```

You'll see **RED** tests (failing). This is good! It means the tests are running.

### Step 6: Implement Until Green

Start implementing your code to make tests pass, one at a time:

1. **Start simple**: Make the easiest test pass first
2. **Run tests frequently**: After each small change
3. **Read the error messages**: They tell you what to fix
4. **Follow the patterns**: Tests show you exactly what to implement

### Step 7: Iterate

- Make one test pass
- Run all tests
- Fix any regressions
- Move to next test
- Repeat until all tests are **GREEN** ✅

## Exercise-Specific Guides

### Exercise 00: ScalarConverter

**Difficulty**: ⭐⭐⭐ (Medium)

**Key Concepts**:
- C++ type casting
- String parsing
- Special values (inf, nan)
- Type detection

**Implementation Order**:
1. Start with integer literals (easiest)
2. Add float literals
3. Add double literals
4. Handle char literals
5. Handle special pseudo-literals (inf, nan)
6. Handle edge cases

**Hint**: Use `strtol()`, `strtof()`, `strtod()` for conversions.

**Tests to focus on first**:
- `IntLiteral_Zero`
- `IntLiteral_Positive`
- `FloatLiteral_Zero`

### Exercise 01: Serializer

**Difficulty**: ⭐⭐ (Easy)

**Key Concepts**:
- Pointer to integer conversion
- `uintptr_t` type
- `reinterpret_cast`
- Serialization concepts

**Implementation Order**:
1. Create the `Data` structure (with some members!)
2. Implement `serialize()` - just cast pointer to `uintptr_t`
3. Implement `deserialize()` - cast back to pointer
4. Ensure it's a static-only class (private constructor)

**Hint**: This is the easiest exercise. The conversion is just:
```cpp
uintptr_t serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}
```

**Tests to focus on first**:
- `SerializeDeserializeRoundtrip`
- `DeserializedDataIsValid`

### Exercise 02: Type Identification

**Difficulty**: ⭐⭐⭐⭐ (Hard)

**Key Concepts**:
- Polymorphism and RTTI
- `dynamic_cast` with pointers
- `dynamic_cast` with references
- Exception handling (`std::bad_cast`)

**Implementation Order**:
1. Create Base class with virtual destructor
2. Create A, B, C classes (can be empty)
3. Implement `generate()` - use `rand()` for randomness
4. Implement `identify(Base* p)` - use pointer dynamic_cast
5. Implement `identify(Base& p)` - use reference dynamic_cast with try-catch

**Important**: The reference version **cannot use pointers** internally!

**Hint for identify(Base& p)**:
```cpp
try {
    (void)dynamic_cast<A&>(p);
    std::cout << "A" << std::endl;
    return;
} catch (std::bad_cast&) {}
// Try B and C similarly
```

**Tests to focus on first**:
- `BaseHasVirtualDestructor`
- `GenerateReturnsNonNull`
- `IdentifyPointer_TypeA`

## Running Specific Tests

Run all tests for an exercise:
```bash
./TestModule06Ex00
./TestModule06Ex01
./TestModule06Ex02
```

Run a specific test:
```bash
./TestModule06Ex00 --gtest_filter=*IntLiteral_Zero*
```

Run tests verbosely:
```bash
./TestModule06Ex00 --gtest_verbose
```

## Understanding Test Output

### GREEN (Pass) ✅
```
[       OK ] ScalarConverterTest.IntLiteral_Zero (0 ms)
```
Your implementation is correct for this test!

### RED (Fail) ❌
```
[  FAILED  ] ScalarConverterTest.IntLiteral_Zero (0 ms)
Expected: output.find("int: 0") != std::string::npos
  Actual: false
```
Read the error message - it tells you exactly what's wrong.

### Build Error 🔨
```
error: 'ScalarConverter' was not declared in this scope
```
You haven't created the class/file yet, or forgot to uncomment the include.

## Tips for Success

1. **Read the test code** - it's like the subject, but clearer
2. **Start small** - make one test pass at a time
3. **Don't skip tests** - they build on each other
4. **Use the hints** - implementation guides are in the test files
5. **Test frequently** - run tests after every change
6. **Understand failures** - read error messages carefully
7. **Refactor when green** - improve your code while tests pass

## Test Coverage

Each exercise has comprehensive test coverage:

### Ex00 (ScalarConverter): ~50 tests
- Char literals
- Int literals
- Float literals
- Double literals
- Special values (inf, nan)
- Edge cases and errors
- Subject examples

### Ex01 (Serializer): ~30 tests
- Basic serialization
- Pointer preservation
- Multiple objects
- Edge cases (null, stack objects)
- Subject example

### Ex02 (Type Identification): ~35 tests
- Base class tests
- Inheritance verification
- Generate function
- Identify with pointers
- Identify with references
- Subject example
- Dynamic cast understanding

## Completion Checklist

### Exercise 00: ScalarConverter
- [ ] Create ScalarConverter class (non-instantiable)
- [ ] Implement static convert() method
- [ ] Handle char literals
- [ ] Handle int literals
- [ ] Handle float literals
- [ ] Handle double literals
- [ ] Handle special values (+inff, -inff, nanf, +inf, -inf, nan)
- [ ] Handle impossible conversions
- [ ] Handle non-displayable characters
- [ ] All tests pass ✅

### Exercise 01: Serializer
- [ ] Create Data structure (non-empty!)
- [ ] Create Serializer class (non-instantiable)
- [ ] Implement static serialize() method
- [ ] Implement static deserialize() method
- [ ] Verify pointer roundtrip works
- [ ] All tests pass ✅

### Exercise 02: Type Identification
- [ ] Create Base class with virtual destructor
- [ ] Create A, B, C classes inheriting from Base
- [ ] Implement generate() function
- [ ] Implement identify(Base* p)
- [ ] Implement identify(Base& p) without using pointers
- [ ] All tests pass ✅

## Learning Goals

By completing this TDD module, you will:
- Understand C++ casting mechanisms (static, dynamic, reinterpret)
- Learn type conversion and detection
- Master polymorphism and RTTI
- Practice exception handling
- Experience TDD methodology
- Learn to read and write tests

## Need Help?

If you're stuck:

1. **Read the test** - it shows you what to do
2. **Check the comments** - implementation hints are included
3. **Look at the error** - it tells you what's missing
4. **Start simple** - get one test passing first
5. **Search the subject PDF** - it has additional context
6. **Ask a peer** - 42 is about peer learning!

## After Completion

Once all tests pass:

1. **Review your code** - is it clean and readable?
2. **Add a main.cpp** - create user-facing programs
3. **Create a Makefile** - follow 42 requirements
4. **Test edge cases** - what about invalid inputs?
5. **Understand WHY** - don't just make tests pass, understand concepts

Good luck! Remember: **Red → Green → Refactor** 🔴 ➡️ 🟢 ➡️ 🔵

---

*This TDD suite was created to help you learn C++ casting and type identification through practical, test-driven implementation.*
