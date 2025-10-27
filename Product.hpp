
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Product {
    public:
    //constructor
    Product(string uniqID, string productName, string brandName, string asin, string categories[10], string details) :
        mUniqID(uniqID), mProductName(productName), mBrandName(brandName), mAsin(asin), mDetails(details) 
        {
            for(int i = 0; i < 10; i++)
            {
                mCategories[i] = categories[i]; //copy whole categroies array
            }
        };

    //getters (for use in listInventory)
    string getUniqueID();

    string getProductName();


    //<< override (for printing use in find)
    friend std::ostream& operator<<(std::ostream &os, Product &product);

    private:
    //fields
    string mUniqID, mProductName, mBrandName, mAsin, mDetails;
    string mCategories[10];
};