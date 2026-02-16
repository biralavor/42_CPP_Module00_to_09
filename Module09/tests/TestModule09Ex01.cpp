/* ************************************************************************** */
/*   TestModule09Ex01.cpp - RPN (Reverse Polish Notation) Tests              */
/*   Stack-based expression evaluation                                       */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../ex01/headers/RPN.hpp"
#include "../ex01/headers/utils.hpp"

// ============================================
// Utils - isOperator Tests
// ============================================

TEST(UtilsOperatorTest, ValidOperators) {
    EXPECT_TRUE(isOperator('+'));
    EXPECT_TRUE(isOperator('-'));
    EXPECT_TRUE(isOperator('*'));
    EXPECT_TRUE(isOperator('/'));
}

TEST(UtilsOperatorTest, InvalidOperators) {
    EXPECT_FALSE(isOperator('1'));
    EXPECT_FALSE(isOperator(' '));
    EXPECT_FALSE(isOperator('('));
    EXPECT_FALSE(isOperator('a'));
}

// ============================================
// Utils - isDoubleDigit Tests
// ============================================

TEST(UtilsDoubleDigitTest, HasDoubleDigit) {
    EXPECT_TRUE(isDoubleDigit("10 5 +"));
    EXPECT_TRUE(isDoubleDigit("99 1 +"));
    EXPECT_TRUE(isDoubleDigit("1 23 +"));
    EXPECT_TRUE(isDoubleDigit("100 2 +"));
}

TEST(UtilsDoubleDigitTest, NoDoubleDigit) {
    EXPECT_FALSE(isDoubleDigit("1 2 +"));
    EXPECT_FALSE(isDoubleDigit("8 9 * 9 - 9 - 9 - 4 - 1 +"));
    EXPECT_FALSE(isDoubleDigit("0 0 +"));
    EXPECT_FALSE(isDoubleDigit("9 1 -"));
}

TEST(UtilsDoubleDigitTest, DigitsAtEnd) {
    EXPECT_TRUE(isDoubleDigit("1 + 55"));
    EXPECT_FALSE(isDoubleDigit("1 + 5"));
}

// ============================================
// Utils - areOperationsValid Tests
// ============================================

TEST(UtilsOpsValidTest, ValidExpressions) {
    char bad = '\0';
    EXPECT_TRUE(areOperationsValid("1 2 +", bad));
    EXPECT_TRUE(areOperationsValid("8 9 * 9 -", bad));
    EXPECT_TRUE(areOperationsValid("1 2 + 3 * 4 /", bad));
    EXPECT_TRUE(areOperationsValid("0 0 +", bad));
}

TEST(UtilsOpsValidTest, InvalidCharacters) {
    char bad = '\0';
    EXPECT_FALSE(areOperationsValid("(1 + 1)", bad));
    EXPECT_EQ(bad, '(');
    EXPECT_FALSE(areOperationsValid("1 2 &", bad));
    EXPECT_EQ(bad, '&');
    EXPECT_FALSE(areOperationsValid("1 2 ^", bad));
    EXPECT_EQ(bad, '^');
    EXPECT_FALSE(areOperationsValid("a b +", bad));
    EXPECT_EQ(bad, 'a');
    EXPECT_FALSE(areOperationsValid("1 2 %", bad));
    EXPECT_EQ(bad, '%');
}

TEST(UtilsOpsValidTest, SpacesAndDigitsOnly) {
    char bad = '\0';
    EXPECT_TRUE(areOperationsValid("1 2 3", bad));
    EXPECT_TRUE(areOperationsValid("   ", bad));
}

// ============================================
// Utils - areTotalOperationsValid Tests
// ============================================

TEST(UtilsTotalOpsTest, ValidCount) {
    EXPECT_TRUE(areTotalOperationsValid("1 2 +"));
    EXPECT_TRUE(areTotalOperationsValid("8 9 * 9 - 9 - 9 - 4 - 1 +"));
    EXPECT_TRUE(areTotalOperationsValid("1 2 + 3 *"));
    EXPECT_TRUE(areTotalOperationsValid("5 1 2 + 4 * + 3 -"));
}

TEST(UtilsTotalOpsTest, TooManyOperands) {
    EXPECT_FALSE(areTotalOperationsValid("1 2 3 +"));
    EXPECT_FALSE(areTotalOperationsValid("1 2 3 4 +"));
}

TEST(UtilsTotalOpsTest, ValidThreeNumbers) {
    EXPECT_TRUE(areTotalOperationsValid("5 5 5 + +"));
}

