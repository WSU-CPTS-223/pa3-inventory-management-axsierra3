#include "Product.hpp"
#include "List.hpp"
#include <functional>

#define TABLE_SIZE 13501 //prime number, keeps collisions low (most lists will have 1 or 0 items so quick lookup)


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
class HashTable 
{
private:
List< KeyValuePair<Key, Value> > hTable[TABLE_SIZE]; //array of lists storing key value pairs
                                                //the array itself is the hash table, we store List in each slot because of single chaininh collision strat
public:
    //we will use std::hash to hask the keys (no hash funct needed)
    void insert(Key k, Value v); //inserting pair into hash map (our pairs will be string and product) 
    Value* find (Key k); //find and return value (a product) based on key, which will be printed in main

};

template <typename Key, typename Value>
void HashTable<Key, Value>::insert(Key k, Value v)
{
    std::hash<Key> keyHasher; // std hash object
    size_t hashValueIndex = keyHasher(k) % TABLE_SIZE; //compute a numerical hash value for our new entry, based on the key, within table size

    List< KeyValuePair<Key, Value> >& currList = hTable[hashValueIndex]; //get reference to the list loacted at that index

    //check if key already exists in the list, if so replace it (hash # can be the same, but keys must be unique)
    Node< KeyValuePair<Key, Value> >* currNode = currList.getHeadPtr();
    while(currNode != nullptr)
    {
        if (currNode->mData.mKey == k) //curr pair in the list (its the data) has the same key stored
        {
            currNode->mData.mValue = v; //now the value (product data) is updated
            return;
        }
        currNode = currNode->mpNext;
    }
    //else, key not found, insert pair are front of linked list
    KeyValuePair<Key, Value> newPair(k, v);
    currList.insertAtFront(newPair); //yay! insert data
}

template <typename Key, typename Value>
Value* HashTable<Key, Value>::find (Key k)
{
    std::hash<Key> keyHasher; //std hash object
    size_t hashValueIndex = keyHasher(k) % TABLE_SIZE; //hash value where th product would be hypthethetically

    List< KeyValuePair<Key, Value> >& currList = hTable[hashValueIndex]; //get reference to the list loacted at that index
    Node < KeyValuePair<Key, Value> >* currNode = currList.getHeadPtr(); //for iterating thru list again

    while(currNode != nullptr)
    {
        if(currNode->mData.mKey == k) //we found the unque key
        {
            return &(currNode->mData.mValue); //return ptr to all the the prodct data to print
        }
        currNode = currNode->mpNext; //move
    }
    //else
    return nullptr; //never found it

}