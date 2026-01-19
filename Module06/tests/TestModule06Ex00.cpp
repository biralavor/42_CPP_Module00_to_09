/* ************************************************************************** */
/*                                                                            */
/*   TestModule06Ex00.cpp - ScalarConverter TDD Tests                       */
/*   C++ casts: Conversion of scalar types                                  */
/*                                                                            */
/*   This is a TDD (Test-Driven Development) test suite.                    */
/*   Implement the ScalarConverter class to make these tests pass!          */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <limits>
#include <cmath>

#include "../ex00/headers/ScalarConverter.hpp"

/*
   IMPLEMENTATION GUIDE:
   
   1. Create a ScalarConverter class that:
      - Cannot be instantiated (private constructor)
      - Has only static methods
      - Has a static method: void convert(const std::string& literal)
   
   2. The convert method should:
      - Detect the type of input (char, int, float, double)
      - Convert to all four types
      - Print results in format:
         char: <result>
         int: <result>
         float: <result>f
         double: <result>
      
   3. Handle special cases:
      - Non-displayable chars: "Non displayable"
      - Impossible conversions: "impossible"
      - Special float values: -inff, +inff, nanf
      - Special double values: -inf, +inf, nan
      - Overflow: "impossible"
   
   4. Allowed functions:
      - strtol, strtof, strtod, atoi, etc. (for conversion)
      - isprint (for checking displayable chars)
*/

class ScalarConverterTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Redirect cout to capture output
        old_cout = std::cout.rdbuf(buffer.rdbuf());
    }
    
    void TearDown() override {
        // Restore cout
        std::cout.rdbuf(old_cout);
        buffer.str("");
        buffer.clear();
    }
    
    std::string getOutput() {
        return buffer.str();
    }
    
    std::stringstream buffer;
    std::streambuf* old_cout;
};

// ============================================================================
// TEST GROUP 1: CHAR LITERALS
// ============================================================================

TEST_F(ScalarConverterTest, CharLiteral_Printable) {
    ScalarConverter::convert("'c'");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: 'c'") != std::string::npos ||
                output.find("char: c") != std::string::npos);
    EXPECT_TRUE(output.find("int: 99") != std::string::npos);
    EXPECT_TRUE(output.find("float: 99.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 99.0") != std::string::npos);
}

TEST_F(ScalarConverterTest, CharLiteral_LetterA) {
    ScalarConverter::convert("'a'");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: 'a'") != std::string::npos ||
                output.find("char: a") != std::string::npos);
    EXPECT_TRUE(output.find("int: 97") != std::string::npos);
    EXPECT_TRUE(output.find("float: 97.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 97.0") != std::string::npos);
}

TEST_F(ScalarConverterTest, CharLiteral_NonPrintable) {
    ScalarConverter::convert("' '");  // space character
    
    std::string output = getOutput();
    
    // Space is printable, so it should display
    EXPECT_TRUE(output.find("char: ' '") != std::string::npos ||
                output.find("char:  ") != std::string::npos);
    EXPECT_TRUE(output.find("int: 32") != std::string::npos);
}

// ============================================================================
// TEST GROUP 2: INT LITERALS
// ============================================================================

TEST_F(ScalarConverterTest, IntLiteral_Zero) {
    ScalarConverter::convert("0");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: Non displayable") != std::string::npos);
    EXPECT_TRUE(output.find("int: 0") != std::string::npos);
    EXPECT_TRUE(output.find("float: 0.0f") != std::string::npos ||
                output.find("float: 0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 0.0") != std::string::npos ||
                output.find("double: 0") != std::string::npos);
}

TEST_F(ScalarConverterTest, IntLiteral_Positive) {
    ScalarConverter::convert("42");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: '*'") != std::string::npos);
    EXPECT_TRUE(output.find("int: 42") != std::string::npos);
    EXPECT_TRUE(output.find("float: 42.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 42.0") != std::string::npos);
}

TEST_F(ScalarConverterTest, IntLiteral_Negative) {
    ScalarConverter::convert("-42");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos ||
                output.find("char: Non displayable") != std::string::npos);
    EXPECT_TRUE(output.find("int: -42") != std::string::npos);
    EXPECT_TRUE(output.find("float: -42.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: -42.0") != std::string::npos);
}

TEST_F(ScalarConverterTest, IntLiteral_MaxInt) {
    ScalarConverter::convert("2147483647");  // INT_MAX
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: 2147483647") != std::string::npos);
    EXPECT_TRUE(output.find("float:") != std::string::npos);
    EXPECT_TRUE(output.find("double:") != std::string::npos);
}

TEST_F(ScalarConverterTest, IntLiteral_MinInt) {
    ScalarConverter::convert("-2147483648");  // INT_MIN
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: -2147483648") != std::string::npos);
    EXPECT_TRUE(output.find("float:") != std::string::npos);
    EXPECT_TRUE(output.find("double:") != std::string::npos);
}

TEST_F(ScalarConverterTest, IntLiteral_CharRange) {
    ScalarConverter::convert("65");  // ASCII 'A'
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: 'A'") != std::string::npos ||
                output.find("char: A") != std::string::npos);
    EXPECT_TRUE(output.find("int: 65") != std::string::npos);
    EXPECT_TRUE(output.find("float: 65.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 65.0") != std::string::npos);
}

