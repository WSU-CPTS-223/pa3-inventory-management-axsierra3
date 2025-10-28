#include "Product.hpp"


//created my custom key value pair struct to use instead of std::pair
template <typename Key, typename Value>
struct KeyValuePair 
{
    Key mKey;
    Value mValue;

    KeyValuePair(const Key& key, const Value& value) : mKey(key), mValue(value) {}

};

//custom hash map class
template <typename Key, typename Value>
class HashMap 
{
List< KeyValuePair<Key, Value> > hTable[100]; //array of lists storing key value pairs
                                                //the array itself is the hash table, we store List in each slot because of single chaininh collision strat
public:
    //we will use std::hash to hask the keys (no hash funct needed)

    void insert(Key k, Value v); //inserting pair into hash map (our pairs will be string and product)
    Value find (Key k); //find and return value (product) based on key, will be printed in main
    
};