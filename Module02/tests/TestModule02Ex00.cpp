/* ************************************************************************** */
/*                                                                            */
/*   TestModule02Ex00.cpp - Fixed Point Class Tests                         */
/*   Orthodox Canonical Form                                                 */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include "../ex00/headers/Fixed.hpp"

/*
   From subject:
   - Private members:
     * int to store fixed-point value
     * static const int for fractional bits (always 8)
   - Public members:
     * Default constructor (initializes to 0)
     * Copy constructor
     * Copy assignment operator
     * Destructor
     * int getRawBits(void) const
     * void setRawBits(int const raw)
*/

class FixedEx00Test : public ::testing::Test {
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
// Constructor/Destructor Message Tests
// ============================================

TEST_F(FixedEx00Test, DefaultConstructorPrintsMessage) {
    Fixed a;

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Default constructor") != std::string::npos ||
                output.find("constructor") != std::string::npos);
}

TEST_F(FixedEx00Test, CopyConstructorPrintsMessage) {
    Fixed a;
    buffer.str("");
    Fixed b(a);

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Copy constructor") != std::string::npos ||
                output.find("copy") != std::string::npos);
}

TEST_F(FixedEx00Test, AssignmentOperatorPrintsMessage) {
    Fixed a;
    Fixed b;
    buffer.str("");
    b = a;

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("assignment") != std::string::npos ||
                output.find("operator") != std::string::npos);
}

TEST_F(FixedEx00Test, DestructorPrintsMessage) {
    {
        Fixed a;
        buffer.str("");
    }

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Destructor") != std::string::npos ||
                output.find("destructor") != std::string::npos);
}

// ============================================
// getRawBits and setRawBits Tests
// ============================================

TEST_F(FixedEx00Test, DefaultConstructorInitializesToZero) {
    Fixed a;
    EXPECT_EQ(a.getRawBits(), 0);
}

TEST_F(FixedEx00Test, SetAndGetRawBits) {
    Fixed a;
    a.setRawBits(42);
    EXPECT_EQ(a.getRawBits(), 42);
}

TEST_F(FixedEx00Test, SetRawBitsNegativeValue) {
    Fixed a;
    a.setRawBits(-100);
    EXPECT_EQ(a.getRawBits(), -100);
}

TEST_F(FixedEx00Test, GetRawBitsPrintsMessage) {
    Fixed a;
    buffer.str("");
    a.getRawBits();

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("getRawBits") != std::string::npos);
}

// ============================================
// Copy Constructor Tests
// ============================================

TEST_F(FixedEx00Test, CopyConstructorCopiesValue) {
    Fixed a;
    a.setRawBits(100);
    Fixed b(a);
    EXPECT_EQ(b.getRawBits(), 100);
}

TEST_F(FixedEx00Test, CopyConstructorIndependentObjects) {
    Fixed a;
    a.setRawBits(50);
    Fixed b(a);
    a.setRawBits(999);
    EXPECT_EQ(b.getRawBits(), 50);
}

// ============================================
// Assignment Operator Tests
// ============================================

TEST_F(FixedEx00Test, AssignmentOperatorCopiesValue) {
    Fixed a;
    Fixed b;
    a.setRawBits(200);
    b = a;
    EXPECT_EQ(b.getRawBits(), 200);
}

TEST_F(FixedEx00Test, AssignmentOperatorIndependentObjects) {
    Fixed a;
    Fixed b;
    a.setRawBits(300);
    b = a;
    a.setRawBits(999);
    EXPECT_EQ(b.getRawBits(), 300);
}

TEST_F(FixedEx00Test, SelfAssignment) {
    Fixed a;
    a.setRawBits(50);
    a = a;
    EXPECT_EQ(a.getRawBits(), 50);
}

TEST_F(FixedEx00Test, ChainedAssignment) {
    Fixed a;
    Fixed b;
    Fixed c;
    a.setRawBits(777);
    c = b = a;
    EXPECT_EQ(b.getRawBits(), 777);
    EXPECT_EQ(c.getRawBits(), 777);
}

// ============================================
// Subject Example Test
// ============================================

TEST_F(FixedEx00Test, SubjectExample) {
    Fixed a;
    Fixed b(a);
    Fixed c;
    c = b;

    EXPECT_EQ(a.getRawBits(), 0);
    EXPECT_EQ(b.getRawBits(), 0);
    EXPECT_EQ(c.getRawBits(), 0);
}
