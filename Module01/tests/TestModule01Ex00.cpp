/* ************************************************************************** */
/*                                                                            */
/*   TestModule01Ex00.cpp - Zombie Tests (BraiiiiiiinnnzzzZ)                */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../ex00/headers/Zombie.hpp"
#include <sstream>

// Test Zombie class
class ZombieTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Redirect cout to capture output
        old_cout = std::cout.rdbuf(buffer.rdbuf());
    }
    
    void TearDown() override {
        // Restore cout
        std::cout.rdbuf(old_cout);
    }
    
    std::stringstream buffer;
    std::streambuf* old_cout;
};

TEST_F(ZombieTest, ZombieConstructor) {
    Zombie* zombie = new Zombie("Foo");
    EXPECT_NE(zombie, NULL);
    delete zombie;
}

TEST_F(ZombieTest, ZombieAnnounce) {
    Zombie zombie("Foo");
    
    zombie.announce();
    
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Foo: BraiiiiiiinnnzzzZ...") != std::string::npos);
}

TEST_F(ZombieTest, ZombieAnnounceFormat) {
    Zombie zombie("TestZombie");
    
    zombie.announce();
    
    std::string output = buffer.str();
    // Should not contain angle brackets
    EXPECT_TRUE(output.find("<") == std::string::npos);
    EXPECT_TRUE(output.find(">") == std::string::npos);
    // Should contain name and announcement
    EXPECT_TRUE(output.find("TestZombie") != std::string::npos);
    EXPECT_TRUE(output.find("BraiiiiiiinnnzzzZ") != std::string::npos);
}

TEST_F(ZombieTest, ZombieDestructor) {
    Zombie* zombie = new Zombie("Destructible");
    
    delete zombie;
    
    std::string output = buffer.str();
    // Destructor should print the zombie's name
    EXPECT_TRUE(output.find("Destructible") != std::string::npos);
}

// Test newZombie function
TEST(NewZombieTest, CreateOnHeap) {
    Zombie* heapZombie = newZombie("HeapZombie");
    
    EXPECT_NE(heapZombie, NULL);
    
    // Zombie should be usable outside function scope
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    heapZombie->announce();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("HeapZombie") != std::string::npos);
    
    delete heapZombie;
}

TEST(NewZombieTest, MultipleZombiesOnHeap) {
    Zombie* z1 = newZombie("Zombie1");
    Zombie* z2 = newZombie("Zombie2");
    Zombie* z3 = newZombie("Zombie3");
    
    EXPECT_NE(z1, NULL);
    EXPECT_NE(z2, NULL);
    EXPECT_NE(z3, NULL);
    
    // All should be different objects
    EXPECT_NE(z1, z2);
    EXPECT_NE(z2, z3);
    EXPECT_NE(z1, z3);
    
    delete z1;
    delete z2;
    delete z3;
}

// Test randomChump function
TEST(RandomChumpTest, CreateOnStack) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    randomChump("StackZombie");
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    // Should announce itself
    EXPECT_TRUE(output.find("StackZombie") != std::string::npos);
    EXPECT_TRUE(output.find("BraiiiiiiinnnzzzZ") != std::string::npos);
    
    // Should also be destroyed automatically (destructor message)
    // The destructor should print the zombie's name
}

TEST(RandomChumpTest, AutomaticDestruction) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    {
        randomChump("TempZombie");
    }
    // TempZombie should be destroyed here automatically
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    // Should have both announcement and destruction messages
    EXPECT_TRUE(output.find("TempZombie") != std::string::npos);
}

// Test allocation strategy
TEST(AllocationStrategyTest, HeapVsStack) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    // Heap allocation - survives scope
    Zombie* heapZombie = newZombie("HeapSurvivor");
    
    {
        // Stack allocation - destroyed at end of scope
        randomChump("StackTemporary");
    } // StackTemporary destroyed here
    
    // HeapSurvivor still exists
    heapZombie->announce();
    
    delete heapZombie; // HeapSurvivor destroyed here
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    // Both zombies should have announced and been destroyed
    EXPECT_TRUE(output.find("HeapSurvivor") != std::string::npos);
    EXPECT_TRUE(output.find("StackTemporary") != std::string::npos);
}

TEST(ZombieLifetimeTest, HeapZombieLongerLifetime) {
    Zombie* persistent = newZombie("Persistent");
    
    // Can be passed around, stored, etc.
    EXPECT_NE(persistent, NULL);
    
    // Still usable after many operations
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    persistent->announce();
    persistent->announce();
    persistent->announce();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    // Should have announced 3 times
    size_t pos = 0;
    int count = 0;
    while ((pos = output.find("Persistent", pos)) != std::string::npos) {
        count++;
        pos++;
    }
    EXPECT_GE(count, 3);
    
    delete persistent;
}

TEST(ZombieNamingTest, EmptyName) {
    Zombie* zombie = newZombie("");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    zombie->announce();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("BraiiiiiiinnnzzzZ") != std::string::npos);
    
    delete zombie;
}

TEST(ZombieNamingTest, SpecialCharacters) {
    Zombie* zombie = newZombie("Zomb!e@123");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    zombie->announce();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Zomb!e@123") != std::string::npos);
    
    delete zombie;
}
