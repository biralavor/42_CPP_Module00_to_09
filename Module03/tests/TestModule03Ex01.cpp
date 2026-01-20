/* ************************************************************************** */
/*                                                                            */
/*   TestModule03Ex01.cpp - ScavTrap Tests                                  */
/*   Inheritance - Derived Class                                             */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include "../ex01/headers/ScavTrap.hpp"

class ScavTrapTest : public ::testing::Test {
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
// Constructor Tests - ScavTrap Default Values
// ============================================

TEST_F(ScavTrapTest, DefaultConstructorValues) {
    ScavTrap scav;

    EXPECT_EQ(scav.getName(), "Default");
    EXPECT_EQ(scav.getHitPoints(), 100);
    EXPECT_EQ(scav.getEnergyPoints(), 50);
    EXPECT_EQ(scav.getAttackDamage(), 20);
}

TEST_F(ScavTrapTest, NameConstructorValues) {
    ScavTrap scav("Guardian");

    EXPECT_EQ(scav.getName(), "Guardian");
    EXPECT_EQ(scav.getHitPoints(), 100);
    EXPECT_EQ(scav.getEnergyPoints(), 50);
    EXPECT_EQ(scav.getAttackDamage(), 20);
}

TEST_F(ScavTrapTest, CopyConstructor) {
    ScavTrap original("Original");
    original.setHitPoints(75);
    ScavTrap copy(original);

    EXPECT_EQ(copy.getName(), "Original");
    EXPECT_EQ(copy.getHitPoints(), 75);
}

TEST_F(ScavTrapTest, AssignmentOperator) {
    ScavTrap a("RobotA");
    ScavTrap b("RobotB");
    a.setHitPoints(80);
    b = a;

    EXPECT_EQ(b.getName(), "RobotA");
    EXPECT_EQ(b.getHitPoints(), 80);
}

// ============================================
// Inheritance Tests
// ============================================

TEST_F(ScavTrapTest, InheritsFromClapTrap) {
    ScavTrap scav("Inherited");

    // Test inherited methods work
    scav.setHitPoints(50);
    EXPECT_EQ(scav.getHitPoints(), 50);

    scav.setEnergyPoints(25);
    EXPECT_EQ(scav.getEnergyPoints(), 25);

    scav.setAttackDamage(10);
    EXPECT_EQ(scav.getAttackDamage(), 10);
}

TEST_F(ScavTrapTest, InheritedTakeDamage) {
    ScavTrap scav("Tank");

    scav.takeDamage(30);

    EXPECT_EQ(scav.getHitPoints(), 100 - 30);
}

TEST_F(ScavTrapTest, InheritedBeRepaired) {
    ScavTrap scav("Mechanic");
    scav.setHitPoints(50);

    scav.beRepaired(20);

    EXPECT_EQ(scav.getHitPoints(), 70);
    EXPECT_EQ(scav.getEnergyPoints(), 50 - 1);
}

// ============================================
// Attack Override Tests
// ============================================

TEST_F(ScavTrapTest, AttackReducesEnergy) {
    ScavTrap scav("Attacker");
    int initialEnergy = scav.getEnergyPoints();

    scav.attack("Target");

    EXPECT_EQ(scav.getEnergyPoints(), initialEnergy - 1);
}

TEST_F(ScavTrapTest, AttackPrintsScavTrapMessage) {
    ScavTrap scav("Fighter");
    buffer.str("");

    scav.attack("Enemy");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("ScavTrap") != std::string::npos);
    EXPECT_TRUE(output.find("Fighter") != std::string::npos);
}

TEST_F(ScavTrapTest, AttackWithNoEnergy) {
    ScavTrap scav("Tired");
    scav.setEnergyPoints(0);

    scav.attack("Target");

    EXPECT_EQ(scav.getEnergyPoints(), 0);
}

// ============================================
// GuardGate Tests (ScavTrap Special Ability)
// ============================================

TEST_F(ScavTrapTest, GuardGateReducesEnergy) {
    ScavTrap scav("Sentinel");
    int initialEnergy = scav.getEnergyPoints();

    scav.guardGate();

    EXPECT_EQ(scav.getEnergyPoints(), initialEnergy - 1);
}

TEST_F(ScavTrapTest, GuardGatePrintsMessage) {
    ScavTrap scav("Sentinel");
    buffer.str("");

    scav.guardGate();

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Sentinel") != std::string::npos);
    EXPECT_TRUE(output.find("Gate") != std::string::npos ||
                output.find("gate") != std::string::npos);
}

// ============================================
// Constructor/Destructor Order Tests
// ============================================

TEST_F(ScavTrapTest, ConstructorPrintsClapTrapFirst) {
    buffer.str("");
    {
        ScavTrap scav("OrderTest");
    }

    std::string output = buffer.str();
    // ClapTrap constructor should be called first (appears earlier in output)
    size_t clapPos = output.find("ClapTrap");
    size_t scavPos = output.find("ScavTrap");

    EXPECT_TRUE(clapPos != std::string::npos);
    EXPECT_TRUE(scavPos != std::string::npos);
    EXPECT_LT(clapPos, scavPos);
}

// ============================================
// Combat Simulation Tests
// ============================================

TEST_F(ScavTrapTest, FullCombatSequence) {
    ScavTrap scav("Warrior");

    // Attack
    scav.attack("Enemy");
    EXPECT_EQ(scav.getEnergyPoints(), 49);

    // Take damage
    scav.takeDamage(40);
    EXPECT_EQ(scav.getHitPoints(), 60);

    // Repair
    scav.beRepaired(20);
    EXPECT_EQ(scav.getHitPoints(), 80);
    EXPECT_EQ(scav.getEnergyPoints(), 48);

    // Guard gate
    scav.guardGate();
    EXPECT_EQ(scav.getEnergyPoints(), 47);
}

TEST_F(ScavTrapTest, MultipleGuardGateCalls) {
    ScavTrap scav("MultiGuard");

    for (int i = 0; i < 5; i++) {
        scav.guardGate();
    }

    EXPECT_EQ(scav.getEnergyPoints(), 50 - 5);
}
