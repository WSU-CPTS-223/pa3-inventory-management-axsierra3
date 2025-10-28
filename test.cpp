#include "HashTable.hpp"
#include "List.hpp"
#include "Product.hpp"
#include "test.hpp"
#include <cassert>


void testHashInsertandFind()
{
    cout << "Testing insert(Key k, Value v) for string key and product value.....";

    HashTable<string, Product> testTable;

    //BASE CASE: normal insert
    string categories[10] = {"Energy Drinks", "Sports Drinks", "Beverages"};

    Product testProduct("1234567", "Alani Nu -- Orange Creamsicle Flavor", categories, "$2.55", "200 mg of caffiene");

    testTable.insert(testProduct.getUniqueID(), testProduct); //insert funct

    Product* insertTest = testTable.find(testProduct.getUniqueID()); //testing if product is actually in hashtable by using find

    assert(insertTest != nullptr);
    assert(insertTest->getProductName() ==  testProduct.getProductName()); //same name


    //EDGE case: Inserting with same key (checking if replacement is successful)
    Product testProduct2("1234567", "Red Bull -- Coconut Flavor", categories, "$1.50", "12 oz");

     testTable.insert(testProduct2.getUniqueID(), testProduct2); 
    
    insertTest = testTable.find("1234567");
    assert(insertTest->getProductName() ==  testProduct2.getProductName()); //asert the 2nd is now the one found

    cout << "Hash Insert and Find tests passed!" << endl;
}

void testLinkedListInsert()
{
    //EDGE CASE: no insert, retrieving empty list
     List<Product> testList; //make test list of products
    assert(testList.getHeadPtr() == nullptr);

    //BASE CASE: normal insert
    cout << "Testing insert for linked list....." << endl;
    string categories[10] = {"Energy Drinks", "Sports Drinks", "Beverages"};
    Product testProduct("1234567", "Alani Nu -- Orange Creamsicle Flavor", categories, "$2.55", "200 mg of caffiene");

    testList.insertAtFront(testProduct); //insert

    assert(testList.getHeadPtr() != nullptr);
}


void testAll()
{
    cout << endl << "--Running all tests--" << endl;

    testHashInsertandFind();
    testLinkedListInsert();

    cout << "ALL TESTS PASSED!" << endl;
}


