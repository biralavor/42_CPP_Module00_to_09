/* ************************************************************************** */
/*   TestModule09Ex00.cpp - BitcoinExchange Tests                             */
/*   CSV parsing, date lookup, value calculation                              */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <cmath>
#include "../ex00/BitcoinExchange.hpp"

// Database path relative to build directory (Module09/build/)
static const char* DB_PATH = "../ex00/src/data.csv";

// Helper for floating point comparison
static bool almostEqual(double a, double b, double epsilon = 0.001) {
    return std::fabs(a - b) < epsilon;
}

// ============================================
// Date Parsing Tests
// ============================================

TEST(BitcoinExchangeDateTest, ValidDateFormat) {
    BitcoinExchange btc;
    EXPECT_TRUE(btc.isValidDate("2011-01-03"));
    EXPECT_TRUE(btc.isValidDate("2022-12-31"));
    EXPECT_TRUE(btc.isValidDate("2009-01-02"));
}

TEST(BitcoinExchangeDateTest, InvalidDateFormat) {
    BitcoinExchange btc;
    EXPECT_FALSE(btc.isValidDate("2001-42-42"));
    EXPECT_FALSE(btc.isValidDate("2011/01/03"));
    EXPECT_FALSE(btc.isValidDate("01-03-2011"));
    EXPECT_FALSE(btc.isValidDate(""));
    EXPECT_FALSE(btc.isValidDate("not-a-date"));
}

TEST(BitcoinExchangeDateTest, InvalidMonth) {
    BitcoinExchange btc;
    EXPECT_FALSE(btc.isValidDate("2011-13-01"));
    EXPECT_FALSE(btc.isValidDate("2011-00-01"));
}

TEST(BitcoinExchangeDateTest, InvalidDay) {
    BitcoinExchange btc;
    EXPECT_FALSE(btc.isValidDate("2011-01-32"));
    EXPECT_FALSE(btc.isValidDate("2011-02-30"));  // Feb doesn't have 30 days
    EXPECT_FALSE(btc.isValidDate("2011-01-00"));
}

TEST(BitcoinExchangeDateTest, LeapYear) {
    BitcoinExchange btc;
    EXPECT_TRUE(btc.isValidDate("2012-02-29"));   // Leap year
    EXPECT_FALSE(btc.isValidDate("2011-02-29"));  // Not leap year
}

// ============================================
// Value Parsing Tests
// ============================================

TEST(BitcoinExchangeValueTest, ValidValues) {
    BitcoinExchange btc;
    EXPECT_TRUE(btc.isValidValue("0"));
    EXPECT_TRUE(btc.isValidValue("1"));
    EXPECT_TRUE(btc.isValidValue("1.5"));
    EXPECT_TRUE(btc.isValidValue("1000"));
    EXPECT_TRUE(btc.isValidValue("999.99"));
}

TEST(BitcoinExchangeValueTest, InvalidValues) {
    BitcoinExchange btc;
    EXPECT_FALSE(btc.isValidValue("-1"));      // Negative
    EXPECT_FALSE(btc.isValidValue("1001"));    // > 1000
    EXPECT_FALSE(btc.isValidValue("2147483648")); // Too large
    EXPECT_FALSE(btc.isValidValue("abc"));     // Not a number
    EXPECT_FALSE(btc.isValidValue(""));        // Empty
}

TEST(BitcoinExchangeValueTest, EdgeValues) {
    BitcoinExchange btc;
    EXPECT_TRUE(btc.isValidValue("0.001"));
    EXPECT_TRUE(btc.isValidValue("1000"));     // Exactly 1000
    EXPECT_FALSE(btc.isValidValue("1000.01")); // Just over 1000
}

// ============================================
// Line Parsing Tests
// ============================================

TEST(BitcoinExchangeParseTest, ValidLineFormat) {
    BitcoinExchange btc;
    EXPECT_TRUE(btc.isValidLine("2011-01-03 | 3"));
    EXPECT_TRUE(btc.isValidLine("2011-01-03 | 1.2"));
}

