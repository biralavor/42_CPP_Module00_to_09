/* ************************************************************************** */
/*   TestModule09Ex00.cpp - BitcoinExchange & Utils Tests                     */
/*   Date validation, value parsing, database lookup                          */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <cmath>
#include <sstream>
#include "../ex00/headers/BitcoinExchange.hpp"
#include "../ex00/headers/utils.hpp"

static bool almostEqual(double a, double b, double epsilon = 0.001) {
    return std::fabs(a - b) < epsilon;
}

// ============================================
// Utils - isValidDateFormat Tests
// ============================================

TEST(UtilsDateFormatTest, ValidFormats) {
    EXPECT_TRUE(isValidDateFormat("2011-01-03"));
    EXPECT_TRUE(isValidDateFormat("2022-12-31"));
    EXPECT_TRUE(isValidDateFormat("9999-01-01"));
}

TEST(UtilsDateFormatTest, InvalidFormats) {
    EXPECT_FALSE(isValidDateFormat("2011/01/03"));
    EXPECT_FALSE(isValidDateFormat("20110103"));
    EXPECT_FALSE(isValidDateFormat("2011-1-3"));
    EXPECT_FALSE(isValidDateFormat(""));
    EXPECT_FALSE(isValidDateFormat("not-a-date"));
    EXPECT_FALSE(isValidDateFormat("abcd-ef-gh"));
}

// ============================================
// Utils - isValidDate Tests
// ============================================

TEST(UtilsDateTest, ValidDates) {
    EXPECT_TRUE(isValidDate("2011-01-03"));
    EXPECT_TRUE(isValidDate("2022-12-31"));
    EXPECT_TRUE(isValidDate("2009-01-02"));
}

TEST(UtilsDateTest, InvalidMonth) {
    EXPECT_FALSE(isValidDate("2011-13-01"));
    EXPECT_FALSE(isValidDate("2011-00-01"));
}

TEST(UtilsDateTest, InvalidDay) {
    EXPECT_FALSE(isValidDate("2011-01-32"));
    EXPECT_FALSE(isValidDate("2011-01-00"));
    EXPECT_FALSE(isValidDate("2011-04-31"));
    EXPECT_FALSE(isValidDate("2011-06-31"));
}

TEST(UtilsDateTest, FebruaryNonLeapYear) {
    EXPECT_TRUE(isValidDate("2011-02-28"));
    EXPECT_FALSE(isValidDate("2011-02-29"));
    EXPECT_FALSE(isValidDate("2011-02-30"));
}

TEST(UtilsDateTest, FebruaryLeapYear) {
    EXPECT_TRUE(isValidDate("2012-02-28"));
    EXPECT_TRUE(isValidDate("2012-02-29"));
    EXPECT_FALSE(isValidDate("2012-02-30"));
}

TEST(UtilsDateTest, BadFormat) {
    EXPECT_FALSE(isValidDate("2001-42-42"));
    EXPECT_FALSE(isValidDate(""));
    EXPECT_FALSE(isValidDate("not-a-date"));
}

// ============================================
// Utils - isLeapYear Tests
// ============================================

TEST(UtilsLeapYearTest, LeapYears) {
    EXPECT_TRUE(isLeapYear(2000));
    EXPECT_TRUE(isLeapYear(2004));
    EXPECT_TRUE(isLeapYear(2012));
    EXPECT_TRUE(isLeapYear(2400));
}

TEST(UtilsLeapYearTest, NonLeapYears) {
    EXPECT_FALSE(isLeapYear(1900));
    EXPECT_FALSE(isLeapYear(2011));
    EXPECT_FALSE(isLeapYear(2100));
    EXPECT_FALSE(isLeapYear(2023));
}

// ============================================
// Utils - isValidValue Tests
// ============================================

TEST(UtilsValueTest, ValidValues) {
    EXPECT_TRUE(isValidValue("0"));
    EXPECT_TRUE(isValidValue("1"));
    EXPECT_TRUE(isValidValue("1.5"));
    EXPECT_TRUE(isValidValue("1000"));
    EXPECT_TRUE(isValidValue("999.99"));
    EXPECT_TRUE(isValidValue("0.001"));
    EXPECT_TRUE(isValidValue("+42"));
}

TEST(UtilsValueTest, InvalidValues) {
    EXPECT_FALSE(isValidValue("-1"));
    EXPECT_FALSE(isValidValue("1001"));
    EXPECT_FALSE(isValidValue("2147483648"));
    EXPECT_FALSE(isValidValue(""));
}

