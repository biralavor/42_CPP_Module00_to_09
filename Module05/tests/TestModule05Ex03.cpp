/* ************************************************************************** */
/*   TestModule05Ex03.cpp - Intern Tests                                      */
/*   Intern class creates forms dynamically                                   */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

// ============================================
// Intern Constructor Tests
// ============================================

TEST(InternConstructorTest, DefaultConstructor) {
    Intern intern;
    SUCCEED();
}

TEST(InternConstructorTest, CopyConstructor) {
    Intern original;
    Intern copy(original);
    SUCCEED();
}

TEST(InternConstructorTest, AssignmentOperator) {
    Intern a;
    Intern b;
    b = a;
    SUCCEED();
}

// ============================================
// makeForm Tests - Valid Forms
// ============================================

TEST(InternMakeFormTest, CreateShrubberyForm) {
    Intern intern;
    AForm* form = intern.makeForm("shrubbery creation", "garden");

    ASSERT_NE(form, static_cast<AForm*>(NULL));
    EXPECT_EQ(form->getName(), "ShrubberyCreationForm");
    EXPECT_EQ(form->getGradeToSign(), 145);

    delete form;
}

TEST(InternMakeFormTest, CreateRobotomyForm) {
    Intern intern;
    AForm* form = intern.makeForm("robotomy request", "Bender");

    ASSERT_NE(form, static_cast<AForm*>(NULL));
    EXPECT_EQ(form->getName(), "RobotomyRequestForm");
    EXPECT_EQ(form->getGradeToSign(), 72);

    delete form;
}

TEST(InternMakeFormTest, CreatePresidentialForm) {
    Intern intern;
    AForm* form = intern.makeForm("presidential pardon", "Arthur");

    ASSERT_NE(form, static_cast<AForm*>(NULL));
    EXPECT_EQ(form->getName(), "PresidentialPardonForm");
    EXPECT_EQ(form->getGradeToSign(), 25);

    delete form;
}

// ============================================
// makeForm Tests - Invalid Forms
// ============================================

TEST(InternMakeFormTest, InvalidFormName) {
    Intern intern;
    AForm* form = intern.makeForm("invalid form name", "target");

    EXPECT_EQ(form, static_cast<AForm*>(NULL));
}

TEST(InternMakeFormTest, EmptyFormName) {
    Intern intern;
    AForm* form = intern.makeForm("", "target");

    EXPECT_EQ(form, static_cast<AForm*>(NULL));
}

TEST(InternMakeFormTest, CaseSensitivity) {
    Intern intern;

    // Test case variations
    AForm* form1 = intern.makeForm("SHRUBBERY CREATION", "test");
    AForm* form2 = intern.makeForm("Robotomy Request", "test");

    // Implementation may or may not be case-sensitive
    // Clean up any created forms
    if (form1) delete form1;
    if (form2) delete form2;
}

// ============================================
// Integration Tests
// ============================================

TEST(InternIntegrationTest, CreateAndSignForm) {
    Intern intern;
    Bureaucrat boss("Boss", 1);

    AForm* form = intern.makeForm("shrubbery creation", "office");
    ASSERT_NE(form, static_cast<AForm*>(NULL));

    boss.signForm(*form);
    EXPECT_TRUE(form->isSigned());

    delete form;
}

TEST(InternIntegrationTest, CreateAndExecuteForm) {
    Intern intern;
    Bureaucrat boss("Boss", 1);

    AForm* form = intern.makeForm("presidential pardon", "prisoner");
    ASSERT_NE(form, static_cast<AForm*>(NULL));

    boss.signForm(*form);
    boss.executeForm(*form);

    delete form;
}

TEST(InternIntegrationTest, FullWorkflow) {
    Intern intern;
    Bureaucrat ceo("CEO", 1);

    // Create all three types of forms
    AForm* shrubbery = intern.makeForm("shrubbery creation", "lobby");
    AForm* robotomy = intern.makeForm("robotomy request", "Marvin");
    AForm* pardon = intern.makeForm("presidential pardon", "Zaphod");

    ASSERT_NE(shrubbery, static_cast<AForm*>(NULL));
    ASSERT_NE(robotomy, static_cast<AForm*>(NULL));
    ASSERT_NE(pardon, static_cast<AForm*>(NULL));

    // Sign all forms
    ceo.signForm(*shrubbery);
    ceo.signForm(*robotomy);
    ceo.signForm(*pardon);

    // Execute all forms
    ceo.executeForm(*shrubbery);
    ceo.executeForm(*robotomy);
    ceo.executeForm(*pardon);

    delete shrubbery;
    delete robotomy;
    delete pardon;
}

// ============================================
// Memory Management Tests
// ============================================

TEST(InternMemoryTest, NoLeaksOnValidForm) {
    Intern intern;
    for (int i = 0; i < 100; i++) {
        AForm* form = intern.makeForm("shrubbery creation", "test");
        if (form) delete form;
    }
    SUCCEED();
}

TEST(InternMemoryTest, NoLeaksOnInvalidForm) {
    Intern intern;
    for (int i = 0; i < 100; i++) {
        AForm* form = intern.makeForm("nonexistent form", "test");
        if (form) delete form;  // Should be NULL
    }
    SUCCEED();
}

// ============================================
// Edge Cases
// ============================================

TEST(InternEdgeTest, MultipleInterns) {
    Intern intern1;
    Intern intern2;

    AForm* form1 = intern1.makeForm("shrubbery creation", "test1");
    AForm* form2 = intern2.makeForm("shrubbery creation", "test2");

    ASSERT_NE(form1, static_cast<AForm*>(NULL));
    ASSERT_NE(form2, static_cast<AForm*>(NULL));

    // Each form should be independent
    Bureaucrat boss("Boss", 1);
    boss.signForm(*form1);

    EXPECT_TRUE(form1->isSigned());
    EXPECT_FALSE(form2->isSigned());

    delete form1;
    delete form2;
}
