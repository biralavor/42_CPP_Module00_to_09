/* ************************************************************************** */
/*                                                                            */
/*   TestModule08Ex01.cpp - Span Class Tests                                  */
/*   STL Containers - Number storage with span calculation                    */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "../ex01/headers/Span.hpp"

// ============================================
// Constructor Tests
// ============================================

TEST(SpanConstructorTest, DefaultConstructor) {
    Span sp(5);
    // Should not throw, just create empty span with capacity 5
    SUCCEED();
}

TEST(SpanConstructorTest, ZeroCapacity) {
    Span sp(0);
    // Zero capacity span should be valid but not accept any numbers
    EXPECT_THROW(sp.addNumber(1), std::exception);
}

TEST(SpanConstructorTest, CopyConstructor) {
    Span original(5);
    original.addNumber(1);
    original.addNumber(2);
    original.addNumber(3);

    Span copy(original);

    EXPECT_EQ(copy.shortestSpan(), original.shortestSpan());
    EXPECT_EQ(copy.longestSpan(), original.longestSpan());
}

TEST(SpanConstructorTest, AssignmentOperator) {
    Span a(5);
    a.addNumber(10);
    a.addNumber(20);
    a.addNumber(30);

    Span b(10);
    b = a;

    EXPECT_EQ(b.shortestSpan(), a.shortestSpan());
    EXPECT_EQ(b.longestSpan(), a.longestSpan());
}

// ============================================
// addNumber Tests
// ============================================

TEST(SpanAddNumberTest, AddSingleNumber) {
    Span sp(5);
    sp.addNumber(42);
    // No exception, number added successfully
    SUCCEED();
}

TEST(SpanAddNumberTest, AddMultipleNumbers) {
    Span sp(5);
    sp.addNumber(1);
    sp.addNumber(2);
    sp.addNumber(3);
    sp.addNumber(4);
    sp.addNumber(5);
    // No exception, all numbers added
    SUCCEED();
}

TEST(SpanAddNumberTest, AddBeyondCapacity) {
    Span sp(3);
    sp.addNumber(1);
    sp.addNumber(2);
    sp.addNumber(3);

    EXPECT_THROW(sp.addNumber(4), std::exception);
}

TEST(SpanAddNumberTest, AddNegativeNumbers) {
    Span sp(5);
    sp.addNumber(-100);
    sp.addNumber(-50);
    sp.addNumber(0);
    sp.addNumber(50);
    sp.addNumber(100);

    EXPECT_EQ(sp.longestSpan(), 200);
}

// ============================================
// shortestSpan Tests
// ============================================

