/* ************************************************************************** */
/*                                                                            */
/*   TestModule08Ex00.cpp - easyfind Function Template Tests                  */
/*   STL Containers and Algorithms                                            */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <deque>
#include "../ex00/easyfind.hpp"

// ============================================
// Tests with std::vector
// ============================================

TEST(EasyfindVectorTest, FindExistingElement) {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    std::vector<int>::iterator it = easyfind(vec, 3);

    EXPECT_NE(it, vec.end());
    EXPECT_EQ(*it, 3);
}

TEST(EasyfindVectorTest, FindFirstElement) {
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    std::vector<int>::iterator it = easyfind(vec, 10);

    EXPECT_NE(it, vec.end());
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(it, vec.begin());
}

TEST(EasyfindVectorTest, FindLastElement) {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::vector<int>::iterator it = easyfind(vec, 3);

    EXPECT_NE(it, vec.end());
    EXPECT_EQ(*it, 3);
}

TEST(EasyfindVectorTest, ElementNotFound) {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    EXPECT_THROW(easyfind(vec, 99), std::exception);
}

TEST(EasyfindVectorTest, EmptyContainer) {
    std::vector<int> vec;

    EXPECT_THROW(easyfind(vec, 1), std::exception);
}

TEST(EasyfindVectorTest, FindFirstOccurrence) {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(2);
    vec.push_back(2);
    vec.push_back(3);

    std::vector<int>::iterator it = easyfind(vec, 2);

    EXPECT_NE(it, vec.end());
    EXPECT_EQ(*it, 2);
    // Should be the first occurrence (index 1)
    EXPECT_EQ(it - vec.begin(), 1);
}

TEST(EasyfindVectorTest, NegativeNumbers) {
    std::vector<int> vec;
    vec.push_back(-5);
    vec.push_back(-3);
    vec.push_back(0);
    vec.push_back(3);
    vec.push_back(5);

    std::vector<int>::iterator it = easyfind(vec, -3);

    EXPECT_NE(it, vec.end());
    EXPECT_EQ(*it, -3);
}

TEST(EasyfindVectorTest, FindZero) {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(0);
    vec.push_back(2);

    std::vector<int>::iterator it = easyfind(vec, 0);

    EXPECT_NE(it, vec.end());
    EXPECT_EQ(*it, 0);
}

// ============================================
// Tests with std::list
// ============================================

TEST(EasyfindListTest, FindExistingElement) {
    std::list<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);

    std::list<int>::iterator it = easyfind(lst, 30);

    EXPECT_NE(it, lst.end());
    EXPECT_EQ(*it, 30);
}

TEST(EasyfindListTest, ElementNotFound) {
    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    EXPECT_THROW(easyfind(lst, 100), std::exception);
}

TEST(EasyfindListTest, EmptyList) {
    std::list<int> lst;

    EXPECT_THROW(easyfind(lst, 1), std::exception);
}

TEST(EasyfindListTest, SingleElement) {
    std::list<int> lst;
    lst.push_back(42);

    std::list<int>::iterator it = easyfind(lst, 42);

    EXPECT_NE(it, lst.end());
    EXPECT_EQ(*it, 42);
}

// ============================================
// Tests with std::deque
// ============================================

TEST(EasyfindDequeTest, FindExistingElement) {
    std::deque<int> deq;
    deq.push_back(100);
    deq.push_back(200);
    deq.push_back(300);

    std::deque<int>::iterator it = easyfind(deq, 200);

    EXPECT_NE(it, deq.end());
    EXPECT_EQ(*it, 200);
}

TEST(EasyfindDequeTest, ElementNotFound) {
    std::deque<int> deq;
    deq.push_back(1);
    deq.push_back(2);

    EXPECT_THROW(easyfind(deq, 999), std::exception);
}

// ============================================
// Large Container Tests
// ============================================

TEST(EasyfindLargeTest, FindInLargeVector) {
    std::vector<int> vec;
    for (int i = 0; i < 10000; i++) {
        vec.push_back(i);
    }

    std::vector<int>::iterator it = easyfind(vec, 5000);

    EXPECT_NE(it, vec.end());
    EXPECT_EQ(*it, 5000);
}

TEST(EasyfindLargeTest, NotFoundInLargeVector) {
    std::vector<int> vec;
    for (int i = 0; i < 10000; i++) {
        vec.push_back(i);
    }

    EXPECT_THROW(easyfind(vec, 99999), std::exception);
}

// ============================================
// Edge Cases
// ============================================

TEST(EasyfindEdgeTest, AllSameElements) {
    std::vector<int> vec;
    for (int i = 0; i < 10; i++) {
        vec.push_back(42);
    }

    std::vector<int>::iterator it = easyfind(vec, 42);

    EXPECT_NE(it, vec.end());
    EXPECT_EQ(*it, 42);
    EXPECT_EQ(it, vec.begin());  // Should be first element
}

TEST(EasyfindEdgeTest, LargeNumbers) {
    std::vector<int> vec;
    vec.push_back(2147483647);  // INT_MAX
    vec.push_back(-2147483648); // INT_MIN
    vec.push_back(0);

    std::vector<int>::iterator it1 = easyfind(vec, 2147483647);
    EXPECT_EQ(*it1, 2147483647);

    std::vector<int>::iterator it2 = easyfind(vec, -2147483648);
    EXPECT_EQ(*it2, -2147483648);
}
