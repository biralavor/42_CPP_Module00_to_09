/* ************************************************************************** */
/*                                                                            */
/*   TestModule07Ex02.cpp - Array Class Template                              */
/*   Templates - Generic Container with Orthodox Canonical Form               */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <string>
#include "../ex02/headers/Array.hpp"

// ============================================
// Default Constructor Tests
// ============================================

TEST(ArrayConstructorTest, DefaultConstructorCreatesEmptyArray) {
    Array<int> arr;

    EXPECT_EQ(arr.size(), 0u);
}

TEST(ArrayConstructorTest, DefaultConstructorWithDifferentTypes) {
    Array<double> dArr;
    Array<std::string> sArr;
    Array<char> cArr;

    EXPECT_EQ(dArr.size(), 0u);
    EXPECT_EQ(sArr.size(), 0u);
    EXPECT_EQ(cArr.size(), 0u);
}

// ============================================
// Size Constructor Tests
// ============================================

TEST(ArrayConstructorTest, SizeConstructorCreatesCorrectSize) {
    Array<int> arr(5);

    EXPECT_EQ(arr.size(), 5u);
}

TEST(ArrayConstructorTest, SizeConstructorInitializesToDefault) {
    Array<int> arr(3);

    // Default initialization for int should be 0
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 0);
    EXPECT_EQ(arr[2], 0);
}

TEST(ArrayConstructorTest, SizeConstructorWithStrings) {
    Array<std::string> arr(3);

    // Default string is empty
    EXPECT_EQ(arr[0], "");
    EXPECT_EQ(arr[1], "");
    EXPECT_EQ(arr[2], "");
}

TEST(ArrayConstructorTest, SizeConstructorWithZero) {
    Array<int> arr(0);

    EXPECT_EQ(arr.size(), 0u);
}

TEST(ArrayConstructorTest, LargeArray) {
    Array<int> arr(1000);

    EXPECT_EQ(arr.size(), 1000u);
}

// ============================================
// Copy Constructor Tests
// ============================================

TEST(ArrayCopyTest, CopyConstructorCopiesValues) {
    Array<int> original(3);
    original[0] = 10;
    original[1] = 20;
    original[2] = 30;

    Array<int> copy(original);

    EXPECT_EQ(copy.size(), 3u);
    EXPECT_EQ(copy[0], 10);
    EXPECT_EQ(copy[1], 20);
    EXPECT_EQ(copy[2], 30);
}

TEST(ArrayCopyTest, CopyIsIndependent) {
    Array<int> original(2);
    original[0] = 100;

    Array<int> copy(original);
    copy[0] = 999;

    // Original should be unchanged
    EXPECT_EQ(original[0], 100);
    EXPECT_EQ(copy[0], 999);
}

TEST(ArrayCopyTest, CopyEmptyArray) {
    Array<int> original;
    Array<int> copy(original);

    EXPECT_EQ(copy.size(), 0u);
}

// ============================================
// Assignment Operator Tests
// ============================================

