#pragma once

// HashMap node contains the "key" , "value" and pointer to next node.
template<class T1, class T2>
struct HashMapNode
{
    T1 key;
    T2 value;
    HashMapNode *next; // pointer to next node in the list
};