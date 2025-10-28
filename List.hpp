#pragma once

    //generic node to be used in list to store multiple products
    template <typename T>
    struct Node {
        T mData;
        Node* mpNext;
        Node(const T& newData): mData(newData), mpNext(nullptr) {}; //passing in new data by const referemce rather than make a copy
    };


template <typename T>
class List {

    private:
    Node<T>* mpHead; //head of list


    public:
    List(): mpHead(nullptr) {}; //constructor, null head

    void insertAtFront(T& newData); //adjusts head ptr to new node

    Node<T>* getHeadPtr(); //getter 

    // T* findNode(T& targetData); //return ptr to node w matching data or null

};

template <typename T>
 void List<T>::insertAtFront(T& newData) 
 {
    Node<T>* newNode = new Node<T>(newData);

    if(mpHead == nullptr) 
    {
        mpHead = newNode;
    } 
    else 
    {
        newNode->mpNext = mpHead; //new node's next ptr is the old head
        mpHead = newNode;   //new node is new head
    }
 }
   template <typename T>
   Node<T>* List<T>::getHeadPtr()
   {
    return mpHead;
   }

 //lowk dont know how im gonna do this one (or if it matters) seeing itd be comparing products w same hash value soooo

 
//  template <typename T>
//  T* List<T>::findNode(T& targetData)
//  {
//     //case 1: empty list
//     if(mpHead == nullptr)
//     {
//         return nullpr;
//     }
//     //non empty list
//     Node<T>* curr = mpHead;
//     while(curr != nullptr)
//     {
//         if(curr->mData == targetData) //found 
//         {
//             return curr-; //return  
//         }
//         curr = curr->mpNext; //next node
//     }
//     return nullptr; //not found
//  }
