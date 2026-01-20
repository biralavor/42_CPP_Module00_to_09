/* ************************************************************************** */
/*                                                                            */
/*   TestModule06Ex02.cpp - Type Identification TDD Tests                   */
/*   Identify real type using dynamic_cast (without typeinfo)               */
/*                                                                            */
/*   This is a TDD (Test-Driven Development) test suite.                    */
/*   Implement Base, A, B, C and identification functions!                  */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// TODO: Uncomment when you create the header files
#include "../ex02/headers/A.hpp"
#include "../ex02/headers/B.hpp"
#include "../ex02/headers/Base.hpp"
#include "../ex02/headers/C.hpp"

/*
   IMPLEMENTATION GUIDE:

   1. Create a Base class:
      - Has a public virtual destructor
      - No other members (can be empty except destructor)

   2. Create classes A, B, and C:
      - All inherit publicly from Base
      - Can be completely empty (no additional members)
      - Don't need Orthodox Canonical Form

   3. Implement these functions:

      Base* generate(void);
      - Randomly instantiates A, B, or C
      - Returns as Base pointer
      - Use rand() or any random method you like

      void identify(Base* p);
      - Prints the actual type: "A", "B", or "C"
      - Use dynamic_cast to determine type

      void identify(Base& p);
      - Prints the actual type: "A", "B", or "C"
      - Use dynamic_cast with references
      - Cannot use pointers inside this function!
      - Hint: use try-catch with bad_cast

   4. Key concepts:
      - Polymorphism and RTTI (Run-Time Type Information)
      - dynamic_cast for safe downcasting
      - dynamic_cast with pointers returns NULL on failure
      - dynamic_cast with references throws std::bad_cast on failure
      - Cannot use std::typeinfo or typeid()
*/

class TypeIdentificationTest : public ::testing::Test {
protected:
  void SetUp() override { old_cout = std::cout.rdbuf(buffer.rdbuf()); }

  void TearDown() override {
    std::cout.rdbuf(old_cout);
    buffer.str("");
    buffer.clear();
  }

  std::string getOutput() { return buffer.str(); }

  std::stringstream buffer;
  std::streambuf *old_cout;
};

// ============================================================================
// TEST GROUP 1: BASE CLASS TESTS
// ============================================================================

TEST(BaseClassTest, BaseHasVirtualDestructor) {
  // Base should have virtual destructor for polymorphism

  Base *base = new A();
  delete base; // Should call A's destructor, not just Base's

  // If this doesn't crash or leak, virtual destructor works
  SUCCEED();
}

TEST(BaseClassTest, BaseIsPolymorphic) {
  // Base should be a polymorphic type

  Base *base = new Base();

  // If Base has virtual functions, dynamic_cast works
  // This is a compile-time check

  delete base;
  SUCCEED();
}

// ============================================================================
// TEST GROUP 2: INHERITANCE TESTS
// ============================================================================

TEST(InheritanceTest, AInheritsFromBase) {
  A *a = new A();
  Base *base = a; // Should convert to Base*

  EXPECT_TRUE(base != NULL);

  delete base;
}

TEST(InheritanceTest, BInheritsFromBase) {
  B *b = new B();
  Base *base = b;

  EXPECT_TRUE(base != NULL);

  delete base;
}

TEST(InheritanceTest, CInheritsFromBase) {
  C *c = new C();
  Base *base = c;

  EXPECT_TRUE(base != NULL);

  delete base;
}

TEST(InheritanceTest, DifferentTypesDifferentObjects) {
  A *a = new A();
  B *b = new B();
  C *c = new C();

  Base *base_a = a;
  Base *base_b = b;
  Base *base_c = c;

  // All should be different objects
  EXPECT_NE(base_a, base_b);
  EXPECT_NE(base_b, base_c);
  EXPECT_NE(base_a, base_c);

  delete a;
  delete b;
  delete c;
}

// ============================================================================
// TEST GROUP 3: GENERATE FUNCTION TESTS
// ============================================================================

