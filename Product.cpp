#include "Product.hpp"


    string Product::getUniqueID()
    {
        return mUniqID;
    }

    string Product::getProductName()
    {
        return mProductName;
    }


 std::ostream& operator<<(std::ostream& os, Product& product)
  {
        os << "Product Name: "<<  product.mProductName << endl << "Price: " << product.mPrice << endl << "Categories: ";
        for (string category : product.mCategories)
        {
            if(category == "N/A")
            {
                cout << category; //print N/A once then break
                break; 
            }
            cout << category << " ";
        }
        cout << endl;
        return os;
  }

  
