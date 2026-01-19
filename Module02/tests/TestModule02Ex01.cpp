/* ************************************************************************** */
/*                                                                            */
/*   TestModule02Ex01.cpp - Fixed Point with Conversions                    */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include "../ex01/headers/Fixed.hpp"

class FixedEx01Test : public ::testing::Test {
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
// Integer Constructor Tests
// ============================================

TEST_F(FixedEx01Test, IntConstructorPositive) {
    Fixed const b(10);
    EXPECT_EQ(b.toInt(), 10);
}

TEST_F(FixedEx01Test, IntConstructorZero) {
    Fixed const b(0);
    EXPECT_EQ(b.toInt(), 0);
}

TEST_F(FixedEx01Test, IntConstructorNegative) {
    Fixed const b(-42);
    EXPECT_EQ(b.toInt(), -42);
}

TEST_F(FixedEx01Test, IntConstructorLargeValue) {
    Fixed const b(1000);
    EXPECT_EQ(b.toInt(), 1000);
}

// ============================================
// Float Constructor Tests
// ============================================

TEST_F(FixedEx01Test, FloatConstructorPositive) {
    Fixed const c(42.42f);
    EXPECT_NEAR(c.toFloat(), 42.42f, 0.01f);
}

TEST_F(FixedEx01Test, FloatConstructorZero) {
    Fixed const c(0.0f);
    EXPECT_FLOAT_EQ(c.toFloat(), 0.0f);
}

TEST_F(FixedEx01Test, FloatConstructorNegative) {
    Fixed const c(-42.42f);
    EXPECT_NEAR(c.toFloat(), -42.42f, 0.01f);
}

TEST_F(FixedEx01Test, FloatConstructorSmallValue) {
    Fixed const c(0.5f);
    EXPECT_NEAR(c.toFloat(), 0.5f, 0.01f);
}

// ============================================
// toInt Conversion Tests
// ============================================

TEST_F(FixedEx01Test, ToIntTruncatesFloat) {
    Fixed const c(42.99f);
    EXPECT_EQ(c.toInt(), 42);
}

TEST_F(FixedEx01Test, ToIntNegativeTruncates) {
    Fixed const c(-42.99f);
    EXPECT_EQ(c.toInt(), -42);
}

// ============================================
// toFloat Conversion Tests
// ============================================

TEST_F(FixedEx01Test, ToFloatPrecision) {
    Fixed const c(42.42f);
    float result = c.toFloat();
    EXPECT_NEAR(result, 42.42f, 0.01f);
}

TEST_F(FixedEx01Test, ToFloatFromInt) {
    Fixed const b(10);
    EXPECT_FLOAT_EQ(b.toFloat(), 10.0f);
}

// ============================================
// Insertion Operator Tests
// ============================================

TEST_F(FixedEx01Test, InsertionOperatorDefault) {
    Fixed a;
    std::stringstream ss;
    ss << a;
    EXPECT_TRUE(ss.str().find("0") != std::string::npos);
}

TEST_F(FixedEx01Test, InsertionOperatorInt) {
    Fixed const b(10);
    std::stringstream ss;
    ss << b;
    EXPECT_TRUE(ss.str().find("10") != std::string::npos);
}

TEST_F(FixedEx01Test, InsertionOperatorFloat) {
    Fixed const c(42.42f);
    std::stringstream ss;
    ss << c;
    std::string output = ss.str();
    EXPECT_TRUE(output.find("42.4") != std::string::npos);
}

TEST_F(FixedEx01Test, InsertionOperatorChained) {
    Fixed a;
    Fixed const b(10);
    std::stringstream ss;
    ss << a << " " << b;
    std::string output = ss.str();
    EXPECT_TRUE(output.find("0") != std::string::npos);
    EXPECT_TRUE(output.find("10") != std::string::npos);
}

// ============================================
// Copy and Assignment Tests
// ============================================

TEST_F(FixedEx01Test, CopyConstructorPreservesValue) {
    Fixed const b(10);
    Fixed const d(b);
    EXPECT_EQ(d.toInt(), 10);
}

TEST_F(FixedEx01Test, AssignmentOperatorPreservesValue) {
    Fixed a;
    a = Fixed(1234.4321f);
    EXPECT_NEAR(a.toFloat(), 1234.43f, 0.01f);
}

// ============================================
// Fixed-Point Precision Tests (8 fractional bits)
// ============================================

TEST_F(FixedEx01Test, FixedPointResolution) {
    // With 8 fractional bits, smallest representable increment is 1/256 = 0.00390625
    Fixed a(0);
    a.setRawBits(1);
    EXPECT_NEAR(a.toFloat(), 1.0f / 256.0f, 0.001f);
}

TEST_F(FixedEx01Test, FixedPointHalfValue) {
    Fixed a(0);
    a.setRawBits(128);  // 128/256 = 0.5
    EXPECT_NEAR(a.toFloat(), 0.5f, 0.001f);
}

// ============================================
// Subject Example Test
// ============================================

TEST_F(FixedEx01Test, SubjectExample) {
    Fixed a;
    Fixed const b(10);
    Fixed const c(42.42f);
    Fixed const d(b);
    a = Fixed(1234.4321f);

    EXPECT_NEAR(a.toFloat(), 1234.43f, 0.01f);
    EXPECT_EQ(a.toInt(), 1234);
    EXPECT_EQ(b.toInt(), 10);
    EXPECT_NEAR(c.toFloat(), 42.42f, 0.01f);
    EXPECT_EQ(d.toInt(), 10);
}