TEST(SpanShortestTest, SubjectExample) {
    Span sp(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    EXPECT_EQ(sp.shortestSpan(), 2);  // 9 and 11
}

TEST(SpanShortestTest, TwoNumbers) {
    Span sp(2);
    sp.addNumber(10);
    sp.addNumber(20);

    EXPECT_EQ(sp.shortestSpan(), 10);
}

TEST(SpanShortestTest, ConsecutiveNumbers) {
    Span sp(5);
    sp.addNumber(1);
    sp.addNumber(2);
    sp.addNumber(3);
    sp.addNumber(4);
    sp.addNumber(5);

    EXPECT_EQ(sp.shortestSpan(), 1);
}

TEST(SpanShortestTest, SameNumbers) {
    Span sp(5);
    sp.addNumber(42);
    sp.addNumber(42);
    sp.addNumber(42);

    EXPECT_EQ(sp.shortestSpan(), 0);
}

TEST(SpanShortestTest, NoNumbersThrows) {
    Span sp(5);

    EXPECT_THROW(sp.shortestSpan(), std::exception);
}

TEST(SpanShortestTest, OneNumberThrows) {
    Span sp(5);
    sp.addNumber(42);

    EXPECT_THROW(sp.shortestSpan(), std::exception);
}

TEST(SpanShortestTest, LargeRangeNoOverflow) {
    Span sp(3);
    sp.addNumber(2147483647);   // INT_MAX
    sp.addNumber(-2147483648);  // INT_MIN
    sp.addNumber(0);

    // Sorted: -2147483648, 0, 2147483647
    // Shortest span should be min(2147483648, 2147483647) = 2147483647
    // Should not overflow to 0
    unsigned int shortest = sp.shortestSpan();
    EXPECT_GT(shortest, 0u);
    EXPECT_EQ(shortest, 2147483647u);
}

// ============================================
// longestSpan Tests
// ============================================

TEST(SpanLongestTest, SubjectExample) {
    Span sp(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    EXPECT_EQ(sp.longestSpan(), 14);  // 17 - 3
}

TEST(SpanLongestTest, TwoNumbers) {
    Span sp(2);
    sp.addNumber(0);
    sp.addNumber(100);

    EXPECT_EQ(sp.longestSpan(), 100);
}

TEST(SpanLongestTest, NegativeAndPositive) {
    Span sp(3);
    sp.addNumber(-100);
    sp.addNumber(0);
    sp.addNumber(100);

    EXPECT_EQ(sp.longestSpan(), 200);
}

TEST(SpanLongestTest, SameNumbers) {
    Span sp(5);
    sp.addNumber(10);
    sp.addNumber(10);
    sp.addNumber(10);

    EXPECT_EQ(sp.longestSpan(), 0);
}

TEST(SpanLongestTest, NoNumbersThrows) {
    Span sp(5);

    EXPECT_THROW(sp.longestSpan(), std::exception);
}

TEST(SpanLongestTest, OneNumberThrows) {
    Span sp(5);
    sp.addNumber(42);

    EXPECT_THROW(sp.longestSpan(), std::exception);
}

// ============================================
// Overflow Prevention Tests - longestSpan
// ============================================

TEST(SpanOverflowTest, LongestSpanIntMaxMinusIntMin) {
    Span sp(2);
    sp.addNumber(2147483647);   // INT_MAX
    sp.addNumber(-2147483648);  // INT_MIN

    // INT_MAX - INT_MIN = 2147483647 - (-2147483648) = 4294967295
    // This is the full range of unsigned int
    unsigned int longest = sp.longestSpan();
    EXPECT_EQ(longest, 4294967295u);
}

TEST(SpanOverflowTest, LongestSpanLargePositiveRange) {
    Span sp(3);
    sp.addNumber(2147483647);   // INT_MAX
    sp.addNumber(0);
    sp.addNumber(1000000000);

    // Longest span: INT_MAX - 0 = 2147483647
    EXPECT_EQ(sp.longestSpan(), 2147483647u);
}

TEST(SpanOverflowTest, LongestSpanLargeNegativeRange) {
    Span sp(3);
    sp.addNumber(-2147483648);  // INT_MIN
    sp.addNumber(0);
    sp.addNumber(-1000000000);

    // Longest span: 0 - INT_MIN = 2147483648
    EXPECT_EQ(sp.longestSpan(), 2147483648u);
}

TEST(SpanOverflowTest, LongestSpanSymmetricValues) {
    Span sp(3);
    sp.addNumber(-1000000000);
    sp.addNumber(0);
    sp.addNumber(1000000000);

    // Longest span: 1000000000 - (-1000000000) = 2000000000
    EXPECT_EQ(sp.longestSpan(), 2000000000u);
}

TEST(SpanOverflowTest, LongestSpanWithMultipleExtremes) {
    Span sp(5);
    sp.addNumber(2147483647);   // INT_MAX
    sp.addNumber(-2147483648);  // INT_MIN
    sp.addNumber(0);
    sp.addNumber(1000000);
    sp.addNumber(-1000000);

    // Longest span should still be INT_MAX - INT_MIN
    EXPECT_EQ(sp.longestSpan(), 4294967295u);
}

// ============================================
// Range Addition Tests (Iterator-based)
// ============================================

TEST(SpanRangeTest, AddFromVector) {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(10);
    vec.push_back(15);
    vec.push_back(20);

    Span sp(10);
    sp.addRange(vec.begin(), vec.end());

    EXPECT_EQ(sp.shortestSpan(), 5);
    EXPECT_EQ(sp.longestSpan(), 15);
}

TEST(SpanRangeTest, AddFromList) {
    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(100);
    lst.push_back(50);

    Span sp(5);
    sp.addRange(lst.begin(), lst.end());

    EXPECT_EQ(sp.longestSpan(), 99);
}

TEST(SpanRangeTest, AddRangeBeyondCapacity) {
    std::vector<int> vec;
    for (int i = 0; i < 10; i++) {
        vec.push_back(i);
    }

    Span sp(5);

    EXPECT_THROW(sp.addRange(vec.begin(), vec.end()), std::exception);
}

TEST(SpanRangeTest, AddPartialRange) {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    Span sp(3);
    std::vector<int>::iterator start = vec.begin();
    std::vector<int>::iterator end = vec.begin();
    std::advance(end, 3);  // Only first 3 elements

    sp.addRange(start, end);

    EXPECT_EQ(sp.shortestSpan(), 1);
    EXPECT_EQ(sp.longestSpan(), 2);
}

// ============================================
// Iterator Traits & Type Safety Tests
// ============================================

TEST(SpanIteratorTraitsTest, VectorIteratorTraits) {
    // Test with random access iterators (vector)
    std::vector<int> vec;
    for (int i = 0; i < 100; i++) {
        vec.push_back(i * 10);
    }

    Span sp(100);
    sp.addRange(vec.begin(), vec.end());

    EXPECT_EQ(sp.shortestSpan(), 10);
    EXPECT_EQ(sp.longestSpan(), 990);
}

TEST(SpanIteratorTraitsTest, ListIteratorTraits) {
    // Test with bidirectional iterators (list)
    std::list<int> lst;
    for (int i = 5; i <= 50; i += 5) {
        lst.push_back(i);
    }

    Span sp(20);
    sp.addRange(lst.begin(), lst.end());

    EXPECT_EQ(sp.shortestSpan(), 5);
    EXPECT_EQ(sp.longestSpan(), 45);
}

TEST(SpanIteratorTraitsTest, ReverseIterators) {
    // Test with reverse iterators
    std::vector<int> vec;
    vec.push_back(100);
    vec.push_back(200);
    vec.push_back(300);

    Span sp(5);
    sp.addRange(vec.rbegin(), vec.rend());

    EXPECT_EQ(sp.shortestSpan(), 100);
    EXPECT_EQ(sp.longestSpan(), 200);
}

TEST(SpanIteratorTraitsTest, InvalidRangeNegativeDistance) {
    // Test when start > end (invalid range)
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    Span sp(10);
    
    // Passing end before start should throw
    EXPECT_THROW(sp.addRange(vec.end(), vec.begin()), std::exception);
}

TEST(SpanIteratorTraitsTest, EmptyRange) {
    // Test with empty range (begin == end)
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    Span sp(10);
    sp.addRange(vec.begin(), vec.begin());  // Empty range

    // Should not add any elements
    EXPECT_THROW(sp.shortestSpan(), std::exception);  // Not enough numbers
}

TEST(SpanIteratorTraitsTest, ConstIterators) {
    // Test with const iterators
    std::vector<int> vec;
    vec.push_back(42);
    vec.push_back(84);
    vec.push_back(126);

    const std::vector<int>& constVec = vec;

    Span sp(5);
    sp.addRange(constVec.begin(), constVec.end());

    EXPECT_EQ(sp.shortestSpan(), 42);
    EXPECT_EQ(sp.longestSpan(), 84);
}

TEST(SpanIteratorTraitsTest, MixedIteratorTypes) {
    // Test mixing different container types
    Span sp(20);

    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    std::list<int> lst;
    lst.push_back(5);
    lst.push_back(15);

    sp.addRange(vec.begin(), vec.end());
    sp.addRange(lst.begin(), lst.end());

    EXPECT_EQ(sp.shortestSpan(), 5);
    EXPECT_EQ(sp.longestSpan(), 25);  // 30 - 5
}

TEST(SpanIteratorTraitsTest, LargeDistanceCalculation) {
    // Test that difference_type properly handles large ranges
    std::vector<int> vec;
    for (int i = 0; i < 50000; i++) {
        vec.push_back(i);
    }

    Span sp(50000);
    
    // Should properly calculate distance without overflow
    EXPECT_NO_THROW(sp.addRange(vec.begin(), vec.end()));
    EXPECT_EQ(sp.longestSpan(), 49999u);
}

// ============================================
// Large Scale Tests (10,000+ numbers)
// ============================================

TEST(SpanLargeTest, TenThousandNumbers) {
    Span sp(10000);

    for (int i = 0; i < 10000; i++) {
        sp.addNumber(i);
    }

    EXPECT_EQ(sp.shortestSpan(), 1);
    EXPECT_EQ(sp.longestSpan(), 9999);
}

TEST(SpanLargeTest, TenThousandViaRange) {
    std::vector<int> vec;
    for (int i = 0; i < 10000; i++) {
        vec.push_back(i * 2);  // Even numbers: 0, 2, 4, ...
    }

    Span sp(10000);
    sp.addRange(vec.begin(), vec.end());

    EXPECT_EQ(sp.shortestSpan(), 2);
    EXPECT_EQ(sp.longestSpan(), 19998);
}

TEST(SpanLargeTest, HundredThousandNumbers) {
    Span sp(100000);

    for (int i = 0; i < 100000; i++) {
        sp.addNumber(i);
    }

    EXPECT_EQ(sp.shortestSpan(), 1);
    EXPECT_EQ(sp.longestSpan(), 99999);
}

// ============================================
// Edge Cases
// ============================================

TEST(SpanEdgeTest, ExtremeValues) {
    Span sp(2);
    sp.addNumber(-2147483648);  // INT_MIN
    sp.addNumber(2147483647);   // INT_MAX

    // This might overflow - implementation should handle it
    // At minimum, should not crash
    EXPECT_GE(sp.longestSpan(), 0u);
}

TEST(SpanEdgeTest, AddAfterFullRangeAdd) {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    Span sp(5);
    sp.addRange(vec.begin(), vec.end());
    sp.addNumber(10);
    sp.addNumber(20);

    EXPECT_EQ(sp.longestSpan(), 19);  // 20 - 1
}

TEST(SpanEdgeTest, MixedAddMethods) {
    Span sp(10);
    sp.addNumber(100);

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(50);

    sp.addRange(vec.begin(), vec.end());
    sp.addNumber(200);

    EXPECT_EQ(sp.longestSpan(), 199);  // 200 - 1
}
