/* ************************************************************************** */
/*   TestModule09Ex02.cpp - PmergeMe (Ford-Johnson Sort) Tests               */
/*   Merge-insert sort with two containers comparison                        */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../ex02/headers/PmergeMe.hpp"

// ============================================
// Input Validation Tests
// ============================================

TEST(PmergeMeInputTest, ValidInput) {
    EXPECT_NO_THROW(PmergeMe("3 5 9 7 4"));
}

TEST(PmergeMeInputTest, SingleNumber) {
    EXPECT_NO_THROW(PmergeMe("42"));
}

TEST(PmergeMeInputTest, LargeNumbers) {
    EXPECT_NO_THROW(PmergeMe("999999 1 500000 250000 750000"));
}

TEST(PmergeMeInputTest, ExtraSpaces) {
    EXPECT_NO_THROW(PmergeMe("3  5  9  7  4"));
}

TEST(PmergeMeInputTest, NegativeNumber) {
    EXPECT_THROW(PmergeMe("-1 2 3"), std::exception);
}

TEST(PmergeMeInputTest, NegativeInMiddle) {
    EXPECT_THROW(PmergeMe("3 -5 9 7 4"), std::exception);
}

TEST(PmergeMeInputTest, InvalidCharacters) {
    EXPECT_THROW(PmergeMe("abc"), std::exception);
    EXPECT_THROW(PmergeMe("1 2 abc 4"), std::exception);
}

TEST(PmergeMeInputTest, SpecialCharacters) {
    EXPECT_THROW(PmergeMe("1 2 + 3"), std::exception);
    EXPECT_THROW(PmergeMe("1,2,3"), std::exception);
}

TEST(PmergeMeInputTest, EmptyInput) {
    EXPECT_THROW(PmergeMe(""), std::exception);
}

TEST(PmergeMeInputTest, WhitespaceOnly) {
    EXPECT_THROW(PmergeMe("   "), std::exception);
}

// ============================================
// Sorting Tests (via sortManager)
// ============================================

TEST(PmergeMeSortTest, SubjectExample) {
    PmergeMe pm("3 5 9 7 4");
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeSortTest, AlreadySorted) {
    PmergeMe pm("1 2 3 4 5");
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeSortTest, ReverseSorted) {
    PmergeMe pm("5 4 3 2 1");
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeSortTest, SingleElement) {
    PmergeMe pm("42");
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeSortTest, TwoElements) {
    PmergeMe pm("5 3");
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeSortTest, ThreeElements) {
    PmergeMe pm("9 1 5");
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeSortTest, Duplicates) {
    PmergeMe pm("5 3 5 1 3");
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeSortTest, AllSameValues) {
    PmergeMe pm("7 7 7 7 7");
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeSortTest, OddCount) {
    PmergeMe pm("8 4 1 6 3 9 2 7 5");
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeSortTest, EvenCount) {
    PmergeMe pm("8 4 1 6 3 9 2 7");
    EXPECT_NO_THROW(pm.sortManager());
}

// ============================================
// Large Input Tests
// ============================================

TEST(PmergeMeLargeTest, ThreeThousandElements) {
    std::ostringstream oss;
    for (int i = 3000; i > 0; i--) {
        if (i < 3000)
            oss << " ";
        oss << i;
    }
    PmergeMe pm(oss.str());
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeLargeTest, FiveThousandElements) {
    std::ostringstream oss;
    for (int i = 5000; i > 0; i--) {
        if (i < 5000)
            oss << " ";
        oss << i;
    }
    PmergeMe pm(oss.str());
    EXPECT_NO_THROW(pm.sortManager());
}

TEST(PmergeMeLargeTest, ThreeThousandWithDuplicates) {
    std::ostringstream oss;
    for (int i = 0; i < 3000; i++) {
        if (i > 0)
            oss << " ";
        oss << (i % 500);
    }
    PmergeMe pm(oss.str());
    EXPECT_NO_THROW(pm.sortManager());
}

// ============================================
// Sorted Output Verification Tests
// ============================================

TEST(PmergeMeVerifyTest, VectorIsSorted) {
    PmergeMe pm("3 5 9 7 4");
    pm.sortManager();
    const std::vector<int>& vec = pm.getVector();
    for (size_t i = 1; i < vec.size(); i++)
        EXPECT_LE(vec[i - 1], vec[i]);
}

TEST(PmergeMeVerifyTest, DequeIsSorted) {
    PmergeMe pm("3 5 9 7 4");
    pm.sortManager();
    const std::deque<int>& deq = pm.getDeque();
    for (size_t i = 1; i < deq.size(); i++)
        EXPECT_LE(deq[i - 1], deq[i]);
}

TEST(PmergeMeVerifyTest, VectorAndDequeMatch) {
    PmergeMe pm("8 4 1 6 3 9 2 7 5");
    pm.sortManager();
    const std::vector<int>& vec = pm.getVector();
    const std::deque<int>& deq = pm.getDeque();
    EXPECT_EQ(vec.size(), deq.size());
    for (size_t i = 0; i < vec.size(); i++)
        EXPECT_EQ(vec[i], deq[i]);
}

TEST(PmergeMeVerifyTest, PreservesAllElements) {
    PmergeMe pm("5 3 8 1 9");
    pm.sortManager();
    const std::vector<int>& vec = pm.getVector();
    EXPECT_EQ(vec.size(), 5u);
    int sum = 0;
    for (size_t i = 0; i < vec.size(); i++)
        sum += vec[i];
    EXPECT_EQ(sum, 5 + 3 + 8 + 1 + 9);
}

TEST(PmergeMeVerifyTest, ReverseSortedIsSorted) {
    PmergeMe pm("5 4 3 2 1");
    pm.sortManager();
    const std::vector<int>& vec = pm.getVector();
    for (size_t i = 0; i < vec.size(); i++)
        EXPECT_EQ(vec[i], static_cast<int>(i + 1));
}

TEST(PmergeMeVerifyTest, DuplicatesAreSorted) {
    PmergeMe pm("5 3 5 1 3");
    pm.sortManager();
    const std::vector<int>& vec = pm.getVector();
    for (size_t i = 1; i < vec.size(); i++)
        EXPECT_LE(vec[i - 1], vec[i]);
}

TEST(PmergeMeVerifyTest, LargeInputIsSorted) {
    std::ostringstream oss;
    for (int i = 3000; i > 0; i--) {
        if (i < 3000)
            oss << " ";
        oss << i;
    }
    PmergeMe pm(oss.str());
    pm.sortManager();
    const std::vector<int>& vec = pm.getVector();
    EXPECT_EQ(vec.size(), 3000u);
    for (size_t i = 1; i < vec.size(); i++)
        EXPECT_LE(vec[i - 1], vec[i]);
}