TEST(UtilsTotalOpsTest, TooManyOperators) {
    EXPECT_FALSE(areTotalOperationsValid("1 + +"));
    EXPECT_FALSE(areTotalOperationsValid("1 2 + + +"));
}

TEST(UtilsTotalOpsTest, SingleNumber) {
    EXPECT_FALSE(areTotalOperationsValid("5"));
}

// ============================================
// RPN - Subject Examples
// ============================================

TEST(RPNSubjectTest, Example1) {
    RPN rpn("8 9 * 9 - 9 - 9 - 4 - 1 +");
    EXPECT_EQ(rpn.evaluate(), 42);
}

TEST(RPNSubjectTest, Example2) {
    RPN rpn("7 7 * 7 -");
    EXPECT_EQ(rpn.evaluate(), 42);
}

TEST(RPNSubjectTest, Example3) {
    RPN rpn("1 2 * 2 / 2 * 2 4 - +");
    EXPECT_EQ(rpn.evaluate(), 0);
}

TEST(RPNSubjectTest, BracketsError) {
    EXPECT_THROW(RPN rpn("(1 + 1)"), std::exception);
}

// ============================================
// RPN - Basic Operations
// ============================================

TEST(RPNOperationTest, Addition) {
    RPN rpn("3 4 +");
    EXPECT_EQ(rpn.evaluate(), 7);
}

TEST(RPNOperationTest, Subtraction) {
    RPN rpn("9 3 -");
    EXPECT_EQ(rpn.evaluate(), 6);
}

TEST(RPNOperationTest, Multiplication) {
    RPN rpn("3 4 *");
    EXPECT_EQ(rpn.evaluate(), 12);
}

TEST(RPNOperationTest, Division) {
    RPN rpn("8 4 /");
    EXPECT_EQ(rpn.evaluate(), 2);
}

TEST(RPNOperationTest, IntegerDivision) {
    RPN rpn("5 2 /");
    EXPECT_EQ(rpn.evaluate(), 2);
}

// ============================================
// RPN - Complex Expressions
// ============================================

TEST(RPNComplexTest, MultipleOperations) {
    RPN rpn("5 1 2 + 4 * + 3 -");
    EXPECT_EQ(rpn.evaluate(), 14);
}

TEST(RPNComplexTest, ChainedAddition) {
    RPN rpn("1 2 + 3 + 4 +");
    EXPECT_EQ(rpn.evaluate(), 10);
}

TEST(RPNComplexTest, ChainedMultiplication) {
    RPN rpn("2 3 * 4 *");
    EXPECT_EQ(rpn.evaluate(), 24);
}

// ============================================
// RPN - Error Handling
// ============================================

TEST(RPNErrorTest, EmptyExpression) {
    EXPECT_THROW(RPN rpn(""), std::exception);
}

TEST(RPNErrorTest, InvalidCharacter) {
    EXPECT_THROW(RPN rpn("1 2 &"), std::exception);
}

TEST(RPNErrorTest, DoubleDigitNumber) {
    EXPECT_THROW(RPN rpn("10 5 +"), std::exception);
    EXPECT_THROW(RPN rpn("99 1 +"), std::exception);
}

TEST(RPNErrorTest, TooManyOperands) {
    EXPECT_THROW(RPN rpn("1 2 3 +"), std::exception);
}

TEST(RPNErrorTest, OperatorBeforeOperands) {
    RPN rpn("+ 1 2");
    EXPECT_THROW(rpn.evaluate(), std::exception);
}

TEST(RPNErrorTest, DivisionByZero) {
    RPN rpn("5 0 /");
    EXPECT_THROW(rpn.evaluate(), std::exception);
}

// ============================================
// RPN - Edge Cases
// ============================================

TEST(RPNEdgeTest, ZeroOperations) {
    RPN rpn("0 0 +");
    EXPECT_EQ(rpn.evaluate(), 0);
}

TEST(RPNEdgeTest, NegativeResult) {
    RPN rpn("1 5 -");
    EXPECT_EQ(rpn.evaluate(), -4);
}

TEST(RPNEdgeTest, ZeroMultiplication) {
    RPN rpn("0 5 *");
    EXPECT_EQ(rpn.evaluate(), 0);
}

TEST(RPNEdgeTest, ZeroDividedByNumber) {
    RPN rpn("0 5 /");
    EXPECT_EQ(rpn.evaluate(), 0);
}
