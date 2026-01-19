/* ************************************************************************** */
/*                                                                            */
/*   TestModule02Ex02.cpp - Fixed Point with Operators                      */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include "../ex02/headers/Fixed.hpp"

class FixedEx02Test : public ::testing::Test {
protected:
    void SetUp() override {
        old_cout = std::cout.rdbuf(buffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(old_cout);
        buffer.str("");
        buffer.clear();
    }

    std::stringstream buffer;
    std::streambuf* old_cout;
};

// ============================================
// Comparison Operators - Greater Than
// ============================================

TEST_F(FixedEx02Test, GreaterThanTrue) {
    Fixed a(10.0f);
    Fixed b(5.0f);
    EXPECT_TRUE(a > b);
}

TEST_F(FixedEx02Test, GreaterThanFalse) {
    Fixed a(5.0f);
    Fixed b(10.0f);
    EXPECT_FALSE(a > b);
}

TEST_F(FixedEx02Test, GreaterThanEqualValues) {
    Fixed a(10.0f);
    Fixed b(10.0f);
    EXPECT_FALSE(a > b);
}

// ============================================
// Comparison Operators - Less Than
// ============================================

TEST_F(FixedEx02Test, LessThanTrue) {
    Fixed a(5.0f);
    Fixed b(10.0f);
    EXPECT_TRUE(a < b);
}

TEST_F(FixedEx02Test, LessThanFalse) {
    Fixed a(10.0f);
    Fixed b(5.0f);
    EXPECT_FALSE(a < b);
}

TEST_F(FixedEx02Test, LessThanEqualValues) {
    Fixed a(10.0f);
    Fixed b(10.0f);
    EXPECT_FALSE(a < b);
}

// ============================================
// Comparison Operators - Greater or Equal
// ============================================

TEST_F(FixedEx02Test, GreaterOrEqualGreater) {
    Fixed a(10.0f);
    Fixed b(5.0f);
    EXPECT_TRUE(a >= b);
}

TEST_F(FixedEx02Test, GreaterOrEqualEqual) {
    Fixed a(10.0f);
    Fixed b(10.0f);
    EXPECT_TRUE(a >= b);
}

TEST_F(FixedEx02Test, GreaterOrEqualLess) {
    Fixed a(5.0f);
    Fixed b(10.0f);
    EXPECT_FALSE(a >= b);
}

// ============================================
// Comparison Operators - Less or Equal
// ============================================

TEST_F(FixedEx02Test, LessOrEqualLess) {
    Fixed a(5.0f);
    Fixed b(10.0f);
    EXPECT_TRUE(a <= b);
}

TEST_F(FixedEx02Test, LessOrEqualEqual) {
    Fixed a(10.0f);
    Fixed b(10.0f);
    EXPECT_TRUE(a <= b);
}

TEST_F(FixedEx02Test, LessOrEqualGreater) {
    Fixed a(10.0f);
    Fixed b(5.0f);
    EXPECT_FALSE(a <= b);
}

// ============================================
// Comparison Operators - Equal
// ============================================

TEST_F(FixedEx02Test, EqualTrue) {
    Fixed a(42.0f);
    Fixed b(42.0f);
    EXPECT_TRUE(a == b);
}

TEST_F(FixedEx02Test, EqualFalse) {
    Fixed a(42.0f);
    Fixed b(41.0f);
    EXPECT_FALSE(a == b);
}

// ============================================
// Comparison Operators - Not Equal
// ============================================

TEST_F(FixedEx02Test, NotEqualTrue) {
    Fixed a(42.0f);
    Fixed b(41.0f);
    EXPECT_TRUE(a != b);
}

TEST_F(FixedEx02Test, NotEqualFalse) {
    Fixed a(42.0f);
    Fixed b(42.0f);
    EXPECT_FALSE(a != b);
}

// ============================================
// Arithmetic Operators - Addition
// ============================================

TEST_F(FixedEx02Test, AdditionPositive) {
    Fixed a(10.5f);
    Fixed b(5.5f);
    Fixed c = a + b;
    EXPECT_NEAR(c.toFloat(), 16.0f, 0.01f);
}

TEST_F(FixedEx02Test, AdditionWithZero) {
    Fixed a(10.0f);
    Fixed b(0);
    Fixed c = a + b;
    EXPECT_NEAR(c.toFloat(), 10.0f, 0.01f);
}

TEST_F(FixedEx02Test, AdditionNegative) {
    Fixed a(10.0f);
    Fixed b(-5.0f);
    Fixed c = a + b;
    EXPECT_NEAR(c.toFloat(), 5.0f, 0.01f);
}

// ============================================
// Arithmetic Operators - Subtraction
// ============================================

TEST_F(FixedEx02Test, SubtractionPositive) {
    Fixed a(10.5f);
    Fixed b(5.5f);
    Fixed c = a - b;
    EXPECT_NEAR(c.toFloat(), 5.0f, 0.01f);
}

TEST_F(FixedEx02Test, SubtractionResultNegative) {
    Fixed a(5.0f);
    Fixed b(10.0f);
    Fixed c = a - b;
    EXPECT_NEAR(c.toFloat(), -5.0f, 0.01f);
}

// ============================================
// Arithmetic Operators - Multiplication
// ============================================

TEST_F(FixedEx02Test, MultiplicationPositive) {
    Fixed a(5.0f);
    Fixed b(2.0f);
    Fixed c = a * b;
    EXPECT_NEAR(c.toFloat(), 10.0f, 0.01f);
}

TEST_F(FixedEx02Test, MultiplicationByZero) {
    Fixed a(5.0f);
    Fixed b(0);
    Fixed c = a * b;
    EXPECT_NEAR(c.toFloat(), 0.0f, 0.01f);
}

TEST_F(FixedEx02Test, MultiplicationFloat) {
    Fixed a(5.05f);
    Fixed b(2);
    Fixed c = a * b;
    EXPECT_NEAR(c.toFloat(), 10.1f, 0.1f);
}

// ============================================
// Arithmetic Operators - Division
// ============================================

TEST_F(FixedEx02Test, DivisionPositive) {
    Fixed a(10.0f);
    Fixed b(2.0f);
    Fixed c = a / b;
    EXPECT_NEAR(c.toFloat(), 5.0f, 0.01f);
}

TEST_F(FixedEx02Test, DivisionFloat) {
    Fixed a(10.0f);
    Fixed b(4.0f);
    Fixed c = a / b;
    EXPECT_NEAR(c.toFloat(), 2.5f, 0.01f);
}

// ============================================
// Increment/Decrement Operators - Pre-increment
// ============================================

TEST_F(FixedEx02Test, PreIncrementValue) {
    Fixed a(0);
    ++a;
    // Pre-increment should add smallest representable value (1/256)
    EXPECT_GT(a.toFloat(), 0.0f);
    EXPECT_NEAR(a.toFloat(), 1.0f / 256.0f, 0.001f);
}

TEST_F(FixedEx02Test, PreIncrementReturnsNewValue) {
    Fixed a(0);
    Fixed b = ++a;
    EXPECT_FLOAT_EQ(a.toFloat(), b.toFloat());
}

// ============================================
// Increment/Decrement Operators - Post-increment
// ============================================

TEST_F(FixedEx02Test, PostIncrementReturnsOldValue) {
    Fixed a(0);
    Fixed b = a++;
    EXPECT_FLOAT_EQ(b.toFloat(), 0.0f);
    EXPECT_GT(a.toFloat(), 0.0f);
}

TEST_F(FixedEx02Test, PostIncrementIncrementsValue) {
    Fixed a(0);
    a++;
    EXPECT_NEAR(a.toFloat(), 1.0f / 256.0f, 0.001f);
}

// ============================================
// Increment/Decrement Operators - Pre-decrement
// ============================================

TEST_F(FixedEx02Test, PreDecrementValue) {
    Fixed a(1.0f);
    --a;
    EXPECT_LT(a.toFloat(), 1.0f);
}

TEST_F(FixedEx02Test, PreDecrementReturnsNewValue) {
    Fixed a(1.0f);
    Fixed b = --a;
    EXPECT_FLOAT_EQ(a.toFloat(), b.toFloat());
}

// ============================================
// Increment/Decrement Operators - Post-decrement
// ============================================

TEST_F(FixedEx02Test, PostDecrementReturnsOldValue) {
    Fixed a(1.0f);
    Fixed b = a--;
    EXPECT_NEAR(b.toFloat(), 1.0f, 0.01f);
    EXPECT_LT(a.toFloat(), 1.0f);
}

// ============================================
// Static min/max Functions
// ============================================

TEST_F(FixedEx02Test, MinFunctionReturnsSmaller) {
    Fixed a(42.0f);
    Fixed b(21.0f);
    EXPECT_NEAR(Fixed::min(a, b).toFloat(), 21.0f, 0.01f);
}

TEST_F(FixedEx02Test, MinFunctionEqualValues) {
    Fixed a(42.0f);
    Fixed b(42.0f);
    EXPECT_NEAR(Fixed::min(a, b).toFloat(), 42.0f, 0.01f);
}

TEST_F(FixedEx02Test, MaxFunctionReturnsLarger) {
    Fixed a(42.0f);
    Fixed b(21.0f);
    EXPECT_NEAR(Fixed::max(a, b).toFloat(), 42.0f, 0.01f);
}

TEST_F(FixedEx02Test, MaxFunctionEqualValues) {
    Fixed a(42.0f);
    Fixed b(42.0f);
    EXPECT_NEAR(Fixed::max(a, b).toFloat(), 42.0f, 0.01f);
}

TEST_F(FixedEx02Test, MinConstFunction) {
    Fixed const a(42.0f);
    Fixed const b(21.0f);
    EXPECT_NEAR(Fixed::min(a, b).toFloat(), 21.0f, 0.01f);
}

TEST_F(FixedEx02Test, MaxConstFunction) {
    Fixed const a(42.0f);
    Fixed const b(21.0f);
    EXPECT_NEAR(Fixed::max(a, b).toFloat(), 42.0f, 0.01f);
}

// ============================================
// Subject Example Test
// ============================================

TEST_F(FixedEx02Test, SubjectExample) {
    Fixed a;
    Fixed const b(Fixed(5.05f) * Fixed(2));

    // a starts at 0
    EXPECT_FLOAT_EQ(a.toFloat(), 0.0f);

    // ++a increments by epsilon, returns new value
    Fixed preInc = ++a;
    EXPECT_GT(a.toFloat(), 0.0f);
    EXPECT_FLOAT_EQ(a.toFloat(), preInc.toFloat());

    // a++ returns old value, then increments
    float beforePost = a.toFloat();
    Fixed postInc = a++;
    EXPECT_FLOAT_EQ(postInc.toFloat(), beforePost);
    EXPECT_GT(a.toFloat(), beforePost);

    // b should be approximately 5.05 * 2 = 10.1
    EXPECT_NEAR(b.toFloat(), 10.1f, 0.1f);

    // max should return b (10.1 > ~0.008)
    EXPECT_NEAR(Fixed::max(a, b).toFloat(), b.toFloat(), 0.01f);
}
