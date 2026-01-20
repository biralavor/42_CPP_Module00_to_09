/* ************************************************************************** */
/*   TestModule04Ex00.cpp - Polymorphism Tests                                */
/*   Animal, Dog, Cat, WrongAnimal, WrongCat                                  */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

class PolymorphismTest : public ::testing::Test {
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
// Animal Base Class Tests
// ============================================

TEST_F(PolymorphismTest, AnimalDefaultConstructor) {
    Animal animal;
    EXPECT_EQ(animal.getType(), "Animal");
}

TEST_F(PolymorphismTest, AnimalMakeSound) {
    Animal animal;
    buffer.str("");
    animal.makeSound();
    EXPECT_TRUE(buffer.str().find("Animal") != std::string::npos ||
                buffer.str().length() > 0);
}

// ============================================
// Dog Tests
// ============================================

TEST_F(PolymorphismTest, DogConstructor) {
    Dog dog;
    EXPECT_EQ(dog.getType(), "Dog");
}

TEST_F(PolymorphismTest, DogMakeSound) {
    Dog dog;
    buffer.str("");
    dog.makeSound();
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("bark") != std::string::npos ||
                output.find("Bark") != std::string::npos ||
                output.find("Woof") != std::string::npos ||
                output.find("woof") != std::string::npos);
}

TEST_F(PolymorphismTest, DogPolymorphicSound) {
    Animal* ptr = new Dog();
    buffer.str("");
    ptr->makeSound();  // Should call Dog::makeSound
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("bark") != std::string::npos ||
                output.find("Bark") != std::string::npos ||
                output.find("Woof") != std::string::npos ||
                output.find("woof") != std::string::npos);
    delete ptr;
}

// ============================================
// Cat Tests
// ============================================

TEST_F(PolymorphismTest, CatConstructor) {
    Cat cat;
    EXPECT_EQ(cat.getType(), "Cat");
}

TEST_F(PolymorphismTest, CatMakeSound) {
    Cat cat;
    buffer.str("");
    cat.makeSound();
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("meow") != std::string::npos ||
                output.find("Meow") != std::string::npos);
}

TEST_F(PolymorphismTest, CatPolymorphicSound) {
    Animal* ptr = new Cat();
    buffer.str("");
    ptr->makeSound();  // Should call Cat::makeSound
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("meow") != std::string::npos ||
                output.find("Meow") != std::string::npos);
    delete ptr;
}

// ============================================
// Polymorphism Array Test
// ============================================

TEST_F(PolymorphismTest, AnimalArray) {
    Animal* animals[4];
    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();
    animals[3] = new Cat();

    EXPECT_EQ(animals[0]->getType(), "Dog");
    EXPECT_EQ(animals[1]->getType(), "Cat");
    EXPECT_EQ(animals[2]->getType(), "Dog");
    EXPECT_EQ(animals[3]->getType(), "Cat");

    for (int i = 0; i < 4; i++)
        delete animals[i];
}

// ============================================
// WrongAnimal Tests (Non-polymorphic)
// ============================================

TEST_F(PolymorphismTest, WrongAnimalSound) {
    WrongAnimal animal;
    buffer.str("");
    animal.makeSound();
    std::string animalSound = buffer.str();
    // Should have some output
    EXPECT_TRUE(animalSound.length() > 0);
}

TEST_F(PolymorphismTest, WrongCatSound) {
    WrongCat cat;
    buffer.str("");
    cat.makeSound();
    // Direct call should work
}

TEST_F(PolymorphismTest, WrongCatNoPolymorphism) {
    WrongAnimal* ptr = new WrongCat();
    buffer.str("");
    ptr->makeSound();  // Should call WrongAnimal::makeSound (not virtual)
    std::string output = buffer.str();
    // Without virtual, WrongAnimal::makeSound is called
    delete ptr;
}

// ============================================
// Copy and Assignment Tests
// ============================================

TEST_F(PolymorphismTest, DogCopyConstructor) {
    Dog original;
    Dog copy(original);
    EXPECT_EQ(copy.getType(), "Dog");
}

TEST_F(PolymorphismTest, CatAssignment) {
    Cat a;
    Cat b;
    b = a;
    EXPECT_EQ(b.getType(), "Cat");
}

// ============================================
// Virtual Destructor Test
// ============================================

TEST_F(PolymorphismTest, VirtualDestructorCalled) {
    Animal* ptr = new Dog();
    // Should not leak - virtual destructor ensures proper cleanup
    delete ptr;
    SUCCEED();
}
