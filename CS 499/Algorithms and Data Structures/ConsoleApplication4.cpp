// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Algorithms and Data Structures

#include <iostream>

// Uncomment the next line to use precompiled headers

// uncomment the next line if you do not use precompiled headers
#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}


 // TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);
    ASSERT_EQ(collection->size(), 5);
    ASSERT_FALSE(collection->empty());
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqualToSize)
{
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(1);
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(4);
    EXPECT_GE(collection->max_size(), collection->size());

    add_entries(5);
    EXPECT_GE(collection->max_size(), collection->size());
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqualToSize)
{
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(1);
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(4);
    EXPECT_GE(collection->capacity(), collection->size());

    add_entries(5);
    EXPECT_GE(collection->capacity(), collection->size());
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingIncreasesCollection)
{
    collection->resize(10);
    ASSERT_EQ(collection->size(), 10);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingDecreasesCollection)
{
    add_entries(10);
    collection->resize(5);
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingToZeroEmptiesCollection)
{
    add_entries(5);
    collection->resize(0);
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->empty());
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    add_entries(5);
    collection->clear();
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->empty());
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginEndErasesCollection)
{
    add_entries(5);
    collection->erase(collection->begin(), collection->end());
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->empty());
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize)
{
    size_t initial_size = collection->size();
    collection->reserve(100);
    ASSERT_GE(collection->capacity(), 100);
    ASSERT_EQ(collection->size(), initial_size);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, AtThrowsOutOfRangeException)
{
    ASSERT_THROW(collection->at(0), std::out_of_range);
    add_entries(5);
    ASSERT_THROW(collection->at(10), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

// Positive test: Verify push_back and back() work correctly
TEST_F(CollectionTest, PushBackAndBackWorkCorrectly)
{
    collection->push_back(42);
    ASSERT_EQ(collection->back(), 42);
    ASSERT_EQ(collection->size(), 1);
}

// Negative test: Verify pop_back on empty vector causes undefined behavior (we'll test it doesn't crash)
TEST_F(CollectionTest, FrontThrowsOnEmptyVector)
{
    ASSERT_THROW(collection->at(0), std::out_of_range);
    ASSERT_TRUE(collection->empty());
}
int main()
{
    std::cout << "Hello World!\n";
    // Register the global test environment
    ::testing::AddGlobalTestEnvironment(new Environment);

    // Initialize Google Test
    ::testing::InitGoogleTest();

    // Run all tests
    return RUN_ALL_TESTS();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
