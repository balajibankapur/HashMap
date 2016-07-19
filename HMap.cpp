// HMap.cpp : Defines the entry point for the console application.
//

#include "HashMap.h"
#include "iostream"
#include <thread>
#include <chrono>
#include <unistd.h>
#include <sys/resource.h>

using namespace std;

// test function for <string,int>
void InsertStringTest(HashMap<string, int> *pHMap)
{
    pHMap->insert("abc", 100);
    pHMap->insert("xyz", 101);
    pHMap->insert("fsdf", 102);
    pHMap->insert("sdff", 103);
    pHMap->insert("sdfff", 104);
    pHMap->insert("jsdfsdfsdfdsf", 105);
    pHMap->insert("fsdfdsfdf", 106);
}

// test function for <string,int>
void RemoveStringTest(HashMap<string, int> *pHMap)
{
    pHMap->remove("abc");
    pHMap->remove("xyz");
    pHMap->remove("fsdf");
    pHMap->remove("sdff");
    pHMap->remove("sdfff");
    pHMap->remove("jsdfsdfsdfdsf");
    pHMap->remove("fsdfdsfdf");
}

// test function for <string,int>
void LookupStringTest(HashMap<string, int> *pHMap)
{
    int value = 0;
    
    pHMap->lookup("abc", value);
    pHMap->lookup("xyz", value);
    pHMap->lookup("fsdf", value);
    pHMap->lookup("sdff", value);
    pHMap->lookup("sdfff", value);
    pHMap->lookup("jsdfsdfsdfdsf", value);
    pHMap->lookup("fsdfdsfdf", value);    
}

// test function for <int,int>
void LookupIntTest(HashMap<int, int> *pHMap)
{
    int value = 0;
    pHMap->lookup(1, value);
    
    if (value == 1)
    {
        std::cout << "Found" << endl;
    }
    pHMap->lookup(2, value);
    if (value == 2)
    {
        cout << "Found" << endl;
    }
    pHMap->lookup(3, value);
    if (value == 3)
    {
        cout << "Found" << endl;
    }
    pHMap->lookup(4, value);
    if (value == 4)
    {
        cout << "Found" << endl;
    }
    pHMap->lookup(5, value);
    if (value == 5)
    {
        cout << "Found" << endl;
    }
    pHMap->lookup(6, value);
    if (value == 6)
    {
        cout << "Found" << endl;
    }
    pHMap->lookup(7, value);
    if (value == 7)
    {
        cout << "Found" << endl;
    }    
}

// test function for <int,int>
void InsertIntTest(HashMap<int, int> *pHMap)
{
    pHMap->insert(1, 100);
    pHMap->insert(2, 101);
    pHMap->insert(4, 102);
    pHMap->insert(3, 103);
    pHMap->insert(5, 104);
    pHMap->insert(6, 105);
    pHMap->insert(7, 106);
    pHMap->insert(1, 100);
    pHMap->insert(2, 101);
    pHMap->insert(4, 102);
    pHMap->insert(3, 103);
    pHMap->insert(5, 104);
    pHMap->insert(6, 105);
    pHMap->insert(7, 106);
    pHMap->insert(1, 100);
    pHMap->insert(2, 101);
    pHMap->insert(4, 102);
    pHMap->insert(3, 103);
    pHMap->insert(5, 104);
    pHMap->insert(6, 105);
    pHMap->insert(7, 106);
    pHMap->insert(1, 100);
    pHMap->insert(2, 101);
    pHMap->insert(4, 102);
    pHMap->insert(3, 103);
    pHMap->insert(5, 104);
    pHMap->insert(6, 105);
    pHMap->insert(7, 106);
    pHMap->insert(1, 100);
    pHMap->insert(2, 101);
    pHMap->insert(4, 102);
    pHMap->insert(3, 103);
    pHMap->insert(5, 104);
    pHMap->insert(6, 105);
    pHMap->insert(7, 106);
}

