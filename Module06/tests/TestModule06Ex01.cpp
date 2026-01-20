/* ************************************************************************** */
/*                                                                            */
/*   TestModule06Ex01.cpp - Serializer TDD Tests                            */
/*   Serialization: Convert pointer to uintptr_t and back                   */
/*                                                                            */
/*   This is a TDD (Test-Driven Development) test suite.                    */
/*   Implement the Serializer and Data classes to make these tests pass!    */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <stdint.h>  // for uintptr_t
#include <string>
#include <sstream>

// C++98 compatible int to string conversion
static std::string intToString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

#include "../ex01/headers/Serializer.hpp"
#include "../ex01/headers/Data.hpp"

/*
   IMPLEMENTATION GUIDE:
   
   1. Create a Data structure with some non-empty data members:
      struct Data {
          int id;
          std::string name;
          float value;
          // Add any other members you want
      };
   
   2. Create a Serializer class that:
      - Cannot be instantiated (private constructor)
      - Has only static methods
      - Has these static methods:
        * uintptr_t serialize(Data* ptr);
          Converts pointer to unsigned integer
        * Data* deserialize(uintptr_t raw);
          Converts unsigned integer back to pointer
   
   3. Key concepts:
      - Serialization: Convert pointer address to integer
      - Deserialization: Convert integer back to pointer
      - Use reinterpret_cast<>() for conversions
      - The original pointer should be recoverable
*/


class SerializerTest : public ::testing::Test {
protected:
    Data* testData;
    
    void SetUp() override {
        testData = new Data(42, "Test", 3.14f, true);
    }
    
    void TearDown() override {
        delete testData;
    }
};

// ============================================================================
// TEST GROUP 1: BASIC SERIALIZATION/DESERIALIZATION
// ============================================================================

TEST_F(SerializerTest, SerializeReturnsNonZero) {
    // TODO: Uncomment when Serializer is implemented
    uintptr_t serialized = Serializer::serialize(testData);
    
    EXPECT_NE(serialized, 0);
    
    // For now, just a placeholder
    SUCCEED();
}

TEST_F(SerializerTest, SerializeDeserializeRoundtrip) {
    // The main test from the subject
    
    // TODO: Uncomment when Serializer is implemented
    uintptr_t serialized = Serializer::serialize(testData);
    Data* deserialized = Serializer::deserialize(serialized);
    
    // The deserialized pointer should equal the original
    EXPECT_EQ(deserialized, testData);
    
    SUCCEED();
}

TEST_F(SerializerTest, DeserializedDataIsValid) {
    // After deserialization, we should be able to access the data
    
    // TODO: Uncomment when Serializer is implemented
    uintptr_t serialized = Serializer::serialize(testData);
    Data* deserialized = Serializer::deserialize(serialized);
    
    // Check that we can access the data through deserialized pointer
    EXPECT_EQ(deserialized->id, 42);
    EXPECT_EQ(deserialized->name, "Test");
    EXPECT_FLOAT_EQ(deserialized->value, 3.14f);
    EXPECT_TRUE(deserialized->active);
    
    SUCCEED();
}

TEST_F(SerializerTest, MultiplSerializations) {
    // Test serializing multiple different pointers
    
    Data* data1 = new Data(1, "First", 1.1f, true);
    Data* data2 = new Data(2, "Second", 2.2f, false);
    Data* data3 = new Data(3, "Third", 3.3f, true);
    
    // TODO: Uncomment when Serializer is implemented
    uintptr_t s1 = Serializer::serialize(data1);
    uintptr_t s2 = Serializer::serialize(data2);
    uintptr_t s3 = Serializer::serialize(data3);
    
    // All serialized values should be different
    EXPECT_NE(s1, s2);
    EXPECT_NE(s2, s3);
    EXPECT_NE(s1, s3);
    
    // All should deserialize correctly
    Data* d1 = Serializer::deserialize(s1);
    Data* d2 = Serializer::deserialize(s2);
    Data* d3 = Serializer::deserialize(s3);
    
    EXPECT_EQ(d1, data1);
    EXPECT_EQ(d2, data2);
    EXPECT_EQ(d3, data3);
    
    delete data1;
    delete data2;
    delete data3;
    
    SUCCEED();
}

// ============================================================================
// TEST GROUP 2: POINTER PRESERVATION
// ============================================================================