TEST(BitcoinExchangeParseTest, InvalidLineFormat) {
    BitcoinExchange btc;
    EXPECT_FALSE(btc.isValidLine("2011-01-03|3"));    // No spaces
    EXPECT_FALSE(btc.isValidLine("2011-01-03 3"));    // Missing |
    EXPECT_FALSE(btc.isValidLine("2011-01-03"));      // No value
    EXPECT_FALSE(btc.isValidLine("date | value"));    // Header line
}

// ============================================
// Database Loading Tests
// ============================================

TEST(BitcoinExchangeDBTest, LoadDatabase) {
    BitcoinExchange btc;
    // Should not throw when loading valid database
    EXPECT_NO_THROW(btc.loadDatabase(DB_PATH));
}

TEST(BitcoinExchangeDBTest, InvalidDatabasePath) {
    BitcoinExchange btc;
    EXPECT_THROW(btc.loadDatabase("nonexistent.csv"), std::exception);
}

// ============================================
// Exchange Rate Calculation Tests
// ============================================

// Data.csv key values:
// 2009-01-02: 0 (first entry)
// 2011-01-01: 0.3
// 2011-01-04: 0.3
// 2011-01-07: 0.32
// 2012-01-11: 7.1

TEST(BitcoinExchangeCalcTest, ExactDateMatch) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // 2012-01-11 exists in DB with rate 7.1
    // Subject example: 2012-01-11 => 1 = 7.1
    double result = btc.getExchangeValue("2012-01-11", 1.0);
    EXPECT_TRUE(almostEqual(result, 7.1));

    // 2011-01-01 exists in DB with rate 0.3
    result = btc.getExchangeValue("2011-01-01", 10.0);
    EXPECT_TRUE(almostEqual(result, 3.0));  // 0.3 * 10 = 3.0
}

TEST(BitcoinExchangeCalcTest, ClosestLowerDate) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // 2011-01-03 not in DB, closest lower is 2011-01-01 (rate 0.3)
    // Subject example: 2011-01-03 => 3 = 0.9
    double result = btc.getExchangeValue("2011-01-03", 3.0);
    EXPECT_TRUE(almostEqual(result, 0.9));

    // Subject example: 2011-01-03 => 1.2 = 0.36
    result = btc.getExchangeValue("2011-01-03", 1.2);
    EXPECT_TRUE(almostEqual(result, 0.36));

    // 2011-01-09 not in DB, closest lower is 2011-01-07 (rate 0.32)
    // Subject example: 2011-01-09 => 1 = 0.32
    result = btc.getExchangeValue("2011-01-09", 1.0);
    EXPECT_TRUE(almostEqual(result, 0.32));
}

TEST(BitcoinExchangeCalcTest, DateBeforeFirstEntry) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // First entry is 2009-01-02, date before should throw or return error
    EXPECT_THROW(btc.getExchangeValue("2008-12-31", 1.0), std::exception);
}

TEST(BitcoinExchangeCalcTest, SubjectExamples) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // All subject PDF examples
    EXPECT_TRUE(almostEqual(btc.getExchangeValue("2011-01-03", 3.0), 0.9));
    EXPECT_TRUE(almostEqual(btc.getExchangeValue("2011-01-03", 2.0), 0.6));
    EXPECT_TRUE(almostEqual(btc.getExchangeValue("2011-01-03", 1.0), 0.3));
    EXPECT_TRUE(almostEqual(btc.getExchangeValue("2011-01-03", 1.2), 0.36));
    EXPECT_TRUE(almostEqual(btc.getExchangeValue("2011-01-09", 1.0), 0.32));
    EXPECT_TRUE(almostEqual(btc.getExchangeValue("2012-01-11", 1.0), 7.1));
}

TEST(BitcoinExchangeCalcTest, ZeroValue) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // Multiplying by 0 should give 0
    double result = btc.getExchangeValue("2012-01-11", 0.0);
    EXPECT_TRUE(almostEqual(result, 0.0));
}

