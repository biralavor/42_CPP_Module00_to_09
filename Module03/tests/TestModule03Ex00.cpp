/* ************************************************************************** */
/*                                                                            */
/*   TestModule03Ex00.cpp - ClapTrap Tests                                  */
/*   Inheritance - Base Class                                                */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include "../ex00/headers/ClapTrap.hpp"

class ClapTrapTest : public ::testing::Test {
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
// Constructor Tests
// ============================================

TEST_F(ClapTrapTest, DefaultConstructor) {
    ClapTrap clap;

    EXPECT_EQ(clap.getName(), "Default");
    EXPECT_EQ(clap.getHitPoints(), 10);
    EXPECT_EQ(clap.getEnergyPoints(), 10);
    EXPECT_EQ(clap.getAttackDamage(), 0);
}

TEST_F(ClapTrapTest, NameConstructor) {
    ClapTrap clap("TestBot");

    EXPECT_EQ(clap.getName(), "TestBot");
    EXPECT_EQ(clap.getHitPoints(), 10);
    EXPECT_EQ(clap.getEnergyPoints(), 10);
    EXPECT_EQ(clap.getAttackDamage(), 0);
}

TEST_F(ClapTrapTest, CopyConstructor) {
    ClapTrap original("Original");
    original.setAttackDamage(5);
    ClapTrap copy(original);

    EXPECT_EQ(copy.getName(), "Original");
    EXPECT_EQ(copy.getAttackDamage(), 5);
}

TEST_F(ClapTrapTest, AssignmentOperator) {
    ClapTrap a("RobotA");
    ClapTrap b("RobotB");
    a.setAttackDamage(7);
    b = a;

    EXPECT_EQ(b.getName(), "RobotA");
    EXPECT_EQ(b.getAttackDamage(), 7);
}

// ============================================
// Getter/Setter Tests
// ============================================

TEST_F(ClapTrapTest, SetHitPoints) {
    ClapTrap clap("Test");
    clap.setHitPoints(50);
    EXPECT_EQ(clap.getHitPoints(), 50);
}

TEST_F(ClapTrapTest, SetEnergyPoints) {
    ClapTrap clap("Test");
    clap.setEnergyPoints(25);
    EXPECT_EQ(clap.getEnergyPoints(), 25);
}

TEST_F(ClapTrapTest, SetAttackDamage) {
    ClapTrap clap("Test");
    clap.setAttackDamage(15);
    EXPECT_EQ(clap.getAttackDamage(), 15);
}

// ============================================
// Attack Tests
// ============================================

TEST_F(ClapTrapTest, AttackReducesEnergy) {
    ClapTrap clap("Attacker");
    int initialEnergy = clap.getEnergyPoints();

    clap.attack("Target");

    EXPECT_EQ(clap.getEnergyPoints(), initialEnergy - 1);
}

TEST_F(ClapTrapTest, AttackPrintsMessage) {
    ClapTrap clap("Attacker");
    buffer.str("");

    clap.attack("Enemy");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Attacker") != std::string::npos);
    EXPECT_TRUE(output.find("Enemy") != std::string::npos);
    EXPECT_TRUE(output.find("attack") != std::string::npos);
}

TEST_F(ClapTrapTest, AttackWithNoEnergy) {
    ClapTrap clap("Exhausted");
    clap.setEnergyPoints(0);

    clap.attack("Target");

    EXPECT_EQ(clap.getEnergyPoints(), 0);
}

TEST_F(ClapTrapTest, MultipleAttacksDepletesEnergy) {
    ClapTrap clap("Fighter");

    for (int i = 0; i < 10; i++) {
        clap.attack("Target");
    }

    EXPECT_EQ(clap.getEnergyPoints(), 0);
}

// ============================================
// TakeDamage Tests
// ============================================

TEST_F(ClapTrapTest, TakeDamageReducesHitPoints) {
    ClapTrap clap("Victim");
    int initialHit = clap.getHitPoints();

    clap.takeDamage(3);

    EXPECT_EQ(clap.getHitPoints(), initialHit - 3);
}

TEST_F(ClapTrapTest, TakeDamagePrintsMessage) {
    ClapTrap clap("Victim");
    buffer.str("");

    clap.takeDamage(5);

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Victim") != std::string::npos);
    EXPECT_TRUE(output.find("damage") != std::string::npos);
}

TEST_F(ClapTrapTest, TakeDamageCanGoNegative) {
    ClapTrap clap("Fragile");
    clap.setHitPoints(5);

    clap.takeDamage(10);

    EXPECT_LE(clap.getHitPoints(), 0);
}

TEST_F(ClapTrapTest, TakeDamageWithNoHitPoints) {
    ClapTrap clap("Dead");
    clap.setHitPoints(0);

    clap.takeDamage(5);

    EXPECT_EQ(clap.getHitPoints(), 0);
}

// ============================================
// BeRepaired Tests
// ============================================

TEST_F(ClapTrapTest, BeRepairedIncreasesHitPoints) {
    ClapTrap clap("Damaged");
    clap.setHitPoints(5);
    int initialHit = clap.getHitPoints();

    clap.beRepaired(3);

    EXPECT_EQ(clap.getHitPoints(), initialHit + 3);
}

TEST_F(ClapTrapTest, BeRepairedReducesEnergy) {
    ClapTrap clap("Repairing");
    int initialEnergy = clap.getEnergyPoints();

    clap.beRepaired(2);

    EXPECT_EQ(clap.getEnergyPoints(), initialEnergy - 1);
}

TEST_F(ClapTrapTest, BeRepairedPrintsMessage) {
    ClapTrap clap("Repairing");
    buffer.str("");

    clap.beRepaired(5);

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Repairing") != std::string::npos);
    EXPECT_TRUE(output.find("repair") != std::string::npos);
}

TEST_F(ClapTrapTest, BeRepairedWithNoEnergy) {
    ClapTrap clap("Exhausted");
    clap.setEnergyPoints(0);
    clap.setHitPoints(5);

    clap.beRepaired(10);

    EXPECT_EQ(clap.getHitPoints(), 5);
}

// ============================================
// Interaction Tests
// ============================================

TEST_F(ClapTrapTest, CombatSequence) {
    ClapTrap attacker("Attacker");
    ClapTrap defender("Defender");

    attacker.setAttackDamage(3);
    attacker.attack("Defender");
    defender.takeDamage(attacker.getAttackDamage());

    EXPECT_EQ(defender.getHitPoints(), 10 - 3);
    EXPECT_EQ(attacker.getEnergyPoints(), 10 - 1);
}

TEST_F(ClapTrapTest, RepairAfterDamage) {
    ClapTrap clap("Survivor");

    clap.takeDamage(5);
    EXPECT_EQ(clap.getHitPoints(), 5);

    clap.beRepaired(3);
    EXPECT_EQ(clap.getHitPoints(), 8);
}