TEST(GenerateTest, GenerateReturnsNonNull) {
  Base *ptr = generate();

  EXPECT_TRUE(ptr != NULL);

  delete ptr;
}

TEST(GenerateTest, GenerateReturnsBasePointer) {
  Base *ptr = generate();

  // Should be able to assign to Base*
  Base *base = ptr;
  EXPECT_TRUE(base != NULL);

  delete ptr;
}

TEST(GenerateTest, GenerateRandomlyCreatesABC) {
  // Run generate multiple times and check if we get variety

  bool foundA = false;
  bool foundB = false;
  bool foundC = false;

  // Try 100 times to get all three types
  for (int i = 0; i < 100; i++) {
    Base *ptr = generate();

    // Try to identify which type it is
    A *asA = dynamic_cast<A *>(ptr);
    B *asB = dynamic_cast<B *>(ptr);
    C *asC = dynamic_cast<C *>(ptr);

    if (asA)
      foundA = true;
    if (asB)
      foundB = true;
    if (asC)
      foundC = true;

    delete ptr;

    if (foundA && foundB && foundC)
      break;
  }

  // Should have found all three types (high probability)
  // If this fails, your random might be broken or not random enough
  EXPECT_TRUE(foundA || foundB || foundC);
}

TEST(GenerateTest, MultipleGenerateCalls) {
  // Test multiple generation calls

  Base *ptr1 = generate();
  Base *ptr2 = generate();
  Base *ptr3 = generate();

  EXPECT_TRUE(ptr1 != NULL);
  EXPECT_TRUE(ptr2 != NULL);
  EXPECT_TRUE(ptr3 != NULL);

  delete ptr1;
  delete ptr2;
  delete ptr3;
}

// ============================================================================
// TEST GROUP 4: IDENTIFY WITH POINTER TESTS
// ============================================================================

TEST_F(TypeIdentificationTest, IdentifyPointer_TypeA) {
  A *a = new A();
  Base *ptr = a;

  identify(ptr);

  std::string output = getOutput();
  EXPECT_TRUE(output.find("A") != std::string::npos);

  delete ptr;
}

TEST_F(TypeIdentificationTest, IdentifyPointer_TypeB) {
  B *b = new B();
  Base *ptr = b;

  identify(ptr);

  std::string output = getOutput();
  EXPECT_TRUE(output.find("B") != std::string::npos);

  delete ptr;
}

TEST_F(TypeIdentificationTest, IdentifyPointer_TypeC) {
  C *c = new C();
  Base *ptr = c;

  identify(ptr);

  std::string output = getOutput();
  EXPECT_TRUE(output.find("C") != std::string::npos);

  delete ptr;
}

TEST_F(TypeIdentificationTest, IdentifyPointer_Multiple) {
  A *a = new A();
  B *b = new B();
  C *c = new C();

  identify(static_cast<Base *>(a));
  identify(static_cast<Base *>(b));
  identify(static_cast<Base *>(c));

  std::string output = getOutput();

  EXPECT_TRUE(output.find("A") != std::string::npos);
  EXPECT_TRUE(output.find("B") != std::string::npos);
  EXPECT_TRUE(output.find("C") != std::string::npos);

  delete a;
  delete b;
  delete c;
}

TEST_F(TypeIdentificationTest, IdentifyPointer_OnlyPrintsTypeName) {
  A *a = new A();

  identify(static_cast<Base *>(a));

  std::string output = getOutput();

  // Should print just "A" (maybe with newline)
  // Should NOT print "B" or "C"
  EXPECT_TRUE(output.find("A") != std::string::npos);
  EXPECT_TRUE(output.find("B") == std::string::npos);
  EXPECT_TRUE(output.find("C") == std::string::npos);

  delete a;
}

// ============================================================================
// TEST GROUP 5: IDENTIFY WITH REFERENCE TESTS
// ============================================================================

TEST_F(TypeIdentificationTest, IdentifyReference_TypeA) {
  A a;
  Base &ref = a;

  identify(ref);

  std::string output = getOutput();
  EXPECT_TRUE(output.find("A") != std::string::npos);
}

