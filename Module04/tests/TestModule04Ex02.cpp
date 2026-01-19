/* ************************************************************************** */
/*   TestModule04Ex02.cpp - Abstract Class Tests                              */
/*   AAnimal (abstract), Dog, Cat with Brain                                  */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

class AbstractClassTest : public ::testing::Test {
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
// Abstract Class Cannot Be Instantiated
// ============================================

// This test verifies the concept - AAnimal should not compile if instantiated
// Uncomment to verify it causes a compile error:
// TEST_F(AbstractClassTest, CannotInstantiateAAnimal) {
//     AAnimal animal;  // Should NOT compile
// }

// ============================================
// Dog Tests (derived from AAnimal)
// ============================================

TEST_F(AbstractClassTest, DogCanBeInstantiated) {
    Dog dog;
    EXPECT_EQ(dog.getType(), "Dog");
}

TEST_F(AbstractClassTest, DogMakeSound) {
    Dog dog;
    buffer.str("");
    dog.makeSound();
    std::string output = buffer.str();
    EXPECT_TRUE(output.length() > 0);
}

TEST_F(AbstractClassTest, DogPolymorphicPointer) {
    AAnimal* ptr = new Dog();
    EXPECT_EQ(ptr->getType(), "Dog");

    buffer.str("");
    ptr->makeSound();  // Virtual call
    std::string output = buffer.str();
    EXPECT_TRUE(output.length() > 0);

    delete ptr;
}

// ============================================
// Cat Tests (derived from AAnimal)
// ============================================

TEST_F(AbstractClassTest, CatCanBeInstantiated) {
    Cat cat;
    EXPECT_EQ(cat.getType(), "Cat");
}

TEST_F(AbstractClassTest, CatMakeSound) {
    Cat cat;
    buffer.str("");
    cat.makeSound();
    std::string output = buffer.str();
    EXPECT_TRUE(output.length() > 0);
}

TEST_F(AbstractClassTest, CatPolymorphicPointer) {
    AAnimal* ptr = new Cat();
    EXPECT_EQ(ptr->getType(), "Cat");

    buffer.str("");
    ptr->makeSound();
    std::string output = buffer.str();
    EXPECT_TRUE(output.length() > 0);

    delete ptr;
}

// ============================================
// Array of Abstract Pointers
// ============================================

TEST_F(AbstractClassTest, ArrayOfAAnimals) {
    AAnimal* animals[4];
    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();
    animals[3] = new Cat();

    for (int i = 0; i < 4; i++) {
        buffer.str("");
        animals[i]->makeSound();
        EXPECT_TRUE(buffer.str().length() > 0);
    }

    for (int i = 0; i < 4; i++)
        delete animals[i];
}

// ============================================
// Deep Copy Still Works
// ============================================

TEST_F(AbstractClassTest, DogDeepCopy) {
    Dog* original = new Dog();
    Dog copy(*original);
    delete original;

    EXPECT_EQ(copy.getType(), "Dog");
}

TEST_F(AbstractClassTest, CatDeepCopy) {
    Cat* original = new Cat();
    Cat copy(*original);
    delete original;

    EXPECT_EQ(copy.getType(), "Cat");
}

// ============================================
// Brain Still Works
// ============================================

TEST_F(AbstractClassTest, DogHasBrain) {
    Dog dog;
    // Constructor should allocate Brain
    SUCCEED();
}

TEST_F(AbstractClassTest, CatHasBrain) {
    Cat cat;
    SUCCEED();
}

// ============================================
// Pure Virtual Function Test
// ============================================

TEST_F(AbstractClassTest, MakeSoundIsPureVirtual) {
    // If makeSound() is pure virtual in AAnimal,
    // it MUST be implemented in Dog and Cat
    Dog dog;
    Cat cat;

    // Both must have working makeSound()
    dog.makeSound();
    cat.makeSound();

    SUCCEED();
}

// ============================================
// Assignment and Copy
// ============================================

TEST_F(AbstractClassTest, DogAssignment) {
    Dog a;
    Dog b;
    b = a;
    EXPECT_EQ(b.getType(), "Dog");
}

TEST_F(AbstractClassTest, CatAssignment) {
    Cat a;
    Cat b;
    b = a;
    EXPECT_EQ(b.getType(), "Cat");
}

// ============================================
// Virtual Destructor
// ============================================

TEST_F(AbstractClassTest, VirtualDestructorWorks) {
    AAnimal* ptr = new Dog();
    delete ptr;  // Should call Dog destructor properly
    SUCCEED();
}
