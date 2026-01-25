/* ************************************************************************** */
/*                                                                            */
/*   TestModule07Ex01.cpp - iter Function Template                            */
/*   Templates - Apply function to array elements                             */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "../ex01/headers/Iter.hpp"

// ============================================
// Helper Functions for Testing
// ============================================

static int g_sum = 0;

void addToSum(int& n) {
    g_sum += n;
}

void doubleValue(int& n) {
    n *= 2;
}

void increment(int& n) {
    n += 1;
}

void toUpperCase(char& c) {
    if (c >= 'a' && c <= 'z')
        c = c - 32;
}

void appendSuffix(std::string& s) {
    s += "_modified";
}

template<typename T>
void printElement(T const& elem) {
    std::cout << elem << " ";
}

// ============================================
// Basic iter Tests - Integer Array
// ============================================

class IterTest : public ::testing::Test {
protected:
    void SetUp() override {
        g_sum = 0;
    }
};

TEST_F(IterTest, IterWithIntegerArray) {
    int arr[] = {1, 2, 3, 4, 5};

    ::iter(arr, 5, addToSum);

    EXPECT_EQ(g_sum, 15);  // 1+2+3+4+5 = 15
}

TEST_F(IterTest, IterModifiesValues) {
    int arr[] = {1, 2, 3, 4, 5};

    ::iter(arr, 5, doubleValue);

    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 4);
    EXPECT_EQ(arr[2], 6);
    EXPECT_EQ(arr[3], 8);
    EXPECT_EQ(arr[4], 10);
}

TEST_F(IterTest, IterIncrement) {
    int arr[] = {10, 20, 30};

    ::iter(arr, 3, increment);

    EXPECT_EQ(arr[0], 11);
    EXPECT_EQ(arr[1], 21);
    EXPECT_EQ(arr[2], 31);
}

// ============================================
// iter with Different Types
// ============================================

TEST_F(IterTest, IterWithCharArray) {
    char arr[] = {'h', 'e', 'l', 'l', 'o'};

    ::iter(arr, 5, toUpperCase);

    EXPECT_EQ(arr[0], 'H');
    EXPECT_EQ(arr[1], 'E');
    EXPECT_EQ(arr[2], 'L');
    EXPECT_EQ(arr[3], 'L');
    EXPECT_EQ(arr[4], 'O');
}

TEST_F(IterTest, IterWithStringArray) {
    std::string arr[] = {"one", "two", "three"};

    ::iter(arr, 3, appendSuffix);

    EXPECT_EQ(arr[0], "one_modified");
    EXPECT_EQ(arr[1], "two_modified");
    EXPECT_EQ(arr[2], "three_modified");
}

// ============================================
// Edge Cases
// ============================================

TEST_F(IterTest, IterWithSingleElement) {
    int arr[] = {42};

    ::iter(arr, 1, doubleValue);

    EXPECT_EQ(arr[0], 84);
}

TEST_F(IterTest, IterWithZeroLength) {
    int arr[] = {1, 2, 3};

    ::iter(arr, 0, doubleValue);

    // No changes should occur
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST_F(IterTest, IterPartialArray) {
    int arr[] = {1, 2, 3, 4, 5};

    ::iter(arr, 3, doubleValue);  // Only first 3 elements

    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 4);
    EXPECT_EQ(arr[2], 6);
    EXPECT_EQ(arr[3], 4);  // Unchanged
    EXPECT_EQ(arr[4], 5);  // Unchanged
}

// ============================================
// Multiple iter Calls
// ============================================

TEST_F(IterTest, MultipleIterCalls) {
    int arr[] = {1, 2, 3};

    ::iter(arr, 3, doubleValue);
    ::iter(arr, 3, doubleValue);

    EXPECT_EQ(arr[0], 4);   // 1*2*2
    EXPECT_EQ(arr[1], 8);   // 2*2*2
    EXPECT_EQ(arr[2], 12);  // 3*2*2
}

// ============================================
// iter with Const Function (read-only)
// ============================================

static std::stringstream g_output;

void captureValue(int const& n) {
    g_output << n << ",";
}

TEST_F(IterTest, IterWithConstFunction) {
    g_output.str("");
    int arr[] = {10, 20, 30};

    ::iter(arr, 3, captureValue);

    EXPECT_EQ(g_output.str(), "10,20,30,");
}

// ============================================
// iter with Doubles
// ============================================

void halveValue(double& d) {
    d /= 2.0;
}

TEST_F(IterTest, IterWithDoubleArray) {
    double arr[] = {10.0, 20.0, 30.0};

    ::iter(arr, 3, halveValue);

    EXPECT_DOUBLE_EQ(arr[0], 5.0);
    EXPECT_DOUBLE_EQ(arr[1], 10.0);
    EXPECT_DOUBLE_EQ(arr[2], 15.0);
}

// ============================================
// Large Array Test
// ============================================

TEST_F(IterTest, IterLargeArray) {
    int arr[100];
    for (int i = 0; i < 100; i++)
        arr[i] = i;

    ::iter(arr, 100, increment);

    for (int i = 0; i < 100; i++)
        EXPECT_EQ(arr[i], i + 1);
}

// ============================================
// Template Function as Argument
// ============================================

template<typename T>
void square(T& val) {
    val = val * val;
}

TEST_F(IterTest, IterWithTemplateFunction) {
    int arr[] = {2, 3, 4};

    ::iter(arr, 3, square<int>);

    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr[1], 9);
    EXPECT_EQ(arr[2], 16);
}

TEST_F(IterTest, IterWithTemplateFunctionDouble) {
    double arr[] = {2.0, 3.0, 4.0};

    ::iter(arr, 3, square<double>);

    EXPECT_DOUBLE_EQ(arr[0], 4.0);
    EXPECT_DOUBLE_EQ(arr[1], 9.0);
    EXPECT_DOUBLE_EQ(arr[2], 16.0);
}