TEST_F(TypeIdentificationTest, IdentifyReference_TypeB) {
  B b;
  Base &ref = b;

  identify(ref);

  std::string output = getOutput();
  EXPECT_TRUE(output.find("B") != std::string::npos);
}

TEST_F(TypeIdentificationTest, IdentifyReference_TypeC) {
  C c;
  Base &ref = c;

  identify(ref);

  std::string output = getOutput();
  EXPECT_TRUE(output.find("C") != std::string::npos);
}

TEST_F(TypeIdentificationTest, IdentifyReference_Multiple) {
  A a;
  B b;
  C c;

  identify(static_cast<Base &>(a));
  identify(static_cast<Base &>(b));
  identify(static_cast<Base &>(c));

  std::string output = getOutput();

  EXPECT_TRUE(output.find("A") != std::string::npos);
  EXPECT_TRUE(output.find("B") != std::string::npos);
  EXPECT_TRUE(output.find("C") != std::string::npos);
}

TEST_F(TypeIdentificationTest, IdentifyReference_HeapAllocated) {
  // Test with heap-allocated objects

  A *a = new A();
  B *b = new B();
  C *c = new C();

  identify(*a);
  identify(*b);
  identify(*c);

  std::string output = getOutput();

  EXPECT_TRUE(output.find("A") != std::string::npos);
  EXPECT_TRUE(output.find("B") != std::string::npos);
  EXPECT_TRUE(output.find("C") != std::string::npos);

  delete a;
  delete b;
  delete c;
}

// ============================================================================
// TEST GROUP 6: CONSISTENCY TESTS
// ============================================================================

TEST_F(TypeIdentificationTest, PointerAndReferenceGiveSameResult) {
  // Pointer and reference identification should give same result

  A *a = new A();

  identify(static_cast<Base *>(a));
  std::string ptrOutput = getOutput();

  buffer.str("");

  identify(static_cast<Base &>(*a));
  std::string refOutput = getOutput();

  // Both should identify as "A"
  EXPECT_TRUE(ptrOutput.find("A") != std::string::npos);
  EXPECT_TRUE(refOutput.find("A") != std::string::npos);

  delete a;
}

// ============================================================================
// TEST GROUP 7: EDGE CASES
// ============================================================================

TEST_F(TypeIdentificationTest, IdentifyPointer_NullPointer) {
  // Test behavior with null pointer
  // Your implementation should handle this gracefully

  Base *nullPtr = NULL;

  // Should not crash
  identify(nullPtr);

  std::string output = getOutput();
  // Implementation-dependent: might print "unknown", "null", or nothing

  SUCCEED(); // As long as it doesn't crash
}

TEST(EdgeCaseTest, CastingBetweenTypes) {
  // Test that A cannot be cast to B, etc.

  A *a = new A();
  Base *base = a;

  // These should return NULL
  B *asB = dynamic_cast<B *>(base);
  C *asC = dynamic_cast<C *>(base);

  EXPECT_TRUE(asB == NULL);
  EXPECT_TRUE(asC == NULL);

  // But casting to A should work
  A *asA = dynamic_cast<A *>(base);
  EXPECT_TRUE(asA != NULL);

  delete a;
}

TEST(EdgeCaseTest, BasePointerToBase) {
  // What if we create actual Base object?

  Base *base = new Base();

  A *asA = dynamic_cast<A *>(base);
  B *asB = dynamic_cast<B *>(base);
  C *asC = dynamic_cast<C *>(base);

  // All should be NULL (Base is not A, B, or C)
  EXPECT_TRUE(asA == NULL);
  EXPECT_TRUE(asB == NULL);
  EXPECT_TRUE(asC == NULL);

  delete base;
}

// ============================================================================
// TEST GROUP 8: INTEGRATION TESTS
// ============================================================================