TEST_F(SerializerTest, PointerAddressPreserved) {
    // The memory address should be preserved through serialization
    
    // TODO: Uncomment when Serializer is implemented
    void* originalAddress = static_cast<void*>(testData);
    uintptr_t serialized = Serializer::serialize(testData);
    Data* deserialized = Serializer::deserialize(serialized);
    void* deserializedAddress = static_cast<void*>(deserialized);
    
    EXPECT_EQ(originalAddress, deserializedAddress);
    
    SUCCEED();
}

TEST_F(SerializerTest, DataContentUnchanged) {
    // The data content should remain unchanged
    
    // TODO: Uncomment when Serializer is implemented
    Data original = *testData;
    
    uintptr_t serialized = Serializer::serialize(testData);
    Data* deserialized = Serializer::deserialize(serialized);
    
    EXPECT_EQ(*deserialized, original);
    
    SUCCEED();
}

TEST_F(SerializerTest, ModifyDataAfterSerialization) {
    // If we modify the original data, the deserialized pointer should reflect it
    // (because they point to the same memory)
    
    // TODO: Uncomment when Serializer is implemented
    uintptr_t serialized = Serializer::serialize(testData);
    
    testData->id = 999;
    testData->name = "Modified";
    
    Data* deserialized = Serializer::deserialize(serialized);
    
    EXPECT_EQ(deserialized->id, 999);
    EXPECT_EQ(deserialized->name, "Modified");
    
    SUCCEED();
}

// ============================================================================
// TEST GROUP 3: NULL AND EDGE CASES
// ============================================================================

TEST(SerializerEdgeTest, SerializeNullPointer) {
    // Test serializing a null pointer
    
    // TODO: Uncomment when Serializer is implemented
    Data* nullData = NULL;
    uintptr_t serialized = Serializer::serialize(nullData);
    
    EXPECT_EQ(serialized, 0);
    
    Data* deserialized = Serializer::deserialize(serialized);
    EXPECT_EQ(deserialized, static_cast<Data*>(NULL));
    
    SUCCEED();
}

TEST(SerializerEdgeTest, DeserializeZero) {
    // Test deserializing zero (should give null pointer)
    
    // TODO: Uncomment when Serializer is implemented
    Data* deserialized = Serializer::deserialize(0);

    EXPECT_EQ(deserialized, static_cast<Data*>(NULL));
    
    SUCCEED();
}

TEST(SerializerEdgeTest, SerializeStackObject) {
    // Test with stack-allocated object
    
    Data stackData(100, "Stack", 9.99f, false);
    
    // TODO: Uncomment when Serializer is implemented
    uintptr_t serialized = Serializer::serialize(&stackData);
    Data* deserialized = Serializer::deserialize(serialized);
    
    EXPECT_EQ(deserialized, &stackData);
    EXPECT_EQ(deserialized->id, 100);
    
    SUCCEED();
}

// ============================================================================
// TEST GROUP 4: UINTPTR_T PROPERTIES
// ============================================================================

TEST(UintPtrTest, CanStorePointer) {
    // Verify that uintptr_t can hold a pointer value
    
    Data* ptr = new Data(1, "Test", 1.0f, true);
    
    // Cast to uintptr_t and back
    uintptr_t intValue = reinterpret_cast<uintptr_t>(ptr);
    Data* restored = reinterpret_cast<Data*>(intValue);
    
    EXPECT_EQ(restored, ptr);
    EXPECT_EQ(restored->id, 1);
    
    delete ptr;
}

TEST(UintPtrTest, DifferentPointersHaveDifferentValues) {
    Data* ptr1 = new Data(1, "First", 1.0f, true);
    Data* ptr2 = new Data(2, "Second", 2.0f, false);
    
    uintptr_t int1 = reinterpret_cast<uintptr_t>(ptr1);
    uintptr_t int2 = reinterpret_cast<uintptr_t>(ptr2);
    
    EXPECT_NE(int1, int2);
    
    delete ptr1;
    delete ptr2;
}

// ============================================================================
// TEST GROUP 5: CLASS DESIGN TESTS
// ============================================================================

TEST(SerializerDesignTest, CannotInstantiate) {
    // This test ensures Serializer cannot be instantiated
    // Uncomment when implementing:
    
    // This should NOT compile if correctly implemented:
    // Serializer serializer;  // Should give compilation error
    
    SUCCEED();  // Manual verification needed
}

TEST(SerializerDesignTest, OnlyStaticMethods) {
    // Verify that methods are static by calling without instance
    
    // TODO: Uncomment when Serializer is implemented
    Data testData(1, "Test", 1.0f, true);
    uintptr_t s = Serializer::serialize(&testData);
    Data* d = Serializer::deserialize(s);
    (void)d;
    
    // If this compiles, methods are static
    SUCCEED();
}

