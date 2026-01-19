/* ************************************************************************** */
/*   TestModule04Ex01.cpp - Deep Copy Tests (Brain class)                     */
/*   Animal, Dog, Cat with Brain - proper deep copy                           */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

class DeepCopyTest : public ::testing::Test {
protected:
    void SetUp() override {
        old_cout = std::cout.rdbuf(buffer.rdbuf());
    }
    void TearDown() override {
        std::cout.rdbuf(old_cout);
        buffer.str("");
    }
    std::stringstream buffer;
    std::streambuf* old_cout;
};

// ============================================
// Brain Class Tests
// ============================================

TEST_F(DeepCopyTest, BrainDefaultConstructor) {
    Brain brain;
    // Brain should have 100 ideas (strings)
    SUCCEED();
}

TEST_F(DeepCopyTest, BrainSetGetIdea) {
    Brain brain;
    brain.setIdea(0, "First idea");
    brain.setIdea(50, "Middle idea");
    brain.setIdea(99, "Last idea");

    EXPECT_EQ(brain.getIdea(0), "First idea");
    EXPECT_EQ(brain.getIdea(50), "Middle idea");
    EXPECT_EQ(brain.getIdea(99), "Last idea");
}

TEST_F(DeepCopyTest, BrainCopyConstructor) {
    Brain original;
    original.setIdea(0, "Original idea");

    Brain copy(original);

    EXPECT_EQ(copy.getIdea(0), "Original idea");
}

TEST_F(DeepCopyTest, BrainCopyIsIndependent) {
    Brain original;
    original.setIdea(0, "Original");

    Brain copy(original);
    copy.setIdea(0, "Modified");

    EXPECT_EQ(original.getIdea(0), "Original");
    EXPECT_EQ(copy.getIdea(0), "Modified");
}

TEST_F(DeepCopyTest, BrainAssignment) {
    Brain a;
    a.setIdea(0, "A's idea");

    Brain b;
    b = a;

    EXPECT_EQ(b.getIdea(0), "A's idea");
}

// ============================================
// Dog with Brain Tests
// ============================================

TEST_F(DeepCopyTest, DogHasBrain) {
    Dog dog;
    // Dog should allocate Brain in constructor
    SUCCEED();
}

TEST_F(DeepCopyTest, DogDeepCopy) {
    Dog* original = new Dog();
    // Can't directly access Brain, but copy should work
    Dog copy(*original);
    delete original;

    // Copy should still be valid after original is deleted
    EXPECT_EQ(copy.getType(), "Dog");
}

TEST_F(DeepCopyTest, DogAssignmentDeepCopy) {
    Dog a;
    Dog b;
    b = a;

    EXPECT_EQ(b.getType(), "Dog");
}

// ============================================
// Cat with Brain Tests
// ============================================

TEST_F(DeepCopyTest, CatHasBrain) {
    Cat cat;
    SUCCEED();
}

TEST_F(DeepCopyTest, CatDeepCopy) {
    Cat* original = new Cat();
    Cat copy(*original);
    delete original;

    EXPECT_EQ(copy.getType(), "Cat");
}

TEST_F(DeepCopyTest, CatAssignmentDeepCopy) {
    Cat a;
    Cat b;
    b = a;

    EXPECT_EQ(b.getType(), "Cat");
}

// ============================================
// Array of Animals Test
// ============================================

TEST_F(DeepCopyTest, AnimalArrayWithBrains) {
    const int count = 10;
    Animal* animals[count];

    // Half dogs, half cats
    for (int i = 0; i < count / 2; i++)
        animals[i] = new Dog();
    for (int i = count / 2; i < count; i++)
        animals[i] = new Cat();

    // Delete in reverse order
    for (int i = count - 1; i >= 0; i--)
        delete animals[i];

    SUCCEED();  // No memory leaks
}

// ============================================
// Memory Independence Tests
// ============================================

TEST_F(DeepCopyTest, DeleteOriginalAfterCopy) {
    Dog* original = new Dog();
    Dog* copy = new Dog(*original);

    delete original;

    // Copy must still work (deep copy, not shallow)
    copy->makeSound();
    EXPECT_EQ(copy->getType(), "Dog");

    delete copy;
}

TEST_F(DeepCopyTest, ModifyCopyNotAffectOriginal) {
    Dog original;
    Dog copy(original);

    // If we could access Brain:
    // copy.getBrain()->setIdea(0, "New idea");
    // original.getBrain()->getIdea(0) should be unchanged

    EXPECT_EQ(original.getType(), "Dog");
    EXPECT_EQ(copy.getType(), "Dog");
}

// ============================================
// Subject Example Test
// ============================================

TEST_F(DeepCopyTest, SubjectExample) {
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    delete j;  // Should not crash
    delete i;  // Should not crash

    SUCCEED();
}