TEST(UtilsValueTest, EdgeValues) {
    EXPECT_TRUE(isValidValue("1000"));
    EXPECT_FALSE(isValidValue("1000.01"));
}

// ============================================
// Utils - skipSpaces Tests
// ============================================

TEST(UtilsSkipSpacesTest, TrimsWhitespace) {
    EXPECT_EQ(skipSpaces("  hello  "), "hello");
    EXPECT_EQ(skipSpaces("hello"), "hello");
    EXPECT_EQ(skipSpaces("  hello"), "hello");
    EXPECT_EQ(skipSpaces("hello  "), "hello");
}

// ============================================
// Utils - skipPipe Tests
// ============================================

TEST(UtilsSkipPipeTest, RemovesPipeAndTrims) {
    EXPECT_EQ(skipPipe(" | 3"), "3");
    EXPECT_EQ(skipPipe(" | 1.2"), "1.2");
    EXPECT_EQ(skipPipe("hello"), "hello");
}

// ============================================
// BitcoinExchange - Database Loading Tests
// ============================================

TEST(BitcoinExchangeDBTest, ConstructorLoadsDatabase) {
    EXPECT_NO_THROW(BitcoinExchange());
}

TEST(BitcoinExchangeDBTest, InvalidDatabasePath) {
    BitcoinExchange btc;
    EXPECT_THROW(btc.loadDatabase("nonexistent.csv"), std::runtime_error);
}

// ============================================
// BitcoinExchange - findClosestDate Tests
// ============================================

TEST(BitcoinExchangeFindTest, ExactDateMatch) {
    BitcoinExchange btc;
    std::map<std::string, double> result = btc.findClosestDate("2012-01-11");
    EXPECT_TRUE(result.find("2012-01-11") != result.end());
    EXPECT_TRUE(almostEqual(result["2012-01-11"], 7.1));
}

TEST(BitcoinExchangeFindTest, ClosestLowerDate) {
    BitcoinExchange btc;
    std::map<std::string, double> result = btc.findClosestDate("2011-01-03");
    EXPECT_TRUE(result.find("2011-01-01") != result.end());
    EXPECT_TRUE(almostEqual(result["2011-01-01"], 0.3));
}

TEST(BitcoinExchangeFindTest, DateBeforeFirstEntry) {
    BitcoinExchange btc;
    std::map<std::string, double> result = btc.findClosestDate("2008-12-31");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_TRUE(result.find("2009-01-02") != result.end());
}

TEST(BitcoinExchangeFindTest, DateAfterLastEntry) {
    BitcoinExchange btc;
    std::map<std::string, double> result = btc.findClosestDate("2023-01-01");
    EXPECT_EQ(result.size(), 1u);
}

TEST(BitcoinExchangeFindTest, FirstDatabaseEntry) {
    BitcoinExchange btc;
    std::map<std::string, double> result = btc.findClosestDate("2009-01-02");
    EXPECT_TRUE(result.find("2009-01-02") != result.end());
    EXPECT_TRUE(almostEqual(result["2009-01-02"], 0.0));
}

TEST(BitcoinExchangeFindTest, UsesLowerDateNotAverage) {
    BitcoinExchange btc;
    // 2011-01-03 not in DB
    // lower neighbor: 2011-01-01 (rate 0.3)
    // upper neighbor: 2011-01-04 (rate 0.3)
    // Must use lower (0.3), not average of both
    std::map<std::string, double> result = btc.findClosestDate("2011-01-03");
    std::map<std::string, double>::iterator it = result.upper_bound("2011-01-03");
    if (it != result.begin())
        --it;
    EXPECT_EQ(it->first, "2011-01-01");
    EXPECT_TRUE(almostEqual(it->second, 0.3));
}

TEST(BitcoinExchangeFindTest, UsesLowerDateBetweenDifferentRates) {
    BitcoinExchange btc;
    // 2011-01-06 not in DB
    // lower neighbor: 2011-01-04 (rate 0.3)
    // upper neighbor: 2011-01-07 (rate 0.32)
    // Must use lower (0.3), not average (0.31)
    std::map<std::string, double> result = btc.findClosestDate("2011-01-06");
    std::map<std::string, double>::iterator it = result.upper_bound("2011-01-06");
    if (it != result.begin())
        --it;
    EXPECT_EQ(it->first, "2011-01-04");
    EXPECT_TRUE(almostEqual(it->second, 0.3));
}

