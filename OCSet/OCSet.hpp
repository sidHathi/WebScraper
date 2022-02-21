//
//  OCSet.hpp
//  WebScraper
//
//  Created by Siddharth Hathi on 2/10/22.
//

#ifndef OCSet_hpp
#define OCSet_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

class OCSet
{
protected:
    int m_size;
    unordered_map<string, int> m_counterSet;
    vector<string> m_orderedKeys;
    unordered_map<string, int> m_positionMap;
    bool binaryInsert(string key, int val);
    bool linearInsert(string key, int val);
public:
    OCSet(int initialCapacity = 0);
    int add(string key);
    int get(string key);
    bool set(string key, int val);
    void write(string filename, int numValues = 100);
    int size();
    void debug();
};


int ocSet_testAdd(OCSet* testSet);
int ocSet_testSet(OCSet* testSet);
int ocSet_testInsert(OCSet* testSet);
void ocSet_runTests();

#endif /* OCSet_hpp */