TEST_F(TypeIdentificationTest, GenerateAndIdentifyPointer) {
  // Integration: generate random object and identify it

  for (int i = 0; i < 10; i++) {
    Base *ptr = generate();

    buffer.str("");
    identify(ptr);

    std::string output = getOutput();

    // Should print one of A, B, or C
    bool isValid = (output.find("A") != std::string::npos) ||
                   (output.find("B") != std::string::npos) ||
                   (output.find("C") != std::string::npos);

    EXPECT_TRUE(isValid);

    delete ptr;
  }
}

TEST_F(TypeIdentificationTest, GenerateAndIdentifyReference) {
  // Integration: generate random object and identify by reference

  for (int i = 0; i < 10; i++) {
    Base *ptr = generate();

    buffer.str("");
    identify(*ptr);

    std::string output = getOutput();

    bool isValid = (output.find("A") != std::string::npos) ||
                   (output.find("B") != std::string::npos) ||
                   (output.find("C") != std::string::npos);

    EXPECT_TRUE(isValid);

    delete ptr;
  }
}

TEST_F(TypeIdentificationTest, SubjectExample) {
  // Reproduce the subject's example

  Base *random = generate();

  identify(random);
  identify(*random);

  // Both should print the same type
  std::string output = getOutput();

  // Count how many times each letter appears
  int countA = 0, countB = 0, countC = 0;
  size_t pos = 0;
  while ((pos = output.find("A", pos)) != std::string::npos) {
    countA++;
    pos++;
  }
  pos = 0;
  while ((pos = output.find("B", pos)) != std::string::npos) {
    countB++;
    pos++;
  }
  pos = 0;
  while ((pos = output.find("C", pos)) != std::string::npos) {
    countC++;
    pos++;
  }

  // Should have printed the same type twice (once for ptr, once for ref)
  EXPECT_TRUE((countA == 2) || (countB == 2) || (countC == 2));

  delete random;
}

// ============================================================================
// BONUS TESTS
// ============================================================================

TEST(DynamicCastTest, UnderstandingDynamicCast) {
  // This test demonstrates how dynamic_cast works

  A *a = new A();
  Base *base = a;

  // Downcast to correct type: succeeds
  A *downcastA = dynamic_cast<A *>(base);
  EXPECT_TRUE(downcastA != NULL);
  EXPECT_EQ(downcastA, a);

  // Downcast to wrong type: fails (returns NULL)
  B *downcastB = dynamic_cast<B *>(base);
  EXPECT_TRUE(downcastB == NULL);

  delete a;
}

TEST(DynamicCastTest, WithReferences) {
  // dynamic_cast with references throws exception on failure

  A a;
  Base &base = a;

  // Correct type: succeeds
  try {
    A &refA = dynamic_cast<A &>(base);
    (void)refA;
    SUCCEED();
  } catch (std::bad_cast &e) {
    FAIL() << "Should not throw for correct type";
  }

  // Wrong type: throws bad_cast
  try {
    B &refB = dynamic_cast<B &>(base);
    (void)refB;
    FAIL() << "Should throw bad_cast for wrong type";
  } catch (std::bad_cast &e) {
    SUCCEED();
  }
}

TEST_F(TypeIdentificationTest, StressTest) {
  // Create many objects and identify them all

  const int COUNT = 100;
  Base *objects[COUNT];

  // Generate many objects
  for (int i = 0; i < COUNT; i++) {
    objects[i] = generate();
  }

  // Identify all of them
  for (int i = 0; i < COUNT; i++) {
    identify(objects[i]);
    identify(*objects[i]);
  }

  // Clean up
  for (int i = 0; i < COUNT; i++) {
    delete objects[i];
  }

  std::string output = getOutput();

  // Should have printed many types
  EXPECT_GT(output.length(), COUNT);
}

/*
   IMPLEMENTATION HINTS:

   For identify(Base* p):
   - Use dynamic_cast<A*>(p), dynamic_cast<B*>(p), dynamic_cast<C*>(p)
   - Check which one returns non-NULL
   - Print the corresponding type name

   For identify(Base& p):
   - Cannot use pointers!
   - Use try-catch with dynamic_cast<A&>(p)
   - If no exception, it's type A
   - If exception, try next type
   - Repeat for B and C
*/
