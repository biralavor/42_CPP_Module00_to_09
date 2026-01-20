/* ************************************************************************** */
/*   TestModule09Ex01.cpp - RPN (Reverse Polish Notation) Tests               */
/*   Stack-based expression evaluation                                        */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../ex01/RPN.hpp"

// ============================================
// Subject Examples Tests
// ============================================

TEST(RPNSubjectTest, Example1) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("8 9 * 9 - 9 - 9 - 4 - 1 +"), 42);
}

TEST(RPNSubjectTest, Example2) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("7 7 * 7 -"), 42);
}

TEST(RPNSubjectTest, Example3) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("1 2 * 2 / 2 * 2 4 - +"), 0);
}

TEST(RPNSubjectTest, BracketsError) {
    RPN rpn;
    EXPECT_THROW(rpn.evaluate("(1 + 1)"), std::exception);
}

// ============================================
// Basic Operations Tests
// ============================================

TEST(RPNOperationTest, Addition) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("3 4 +"), 7);
    EXPECT_EQ(rpn.evaluate("1 1 +"), 2);
    EXPECT_EQ(rpn.evaluate("0 5 +"), 5);
}

TEST(RPNOperationTest, Subtraction) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("9 3 -"), 6);
    EXPECT_EQ(rpn.evaluate("5 5 -"), 0);
    EXPECT_EQ(rpn.evaluate("3 9 -"), -6);
}

TEST(RPNOperationTest, Multiplication) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("3 4 *"), 12);
    EXPECT_EQ(rpn.evaluate("0 9 *"), 0);
    EXPECT_EQ(rpn.evaluate("1 7 *"), 7);
}

TEST(RPNOperationTest, Division) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("8 4 /"), 2);
    EXPECT_EQ(rpn.evaluate("9 3 /"), 3);
    EXPECT_EQ(rpn.evaluate("5 2 /"), 2);  // Integer division
}

// ============================================
// Complex Expression Tests
// ============================================

TEST(RPNComplexTest, MultipleOperations) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("5 1 2 + 4 * + 3 -"), 14);
    // 5 + ((1 + 2) * 4) - 3 = 5 + 12 - 3 = 14
}

TEST(RPNComplexTest, ChainedAddition) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("1 2 + 3 + 4 +"), 10);
}

TEST(RPNComplexTest, ChainedMultiplication) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("2 3 * 4 *"), 24);
}

// ============================================
// Error Handling Tests
// ============================================

TEST(RPNErrorTest, EmptyExpression) {
    RPN rpn;
    EXPECT_THROW(rpn.evaluate(""), std::exception);
}

TEST(RPNErrorTest, InvalidCharacter) {
    RPN rpn;
    EXPECT_THROW(rpn.evaluate("1 2 &"), std::exception);
    EXPECT_THROW(rpn.evaluate("a b +"), std::exception);
}

TEST(RPNErrorTest, NotEnoughOperands) {
    RPN rpn;
    EXPECT_THROW(rpn.evaluate("1 +"), std::exception);
    EXPECT_THROW(rpn.evaluate("+"), std::exception);
}

TEST(RPNErrorTest, TooManyOperands) {
    RPN rpn;
    EXPECT_THROW(rpn.evaluate("1 2 3 +"), std::exception);
}

TEST(RPNErrorTest, DivisionByZero) {
    RPN rpn;
    EXPECT_THROW(rpn.evaluate("5 0 /"), std::exception);
}

TEST(RPNErrorTest, NumberGreaterThan9) {
    RPN rpn;
    // Numbers must be < 10 as per subject
    EXPECT_THROW(rpn.evaluate("10 5 +"), std::exception);
    EXPECT_THROW(rpn.evaluate("99 1 +"), std::exception);
}

// ============================================
// Edge Cases Tests
// ============================================

TEST(RPNEdgeTest, SingleDigitResult) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("9 1 -"), 8);
}

TEST(RPNEdgeTest, ZeroOperations) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("0 0 +"), 0);
    EXPECT_EQ(rpn.evaluate("0 5 *"), 0);
}

TEST(RPNEdgeTest, NegativeResult) {
    RPN rpn;
    EXPECT_EQ(rpn.evaluate("1 5 -"), -4);
}

// ============================================
// Orthodox Canonical Form Tests
// ============================================

TEST(RPNOCFTest, CopyConstructor) {
    RPN original;
    RPN copy(original);
    EXPECT_EQ(copy.evaluate("2 3 +"), 5);
}

TEST(RPNOCFTest, AssignmentOperator) {
    RPN a;
    RPN b;
    b = a;
    EXPECT_EQ(b.evaluate("4 2 *"), 8);
}
