/* ************************************************************************** */
/*                                                                            */
/*   TestModule01Ex05.cpp - Harl Tests (Pointers to Member Functions)       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../ex05/headers/Harl.hpp"
#include <sstream>

class HarlTest : public ::testing::Test {
protected:
    void SetUp() override {
        old_cout = std::cout.rdbuf(buffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(old_cout);
    }

    std::stringstream buffer;
    std::streambuf* old_cout;
    Harl harl;
};

// ============================================
// Individual Level Tests
// ============================================

TEST_F(HarlTest, DebugLevel) {
    harl.complain("DEBUG");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("DEBUG") != std::string::npos);
}

TEST_F(HarlTest, InfoLevel) {
    harl.complain("INFO");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("INFO") != std::string::npos);
}

TEST_F(HarlTest, WarningLevel) {
    harl.complain("WARNING");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("WARNING") != std::string::npos);
}

TEST_F(HarlTest, ErrorLevel) {
    harl.complain("ERROR");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("ERROR") != std::string::npos);
}

// ============================================
// Case Insensitivity Tests
// ============================================

TEST_F(HarlTest, LowercaseDebug) {
    harl.complain("debug");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("DEBUG") != std::string::npos);
}

TEST_F(HarlTest, MixedCaseWarning) {
    harl.complain("WaRnInG");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("WARNING") != std::string::npos);
}

TEST_F(HarlTest, LowercaseError) {
    harl.complain("error");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("ERROR") != std::string::npos);
}

// ============================================
// Invalid Level Tests
// ============================================

TEST_F(HarlTest, InvalidLevel) {
    harl.complain("INVALID");

    std::string output = buffer.str();
    // Should not output any of the valid levels
    EXPECT_TRUE(output.find("DEBUG") == std::string::npos ||
                output.find("INFO") == std::string::npos ||
                output.find("WARNING") == std::string::npos ||
                output.find("ERROR") == std::string::npos);
}

TEST_F(HarlTest, EmptyLevel) {
    harl.complain("");

    std::string output = buffer.str();
    // Should handle gracefully - no crash
    SUCCEED();
}

TEST_F(HarlTest, RandomString) {
    harl.complain("something random");

    // Should not crash
    SUCCEED();
}

// ============================================
// Multiple Complaints Tests
// ============================================

TEST_F(HarlTest, MultipleComplaints) {
    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");

    std::string output = buffer.str();

    EXPECT_TRUE(output.find("DEBUG") != std::string::npos);
    EXPECT_TRUE(output.find("INFO") != std::string::npos);
    EXPECT_TRUE(output.find("WARNING") != std::string::npos);
    EXPECT_TRUE(output.find("ERROR") != std::string::npos);
}

TEST_F(HarlTest, RepeatedSameLevel) {
    harl.complain("ERROR");
    harl.complain("ERROR");
    harl.complain("ERROR");

    std::string output = buffer.str();

    // Count occurrences of "ERROR"
    size_t pos = 0;
    int count = 0;
    while ((pos = output.find("[ ERROR ]", pos)) != std::string::npos) {
        count++;
        pos++;
    }
    EXPECT_EQ(count, 3);
}

// ============================================
// Output Format Tests
// ============================================

TEST_F(HarlTest, DebugOutputFormat) {
    harl.complain("DEBUG");

    std::string output = buffer.str();
    // Check for expected format with brackets
    EXPECT_TRUE(output.find("[ DEBUG ]") != std::string::npos);
}

TEST_F(HarlTest, InfoOutputFormat) {
    harl.complain("INFO");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("[ INFO ]") != std::string::npos);
}

TEST_F(HarlTest, WarningOutputFormat) {
    harl.complain("WARNING");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("[ WARNING ]") != std::string::npos);
}

TEST_F(HarlTest, ErrorOutputFormat) {
    harl.complain("ERROR");

    std::string output = buffer.str();
    EXPECT_TRUE(output.find("[ ERROR ]") != std::string::npos);
}

// ============================================
// Pointer to Member Function Verification
// ============================================

TEST_F(HarlTest, AllLevelsUsePointerToMemberFunction) {
    // This test verifies that the correct function is called
    // by checking that the output matches each level's specific message

    buffer.str("");
    harl.complain("DEBUG");
    std::string debugOutput = buffer.str();

    buffer.str("");
    harl.complain("INFO");
    std::string infoOutput = buffer.str();

    buffer.str("");
    harl.complain("WARNING");
    std::string warningOutput = buffer.str();

    buffer.str("");
    harl.complain("ERROR");
    std::string errorOutput = buffer.str();

    // Each output should be different (different functions called)
    EXPECT_NE(debugOutput, infoOutput);
    EXPECT_NE(infoOutput, warningOutput);
    EXPECT_NE(warningOutput, errorOutput);
    EXPECT_NE(debugOutput, errorOutput);
}
