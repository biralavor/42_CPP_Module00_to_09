/* ************************************************************************** */
/*                                                                            */
/*   TestModule01Ex01.cpp - ZombieHorde Tests (Moar brainz!)                */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../ex01/headers/Zombie.hpp"
#include "../ex01/headers/ZombieHorde.hpp"
#include <sstream>

class ZombieHordeTest : public ::testing::Test {
protected:
    void SetUp() override {
        old_cout = std::cout.rdbuf(buffer.rdbuf());
    }
    
    void TearDown() override {
        std::cout.rdbuf(old_cout);
    }
    
    std::stringstream buffer;
    std::streambuf* old_cout;
};

TEST_F(ZombieHordeTest, CreateHordeOfOne) {
    Zombie* horde = zombieHorde(1, "SingleZombie");
    
    EXPECT_NE(horde, NULL);
    
    horde[0].announce();
    
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("SingleZombie") != std::string::npos);
    
    delete[] horde;
}

TEST_F(ZombieHordeTest, CreateHordeOfMultiple) {
    int N = 5;
    Zombie* horde = zombieHorde(N, "HordeZombie");
    
    EXPECT_NE(horde, NULL);
    
    // Each zombie should announce
    for (int i = 0; i < N; i++) {
        horde[i].announce();
    }
    
    std::string output = buffer.str();
    
    // Count occurrences of "HordeZombie"
    size_t pos = 0;
    int count = 0;
    while ((pos = output.find("HordeZombie", pos)) != std::string::npos) {
        count++;
        pos++;
    }
    EXPECT_GE(count, N);
    
    delete[] horde;
}

TEST_F(ZombieHordeTest, SingleAllocation) {
    // All zombies should be allocated in a single allocation
    int N = 10;
    Zombie* horde = zombieHorde(N, "ArrayZombie");
    
    EXPECT_NE(horde, NULL);
    
    // Check memory is contiguous (addresses are sequential)
    for (int i = 0; i < N - 1; i++) {
        ptrdiff_t diff = reinterpret_cast<char*>(&horde[i + 1]) - 
                        reinterpret_cast<char*>(&horde[i]);
        EXPECT_EQ(diff, sizeof(Zombie));
    }
    
    delete[] horde;
}

TEST_F(ZombieHordeTest, AllZombiesHaveSameName) {
    int N = 7;
    Zombie* horde = zombieHorde(N, "ClonedZombie");
    
    // Clear buffer from constructor messages
    buffer.str("");
    
    // Each zombie should have the same name
    for (int i = 0; i < N; i++) {
        horde[i].announce();
    }
    
    std::string output = buffer.str();
    
    // All should have "ClonedZombie"
    size_t pos = 0;
    int count = 0;
    while ((pos = output.find("ClonedZombie", pos)) != std::string::npos) {
        count++;
        pos++;
    }
    EXPECT_EQ(count, N);
    
    delete[] horde;
}

TEST_F(ZombieHordeTest, HordeDestruction) {
    int N = 3;
    Zombie* horde = zombieHorde(N, "MortalZombie");
    
    buffer.str(""); // Clear construction messages
    
    delete[] horde;
    
    std::string output = buffer.str();
    
    // Destructor messages should appear for all zombies
    EXPECT_TRUE(output.find("MortalZombie") != std::string::npos);
}

TEST_F(ZombieHordeTest, LargeHorde) {
    int N = 100;
    Zombie* horde = zombieHorde(N, "MassZombie");
    
    EXPECT_NE(horde, NULL);
    
    // Test a few random zombies
    horde[0].announce();
    horde[50].announce();
    horde[99].announce();
    
    delete[] horde;
}

TEST_F(ZombieHordeTest, ZeroSizedHorde) {
    // Edge case: requesting 0 zombies
    Zombie* horde = zombieHorde(0, "NoZombie");
    
    // Behavior depends on implementation
    // It might return NULL or a valid pointer
    // Just ensure it doesn't crash
    
    if (horde != NULL) {
        delete[] horde;
    }
}

TEST_F(ZombieHordeTest, HordeWithEmptyName) {
    int N = 5;
    Zombie* horde = zombieHorde(N, "");
    
    EXPECT_NE(horde, NULL);
    
    buffer.str("");
    horde[0].announce();
    
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("BraiiiiiiinnnzzzZ") != std::string::npos);
    
    delete[] horde;
}

TEST_F(ZombieHordeTest, MultipleHordes) {
    Zombie* horde1 = zombieHorde(3, "Horde1");
    Zombie* horde2 = zombieHorde(5, "Horde2");
    Zombie* horde3 = zombieHorde(2, "Horde3");
    
    EXPECT_NE(horde1, NULL);
    EXPECT_NE(horde2, NULL);
    EXPECT_NE(horde3, NULL);
    
    // All hordes should be independent
    EXPECT_NE(horde1, horde2);
    EXPECT_NE(horde2, horde3);
    EXPECT_NE(horde1, horde3);
    
    delete[] horde1;
    delete[] horde2;
    delete[] horde3;
}

TEST_F(ZombieHordeTest, AnnounceAllZombies) {
    int N = 4;
    Zombie* horde = zombieHorde(N, "Announcer");
    
    buffer.str("");
    
    // Announce all zombies in the horde
    for (int i = 0; i < N; i++) {
        horde[i].announce();
    }
    
    std::string output = buffer.str();
    
    // Should have N announcements
    size_t pos = 0;
    int count = 0;
    while ((pos = output.find("BraiiiiiiinnnzzzZ", pos)) != std::string::npos) {
        count++;
        pos++;
    }
    EXPECT_EQ(count, N);
    
    delete[] horde;
}

// Memory leak test - valgrind would be better, but we can check basics
TEST(ZombieHordeMemoryTest, NoLeaksWithMultipleAllocations) {
    // Allocate and deallocate multiple hordes
    for (int i = 0; i < 10; i++) {
        Zombie* horde = zombieHorde(5, "TempHorde");
        delete[] horde;
    }
    
    // If we got here without crashing, basic memory management works
    SUCCEED();
}
