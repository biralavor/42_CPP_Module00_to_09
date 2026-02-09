/* ************************************************************************** */
/*   TestModule08Ex02.cpp - MutantStack Tests                                 */
/*   STL - Iterable Stack Container                                           */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <list>
#include "../ex02/headers/MutantStack.hpp"

// ============================================
// Basic Stack Operations
// ============================================

TEST(MutantStackBasicTest, PushAndTop) {
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    EXPECT_EQ(mstack.top(), 17);
}

TEST(MutantStackBasicTest, Pop) {
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.pop();
    EXPECT_EQ(mstack.size(), 1u);
}

TEST(MutantStackBasicTest, Size) {
    MutantStack<int> mstack;
    EXPECT_EQ(mstack.size(), 0u);
    mstack.push(1);
    mstack.push(2);
    EXPECT_EQ(mstack.size(), 2u);
}

TEST(MutantStackBasicTest, Empty) {
    MutantStack<int> mstack;
    EXPECT_TRUE(mstack.empty());
    mstack.push(42);
    EXPECT_FALSE(mstack.empty());
}

// ============================================
// Iterator Tests
// ============================================

TEST(MutantStackIteratorTest, BeginEnd) {
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    EXPECT_NE(it, ite);
}

TEST(MutantStackIteratorTest, IterateAll) {
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(3);
    mstack.push(737);
    mstack.push(0);

    int sum = 0;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        sum += *it;

    EXPECT_EQ(sum, 745);  // 5+3+737+0
}

TEST(MutantStackIteratorTest, IncrementDecrement) {
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);

    MutantStack<int>::iterator it = mstack.begin();
    ++it;
    --it;
    EXPECT_EQ(*it, 1);
}

TEST(MutantStackIteratorTest, ModifyThroughIterator) {
    MutantStack<int> mstack;
    mstack.push(10);
    mstack.push(20);

    MutantStack<int>::iterator it = mstack.begin();
    *it = 100;

    it = mstack.begin();
    EXPECT_EQ(*it, 100);
}

// ============================================
// Subject Example Test
// ============================================

TEST(MutantStackSubjectTest, ExactExample) {
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    EXPECT_EQ(mstack.top(), 17);

    mstack.pop();
    EXPECT_EQ(mstack.size(), 1u);

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    std::vector<int> values;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        values.push_back(*it);

    EXPECT_EQ(values.size(), 5u);
}

// ============================================
// Comparison with std::list
// ============================================

TEST(MutantStackCompareTest, SameAsListOutput) {
    MutantStack<int> mstack;
    std::list<int> lst;

    mstack.push(5);   lst.push_back(5);
    mstack.push(17);  lst.push_back(17);
    mstack.pop();     lst.pop_back();
    mstack.push(3);   lst.push_back(3);
    mstack.push(737); lst.push_back(737);

    std::vector<int> stackVals, listVals;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        stackVals.push_back(*it);
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
        listVals.push_back(*it);

    EXPECT_EQ(stackVals, listVals);
}

// ============================================
// Copy and Assignment
// ============================================

TEST(MutantStackCopyTest, CopyConstructor) {
    MutantStack<int> original;
    original.push(1);
    original.push(2);

    MutantStack<int> copy(original);
    EXPECT_EQ(copy.top(), 2);
    EXPECT_EQ(copy.size(), 2u);
}

TEST(MutantStackCopyTest, AssignmentOperator) {
    MutantStack<int> a;
    a.push(10);

    MutantStack<int> b;
    b = a;

    EXPECT_EQ(b.top(), 10);
}

TEST(MutantStackCopyTest, CopyIsIndependent) {
    MutantStack<int> original;
    original.push(100);

    MutantStack<int> copy(original);
    copy.push(200);

    EXPECT_EQ(original.size(), 1u);
    EXPECT_EQ(copy.size(), 2u);
}

// ============================================
// Different Types
// ============================================

TEST(MutantStackTypesTest, StringStack) {
    MutantStack<std::string> mstack;
    mstack.push("hello");
    mstack.push("world");

    EXPECT_EQ(mstack.top(), "world");

    std::string concat;
    for (MutantStack<std::string>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        concat += *it;

    EXPECT_EQ(concat, "helloworld");
}

TEST(MutantStackTypesTest, DoubleStack) {
    MutantStack<double> mstack;
    mstack.push(1.5);
    mstack.push(2.5);
    mstack.push(3.5);

    double sum = 0;
    for (MutantStack<double>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        sum += *it;

    EXPECT_DOUBLE_EQ(sum, 7.5);
}

// ============================================
// Const Iterator Tests
// ============================================

TEST(MutantStackConstTest, ConstIterator) {
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);

    const MutantStack<int>& constRef = mstack;

    int sum = 0;
    for (MutantStack<int>::const_iterator it = constRef.begin(); it != constRef.end(); ++it)
        sum += *it;

    EXPECT_EQ(sum, 3);
}

// ============================================
// Convertible to std::stack
// ============================================

TEST(MutantStackConvertTest, ToStdStack) {
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);

    std::stack<int> s(mstack);

    EXPECT_EQ(s.top(), 3);
    EXPECT_EQ(s.size(), 3u);
}

