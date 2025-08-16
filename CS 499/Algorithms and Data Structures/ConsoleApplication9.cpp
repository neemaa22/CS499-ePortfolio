// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Algorithms and Data Structures - Enhanced with std::array

#include <iostream>
#include <array>
#include <algorithm>

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

// CAPSTONE Enhanced test class using std::array with custom tracking
template<size_t MaxSize = 100>
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    // Use std::array with fixed size and track actual elements
    std::unique_ptr<std::array<int, MaxSize>> collection;
    size_t element_count;  // Track how many elements are actually used

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::array<int, MaxSize>);
        element_count = 0;  // Start with no elements
        collection->fill(0);  // Initialize all to zero
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        element_count = 0;
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        assert(element_count + count <= MaxSize);

        for (auto i = 0; i < count; ++i) {
            (*collection)[element_count] = rand() % 100;
            element_count++;
        }
    }

    // Custom functions to mimic vector behavior
    bool empty() const {
        return element_count == 0;
    }

    size_t size() const {
        return element_count;
    }

    void clear() {
        element_count = 0;
        collection->fill(0);
    }

    int& at(size_t index) {
        if (index >= element_count) {
            throw std::out_of_range("Index out of bounds");
        }
        return (*collection)[index];
    }

    void resize(size_t new_size) {
        if (new_size > MaxSize) {
            throw std::length_error("Cannot resize beyond max capacity");
        }
        element_count = new_size;
    }
};

// Instantiate test fixture
using ArrayCollectionTest = CollectionTest<100>;

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(ArrayCollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(ArrayCollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(empty());

    // if empty, the size must be 0
    ASSERT_EQ(size(), 0);
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(ArrayCollectionTest, CanAddToEmptyArray)
{
    // is the collection empty?
    ASSERT_TRUE(empty());
    // if empty, the size must be 0
    ASSERT_EQ(size(), 0);

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(empty());
    // if not empty, what must the size be?
    ASSERT_EQ(size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(ArrayCollectionTest, CanAddFiveValuesToArray)
{
    add_entries(5);
    ASSERT_EQ(size(), 5);
    ASSERT_FALSE(empty());
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(ArrayCollectionTest, MaxSizeIsConstant)
{
    EXPECT_EQ(collection->max_size(), 100);

    add_entries(1);
    EXPECT_EQ(collection->max_size(), 100);

    add_entries(4);
    EXPECT_EQ(collection->max_size(), 100);

    add_entries(5);
    EXPECT_EQ(collection->max_size(), 100);
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(ArrayCollectionTest, ArraySizeIsAlwaysFixed)
{
    EXPECT_EQ(collection->size(), 100);

    add_entries(1);
    EXPECT_EQ(collection->size(), 100);  // Array size stays 100
    EXPECT_EQ(size(), 1);  // But element count is 1
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(ArrayCollectionTest, ResizingIncreasesElementCount)
{
    resize(10);
    ASSERT_EQ(size(), 10);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(ArrayCollectionTest, ResizingDecreasesElementCount)
{
    add_entries(10);
    resize(5);
    ASSERT_EQ(size(), 5);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(ArrayCollectionTest, ResizingToZeroEmptiesCollection)
{
    add_entries(5);
    resize(0);
    ASSERT_EQ(size(), 0);
    ASSERT_TRUE(empty());
}

// TODO: Create a test to verify clear erases the collection
TEST_F(ArrayCollectionTest, ClearEmptiesCollection)
{
    add_entries(5);
    clear();
    ASSERT_EQ(size(), 0);
    ASSERT_TRUE(empty());
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(ArrayCollectionTest, FillSetsAllElements)
{
    collection->fill(42);
    for (size_t i = 0; i < collection->size(); ++i) {
        ASSERT_EQ((*collection)[i], 42);
    }
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(ArrayCollectionTest, ArrayHasFixedCapacity)
{
    size_t initial_size = collection->size();
    // Arrays have fixed size, so size() always returns the template parameter
    ASSERT_EQ(initial_size, 100);
    ASSERT_EQ(collection->size(), 100);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(ArrayCollectionTest, AtThrowsOutOfRangeException)
{
    ASSERT_THROW(at(0), std::out_of_range);
    add_entries(5);
    ASSERT_THROW(at(10), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

// Positive test: Verify we can access and modify elements
TEST_F(ArrayCollectionTest, CanAccessAndModifyElements)
{
    add_entries(3);
    (*collection)[0] = 100;
    (*collection)[1] = 200;
    (*collection)[2] = 300;

    ASSERT_EQ((*collection)[0], 100);
    ASSERT_EQ((*collection)[1], 200);
    ASSERT_EQ((*collection)[2], 300);
}

// Negative test: Verify resize beyond capacity throws exception
TEST_F(ArrayCollectionTest, ResizeBeyondCapacityThrows)
{
    ASSERT_THROW(resize(101), std::length_error);
}

// Additional test: std::sort works with array
TEST_F(ArrayCollectionTest, CanSortArray)
{
    add_entries(5);
    // Set specific values for testing
    (*collection)[0] = 5;
    (*collection)[1] = 2;
    (*collection)[2] = 8;
    (*collection)[3] = 1;
    (*collection)[4] = 9;

    // Sort only the used portion
    std::sort(collection->begin(), collection->begin() + element_count);

    ASSERT_EQ((*collection)[0], 1);
    ASSERT_EQ((*collection)[1], 2);
    ASSERT_EQ((*collection)[2], 5);
    ASSERT_EQ((*collection)[3], 8);
    ASSERT_EQ((*collection)[4], 9);
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