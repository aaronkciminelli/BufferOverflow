// Uncomment the next line to use precompiled headers
#include "pch.h"
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

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
//TEST_F(CollectionTest, AlwaysFail)
//{
//    FAIL();
//}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty());
    // if empty, the size must be 0

    add_entries(1);

    EXPECT_FALSE(collection->empty());

    // is the collection still empty?
    // if not empty, what must the size be?
    EXPECT_FALSE(collection->empty());
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxIsGreaterOrEqual) {
    add_entries(11);

    ASSERT_TRUE(collection->max_size() >= 0); //AC* Verify that the maxsize is greater than or equal to 0
    ASSERT_TRUE(collection->max_size() >= 1); //AC* Verify that the maxsize is greater than or equal to 1
    ASSERT_TRUE(collection->max_size() >= 5); //AC* Verify that the maxsize is greater than or equal to 5
    ASSERT_TRUE(collection->max_size() >= 10); //AC* Verify that the maxsize is greater than or equal to 10
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGtEt_Test) {
    add_entries(11); //AC* Add 11 entries to the collection

    ASSERT_TRUE(collection->capacity() >= 0); //AC* Verify that the capacity is greater than or equal to 0
    ASSERT_TRUE(collection->capacity() >= 1); //AC* Verify that the capacity is greater than or equal to 1
    ASSERT_TRUE(collection->capacity() >= 5); //AC* Verify that the capacity is greater than or equal to 5
    ASSERT_TRUE(collection->capacity() >= 10); //AC* Verify that the capacity is greater than or equal to 10
}
// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreases_Test) {
    //AC* Call add_entries function with argument 1
    add_entries(1);

    //AC* Create var previousSize and assign it with current collection size
    int previousSize = collection->size();

    //AC* Resize collection to 20
    collection->resize(20);

    //AC* Assert that the new collection size is greater than previousSize
    ASSERT_TRUE(collection->size() > previousSize);
}
// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreseInSize_Test) {
    add_entries(20); //AC* Add 20 entries to the collection

    int previousSize = collection->size(); //AC* Get the current size of the collection
    collection->resize(1); //AC* Resize the collection to 1
    ASSERT_TRUE(collection->size() < previousSize); //AC* Assert that the new size is less than the previous size
}
// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeDescreaseTo_Zero_Test) {
    //AC* Call add_entries method to add 20 entries to the collection
    add_entries(20);

    //AC* Store the previous size of the collection
    int previousSize = collection->size();

    //AC* Resize the collection to zero
    collection->resize(0);

    //AC* Assert that the size of the collection is zero
    ASSERT_TRUE(collection->size() == 0);
}
// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearCollection_Test) {  //AC* declare and define test function
    add_entries(20);  //AC* call function add_entries with 20 as argument

    collection->clear();  //AC* call clear() function for the collection pointer
    ASSERT_TRUE(collection->size() == 0);  //AC* assert that size of the collection is now 0
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseCollection_Test) { 
    add_entries(20); //AC* Add this adds 20 entries to the collection

    collection->erase(collection->begin(), collection->end()); //AC* this line erases the collection

    ASSERT_TRUE(collection->size() == 0); //AC*  this line verifies that the collection is empty
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveCapTest) {
    //AC* Add 20 entries to the collection
    add_entries(20);

    int prevCapacity = collection->capacity();
    int prevSize = collection->size();

    //AC* Reserve space for 30 entries
    collection->reserve(30);

    //AC* Check that the size of the collection hasn't changed
    ASSERT_TRUE(collection->size() == prevSize);

    //AC* Check that the capacity of the collection has been increased
    ASSERT_TRUE(collection->capacity() > prevCapacity);
}


// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
//AC* test fixture for CollectionTest class and test case for IndexOutOfBounds
TEST_F(CollectionTest, IndexOutOfBounds_Test) {
    //AC* a vector of 10 integers
    std::vector<int> myvector(10);

    //AC* Expect an std::out_of_range exception when attempting to access an index that is out of bounds
    EXPECT_THROW(myvector.at(20), std::out_of_range);
}

// NOTE: This is a negative test

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
//AC* Test case: Custom_Test1
//AC* This test case verifies the behavior of adding an entry to a collection and then performing assertions on the collection's size and element at a specific index.

TEST_F(CollectionTest, aCustom_Test1) {
    add_entries(10); //AC* Adding 10 entries to the collection

    collection->push_back(1);  //AC* Adding 10 entries to the collection
    //AC* Asserting that the collection's size is greater than 10 and the element at index 10 is equal to 1
    ASSERT_TRUE(collection->size() > 10);
    ASSERT_TRUE(collection->at(10) == 1);
}

//AC* Test case: Custom_Test2
//AC* This test case verifies the behavior of removing the last entry from a collection and then performing an assertion on the collection's size.
TEST_F(CollectionTest, aCustom_Test2) {
    add_entries(10);

    collection->pop_back(); //AC* Removing the last entry from the collection

    ASSERT_FALSE(collection->size() == 10); //AC* Asserting that the collection's size is not equal to 10
}