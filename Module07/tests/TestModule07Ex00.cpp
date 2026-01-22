/* ************************************************************************** */
/*                                                                            */
/*   TestModule07Ex00.cpp - Function Templates: swap, min, max                */
/*   Templates - Generic Programming                                          */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <string>
#include "../ex00/headers/Whatever.hpp"

// ============================================
// Swap Tests - Integer
// ============================================

TEST(SwapTest, SwapIntegers) {
    int a = 2;
    int b = 3;

    ::swap(a, b);

    EXPECT_EQ(a, 3);
    EXPECT_EQ(b, 2);
}

TEST(SwapTest, SwapNegativeIntegers) {
    int a = -10;
    int b = 20;

    ::swap(a, b);

    EXPECT_EQ(a, 20);
    EXPECT_EQ(b, -10);
}

TEST(SwapTest, SwapSameIntegers) {
    int a = 5;
    int b = 5;

    ::swap(a, b);

    EXPECT_EQ(a, 5);
    EXPECT_EQ(b, 5);
}

// ============================================
// Swap Tests - Other Types
// ============================================

TEST(SwapTest, SwapDoubles) {
    double a = 3.14;
    double b = 2.71;

    ::swap(a, b);

    EXPECT_DOUBLE_EQ(a, 2.71);
    EXPECT_DOUBLE_EQ(b, 3.14);
}

TEST(SwapTest, SwapStrings) {
    std::string a = "hello";
    std::string b = "world";

    ::swap(a, b);

    EXPECT_EQ(a, "world");
    EXPECT_EQ(b, "hello");
}

TEST(SwapTest, SwapChars) {
    char a = 'X';
    char b = 'Y';

    ::swap(a, b);

    EXPECT_EQ(a, 'Y');
    EXPECT_EQ(b, 'X');
}

// ============================================
// Min Tests - Integer
// ============================================

TEST(MinTest, MinWithDifferentIntegers) {
    int a = 2;
    int b = 3;

    EXPECT_EQ(::min(a, b), 2);
}

TEST(MinTest, MinWithEqualIntegers) {
    int a = 5;
    int b = 5;

    // When equal, returns second argument (reference)
    EXPECT_EQ(&::min(a, b), &b);
}

TEST(MinTest, MinWithNegativeIntegers) {
    int a = -10;
    int b = -5;

    EXPECT_EQ(::min(a, b), -10);
}

TEST(MinTest, MinFirstSmaller) {
    int a = 1;
    int b = 100;

    EXPECT_EQ(::min(a, b), 1);
}

TEST(MinTest, MinSecondSmaller) {
    int a = 100;
    int b = 1;

    EXPECT_EQ(::min(a, b), 1);
}

// ============================================
// Min Tests - Other Types
// ============================================

TEST(MinTest, MinDoubles) {
    double a = 3.14;
    double b = 2.71;

    EXPECT_DOUBLE_EQ(::min(a, b), 2.71);
}

TEST(MinTest, MinStrings) {
    std::string a = "abc";
    std::string b = "xyz";

    // Lexicographic comparison
    EXPECT_EQ(::min(a, b), "abc");
}

TEST(MinTest, MinChars) {
    char a = 'a';
    char b = 'z';

    EXPECT_EQ(::min(a, b), 'a');
}

// ============================================
// Max Tests - Integer
// ============================================

TEST(MaxTest, MaxWithDifferentIntegers) {
    int a = 2;
    int b = 3;

    EXPECT_EQ(::max(a, b), 3);
}

TEST(MaxTest, MaxWithEqualIntegers) {
    int a = 5;
    int b = 5;

    // When equal, returns second argument (reference)
    EXPECT_EQ(&::max(a, b), &b);
}

TEST(MaxTest, MaxWithNegativeIntegers) {
    int a = -10;
    int b = -5;

    EXPECT_EQ(::max(a, b), -5);
}

TEST(MaxTest, MaxFirstLarger) {
    int a = 100;
    int b = 1;

    EXPECT_EQ(::max(a, b), 100);
}

TEST(MaxTest, MaxSecondLarger) {
    int a = 1;
    int b = 100;

    EXPECT_EQ(::max(a, b), 100);
}

// ============================================
// Max Tests - Other Types
// ============================================

TEST(MaxTest, MaxDoubles) {
    double a = 3.14;
    double b = 2.71;

    EXPECT_DOUBLE_EQ(::max(a, b), 3.14);
}

TEST(MaxTest, MaxStrings) {
    std::string a = "abc";
    std::string b = "xyz";

    // Lexicographic comparison
    EXPECT_EQ(::max(a, b), "xyz");
}

TEST(MaxTest, MaxChars) {
    char a = 'a';
    char b = 'z';

    EXPECT_EQ(::max(a, b), 'z');
}

// ============================================
// Subject PDF Example Test
// ============================================

TEST(SubjectExampleTest, ExactSubjectExample) {
    int a = 2;
    int b = 3;

    ::swap(a, b);
    EXPECT_EQ(a, 3);
    EXPECT_EQ(b, 2);

    EXPECT_EQ(::min(a, b), 2);
    EXPECT_EQ(::max(a, b), 3);

    std::string c = "chaine1";
    std::string d = "chaine2";

    ::swap(c, d);
    EXPECT_EQ(c, "chaine2");
    EXPECT_EQ(d, "chaine1");

    EXPECT_EQ(::min(c, d), "chaine1");
    EXPECT_EQ(::max(c, d), "chaine2");
}

// ============================================
// Reference Return Tests
// ============================================

TEST(ReferenceTest, MinReturnsReference) {
    int a = 5;
    int b = 10;

    int& result = ::min(a, b);
    result = 100;

    EXPECT_EQ(a, 100);  // a was modified through reference
}

TEST(ReferenceTest, MaxReturnsReference) {
    int a = 5;
    int b = 10;

    int& result = ::max(a, b);
    result = 100;

    EXPECT_EQ(b, 100);  // b was modified through reference
}
