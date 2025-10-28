[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pAwGQi_N)

TEST CASES:
Created a test function for testHashInsertAndFind(). The base case creates a Hash Table that maps string product ID keys to Product objects. This mirrors the functionality of the REPL system in main. The key and value pair is then inserted into the Hash Table. I used the find function to test if the product was inserted correctly in the hash table. Asserting that the find function does not return null pointer, and that the pointer stores the correct name data, assures both the insert and find function  in my custom HashTable are working for the base case.

Created a test function for testLinkedListInsert(). The base case creates a List and inserts a product object into the front. This mirrors how my custom List class is used in the REPL system for the purpose of separate chaining and to store the Lists of objects of the same category. The function asserts that the product was inserted successfully by retrieving the head pointer and asserting that it is no longer null. The edge case is no insertion. The function attempts to access the head pointer of an empty list, which can happen in my program. The head pointer is expected to be null.

testAll(): Test all combines all of my test cases and prints text if all the tests were passed. This function is called in main.