// ============================================
// Edge Cases - Empty Stack
// ============================================

TEST(MutantStackEdgeTest, EmptyStackBeginEqualsEnd) {
    MutantStack<int> mstack;
    EXPECT_EQ(mstack.begin(), mstack.end());
}

TEST(MutantStackEdgeTest, EmptyStackSize) {
    MutantStack<int> mstack;
    EXPECT_EQ(mstack.size(), 0u);
    EXPECT_TRUE(mstack.empty());
}

TEST(MutantStackEdgeTest, SingleElement) {
    MutantStack<int> mstack;
    mstack.push(42);

    EXPECT_EQ(mstack.size(), 1u);
    EXPECT_EQ(mstack.top(), 42);
    EXPECT_EQ(*mstack.begin(), 42);

    MutantStack<int>::iterator it = mstack.begin();
    ++it;
    EXPECT_EQ(it, mstack.end());
}

TEST(MutantStackEdgeTest, PushPopUntilEmpty) {
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);
    mstack.pop();
    mstack.pop();
    mstack.pop();

    EXPECT_TRUE(mstack.empty());
    EXPECT_EQ(mstack.begin(), mstack.end());
}

// ============================================
// Large Scale Tests (matching Ex00/Ex01 patterns)
// ============================================

TEST(MutantStackLargeTest, TenThousandElements) {
    MutantStack<int> mstack;
    for (int i = 0; i < 10000; i++) {
        mstack.push(i);
    }

    EXPECT_EQ(mstack.size(), 10000u);
    EXPECT_EQ(mstack.top(), 9999);

    int count = 0;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        count++;
    EXPECT_EQ(count, 10000);
}

TEST(MutantStackLargeTest, IterateSumLarge) {
    MutantStack<int> mstack;
    for (int i = 1; i <= 1000; i++) {
        mstack.push(i);
    }

    long sum = 0;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        sum += *it;

    // Sum 1..1000 = n(n+1)/2 = 500500
    EXPECT_EQ(sum, 500500);
}

// ============================================
// Extreme Values (INT_MAX/INT_MIN)
// ============================================

TEST(MutantStackExtremeTest, IntMaxValue) {
    MutantStack<int> mstack;
    mstack.push(2147483647);  // INT_MAX

    EXPECT_EQ(mstack.top(), 2147483647);
    EXPECT_EQ(*mstack.begin(), 2147483647);
}

TEST(MutantStackExtremeTest, IntMinValue) {
    MutantStack<int> mstack;
    mstack.push(-2147483648);  // INT_MIN

    EXPECT_EQ(mstack.top(), -2147483648);
    EXPECT_EQ(*mstack.begin(), -2147483648);
}

TEST(MutantStackExtremeTest, MixedExtremes) {
    MutantStack<int> mstack;
    mstack.push(-2147483648);  // INT_MIN
    mstack.push(0);
    mstack.push(2147483647);   // INT_MAX

    std::vector<int> values;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        values.push_back(*it);

    EXPECT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], -2147483648);
    EXPECT_EQ(values[1], 0);
    EXPECT_EQ(values[2], 2147483647);
}

// ============================================
// Negative Numbers
// ============================================

TEST(MutantStackNegativeTest, AllNegative) {
    MutantStack<int> mstack;
    mstack.push(-100);
    mstack.push(-50);
    mstack.push(-1);

    EXPECT_EQ(mstack.top(), -1);

    int sum = 0;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        sum += *it;

    EXPECT_EQ(sum, -151);
}

TEST(MutantStackNegativeTest, MixedSigns) {
    MutantStack<int> mstack;
    mstack.push(-5);
    mstack.push(0);
    mstack.push(5);

    std::vector<int> values;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        values.push_back(*it);

    EXPECT_EQ(values[0], -5);
    EXPECT_EQ(values[1], 0);
    EXPECT_EQ(values[2], 5);
}

// ============================================
// Reverse Iterator Tests
// ============================================

TEST(MutantStackReverseTest, ReverseIteration) {
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);
    mstack.push(4);
    mstack.push(5);

    std::vector<int> reversed;
    for (MutantStack<int>::reverse_iterator it = mstack.rbegin(); it != mstack.rend(); ++it)
        reversed.push_back(*it);

    EXPECT_EQ(reversed.size(), 5u);
    EXPECT_EQ(reversed[0], 5);  // Last pushed = first in reverse
    EXPECT_EQ(reversed[4], 1);  // First pushed = last in reverse
}

