/* ************************************************************************** */
/*                                                                            */
/*   TestModule00Ex01.cpp - PhoneBook Tests                                 */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../ex01/headers/PhoneBook.hpp"
#include "../ex01/headers/Contact.hpp"
#include <sstream>
#include <cstdlib>

// C++98 compatible int to string conversion
static std::string intToString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

// Test Contact class
class ContactTest : public ::testing::Test {
protected:
    Contact contact;
};

TEST_F(ContactTest, DefaultConstructor) {
    EXPECT_TRUE(contact.getFirstName().empty());
    EXPECT_TRUE(contact.getLastName().empty());
    EXPECT_TRUE(contact.getNickname().empty());
}

TEST_F(ContactTest, SetAndGetFields) {
    contact.setFirstName("John");
    contact.setLastName("Doe");
    contact.setNickname("JD");
    contact.setPhoneNumber("1234567890");
    contact.setDarkestSecret("Loves C++");

    EXPECT_EQ(contact.getFirstName(), "John");
    EXPECT_EQ(contact.getLastName(), "Doe");
    EXPECT_EQ(contact.getNickname(), "JD");
    EXPECT_EQ(contact.getPhoneNumber(), "1234567890");
    EXPECT_EQ(contact.getDarkestSecret(), "Loves C++");
}

TEST_F(ContactTest, IsValidWithAllFields) {
    contact.setFirstName("John");
    contact.setLastName("Doe");
    contact.setNickname("JD");
    contact.setPhoneNumber("1234567890");
    contact.setDarkestSecret("Secret");

    EXPECT_TRUE(contact.isValid());
}

TEST_F(ContactTest, IsInvalidWithEmptyFields) {
    EXPECT_FALSE(contact.isValid());
    
    contact.setFirstName("John");
    EXPECT_FALSE(contact.isValid());
    
    contact.setLastName("Doe");
    EXPECT_FALSE(contact.isValid());
    
    contact.setNickname("JD");
    EXPECT_FALSE(contact.isValid());
    
    contact.setPhoneNumber("1234567890");
    EXPECT_FALSE(contact.isValid());
}

// Test PhoneBook class
class PhoneBookTest : public ::testing::Test {
protected:
    PhoneBook phoneBook;
    
    Contact createContact(const std::string& firstName,
                         const std::string& lastName,
                         const std::string& nickname,
                         const std::string& phone,
                         const std::string& secret) {
        Contact c;
        c.setFirstName(firstName);
        c.setLastName(lastName);
        c.setNickname(nickname);
        c.setPhoneNumber(phone);
        c.setDarkestSecret(secret);
        return c;
    }
};

TEST_F(PhoneBookTest, InitiallyEmpty) {
    EXPECT_EQ(phoneBook.getContactCount(), 0);
}

TEST_F(PhoneBookTest, AddOneContact) {
    Contact c = createContact("Alice", "Smith", "Ali", "5551234", "Loves coffee");
    phoneBook.addContact(c);
    
    EXPECT_EQ(phoneBook.getContactCount(), 1);
}

TEST_F(PhoneBookTest, AddMultipleContacts) {
    for (int i = 0; i < 5; i++) {
        Contact c = createContact("First" + intToString(i),
                                 "Last" + intToString(i),
                                 "Nick" + intToString(i),
                                 "555000" + intToString(i),
                                 "Secret" + intToString(i));
        phoneBook.addContact(c);
    }
    
    EXPECT_EQ(phoneBook.getContactCount(), 5);
}

TEST_F(PhoneBookTest, MaxCapacityIs8) {
    for (int i = 0; i < 10; i++) {
        Contact c = createContact("First" + intToString(i),
                                 "Last" + intToString(i),
                                 "Nick" + intToString(i),
                                 "555000" + intToString(i),
                                 "Secret" + intToString(i));
        phoneBook.addContact(c);
    }
    
    EXPECT_EQ(phoneBook.getContactCount(), 8);
}

TEST_F(PhoneBookTest, OldestContactReplacedWhenFull) {
    // Add 8 contacts
    for (int i = 0; i < 8; i++) {
        Contact c = createContact("First" + intToString(i),
                                 "Last" + intToString(i),
                                 "Nick" + intToString(i),
                                 "555000" + intToString(i),
                                 "Secret" + intToString(i));
        phoneBook.addContact(c);
    }
    
    // Add 9th contact - should replace index 0
    Contact newContact = createContact("NewFirst", "NewLast", "NewNick", "5559999", "NewSecret");
    phoneBook.addContact(newContact);
    
    EXPECT_EQ(phoneBook.getContactCount(), 8);
    
    // The contact at index 0 should now be the new contact
    Contact retrieved = phoneBook.getContact(0);
    EXPECT_EQ(retrieved.getFirstName(), "NewFirst");
}

TEST_F(PhoneBookTest, GetContactByValidIndex) {
    Contact c = createContact("Bob", "Jones", "BJ", "5555678", "Night owl");
    phoneBook.addContact(c);
    
    Contact retrieved = phoneBook.getContact(0);
    EXPECT_EQ(retrieved.getFirstName(), "Bob");
    EXPECT_EQ(retrieved.getLastName(), "Jones");
}

TEST_F(PhoneBookTest, GetContactByInvalidIndex) {
    Contact c = createContact("Bob", "Jones", "BJ", "5555678", "Night owl");
    phoneBook.addContact(c);
    
    // Out of bounds indices should return empty contact
    Contact invalid1 = phoneBook.getContact(-1);
    Contact invalid2 = phoneBook.getContact(8);
    Contact invalid3 = phoneBook.getContact(5);
    
    EXPECT_FALSE(invalid1.isValid());
    EXPECT_FALSE(invalid2.isValid());
    EXPECT_FALSE(invalid3.isValid());
}

TEST_F(PhoneBookTest, TruncateLongStrings) {
    std::string longString = "ThisIsAVeryLongStringThatExceedsTenCharacters";
    std::string truncated = phoneBook.truncate(longString, 10);
    
    EXPECT_EQ(truncated.length(), 10);
    EXPECT_EQ(truncated[9], '.');
}

TEST_F(PhoneBookTest, DoNotTruncateShortStrings) {
    std::string shortString = "Short";
    std::string result = phoneBook.truncate(shortString, 10);
    
    EXPECT_EQ(result, shortString);
}

TEST_F(PhoneBookTest, DisplayContactsList) {
    Contact c1 = createContact("John", "Doe", "JD", "5551111", "Secret1");
    Contact c2 = createContact("Jane", "Smith", "JS", "5552222", "Secret2");
    Contact c3 = createContact("VeryLongFirstName", "VeryLongLastName", "VeryLongNickname", "5553333", "Secret3");
    
    phoneBook.addContact(c1);
    phoneBook.addContact(c2);
    phoneBook.addContact(c3);
    
    // Redirect cout to test output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    phoneBook.displayContacts();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    // Check that output contains expected elements
    EXPECT_TRUE(output.find("John") != std::string::npos);
    EXPECT_TRUE(output.find("Jane") != std::string::npos);
    EXPECT_TRUE(output.find("VeryLongF.") != std::string::npos);  // Truncated
}

TEST_F(PhoneBookTest, EmptyPhoneBookDisplay) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    phoneBook.displayContacts();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("PhoneBook is empty") != std::string::npos ||
                output.find("No contacts") != std::string::npos);
}