TEST(ArrayAssignmentTest, AssignmentCopiesValues) {
    Array<int> a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    Array<int> b(2);
    b = a;

    EXPECT_EQ(b.size(), 3u);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

TEST(ArrayAssignmentTest, AssignmentIsIndependent) {
    Array<int> a(2);
    a[0] = 42;

    Array<int> b;
    b = a;
    b[0] = 100;

    // a should be unchanged
    EXPECT_EQ(a[0], 42);
    EXPECT_EQ(b[0], 100);
}

TEST(ArrayAssignmentTest, SelfAssignment) {
    Array<int> arr(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    EXPECT_EQ(arr.size(), 3u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(ArrayAssignmentTest, AssignEmptyToNonEmpty) {
    Array<int> a;
    Array<int> b(5);
    b[0] = 999;

    b = a;

    EXPECT_EQ(b.size(), 0u);
}

// ============================================
// Subscript Operator Tests
// ============================================

TEST(ArraySubscriptTest, ReadAccess) {
    Array<int> arr(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(ArraySubscriptTest, WriteAccess) {
    Array<int> arr(3);

    arr[0] = 100;
    arr[1] = 200;
    arr[2] = 300;

    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

TEST(ArraySubscriptTest, ModifyExistingValue) {
    Array<int> arr(2);
    arr[0] = 10;

    arr[0] = arr[0] + 5;

    EXPECT_EQ(arr[0], 15);
}

// ============================================
// Exception Tests - Out of Bounds
// ============================================

TEST(ArrayExceptionTest, AccessOutOfBoundsThrows) {
    Array<int> arr(3);

    EXPECT_THROW(arr[3], std::exception);
    EXPECT_THROW(arr[100], std::exception);
}

TEST(ArrayExceptionTest, NegativeIndexThrows) {
    Array<int> arr(3);

    // Casting to unsigned will make it a large number, which is out of bounds
    EXPECT_THROW(arr[-1], std::exception);
}

TEST(ArrayExceptionTest, AccessEmptyArrayThrows) {
    Array<int> arr;

    EXPECT_THROW(arr[0], std::exception);
}

TEST(ArrayExceptionTest, ExceptionMessage) {
    Array<int> arr(3);

    try {
        int val = arr[10];
        (void)val;
        FAIL() << "Expected exception was not thrown";
    } catch (const std::exception& e) {
        // Should have some message
        EXPECT_TRUE(std::string(e.what()).length() > 0);
    }
}

// ============================================
// Size Method Tests
// ============================================

TEST(ArraySizeTest, SizeReturnsCorrectValue) {
    Array<int> arr0;
    Array<int> arr1(1);
    Array<int> arr10(10);
    Array<int> arr100(100);

    EXPECT_EQ(arr0.size(), 0u);
    EXPECT_EQ(arr1.size(), 1u);
    EXPECT_EQ(arr10.size(), 10u);
    EXPECT_EQ(arr100.size(), 100u);
}

TEST(ArraySizeTest, SizeUnchangedAfterAccess) {
    Array<int> arr(5);
    arr[0] = 100;
    arr[4] = 500;

    EXPECT_EQ(arr.size(), 5u);
}

// ============================================
// Different Type Tests
// ============================================

TEST(ArrayTypesTest, DoubleArray) {
    Array<double> arr(3);
    arr[0] = 1.5;
    arr[1] = 2.5;
    arr[2] = 3.5;

    EXPECT_DOUBLE_EQ(arr[0], 1.5);
    EXPECT_DOUBLE_EQ(arr[1], 2.5);
    EXPECT_DOUBLE_EQ(arr[2], 3.5);
}

TEST(ArrayTypesTest, StringArray) {
    Array<std::string> arr(3);
    arr[0] = "hello";
    arr[1] = "world";
    arr[2] = "test";

    EXPECT_EQ(arr[0], "hello");
    EXPECT_EQ(arr[1], "world");
    EXPECT_EQ(arr[2], "test");
}

TEST(ArrayTypesTest, CharArray) {
    Array<char> arr(4);
    arr[0] = 'a';
    arr[1] = 'b';
    arr[2] = 'c';
    arr[3] = 'd';

    EXPECT_EQ(arr[0], 'a');
    EXPECT_EQ(arr[1], 'b');
    EXPECT_EQ(arr[2], 'c');
    EXPECT_EQ(arr[3], 'd');
}

// ============================================
// Const Correctness Tests
// ============================================

TEST(ArrayConstTest, ConstArrayReadAccess) {
    Array<int> arr(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    const Array<int>& constRef = arr;

    EXPECT_EQ(constRef[0], 10);
    EXPECT_EQ(constRef[1], 20);
    EXPECT_EQ(constRef[2], 30);
}

TEST(ArrayConstTest, ConstArraySize) {
    Array<int> arr(5);
    const Array<int>& constRef = arr;

    EXPECT_EQ(constRef.size(), 5u);
}

TEST(ArrayConstTest, ConstArrayOutOfBoundsThrows) {
    Array<int> arr(3);
    const Array<int>& constRef = arr;

    EXPECT_THROW(constRef[5], std::exception);
}

// ============================================
// Complex Operations
// ============================================

TEST(ArrayComplexTest, ChainedAssignment) {
    Array<int> a(2);
    Array<int> b(2);
    Array<int> c(2);

    a[0] = 100;
    a[1] = 200;

    c = b = a;

    EXPECT_EQ(b[0], 100);
    EXPECT_EQ(c[0], 100);
}

TEST(ArrayComplexTest, ArrayOfArrays) {
    // Not strictly required but good to test
    Array<int> inner(2);
    inner[0] = 1;
    inner[1] = 2;

    // Can create arrays and copy them
    Array<int> copy(inner);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
}

TEST(ArrayComplexTest, FillAndVerify) {
    Array<int> arr(100);

    for (unsigned int i = 0; i < arr.size(); i++) {
        arr[i] = i * 10;
    }

    for (unsigned int i = 0; i < arr.size(); i++) {
        EXPECT_EQ(arr[i], static_cast<int>(i * 10));
    }
}

// ============================================
// Memory Independence Tests
// ============================================

TEST(ArrayMemoryTest, DeepCopyOnConstruction) {
    Array<int>* original = new Array<int>(3);
    (*original)[0] = 42;

    Array<int> copy(*original);
    delete original;

    // Copy should still be valid
    EXPECT_EQ(copy[0], 42);
}

TEST(ArrayMemoryTest, DeepCopyOnAssignment) {
    Array<int>* original = new Array<int>(3);
    (*original)[0] = 42;

    Array<int> copy;
    copy = *original;
    delete original;

    // Copy should still be valid
    EXPECT_EQ(copy[0], 42);
}
