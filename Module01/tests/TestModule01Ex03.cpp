/* ************************************************************************** */
/*                                                                            */
/*   TestModule01Ex03.cpp - Weapon, HumanA, HumanB Tests                    */
/*   (Unnecessary violence - References vs Pointers)                          */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../ex03/headers/Weapon.hpp"
#include "../ex03/headers/HumanA.hpp"
#include "../ex03/headers/HumanB.hpp"
#include <sstream>

// ============================================
// Weapon Tests
// ============================================

TEST(WeaponTest, ConstructorAndGetType) {
    Weapon club("crude spiked club");

    EXPECT_EQ(club.getType(), "crude spiked club");
}

TEST(WeaponTest, SetType) {
    Weapon club("crude spiked club");

    club.setType("some other type of club");

    EXPECT_EQ(club.getType(), "some other type of club");
}

TEST(WeaponTest, EmptyType) {
    Weapon weapon("");

    EXPECT_EQ(weapon.getType(), "");
}

TEST(WeaponTest, SpecialCharactersInType) {
    Weapon weapon("Sword of @wesome+ness!");

    EXPECT_EQ(weapon.getType(), "Sword of @wesome+ness!");
}

// ============================================
// HumanA Tests (uses REFERENCE - always armed)
// ============================================

class HumanATest : public ::testing::Test {
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

TEST_F(HumanATest, AttackWithWeapon) {
    Weapon club("crude spiked club");
    HumanA bob("Bob", club);

    bob.attack();

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Bob") != std::string::npos);
    EXPECT_TRUE(output.find("crude spiked club") != std::string::npos);
}

TEST_F(HumanATest, WeaponChangeReflectedInAttack) {
    Weapon club("crude spiked club");
    HumanA bob("Bob", club);

    bob.attack();

    club.setType("some other type of club");
    bob.attack();

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("crude spiked club") != std::string::npos);
    EXPECT_TRUE(output.find("some other type of club") != std::string::npos);
}

TEST_F(HumanATest, AttackFormat) {
    Weapon sword("longsword");
    HumanA knight("Arthur", sword);

    knight.attack();

    std::string output = buffer.str();
    // Format: "<name> attacks with their <weapon type>"
    EXPECT_TRUE(output.find("Arthur") != std::string::npos);
    EXPECT_TRUE(output.find("attacks") != std::string::npos);
    EXPECT_TRUE(output.find("longsword") != std::string::npos);
}

// ============================================
// HumanB Tests (uses POINTER - may be unarmed)
// ============================================

class HumanBTest : public ::testing::Test {
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

TEST_F(HumanBTest, CreateWithoutWeapon) {
    HumanB jim("Jim");

    // Should not crash when created without weapon
    SUCCEED();
}

TEST_F(HumanBTest, SetWeaponAndAttack) {
    Weapon club("crude spiked club");
    HumanB jim("Jim");

    jim.setWeapon(club);
    jim.attack();

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Jim") != std::string::npos);
    EXPECT_TRUE(output.find("crude spiked club") != std::string::npos);
}

TEST_F(HumanBTest, WeaponChangeReflectedInAttack) {
    Weapon club("crude spiked club");
    HumanB jim("Jim");

    jim.setWeapon(club);
    jim.attack();

    club.setType("some other type of club");
    jim.attack();

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("crude spiked club") != std::string::npos);
    EXPECT_TRUE(output.find("some other type of club") != std::string::npos);
}

TEST_F(HumanBTest, AttackWithoutWeapon) {
    HumanB jim("Jim");

    // Attacking without weapon - should handle gracefully
    jim.attack();

    // Should not crash
    SUCCEED();
}

// ============================================
// Integration Tests (both HumanA and HumanB)
// ============================================

class HumanIntegrationTest : public ::testing::Test {
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

TEST_F(HumanIntegrationTest, SubjectExample) {
    // This is the exact test from the subject
    {
        Weapon club("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club");
        bob.attack();
    }

    std::string outputA = buffer.str();
    EXPECT_TRUE(outputA.find("crude spiked club") != std::string::npos);
    EXPECT_TRUE(outputA.find("some other type of club") != std::string::npos);

    buffer.str("");

    {
        Weapon club("crude spiked club");
        HumanB jim("Jim");
        jim.setWeapon(club);
        jim.attack();
        club.setType("some other type of club");
        jim.attack();
    }

    std::string outputB = buffer.str();
    EXPECT_TRUE(outputB.find("crude spiked club") != std::string::npos);
    EXPECT_TRUE(outputB.find("some other type of club") != std::string::npos);
}

TEST_F(HumanIntegrationTest, SharedWeapon) {
    Weapon sharedWeapon("shared sword");
    HumanA alice("Alice", sharedWeapon);
    HumanB bob("Bob");
    bob.setWeapon(sharedWeapon);

    alice.attack();
    bob.attack();

    sharedWeapon.setType("upgraded sword");

    alice.attack();
    bob.attack();

    std::string output = buffer.str();

    // Both should see the weapon change
    size_t upgradeCount = 0;
    size_t pos = 0;
    while ((pos = output.find("upgraded sword", pos)) != std::string::npos) {
        upgradeCount++;
        pos++;
    }
    EXPECT_EQ(upgradeCount, 2);
}
