/* ************************************************************************** */
/*   TestModule09Ex00.cpp - BitcoinExchange Tests                             */
/*   CSV parsing, date lookup, value calculation                              */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../ex00/BitcoinExchange.hpp"

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
    EXPECT_NO_THROW(btc.loadDatabase("data.csv"));
}

TEST(BitcoinExchangeDBTest, InvalidDatabasePath) {
    BitcoinExchange btc;
    EXPECT_THROW(btc.loadDatabase("nonexistent.csv"), std::exception);
}

// ============================================
// Exchange Rate Calculation Tests
// ============================================

TEST(BitcoinExchangeCalcTest, ExactDateMatch) {
    BitcoinExchange btc;
    btc.loadDatabase("data.csv");
    // Test with known date in database
    // Result depends on actual data.csv content
}

TEST(BitcoinExchangeCalcTest, ClosestLowerDate) {
    BitcoinExchange btc;
    btc.loadDatabase("data.csv");
    // When date not in DB, should use closest lower date
}

TEST(BitcoinExchangeCalcTest, DateBeforeFirstEntry) {
    BitcoinExchange btc;
    btc.loadDatabase("data.csv");
    // Should handle dates before first database entry
}

// ============================================
// Orthodox Canonical Form Tests
// ============================================

TEST(BitcoinExchangeOCFTest, CopyConstructor) {
    BitcoinExchange original;
    original.loadDatabase("data.csv");

    BitcoinExchange copy(original);
    // Copy should work independently
}

TEST(BitcoinExchangeOCFTest, AssignmentOperator) {
    BitcoinExchange a;
    a.loadDatabase("data.csv");

    BitcoinExchange b;
    b = a;
    // Assignment should work
}

// ============================================
// Error Message Tests
// ============================================

TEST(BitcoinExchangeErrorTest, NegativeNumber) {
    BitcoinExchange btc;
    btc.loadDatabase("data.csv");
    // Should output "Error: not a positive number."
}

TEST(BitcoinExchangeErrorTest, TooLargeNumber) {
    BitcoinExchange btc;
    btc.loadDatabase("data.csv");
    // Should output "Error: too large a number."
}

TEST(BitcoinExchangeErrorTest, BadInput) {
    BitcoinExchange btc;
    btc.loadDatabase("data.csv");
    // Should output "Error: bad input => ..."
}
