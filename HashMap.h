#pragma once
#include "HashMapNode.h"
#include <mutex>

// 1. Provides insert, remove and lookup functionality.
// 2. This class supports generic key-value pair
// 3. Hash Table synchronization has following features
//    a. Bucket index based locking.
//	  b. Supports multiple writers at the same time if the writers are writing to different bucket index
//	  c. std::mutex is used as a synchronization primitive for lookup, insert and remove.
//		 (pthreads read_write locks can be used instead of std::mutex, which is optimized in terms
//		 of simultaneous reads). 
//		 Used simple mutex because, 
//	     1. read write locks are more expensive than simple mutex and 
//		 2. given requirements is to support the multiple writers at the same time.  
template<class T1, class T2>
class HashMap
{
public:
    HashMap(unsigned int nSize);
    ~HashMap(void);

    void insert(T1 key, T2 value);
    void remove(T1 key);
    bool lookup(T1 key, T2 &value);
    
private:
    
    HashMap(HashMap const &);
    HashMap& operator=(HashMap const &);

    size_t myHash(T1 key); // calculates the index for the given key
    void clearList(HashMapNode<T1,T2> *listPtr);

    std::hash<T1> ptrToHash;

    HashMapNode<T1, T2> **m_mapList; // hash table 
    unsigned int m_tableSize; // size of the hash table (number of buckets)

    std::mutex *m_bucketLock; // Array of mutex locks while updating each bucket in hash table.
};

#include "HashMap.h"
#include <iostream>
#include <functional>

using namespace std;


// Construct the hash map with given table size
template<class T1, class T2>
HashMap<T1, T2>::HashMap(unsigned int nTableSize)
{
    m_tableSize = nTableSize;
    m_mapList = new HashMapNode<T1, T2>*[m_tableSize];
    m_bucketLock = new std::mutex[m_tableSize];

    for(unsigned int iTableIndex = 0; iTableIndex < m_tableSize; iTableIndex++)
    {
        m_mapList[iTableIndex] = NULL;    
    }
}

// Remove the table enteries on deletion
template<class T1, class T2>
HashMap<T1, T2>::~HashMap(void)
{
	// delete all the nodes from the hash table
	for(unsigned int iTableIndex = 0; iTableIndex < m_tableSize; iTableIndex++)
    {
        clearList(m_mapList[iTableIndex]);
        m_mapList[iTableIndex] = NULL;
    }
}

// Remove the table enteries on deletion
template<class T1, class T2>
void HashMap<T1, T2>::clearList(HashMapNode<T1, T2> *listPtr)
{
	HashMapNode<T1, T2> *tempNode = listPtr;
	while(tempNode != NULL)
	{
		HashMapNode<T1, T2> *deleteNode = tempNode;
		tempNode = tempNode->next;
		delete deleteNode;
	}
}

// Add's key-value pair to the hash table
template<class T1, class T2>
void HashMap<T1, T2>::insert(T1 key, T2 value)
{
    // Compute the hash index.
    unsigned int nIndex = myHash(key); 
        
    // Insert new hash node with given key-value
    HashMapNode<T1, T2> *newNode = new HashMapNode<T1, T2>();
    newNode->next = NULL;
    newNode->key = key;
    newNode->value = value;

    // Lock the bucket index.
    lock_guard<mutex> lockit(m_bucketLock[nIndex]);
    
    // Find and insert the key-value at the right position.
    HashMapNode<T1, T2> *temp = m_mapList[nIndex];
    if(temp == NULL)
    {
        m_mapList[nIndex] = newNode;
    }
    else
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Remove the key-value entry from the hash table
// if there are more than one entry with the given key then 
// the first key will be removed.
// order of items is not maintained.
template<class T1, class T2>
void HashMap<T1, T2>::remove(T1 key)
{
    unsigned int nIndex = myHash(key);
    HashMapNode<T1, T2> *deleteNode = NULL;
    
    lock_guard<mutex> lockit(m_bucketLock[nIndex]);

    HashMapNode<T1, T2> *temp = m_mapList[nIndex];
    
    if(temp == NULL) return;
    
    if(temp->key == key)
    {
        deleteNode = temp;
        m_mapList[nIndex] = temp->next;
        delete deleteNode;
    }
    else
    {
        while(temp->next != NULL && temp->next->key != key)
        {
            temp = temp->next;
        }
        
        if(temp->next != NULL)
        {
            deleteNode = temp->next;
            temp = temp->next->next;
            delete deleteNode;
        }
    }
}

// Find the given key entry from the hash table and return the value.
// if there are more than one entry with the given key then 
// the first key will be returned.
// order of items is not maintained.
// return:
//          false: Given "Key" not found
//          true:  Found the given "Key" and out parameter "value" 
//                 contains the value associated with the key
template<class T1, class T2>
bool HashMap<T1, T2>::lookup(T1 key, T2 &value)
{
    bool bFound = false;
    unsigned int nIndex = myHash(key);
    
    lock_guard<mutex> lockit(m_bucketLock[nIndex]);
    
    HashMapNode<T1, T2> *temp = m_mapList[nIndex];
    while(temp != NULL)
    {
        if(temp->key == key)
        {
            bFound = true;
            value = temp->value;
            break;
        }
        temp = temp->next;
    }

    return bFound;
}

// Compute the index (based on the table size) for the given key 
template<class T1, class T2>
size_t HashMap<T1, T2>::myHash(T1 key)
{
   std::size_t index = ptrToHash(key);
   return index % m_tableSize;
}