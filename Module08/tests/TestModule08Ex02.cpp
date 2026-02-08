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