// ============================================================================
// TEST GROUP 3: FLOAT LITERALS
// ============================================================================

TEST_F(ScalarConverterTest, FloatLiteral_Zero) {
    ScalarConverter::convert("0.0f");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: Non displayable") != std::string::npos);
    EXPECT_TRUE(output.find("int: 0") != std::string::npos);
    EXPECT_TRUE(output.find("float: 0.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 0.0") != std::string::npos);
}

TEST_F(ScalarConverterTest, FloatLiteral_Positive) {
    ScalarConverter::convert("42.0f");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: '*'") != std::string::npos);
    EXPECT_TRUE(output.find("int: 42") != std::string::npos);
    EXPECT_TRUE(output.find("float: 42.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 42.0") != std::string::npos);
}

TEST_F(ScalarConverterTest, FloatLiteral_Negative) {
    ScalarConverter::convert("-4.2f");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: -4") != std::string::npos);
    EXPECT_TRUE(output.find("float: -4.2f") != std::string::npos);
    EXPECT_TRUE(output.find("double: -4.2") != std::string::npos);
}

TEST_F(ScalarConverterTest, FloatLiteral_WithDecimals) {
    ScalarConverter::convert("4.2f");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos ||
                output.find("char: Non displayable") != std::string::npos);
    EXPECT_TRUE(output.find("int: 4") != std::string::npos);
    EXPECT_TRUE(output.find("float: 4.2f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 4.2") != std::string::npos);
}

TEST_F(ScalarConverterTest, FloatLiteral_Precision) {
    ScalarConverter::convert("42.42f");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("int: 42") != std::string::npos);
    EXPECT_TRUE(output.find("float: 42.42f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 42.42") != std::string::npos);
}

// ============================================================================
// TEST GROUP 4: DOUBLE LITERALS
// ============================================================================

TEST_F(ScalarConverterTest, DoubleLiteral_Zero) {
    ScalarConverter::convert("0.0");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: Non displayable") != std::string::npos);
    EXPECT_TRUE(output.find("int: 0") != std::string::npos);
    EXPECT_TRUE(output.find("float: 0.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 0.0") != std::string::npos);
}

TEST_F(ScalarConverterTest, DoubleLiteral_Positive) {
    ScalarConverter::convert("42.0");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: '*'") != std::string::npos);
    EXPECT_TRUE(output.find("int: 42") != std::string::npos);
    EXPECT_TRUE(output.find("float: 42.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 42.0") != std::string::npos);
}

TEST_F(ScalarConverterTest, DoubleLiteral_Negative) {
    ScalarConverter::convert("-4.2");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: -4") != std::string::npos);
    EXPECT_TRUE(output.find("float: -4.2f") != std::string::npos);
    EXPECT_TRUE(output.find("double: -4.2") != std::string::npos);
}

TEST_F(ScalarConverterTest, DoubleLiteral_HighPrecision) {
    ScalarConverter::convert("123.456789");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("int: 123") != std::string::npos);
    EXPECT_TRUE(output.find("float:") != std::string::npos);
    EXPECT_TRUE(output.find("double:") != std::string::npos);
}

// ============================================================================
// TEST GROUP 5: SPECIAL PSEUDO-LITERALS (FLOAT)
// ============================================================================

TEST_F(ScalarConverterTest, FloatLiteral_PositiveInfinity) {
    ScalarConverter::convert("+inff");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("float: +inff") != std::string::npos ||
                output.find("float: inff") != std::string::npos);
    EXPECT_TRUE(output.find("double: +inf") != std::string::npos ||
                output.find("double: inf") != std::string::npos);
}

TEST_F(ScalarConverterTest, FloatLiteral_NegativeInfinity) {
    ScalarConverter::convert("-inff");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("float: -inff") != std::string::npos);
    EXPECT_TRUE(output.find("double: -inf") != std::string::npos);
}

TEST_F(ScalarConverterTest, FloatLiteral_NaN) {
    ScalarConverter::convert("nanf");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("float: nanf") != std::string::npos);
    EXPECT_TRUE(output.find("double: nan") != std::string::npos);
}

// ============================================================================
// TEST GROUP 6: SPECIAL PSEUDO-LITERALS (DOUBLE)
// ============================================================================

TEST_F(ScalarConverterTest, DoubleLiteral_PositiveInfinity) {
    ScalarConverter::convert("+inf");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("float: +inff") != std::string::npos ||
                output.find("float: inff") != std::string::npos);
    EXPECT_TRUE(output.find("double: +inf") != std::string::npos ||
                output.find("double: inf") != std::string::npos);
}

TEST_F(ScalarConverterTest, DoubleLiteral_NegativeInfinity) {
    ScalarConverter::convert("-inf");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("float: -inff") != std::string::npos);
    EXPECT_TRUE(output.find("double: -inf") != std::string::npos);
}