// ============================================================================
// TEST GROUP 6: DATA STRUCTURE TESTS
// ============================================================================

TEST(DataStructureTest, DataHasMembers) {
    // Verify that Data structure is not empty
    
    Data data;
    
    // Data should have non-empty members
    EXPECT_GT(sizeof(Data), 1);
}

TEST(DataStructureTest, DataCanBeConstructed) {
    // Test Data construction
    
    Data data1;  // Default constructor
    Data data2(42, "Name", 3.14f, true);  // Parameterized constructor
    
    EXPECT_EQ(data2.id, 42);
    EXPECT_EQ(data2.name, "Name");
}

TEST(DataStructureTest, DataCanBeCopied) {
    // Test that Data can be copied
    
    Data original(1, "Original", 1.0f, true);
    Data copy = original;
    
    EXPECT_EQ(copy.id, original.id);
    EXPECT_EQ(copy.name, original.name);
}

// ============================================================================
// INTEGRATION TESTS
// ============================================================================

TEST(SerializerIntegrationTest, SubjectExample) {
    // From the subject: create Data, serialize, deserialize, and compare
    
    Data* original = new Data(42, "Subject", 3.14f, true);
    
    // TODO: Uncomment when Serializer is implemented
    uintptr_t raw = Serializer::serialize(original);
    Data* result = Serializer::deserialize(raw);
    
    EXPECT_EQ(result, original);
    EXPECT_EQ(result->id, 42);
    
    delete original;
    
    SUCCEED();
}

TEST(SerializerIntegrationTest, ChainedSerializations) {
    // Test multiple serialize/deserialize operations
    
    Data* data = new Data(1, "Chain", 1.0f, true);
    
    // TODO: Uncomment when Serializer is implemented
    uintptr_t s1 = Serializer::serialize(data);
    Data* d1 = Serializer::deserialize(s1);
    
    uintptr_t s2 = Serializer::serialize(d1);
    Data* d2 = Serializer::deserialize(s2);
    
    // All should point to the same memory
    EXPECT_EQ(data, d1);
    EXPECT_EQ(d1, d2);
    
    delete data;
    
    SUCCEED();
}

TEST(SerializerIntegrationTest, ArrayOfData) {
    // Test with array of Data objects
    
    const int SIZE = 5;
    Data* dataArray = new Data[SIZE];
    
    for (int i = 0; i < SIZE; i++) {
        dataArray[i] = Data(i, "Item" + intToString(i), i * 1.1f, i % 2 == 0);
    }
    
    // TODO: Uncomment when Serializer is implemented
    for (int i = 0; i < SIZE; i++) {
        uintptr_t serialized = Serializer::serialize(&dataArray[i]);
        Data* deserialized = Serializer::deserialize(serialized);
        
        EXPECT_EQ(deserialized, &dataArray[i]);
        EXPECT_EQ(deserialized->id, i);
    }
    
    delete[] dataArray;
    
    SUCCEED();
}

/*
   BONUS TESTS - Advanced scenarios
*/

TEST(SerializerBonusTest, LargeDataStructure) {
    // Test with a large Data structure
    
    struct LargeData {
        int values[1000];
        std::string name;
    };
    
    LargeData* largeData = new LargeData();
    largeData->name = "Large";
    for (int i = 0; i < 1000; i++) {
        largeData->values[i] = i;
    }
    
    // Serialization should work regardless of size
    uintptr_t serialized = reinterpret_cast<uintptr_t>(largeData);
    LargeData* deserialized = reinterpret_cast<LargeData*>(serialized);
    
    EXPECT_EQ(deserialized, largeData);
    EXPECT_EQ(deserialized->name, "Large");
    EXPECT_EQ(deserialized->values[500], 500);
    
    delete largeData;
}

TEST(SerializerBonusTest, PointerToConstData) {
    // Test with const pointer
    
    const Data* constData = new Data(99, "Const", 9.9f, true);
    
    // TODO: Uncomment when Serializer is implemented
    // Should your serialize function accept const Data*?
    uintptr_t serialized = Serializer::serialize(const_cast<Data*>(constData));
    Data* deserialized = Serializer::deserialize(serialized);
    
    EXPECT_EQ(deserialized, constData);
    
    delete constData;
    
    SUCCEED();
}