TEST(BitcoinExchangeCalcTest, MaxValue) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // Value of 1000 (max allowed)
    // 2012-01-11 rate is 7.1, so 7.1 * 1000 = 7100
    double result = btc.getExchangeValue("2012-01-11", 1000.0);
    EXPECT_TRUE(almostEqual(result, 7100.0));
}

// ============================================
// Orthodox Canonical Form Tests
// ============================================

TEST(BitcoinExchangeOCFTest, CopyConstructor) {
    BitcoinExchange original;
    original.loadDatabase(DB_PATH);

    BitcoinExchange copy(original);

    // Copy should produce same results as original
    double origResult = original.getExchangeValue("2012-01-11", 1.0);
    double copyResult = copy.getExchangeValue("2012-01-11", 1.0);
    EXPECT_TRUE(almostEqual(origResult, copyResult));
}

TEST(BitcoinExchangeOCFTest, AssignmentOperator) {
    BitcoinExchange a;
    a.loadDatabase(DB_PATH);

    BitcoinExchange b;
    b = a;

    // Assignment should produce same results
    double aResult = a.getExchangeValue("2011-01-03", 3.0);
    double bResult = b.getExchangeValue("2011-01-03", 3.0);
    EXPECT_TRUE(almostEqual(aResult, bResult));
}

TEST(BitcoinExchangeOCFTest, SelfAssignment) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    btc = btc;

    // Should still work after self-assignment
    double result = btc.getExchangeValue("2012-01-11", 1.0);
    EXPECT_TRUE(almostEqual(result, 7.1));
}

// ============================================
// Error Handling Tests
// ============================================

TEST(BitcoinExchangeErrorTest, NegativeNumber) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // Negative values should throw or return error
    // Subject: "Error: not a positive number."
    EXPECT_THROW(btc.getExchangeValue("2012-01-11", -1.0), std::exception);
}

TEST(BitcoinExchangeErrorTest, TooLargeNumber) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // Values > 1000 should throw or return error
    // Subject: "Error: too large a number."
    EXPECT_THROW(btc.getExchangeValue("2012-01-11", 1001.0), std::exception);
}

TEST(BitcoinExchangeErrorTest, BadDateFormat) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // Invalid date format should throw
    // Subject: "Error: bad input => 2001-42-42"
    EXPECT_THROW(btc.getExchangeValue("2001-42-42", 1.0), std::exception);
}

TEST(BitcoinExchangeErrorTest, InvalidMonth) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    EXPECT_THROW(btc.getExchangeValue("2011-13-01", 1.0), std::exception);
    EXPECT_THROW(btc.getExchangeValue("2011-00-15", 1.0), std::exception);
}

TEST(BitcoinExchangeErrorTest, InvalidDay) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    EXPECT_THROW(btc.getExchangeValue("2011-02-30", 1.0), std::exception);
    EXPECT_THROW(btc.getExchangeValue("2011-01-32", 1.0), std::exception);
}

// ============================================
// Edge Cases
// ============================================

TEST(BitcoinExchangeEdgeTest, FirstDatabaseEntry) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // First entry is 2009-01-02 with rate 0
    double result = btc.getExchangeValue("2009-01-02", 100.0);
    EXPECT_TRUE(almostEqual(result, 0.0));  // 0 * 100 = 0
}

TEST(BitcoinExchangeEdgeTest, LastDatabaseEntry) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // Last entry is 2022-03-29 with rate 47115.93
    double result = btc.getExchangeValue("2022-03-29", 1.0);
    EXPECT_TRUE(almostEqual(result, 47115.93));
}

TEST(BitcoinExchangeEdgeTest, DateAfterLastEntry) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // Date after last entry should use last available rate
    // 2022-03-29 is last entry with rate 47115.93
    double result = btc.getExchangeValue("2023-01-01", 1.0);
    EXPECT_TRUE(almostEqual(result, 47115.93));
}

TEST(BitcoinExchangeEdgeTest, LeapYearDate) {
    BitcoinExchange btc;
    btc.loadDatabase(DB_PATH);

    // 2012-02-29 is a valid leap year date
    // Should not throw, should find closest lower date
    EXPECT_NO_THROW(btc.getExchangeValue("2012-02-29", 1.0));
}
