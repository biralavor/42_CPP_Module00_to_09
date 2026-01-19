/* ************************************************************************** */
/*   TestModule05Ex02.cpp - Abstract Form Tests                               */
/*   AForm, ShrubberyCreationForm, RobotomyRequestForm, PresidentialPardonForm*/
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// ============================================
// ShrubberyCreationForm Tests
// ============================================

TEST(ShrubberyFormTest, Constructor) {
    ShrubberyCreationForm form("garden");
    EXPECT_EQ(form.getName(), "ShrubberyCreationForm");
    EXPECT_EQ(form.getGradeToSign(), 145);
    EXPECT_EQ(form.getGradeToExecute(), 137);
    EXPECT_FALSE(form.isSigned());
}

TEST(ShrubberyFormTest, SignAndExecute) {
    Bureaucrat boss("Boss", 1);
    ShrubberyCreationForm form("test");

    boss.signForm(form);
    EXPECT_TRUE(form.isSigned());

    boss.executeForm(form);
    // Should create test_shrubbery file
}

TEST(ShrubberyFormTest, GradeTooLowToSign) {
    Bureaucrat intern("Intern", 150);
    ShrubberyCreationForm form("target");

    EXPECT_THROW(form.beSigned(intern), AForm::GradeTooLowException);
}

TEST(ShrubberyFormTest, NotSignedCannotExecute) {
    Bureaucrat boss("Boss", 1);
    ShrubberyCreationForm form("unsigned");

    EXPECT_THROW(form.execute(boss), AForm::FormNotSignedException);
}

// ============================================
// RobotomyRequestForm Tests
// ============================================

TEST(RobotomyFormTest, Constructor) {
    RobotomyRequestForm form("Target");
    EXPECT_EQ(form.getName(), "RobotomyRequestForm");
    EXPECT_EQ(form.getGradeToSign(), 72);
    EXPECT_EQ(form.getGradeToExecute(), 45);
}

TEST(RobotomyFormTest, SignAndExecute) {
    Bureaucrat boss("Boss", 1);
    RobotomyRequestForm form("Bender");

    boss.signForm(form);
    EXPECT_TRUE(form.isSigned());

    // Execute multiple times (50% success rate)
    for (int i = 0; i < 10; i++) {
        boss.executeForm(form);
    }
}

TEST(RobotomyFormTest, GradeTooLowToExecute) {
    Bureaucrat signer("Signer", 72);
    Bureaucrat executor("Executor", 50);  // Not high enough to execute
    RobotomyRequestForm form("Target");

    signer.signForm(form);
    EXPECT_TRUE(form.isSigned());

    EXPECT_THROW(form.execute(executor), AForm::GradeTooLowException);
}

// ============================================
// PresidentialPardonForm Tests
// ============================================

TEST(PresidentialPardonFormTest, Constructor) {
    PresidentialPardonForm form("Prisoner");
    EXPECT_EQ(form.getName(), "PresidentialPardonForm");
    EXPECT_EQ(form.getGradeToSign(), 25);
    EXPECT_EQ(form.getGradeToExecute(), 5);
}

TEST(PresidentialPardonFormTest, SignAndExecute) {
    Bureaucrat president("President", 1);
    PresidentialPardonForm form("Arthur Dent");

    president.signForm(form);
    EXPECT_TRUE(form.isSigned());

    president.executeForm(form);
    // Should print pardon message
}

TEST(PresidentialPardonFormTest, OnlyHighGradeCanSign) {
    Bureaucrat low("Low", 30);
    PresidentialPardonForm form("Target");

    EXPECT_THROW(form.beSigned(low), AForm::GradeTooLowException);
}

TEST(PresidentialPardonFormTest, OnlyHighGradeCanExecute) {
    Bureaucrat signer("Signer", 25);
    Bureaucrat executor("Executor", 10);
    PresidentialPardonForm form("Target");

    signer.signForm(form);
    EXPECT_THROW(form.execute(executor), AForm::GradeTooLowException);
}

// ============================================
// AForm Abstract Class Tests
// ============================================

TEST(AFormTest, CannotInstantiateDirectly) {
    // AForm is abstract - this should not compile if uncommented:
    // AForm form("test", 10, 5);
    SUCCEED();
}

TEST(AFormTest, CopyConstructor) {
    ShrubberyCreationForm original("original");
    ShrubberyCreationForm copy(original);

    EXPECT_EQ(copy.getName(), original.getName());
    EXPECT_EQ(copy.isSigned(), original.isSigned());
}

TEST(AFormTest, AssignmentOperator) {
    ShrubberyCreationForm a("a");
    ShrubberyCreationForm b("b");

    Bureaucrat boss("Boss", 1);
    boss.signForm(a);

    b = a;
    EXPECT_EQ(b.isSigned(), a.isSigned());
}

// ============================================
// Bureaucrat Form Integration Tests
// ============================================

TEST(BureaucratFormTest, SignFormSuccess) {
    Bureaucrat b("Signer", 100);
    ShrubberyCreationForm form("target");

    b.signForm(form);
    EXPECT_TRUE(form.isSigned());
}

TEST(BureaucratFormTest, SignFormFailure) {
    Bureaucrat b("Intern", 150);
    RobotomyRequestForm form("target");

    b.signForm(form);  // Should print failure message
    EXPECT_FALSE(form.isSigned());
}

TEST(BureaucratFormTest, ExecuteFormSuccess) {
    Bureaucrat b("Boss", 1);
    ShrubberyCreationForm form("execute_test");

    b.signForm(form);
    b.executeForm(form);
    // Should not throw
}

TEST(BureaucratFormTest, ExecuteFormNotSigned) {
    Bureaucrat b("Boss", 1);
    ShrubberyCreationForm form("unsigned");

    b.executeForm(form);  // Should print failure message
}

// ============================================
// Stream Operator Test
// ============================================

TEST(AFormStreamTest, OutputFormat) {
    ShrubberyCreationForm form("test");
    std::stringstream ss;
    ss << form;

    std::string output = ss.str();
    EXPECT_TRUE(output.find("ShrubberyCreationForm") != std::string::npos);
}
