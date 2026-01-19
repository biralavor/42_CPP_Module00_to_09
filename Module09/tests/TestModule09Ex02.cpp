/* ************************************************************************** */
/*   TestModule09Ex02.cpp - PmergeMe (Ford-Johnson Sort) Tests                */
/*   Merge-insert sort with two containers comparison                         */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include "../ex02/PmergeMe.hpp"

// ============================================
// Basic Sorting Tests
// ============================================

TEST(PmergeMeBasicTest, SubjectExample) {
    PmergeMe sorter;
    int input[] = {3, 5, 9, 7, 4};
    std::vector<int> vec(input, input + 5);

    std::vector<int> result = sorter.sortVector(vec);

    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 5);
    EXPECT_EQ(result[3], 7);
    EXPECT_EQ(result[4], 9);
}

TEST(PmergeMeBasicTest, AlreadySorted) {
    PmergeMe sorter;
    int input[] = {1, 2, 3, 4, 5};
    std::vector<int> vec(input, input + 5);

    std::vector<int> result = sorter.sortVector(vec);

    for (size_t i = 0; i < 5; i++)
        EXPECT_EQ(result[i], static_cast<int>(i + 1));
}

TEST(PmergeMeBasicTest, ReverseSorted) {
    PmergeMe sorter;
    int input[] = {5, 4, 3, 2, 1};
    std::vector<int> vec(input, input + 5);

    std::vector<int> result = sorter.sortVector(vec);

    for (size_t i = 0; i < 5; i++)
        EXPECT_EQ(result[i], static_cast<int>(i + 1));
}

TEST(PmergeMeBasicTest, SingleElement) {
    PmergeMe sorter;
    std::vector<int> vec(1, 42);

    std::vector<int> result = sorter.sortVector(vec);

    EXPECT_EQ(result[0], 42);
}

TEST(PmergeMeBasicTest, TwoElements) {
    PmergeMe sorter;
    int input[] = {5, 3};
    std::vector<int> vec(input, input + 2);

    std::vector<int> result = sorter.sortVector(vec);

    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 5);
}

// ============================================
// Deque Tests (Second Container)
// ============================================

TEST(PmergeMeDequeTest, BasicSort) {
    PmergeMe sorter;
    int input[] = {9, 1, 5, 3, 7};
    std::deque<int> deq(input, input + 5);

    std::deque<int> result = sorter.sortDeque(deq);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 3);
    EXPECT_EQ(result[2], 5);
    EXPECT_EQ(result[3], 7);
    EXPECT_EQ(result[4], 9);
}

TEST(PmergeMeDequeTest, MatchesVectorResult) {
    PmergeMe sorter;
    int input[] = {8, 2, 6, 4, 10};

    std::vector<int> vec(input, input + 5);
    std::deque<int> deq(input, input + 5);

    std::vector<int> vecResult = sorter.sortVector(vec);
    std::deque<int> deqResult = sorter.sortDeque(deq);

    for (size_t i = 0; i < 5; i++)
        EXPECT_EQ(vecResult[i], deqResult[i]);
}

// ============================================
// Large Input Tests (3000+ elements)
// ============================================

TEST(PmergeMeLargeTest, ThreeThousandElements) {
    PmergeMe sorter;
    std::vector<int> vec;

    // Generate 3000 random-ish numbers
    for (int i = 3000; i > 0; i--)
        vec.push_back(i);

    std::vector<int> result = sorter.sortVector(vec);

    // Verify sorted
    for (size_t i = 1; i < result.size(); i++)
        EXPECT_LE(result[i - 1], result[i]);
}

TEST(PmergeMeLargeTest, FiveThousandElements) {
    PmergeMe sorter;
    std::vector<int> vec;

    for (int i = 5000; i > 0; i--)
        vec.push_back(i);

    std::vector<int> result = sorter.sortVector(vec);

    EXPECT_EQ(result.size(), 5000u);
    for (size_t i = 1; i < result.size(); i++)
        EXPECT_LE(result[i - 1], result[i]);
}

// ============================================
// Error Handling Tests
// ============================================

TEST(PmergeMeErrorTest, NegativeNumbers) {
    PmergeMe sorter;
    // Should reject negative numbers
    EXPECT_THROW(sorter.parseInput("-1 2 3"), std::exception);
}

TEST(PmergeMeErrorTest, InvalidInput) {
    PmergeMe sorter;
    EXPECT_THROW(sorter.parseInput("abc"), std::exception);
    EXPECT_THROW(sorter.parseInput("1 2 abc 4"), std::exception);
}

TEST(PmergeMeErrorTest, EmptyInput) {
    PmergeMe sorter;
    EXPECT_THROW(sorter.parseInput(""), std::exception);
}

// ============================================
// Verification Tests
// ============================================

TEST(PmergeMeVerifyTest, ResultIsSorted) {
    PmergeMe sorter;
    int input[] = {42, 17, 89, 3, 56, 12, 78, 34, 91, 25};
    std::vector<int> vec(input, input + 10);

    std::vector<int> result = sorter.sortVector(vec);

    for (size_t i = 1; i < result.size(); i++)
        EXPECT_LE(result[i - 1], result[i]);
}

TEST(PmergeMeVerifyTest, PreservesAllElements) {
    PmergeMe sorter;
    int input[] = {5, 3, 8, 1, 9};
    std::vector<int> vec(input, input + 5);

    std::vector<int> result = sorter.sortVector(vec);

    EXPECT_EQ(result.size(), vec.size());
    // Sum should be preserved
    int sumBefore = 0, sumAfter = 0;
    for (size_t i = 0; i < vec.size(); i++) sumBefore += vec[i];
    for (size_t i = 0; i < result.size(); i++) sumAfter += result[i];
    EXPECT_EQ(sumBefore, sumAfter);
}

// ============================================
// Orthodox Canonical Form Tests
// ============================================

TEST(PmergeMeOCFTest, CopyConstructor) {
    PmergeMe original;
    PmergeMe copy(original);
    // Should compile and work
}

TEST(PmergeMeOCFTest, AssignmentOperator) {
    PmergeMe a;
    PmergeMe b;
    b = a;
    // Should compile and work
}

// ============================================
// Timing Comparison (manual verification)
// ============================================

TEST(PmergeMeTimingTest, BothContainersComplete) {
    PmergeMe sorter;
    std::vector<int> vec;
    std::deque<int> deq;

    for (int i = 1000; i > 0; i--) {
        vec.push_back(i);
        deq.push_back(i);
    }

    std::vector<int> vecResult = sorter.sortVector(vec);
    std::deque<int> deqResult = sorter.sortDeque(deq);

    // Both should produce sorted output
    EXPECT_EQ(vecResult.size(), 1000u);
    EXPECT_EQ(deqResult.size(), 1000u);
}
