/* ************************************************************************** */
/*                                                                            */
/*   TestModule03Ex02.cpp - FragTrap Tests                                  */
/*   Inheritance - Another Derived Class                                     */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include "../ex02/headers/FragTrap.hpp"

class FragTrapTest : public ::testing::Test {
protected:
    void SetUp() override {
        old_cout = std::cout.rdbuf(buffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(old_cout);
        buffer.str("");
        buffer.clear();
    }

    std::stringstream buffer;
    std::streambuf* old_cout;
};

// ============================================
// Constructor Tests - FragTrap Default Values
// ============================================

TEST_F(FragTrapTest, DefaultConstructorValues) {
    FragTrap frag;

    EXPECT_EQ(frag.getName(), "Default");
    EXPECT_EQ(frag.getHitPoints(), 100);
    EXPECT_EQ(frag.getEnergyPoints(), 100);
    EXPECT_EQ(frag.getAttackDamage(), 30);
}

TEST_F(FragTrapTest, NameConstructorValues) {
    FragTrap frag("Powerhouse");

    EXPECT_EQ(frag.getName(), "Powerhouse");
    EXPECT_EQ(frag.getHitPoints(), 100);
    EXPECT_EQ(frag.getEnergyPoints(), 100);
    EXPECT_EQ(frag.getAttackDamage(), 30);
}

TEST_F(FragTrapTest, CopyConstructor) {
    FragTrap original("Original");
    original.setHitPoints(80);
    FragTrap copy(original);

    EXPECT_EQ(copy.getName(), "Original");
    EXPECT_EQ(copy.getHitPoints(), 80);
}

TEST_F(FragTrapTest, AssignmentOperator) {
    FragTrap a("RobotA");
    FragTrap b("RobotB");
    a.setEnergyPoints(60);
    b = a;

    EXPECT_EQ(b.getName(), "RobotA");
    EXPECT_EQ(b.getEnergyPoints(), 60);
}

// ============================================
// Inheritance Tests
// ============================================

TEST_F(FragTrapTest, InheritsFromClapTrap) {
    FragTrap frag("Inherited");

    frag.setHitPoints(50);
    EXPECT_EQ(frag.getHitPoints(), 50);

    frag.setEnergyPoints(25);
    EXPECT_EQ(frag.getEnergyPoints(), 25);

    frag.setAttackDamage(10);
    EXPECT_EQ(frag.getAttackDamage(), 10);
}

TEST_F(FragTrapTest, InheritedAttack) {
    FragTrap frag("Fighter");
    int initialEnergy = frag.getEnergyPoints();

    frag.attack("Target");

    EXPECT_EQ(frag.getEnergyPoints(), initialEnergy - 1);
}

TEST_F(FragTrapTest, InheritedTakeDamage) {
    FragTrap frag("Tank");

    frag.takeDamage(50);

    EXPECT_EQ(frag.getHitPoints(), 100 - 50);
}

TEST_F(FragTrapTest, InheritedBeRepaired) {
    FragTrap frag("Mechanic");
    frag.setHitPoints(30);

    frag.beRepaired(40);

    EXPECT_EQ(frag.getHitPoints(), 70);
    EXPECT_EQ(frag.getEnergyPoints(), 100 - 1);
}

// ============================================
// HighFivesGuys Tests (FragTrap Special Ability)
// ============================================

TEST_F(FragTrapTest, HighFivesGuysReducesEnergy) {
    FragTrap frag("Friendly");
    int initialEnergy = frag.getEnergyPoints();

    frag.highFivesGuys();

    EXPECT_EQ(frag.getEnergyPoints(), initialEnergy - 1);
}

TEST_F(FragTrapTest, HighFivesGuysPrintsMessage) {
    FragTrap frag("Friendly");
    buffer.str("");

    frag.highFivesGuys();

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Friendly") != std::string::npos);
    EXPECT_TRUE(output.find("high five") != std::string::npos ||
                output.find("High Five") != std::string::npos ||
                output.find("five") != std::string::npos);
}

// ============================================
// Constructor/Destructor Order Tests
// ============================================

TEST_F(FragTrapTest, ConstructorPrintsClapTrapFirst) {
    buffer.str("");
    {
        FragTrap frag("OrderTest");
    }

    std::string output = buffer.str();
    size_t clapPos = output.find("ClapTrap");
    size_t fragPos = output.find("FragTrap");

    EXPECT_TRUE(clapPos != std::string::npos);
    EXPECT_TRUE(fragPos != std::string::npos);
    EXPECT_LT(clapPos, fragPos);
}

// ============================================
// Compare With ScavTrap Tests
// ============================================

TEST_F(FragTrapTest, DifferentFromScavTrapValues) {
    FragTrap frag("Frag");
    ScavTrap scav("Scav");

    // FragTrap has more energy than ScavTrap
    EXPECT_GT(frag.getEnergyPoints(), scav.getEnergyPoints());

    // FragTrap has more attack damage than ScavTrap
    EXPECT_GT(frag.getAttackDamage(), scav.getAttackDamage());

    // Both have same hit points
    EXPECT_EQ(frag.getHitPoints(), scav.getHitPoints());
}

// ============================================
// Combat Simulation Tests
// ============================================

TEST_F(FragTrapTest, FullCombatSequence) {
    FragTrap frag("Powerhouse");

    // Attack (high damage: 30)
    frag.attack("Enemy");
    EXPECT_EQ(frag.getEnergyPoints(), 99);

    // Take damage
    frag.takeDamage(60);
    EXPECT_EQ(frag.getHitPoints(), 40);

    // Repair
    frag.beRepaired(30);
    EXPECT_EQ(frag.getHitPoints(), 70);
    EXPECT_EQ(frag.getEnergyPoints(), 98);

    // High five
    frag.highFivesGuys();
    EXPECT_EQ(frag.getEnergyPoints(), 97);
}

TEST_F(FragTrapTest, EnergyIntensiveBattle) {
    FragTrap frag("Tireless");

    // FragTrap has 100 energy, can do many actions
    for (int i = 0; i < 50; i++) {
        frag.attack("Target");
    }

    EXPECT_EQ(frag.getEnergyPoints(), 50);
}

TEST_F(FragTrapTest, HighFiveSpam) {
    FragTrap frag("Enthusiastic");

    for (int i = 0; i < 10; i++) {
        frag.highFivesGuys();
    }

    EXPECT_EQ(frag.getEnergyPoints(), 100 - 10);
}