TEST(MutantStackReverseTest, ReverseEmptyStack) {
    MutantStack<int> mstack;
    EXPECT_EQ(mstack.rbegin(), mstack.rend());
}

TEST(MutantStackReverseTest, ReverseSingleElement) {
    MutantStack<int> mstack;
    mstack.push(42);

    MutantStack<int>::reverse_iterator rit = mstack.rbegin();
    EXPECT_EQ(*rit, 42);
    ++rit;
    EXPECT_EQ(rit, mstack.rend());
}

TEST(MutantStackReverseTest, ReverseVsForward) {
    MutantStack<int> mstack;
    for (int i = 1; i <= 10; i++)
        mstack.push(i);

    std::vector<int> forward, reverse;

    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        forward.push_back(*it);

    for (MutantStack<int>::reverse_iterator it = mstack.rbegin(); it != mstack.rend(); ++it)
        reverse.push_back(*it);

    EXPECT_EQ(forward.size(), reverse.size());

    // Forward: 1,2,3...10 - Reverse: 10,9,8...1
    for (size_t i = 0; i < forward.size(); i++) {
        EXPECT_EQ(forward[i], reverse[forward.size() - 1 - i]);
    }
}

TEST(MutantStackReverseTest, ConstReverseIterator) {
    MutantStack<int> mstack;
    mstack.push(10);
    mstack.push(20);
    mstack.push(30);

    const MutantStack<int>& constRef = mstack;

    std::vector<int> values;
    for (MutantStack<int>::const_reverse_iterator it = constRef.rbegin();
         it != constRef.rend(); ++it) {
        values.push_back(*it);
    }

    EXPECT_EQ(values[0], 30);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 10);
}

// ============================================
// Iterator Arithmetic
// ============================================

TEST(MutantStackIteratorArithmeticTest, IncrementDecrement) {
    MutantStack<int> mstack;
    mstack.push(10);
    mstack.push(20);
    mstack.push(30);

    MutantStack<int>::iterator it = mstack.begin();
    EXPECT_EQ(*it, 10);

    ++it;
    EXPECT_EQ(*it, 20);

    ++it;
    EXPECT_EQ(*it, 30);

    --it;
    EXPECT_EQ(*it, 20);

    --it;
    EXPECT_EQ(*it, 10);
}

TEST(MutantStackIteratorArithmeticTest, PostIncrementDecrement) {
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator prev = it++;

    EXPECT_EQ(*prev, 1);
    EXPECT_EQ(*it, 2);

    MutantStack<int>::iterator curr = it--;
    EXPECT_EQ(*curr, 2);
    EXPECT_EQ(*it, 1);
}

// ============================================
// Multiple Iterations
// ============================================

TEST(MutantStackMultiIterTest, IterateTwice) {
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);

    int sum1 = 0, sum2 = 0;

    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        sum1 += *it;

    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        sum2 += *it;

    EXPECT_EQ(sum1, sum2);
    EXPECT_EQ(sum1, 6);
}

TEST(MutantStackMultiIterTest, MultipleActiveIterators) {
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);

    MutantStack<int>::iterator it1 = mstack.begin();
    MutantStack<int>::iterator it2 = mstack.begin();

    EXPECT_EQ(*it1, *it2);

    ++it1;
    EXPECT_NE(*it1, *it2);
    EXPECT_EQ(*it1, 2);
    EXPECT_EQ(*it2, 1);
}

// ============================================
// Deep Copy Verification with Iterators
// ============================================

TEST(MutantStackDeepCopyTest, CopyHasOwnIterators) {
    MutantStack<int> original;
    original.push(100);
    original.push(200);

    MutantStack<int> copy(original);

    // Modify copy through iterator
    MutantStack<int>::iterator copyIt = copy.begin();
    *copyIt = 999;

    // Original should be unchanged
    EXPECT_EQ(*original.begin(), 100);
    EXPECT_EQ(*copy.begin(), 999);
}

TEST(MutantStackDeepCopyTest, AssignmentHasOwnIterators) {
    MutantStack<int> a;
    a.push(1);
    a.push(2);

    MutantStack<int> b;
    b = a;

    // Modify b
    b.push(3);

    // a should be unchanged
    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 3u);

    std::vector<int> aVals, bVals;
    for (MutantStack<int>::iterator it = a.begin(); it != a.end(); ++it)
        aVals.push_back(*it);
    for (MutantStack<int>::iterator it = b.begin(); it != b.end(); ++it)
        bVals.push_back(*it);

    EXPECT_EQ(aVals.size(), 2u);
    EXPECT_EQ(bVals.size(), 3u);
}