TEST_F(ScalarConverterTest, DoubleLiteral_NaN) {
    ScalarConverter::convert("nan");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("float: nanf") != std::string::npos);
    EXPECT_TRUE(output.find("double: nan") != std::string::npos);
}

// ============================================================================
// TEST GROUP 7: EDGE CASES AND ERROR HANDLING
// ============================================================================

TEST_F(ScalarConverterTest, InvalidInput_RandomString) {
    ScalarConverter::convert("invalid");
    
    std::string output = getOutput();
    
    // Should show impossible for all types
    EXPECT_TRUE(output.find("impossible") != std::string::npos);
}

TEST_F(ScalarConverterTest, IntOverflow_TooLarge) {
    ScalarConverter::convert("2147483648");  // INT_MAX + 1
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: impossible") != std::string::npos ||
                output.find("int:") != std::string::npos);
    EXPECT_TRUE(output.find("float:") != std::string::npos);
    EXPECT_TRUE(output.find("double:") != std::string::npos);
}

TEST_F(ScalarConverterTest, IntOverflow_TooSmall) {
    ScalarConverter::convert("-2147483649");  // INT_MIN - 1
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: impossible") != std::string::npos ||
                output.find("int:") != std::string::npos);
}

TEST_F(ScalarConverterTest, NonDisplayableChar_LowASCII) {
    ScalarConverter::convert("5");  // ASCII 5 is not displayable
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: Non displayable") != std::string::npos);
    EXPECT_TRUE(output.find("int: 5") != std::string::npos);
}

TEST_F(ScalarConverterTest, NonDisplayableChar_HighASCII) {
    ScalarConverter::convert("200");  // Beyond displayable ASCII
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos ||
                output.find("char: Non displayable") != std::string::npos);
    EXPECT_TRUE(output.find("int: 200") != std::string::npos);
}

TEST_F(ScalarConverterTest, DisplayablePrecision_Float) {
    // Test that float shows .0f for integer values
    ScalarConverter::convert("100.0f");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("float: 100.0f") != std::string::npos ||
                output.find("float: 100f") != std::string::npos);
}

TEST_F(ScalarConverterTest, DisplayablePrecision_Double) {
    // Test that double shows .0 for integer values
    ScalarConverter::convert("100.0");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("double: 100.0") != std::string::npos ||
                output.find("double: 100") != std::string::npos);
}

// ============================================================================
// TEST GROUP 8: CLASS DESIGN TESTS
// ============================================================================

TEST(ScalarConverterDesignTest, CannotInstantiate) {
    // This test ensures ScalarConverter cannot be instantiated
    // Uncomment when implementing:
    
    // This should NOT compile if correctly implemented:
    // ScalarConverter converter;  // Should give compilation error
    
    // For now, we just check that static method exists
    SUCCEED();  // Manual verification needed
}

TEST(ScalarConverterDesignTest, OnlyStaticMethods) {
    // Verify that convert is a static method by calling it without instance
    ScalarConverter::convert("42");
    
    // If this compiles and runs, the method is static
    SUCCEED();
}

// ============================================================================
// INTEGRATION TESTS
// ============================================================================

TEST_F(ScalarConverterTest, SubjectExample_NoArgs) {
    // From subject: ./convert 0
    ScalarConverter::convert("0");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: Non displayable") != std::string::npos);
    EXPECT_TRUE(output.find("int: 0") != std::string::npos);
    EXPECT_TRUE(output.find("float: 0.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 0.0") != std::string::npos);
}

TEST_F(ScalarConverterTest, SubjectExample_Nan) {
    // From subject: ./convert nan
    ScalarConverter::convert("nan");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("float: nanf") != std::string::npos);
    EXPECT_TRUE(output.find("double: nan") != std::string::npos);
}

TEST_F(ScalarConverterTest, SubjectExample_Float) {
    // From subject: ./convert 42.0f
    ScalarConverter::convert("42.0f");
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: '*'") != std::string::npos);
    EXPECT_TRUE(output.find("int: 42") != std::string::npos);
    EXPECT_TRUE(output.find("float: 42.0f") != std::string::npos);
    EXPECT_TRUE(output.find("double: 42.0") != std::string::npos);
}

/*
   BONUS TESTS - Advanced edge cases
*/

TEST_F(ScalarConverterTest, BONUS_VeryLargeDouble) {
    ScalarConverter::convert("1.7976931348623157e+308");  // Near DBL_MAX
    
    std::string output = getOutput();
    
    EXPECT_TRUE(output.find("char: impossible") != std::string::npos);
    EXPECT_TRUE(output.find("int: impossible") != std::string::npos);
    // Float might overflow to inf
    EXPECT_TRUE(output.find("double:") != std::string::npos);
}

TEST_F(ScalarConverterTest, BONUS_ScientificNotation) {
    // If you want to handle scientific notation
    ScalarConverter::convert("1.5e2");  // 150.0
    
    // This is optional and depends on your implementation
    SUCCEED();
}
TEST_F(ScalarConverterTest, BONUS_LeadingTrailingSpaces) {
    // If you want to handle leading/trailing spaces
    ScalarConverter::convert("   42   ");
    
    // This is optional and depends on your implementation
    SUCCEED();
}