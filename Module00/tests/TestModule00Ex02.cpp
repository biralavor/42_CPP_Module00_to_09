/* ************************************************************************** */
/*                                                                            */
/*   TestModule00Ex02.cpp - Account Tests                                   */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../ex02/headers/Account.hpp"
#include <sstream>
#include <vector>

class AccountTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset static variables before each test
        Account::_nbAccounts = 0;
        Account::_totalAmount = 0;
        Account::_totalNbDeposits = 0;
        Account::_totalNbWithdrawals = 0;
    }
};

TEST_F(AccountTest, InitialAccountCreation) {
    Account acc(42);
    
    EXPECT_EQ(acc.checkAmount(), 42);
    EXPECT_EQ(Account::getNbAccounts(), 1);
    EXPECT_EQ(Account::getTotalAmount(), 42);
}

TEST_F(AccountTest, MultipleAccountsCreation) {
    Account acc1(100);
    Account acc2(200);
    Account acc3(300);
    
    EXPECT_EQ(Account::getNbAccounts(), 3);
    EXPECT_EQ(Account::getTotalAmount(), 600);
}

TEST_F(AccountTest, MakeDeposit) {
    Account acc(50);
    
    acc.makeDeposit(25);
    
    EXPECT_EQ(acc.checkAmount(), 75);
    EXPECT_EQ(Account::getTotalAmount(), 75);
    EXPECT_EQ(Account::getTotalNbDeposits(), 1);
}

TEST_F(AccountTest, MultipleDeposits) {
    Account acc(100);
    
    acc.makeDeposit(50);
    acc.makeDeposit(30);
    acc.makeDeposit(20);
    
    EXPECT_EQ(acc.checkAmount(), 200);
    EXPECT_EQ(Account::getTotalNbDeposits(), 3);
}

TEST_F(AccountTest, MakeWithdrawalSuccess) {
    Account acc(100);
    
    bool result = acc.makeWithdrawal(30);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(acc.checkAmount(), 70);
    EXPECT_EQ(Account::getTotalAmount(), 70);
    EXPECT_EQ(Account::getTotalNbWithdrawals(), 1);
}

TEST_F(AccountTest, MakeWithdrawalFailure) {
    Account acc(50);
    
    bool result = acc.makeWithdrawal(100);
    
    EXPECT_FALSE(result);
    EXPECT_EQ(acc.checkAmount(), 50);  // Amount should remain unchanged
    EXPECT_EQ(Account::getTotalNbWithdrawals(), 0);
}

TEST_F(AccountTest, WithdrawalExactAmount) {
    Account acc(100);
    
    bool result = acc.makeWithdrawal(100);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(acc.checkAmount(), 0);
}

TEST_F(AccountTest, MultipleWithdrawals) {
    Account acc(200);
    
    bool result1 = acc.makeWithdrawal(50);
    bool result2 = acc.makeWithdrawal(30);
    bool result3 = acc.makeWithdrawal(20);
    
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
    EXPECT_TRUE(result3);
    EXPECT_EQ(acc.checkAmount(), 100);
    EXPECT_EQ(Account::getTotalNbWithdrawals(), 3);
}

TEST_F(AccountTest, GetNbDeposits) {
    Account acc(100);
    
    acc.makeDeposit(10);
    acc.makeDeposit(20);
    
    EXPECT_EQ(Account::getTotalNbDeposits(), 2);
}

TEST_F(AccountTest, GetNbWithdrawals) {
    Account acc(100);
    
    acc.makeWithdrawal(10);
    acc.makeWithdrawal(20);
    
    EXPECT_EQ(Account::getTotalNbWithdrawals(), 2);
}

TEST_F(AccountTest, DisplayAccountsInfo) {
    std::vector<Account*> accounts;
    accounts.push_back(new Account(42));
    accounts.push_back(new Account(54));
    accounts.push_back(new Account(957));
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    Account::displayAccountsInfos();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    // Check that output contains expected information
    EXPECT_TRUE(output.find("accounts:3") != std::string::npos ||
                output.find("accounts") != std::string::npos);
    EXPECT_TRUE(output.find("total:1053") != std::string::npos ||
                output.find("1053") != std::string::npos);
    
    // Cleanup
    for (auto acc : accounts) {
        delete acc;
    }
}

TEST_F(AccountTest, DisplayStatus) {
    Account acc(100);
    acc.makeDeposit(50);
    acc.makeWithdrawal(20);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    acc.displayStatus();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    // Check that output contains account information
    EXPECT_TRUE(output.find("amount:130") != std::string::npos ||
                output.find("130") != std::string::npos);
    EXPECT_TRUE(output.find("deposits:1") != std::string::npos);
    EXPECT_TRUE(output.find("withdrawals:1") != std::string::npos);
}

TEST_F(AccountTest, ComplexScenario) {
    // Similar to the test from the subject
    std::vector<Account*> accounts;
    accounts.push_back(new Account(42));
    accounts.push_back(new Account(54));
    accounts.push_back(new Account(957));
    accounts.push_back(new Account(432));
    accounts.push_back(new Account(1234));
    accounts.push_back(new Account(0));
    accounts.push_back(new Account(754));
    accounts.push_back(new Account(16576));
    
    EXPECT_EQ(Account::getNbAccounts(), 8);
    EXPECT_EQ(Account::getTotalAmount(), 20049);
    
    // Make deposits
    accounts[0]->makeDeposit(5);
    accounts[1]->makeDeposit(765);
    accounts[2]->makeDeposit(564);
    accounts[3]->makeDeposit(2);
    accounts[4]->makeDeposit(87);
    accounts[5]->makeDeposit(23);
    accounts[6]->makeDeposit(9);
    accounts[7]->makeDeposit(20);
    
    EXPECT_EQ(Account::getTotalAmount(), 21524);
    EXPECT_EQ(Account::getTotalNbDeposits(), 8);
    
    // Make withdrawals
    accounts[0]->makeWithdrawal(321);  // Should fail
    accounts[1]->makeWithdrawal(34);
    accounts[2]->makeWithdrawal(657);
    accounts[3]->makeWithdrawal(4);
    accounts[4]->makeWithdrawal(76);
    accounts[5]->makeWithdrawal(657); // Should fail
    accounts[6]->makeWithdrawal(7);
    accounts[7]->makeWithdrawal(657);
    
    EXPECT_EQ(Account::getTotalAmount(), 20320);
    EXPECT_EQ(Account::getTotalNbWithdrawals(), 6);
    
    // Cleanup
    for (auto acc : accounts) {
        delete acc;
    }
}

TEST_F(AccountTest, ZeroInitialDeposit) {
    Account acc(0);
    
    EXPECT_EQ(acc.checkAmount(), 0);
    
    bool result = acc.makeWithdrawal(10);
    EXPECT_FALSE(result);
    
    acc.makeDeposit(50);
    EXPECT_EQ(acc.checkAmount(), 50);
}