TEST(BitcoinExchangeFindTest, SubjectExampleRates) {
    BitcoinExchange btc;
    // Subject: 2011-01-03 => 3 = 0.9 (rate 0.3 * 3)
    std::map<std::string, double> result = btc.findClosestDate("2011-01-03");
    std::map<std::string, double>::iterator it = result.upper_bound("2011-01-03");
    if (it != result.begin())
        --it;
    EXPECT_TRUE(almostEqual(it->second * 3.0, 0.9));

    // Subject: 2011-01-09 => 1 = 0.32 (rate 0.32 * 1)
    result = btc.findClosestDate("2011-01-09");
    it = result.upper_bound("2011-01-09");
    if (it != result.begin())
        --it;
    EXPECT_TRUE(almostEqual(it->second * 1.0, 0.32));
}

// ============================================
// BitcoinExchange - inputValidation Tests
// ============================================

TEST(BitcoinExchangeInputTest, ValidInput) {
    BitcoinExchange btc;
    std::istringstream iss("2011-01-03 | 3");
    std::string date, valueStr;
    EXPECT_TRUE(btc.inputValidation(iss, date, valueStr));
    EXPECT_EQ(date, "2011-01-03");
    EXPECT_EQ(valueStr, "3");
}

TEST(BitcoinExchangeInputTest, ValidInputDecimal) {
    BitcoinExchange btc;
    std::istringstream iss("2011-01-03 | 1.2");
    std::string date, valueStr;
    EXPECT_TRUE(btc.inputValidation(iss, date, valueStr));
    EXPECT_EQ(date, "2011-01-03");
    EXPECT_EQ(valueStr, "1.2");
}

TEST(BitcoinExchangeInputTest, InvalidDate) {
    BitcoinExchange btc;
    std::istringstream iss("2001-42-42 | 1");
    std::string date, valueStr;
    EXPECT_FALSE(btc.inputValidation(iss, date, valueStr));
}

TEST(BitcoinExchangeInputTest, NegativeValue) {
    BitcoinExchange btc;
    std::istringstream iss("2011-01-03 | -1");
    std::string date, valueStr;
    EXPECT_FALSE(btc.inputValidation(iss, date, valueStr));
}

TEST(BitcoinExchangeInputTest, TooLargeValue) {
    BitcoinExchange btc;
    std::istringstream iss("2011-01-03 | 1001");
    std::string date, valueStr;
    EXPECT_FALSE(btc.inputValidation(iss, date, valueStr));
}

TEST(BitcoinExchangeInputTest, EmptyInput) {
    BitcoinExchange btc;
    std::istringstream iss("");
    std::string date, valueStr;
    EXPECT_FALSE(btc.inputValidation(iss, date, valueStr));
}

TEST(BitcoinExchangeInputTest, DateOnlyNoValue) {
    BitcoinExchange btc;
    std::istringstream iss("2011-01-03");
    std::string date, valueStr;
    EXPECT_FALSE(btc.inputValidation(iss, date, valueStr));
}

// ============================================
// BitcoinExchange - OCF Tests
// ============================================

TEST(BitcoinExchangeOCFTest, CopyConstructor) {
    BitcoinExchange original;
    BitcoinExchange copy(original);

    std::map<std::string, double> origResult = original.findClosestDate("2012-01-11");
    std::map<std::string, double> copyResult = copy.findClosestDate("2012-01-11");

    EXPECT_EQ(origResult.size(), copyResult.size());
    EXPECT_TRUE(almostEqual(origResult["2012-01-11"], copyResult["2012-01-11"]));
}

TEST(BitcoinExchangeOCFTest, AssignmentOperator) {
    BitcoinExchange a;
    BitcoinExchange b;
    b = a;

    std::map<std::string, double> aResult = a.findClosestDate("2012-01-11");
    std::map<std::string, double> bResult = b.findClosestDate("2012-01-11");

    EXPECT_EQ(aResult.size(), bResult.size());
    EXPECT_TRUE(almostEqual(aResult["2012-01-11"], bResult["2012-01-11"]));
}

TEST(BitcoinExchangeOCFTest, SelfAssignment) {
    BitcoinExchange btc;
    btc = btc;

    std::map<std::string, double> result = btc.findClosestDate("2012-01-11");
    EXPECT_FALSE(result.empty());
}
