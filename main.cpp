#include <iostream>
#include <string>
#include "Product.hpp"
#include "fileParser.hpp"

using namespace std;

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

void evalCommand(string line)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Look up the appropriate datastructure to find if the inventory exist
        cout << "YET TO IMPLEMENT!" << endl;
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0)
    {
        // Look up the appropriate datastructure to find all inventory belonging to a specific category
        cout << "YET TO IMPLEMENT!" << endl;
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

    std::ifstream inputFile("miniData.csv");
    string buffer, categoryBuffer;
    string ID, prodName, brand, asin, details;
    size_t delim;

    getline(inputFile, buffer); //eat first line
    while( getline(inputFile, buffer) ) 
    {
        ID = parseField(buffer);
        prodName = parseField(buffer);
        brand = parseField(buffer);
        asin = parseField(buffer);
        categoryBuffer = parseField(buffer);
        string categories[10] = {"N/A"}; 

        for(int i = 0; i < 10; i++)
        {
            delim = categoryBuffer.find('|'); //find the separator
            if (delim != string::npos) //we fouund a sepator (multiple categoties)
            {
                categories[i] = categoryBuffer.substr(0, delim); //get single category in array w/out the spaces around it
                categoryBuffer = categoryBuffer.substr(delim + 1, categoryBuffer.length()); //crop and look for another sepator
            }
            else {
                categories[i] = categoryBuffer; //only one category or last category
                break;
            }
        }
        details = buffer; //rest of line stored in details
        Product newProduct(ID, prodName, brand, asin, categories, details); //store new product
        cout << newProduct << endl; //TESTING PARSINGak
    }
}

int main(int argc, char const *argv[])
{
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
