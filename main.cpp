#include <iostream>
#include <string>
#include "Product.hpp"
#include "fileParser.hpp"
#include "HashTable.hpp"
#include "test.hpp"

using namespace std;

HashTable <string, Product> productTable; //global hash table that maps each uniq ID to the product that matches it
HashTable <string, List<Product> > categoryTable;  //global hash table that maps each category to a list of every product that had that category

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line) //added in reference tpo product table
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Look up the appropriate datastructure to find if the inventory exist
        size_t bracket1 = line.find('<');
        size_t bracket2 = line.find('>');
        
        string inventoryID = line.substr(bracket1 + 1, (bracket2 - bracket1) - 1); //everything between the brackets

        Product* foundProduct = productTable.find(inventoryID); //look up in hash table, assign to product ptr
        if(foundProduct != nullptr) //found
        {
            cout << *foundProduct << endl; //print it using overloaded op
        }
        else 
        {
            cout << "Inventory/Product not found" << endl;
        }
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0)
    {
        // Look up the appropriate datastructure to find all inventory belonging to a specific category
        size_t bracket1 = line.find('<');
        size_t bracket2 = line.find('>');
        
        string category_string = line.substr(bracket1 + 1, (bracket2 - bracket1) - 1); //everything between the brackets

        List<Product>* foundCatList = categoryTable.find(category_string);
        if(foundCatList != nullptr)
        {
            foundCatList->print(); //print all the prods that match that
        }
        else 
        {
            cout << "Invalid Category" << endl;
        }
    }
}

void bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
    // TODO: Do all your bootstrap operations here
    // example: reading from CSV and initializing the data structures
    // Don't dump all code into this single function
    // use proper programming practices

    std::ifstream inputFile("productData.csv");
    string buffer, categoryBuffer;
    string ID, prodName, brand, asin, extraInfo, details;
    size_t delim;


    getline(inputFile, buffer); //eat first line
    while( getline(inputFile, buffer) ) 
    {
        ID = parseField(buffer);
        prodName = parseField(buffer);
        extraInfo = parseField(buffer); //brand always empty according to Kaggle
        extraInfo = parseField(buffer); //ASIN always empty
        categoryBuffer = parseField(buffer);
        string categories[10] = {"N/A"}; 

        for(int i = 0; i < 10; i++)
        {
            delim = categoryBuffer.find('|'); //find the separator
            if (delim != string::npos) //we actually found a sepator (multiple categories)
            {
                categories[i] = categoryBuffer.substr(0, delim); //get single category in array 
                categories[i].erase(0, categories[i].find_first_not_of(" ")); //trimming the leading white space by erasing everying from start to first non space char
                categories[i].erase(categories[i].find_last_not_of(" ") + 1);  //trimming the trailing white space by erasing everyhting from one after the last non white space

                categoryBuffer = categoryBuffer.substr(delim + 1, categoryBuffer.length()); //crop and look for another sepator
            }
            else {
                if(categoryBuffer != "\"\"") //not empty quotes
                {
                categories[i] = categoryBuffer; //only one category or last category
                }
                break;
            }
        }
        extraInfo = parseField(buffer); //upc and list price are always null according to Kaggle documentation
        extraInfo = parseField(buffer);
        string price = parseField(buffer);
        details = buffer; //rest of line stored in details
        Product newProduct(ID, prodName, categories, price, details); //store new product
        // cout << newProduct << endl; //TESTING 

        productTable.insert(ID, newProduct); //insert into ID based hash

        //now inserting into category based hash
        for(int i = 0; i < 10; i++)
        {
            if(categories[i] == "N/A")
            {
                break; //if theres no categories for that prod theres nothing to insert
            }

            List<Product>* currCatList = categoryTable.find(categories[i]); //find will return a ptr to list of all products mathcing that category key---if it exists, otherwise, it returns nullptr

            //so if we already added that category, lets add this new product to its list inside hash
            if(currCatList != nullptr)
            {
            currCatList->insertAtFront(newProduct);
            }
            //else, this is a new category we havent added yet! (no list found), lets make a list
            else 
            {
                List<Product> newCategoryList; //make new list

                newCategoryList.insertAtFront(newProduct); //add first product item of that cat
                categoryTable.insert(categories[i], newCategoryList); //insert key and new list
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    //test cases
    // testAll();

    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