// test function for <int,int>
void RemoveIntTest(HashMap<int, int> *pHMap)
{
    pHMap->remove(1);
    pHMap->remove(2);
    pHMap->remove(3);
    pHMap->remove(5);
    pHMap->remove(4);
    pHMap->remove(6);
    pHMap->remove(7);
    pHMap->remove(1);
    pHMap->remove(2);
    pHMap->remove(3);
    pHMap->remove(5);
    pHMap->remove(4);
    pHMap->remove(6);
    pHMap->remove(7);
    pHMap->remove(1);
    pHMap->remove(2);
    pHMap->remove(3);
    pHMap->remove(5);
    pHMap->remove(4);
    pHMap->remove(6);
    pHMap->remove(7);
    pHMap->remove(1);
    pHMap->remove(2);
    pHMap->remove(3);
    pHMap->remove(5);
    pHMap->remove(4);
    pHMap->remove(6);
    pHMap->remove(7);
    pHMap->remove(1);
    pHMap->remove(2);
    pHMap->remove(3);
    pHMap->remove(5);
    pHMap->remove(4);
    pHMap->remove(6);
    pHMap->remove(7);
}

// test function for <int,int>
/* void Thread1(HashMap<int, int> *pHMapint)
{
    
    InsertIntTest(pHMapint);
    InsertIntTest(pHMapint);
    RemoveIntTest(pHMapint);
    InsertIntTest(pHMapint);
    RemoveIntTest(pHMapint);
    RemoveIntTest(pHMapint);
}

// test function for <int,int>
void Thread2(HashMap<int, int> *pHMapint)
{
    InsertIntTest(pHMapint);
    InsertIntTest(pHMapint);
    RemoveIntTest(pHMapint);
    InsertIntTest(pHMapint);
    RemoveIntTest(pHMapint);
    RemoveIntTest(pHMapint);
}

// test function for <int,int>
void Thread3(HashMap<int, int> *pHMapint)
{
    LookupIntTest(pHMapint);
}

// test function for <string,int>
void Thread4(HashMap<string, int> *pHMap)
{
    
    InsertStringTest(pHMap);
    InsertStringTest(pHMap);
    RemoveStringTest(pHMap);
    InsertStringTest(pHMap);
    RemoveStringTest(pHMap);
    RemoveStringTest(pHMap);
} */ 

// test function for <string,int>
/* void Thread5(HashMap<string, int> *pHMap)
{
    InsertStringTest(pHMap);
    InsertStringTest(pHMap);
    RemoveStringTest(pHMap);
    InsertStringTest(pHMap);
    RemoveStringTest(pHMap);
    RemoveStringTest(pHMap);
} */ 

// test function for <string,int>
/* void Thread6(HashMap<string, int> *pHMap)
{
    LookupStringTest(pHMap);
} */

static const int num_threads = 1;

int main()
{
    // Test 1: <int, int>
    HashMap<int, int> *pHMapint = new HashMap<int, int>(100);
    
//    struct rlimit rl;
//    int result;
//    result = getrlimit(RLIMIT_STACK, &rl);
//    std::cout << " Stack Size = "<<rl.rlim_cur << std::endl;

    std::thread ti[num_threads];
    std::thread tr[num_threads];
    std::thread tii[num_threads];
    std::thread trr[num_threads];
     //Launch a group of threads
    for (int i = 0; i < num_threads; ++i) 
    {
       ti[i] = std::thread(InsertIntTest, pHMapint);
       tr[i] = std::thread(RemoveIntTest, pHMapint);
       tii[i] = std::thread(InsertIntTest, pHMapint);
       trr[i] = std::thread(RemoveIntTest, pHMapint);
    }
 
    //Join the threads with the main thread
    for (int i = 0; i < num_threads; ++i) 
    {
         ti[i].join();
         tr[i].join();
         tii[i].join();
         trr[i].join();
    }
    

    std::thread tlookup(LookupIntTest, std::ref(pHMapint));
    tlookup.join();


    // Test 2: <string, int>
    //HashMap<string, int> *pHMapString = new HashMap<string, int>(100);
    //std::thread t4(Thread4, std::ref(pHMapString));
    //std::thread t5(Thread5, std::ref(pHMapString));
    //t4.join();
    //t5.join();
    //std::thread t6(Thread6, std::ref(pHMapString));
    //t6.join();

    delete pHMapint;

    return 0;
}