//
//  OCSet.cpp
//  WebScraper
//
//  Created by Siddharth Hathi on 2/10/22.
//

#include "OCSet.hpp"

OCSet::OCSet(int initialCapacity)
{
    m_orderedKeys.reserve(initialCapacity);
    m_counterSet.reserve(initialCapacity);
    m_positionMap.reserve(initialCapacity);
}

int
OCSet::add(string key)
{
    // if key exists in counterset
        // Increment value in counterSet by 1
        // Check if the new value is higher than the next highest element
        // Repeat above step until it's no longer true or the index is 0
        // If necessary, change the location of the key within the keys vector and the positionMap
    // otherwise:
        // add entry to the counterset with initial value of 1
        // add entry to orderedKeys at the end of the list
        // update positionMap
    
    if (m_counterSet.count(key) > 0) {
        int curVal = m_counterSet.at(key);
        m_counterSet[key] = curVal + 1;
        curVal ++;
        
        int index = m_positionMap.at(key);
        int nextVal;
        while (index > 0 && (nextVal = m_counterSet.at(m_orderedKeys.at(index - 1))) < curVal) {
            string temp = m_orderedKeys.at(index - 1);
            m_orderedKeys.at(index - 1) = key;
            m_positionMap.at(key) = index - 1;
            m_orderedKeys.at(index) = temp;
            m_positionMap.at(temp) = index;
            index --;
        }
        return curVal;
    } else {
        m_counterSet[key] = 1;
        m_orderedKeys.push_back(key);
        m_positionMap[key] = (int)m_orderedKeys.size() - 1;
        m_size ++;
    }
    
    return 1;
}

bool
OCSet::set(string key, int val)
{
    // If the key exists in the counterSet
        // Update value in counterSet
        // Use a binary search to re-insert the key into the ordered keys vector
        // update positionMap
    // otherwise:
        // Insert into counterset
        // Use a binary search to insert the key into the ordered keys vector
        // insert into positionMap
    
    if (m_counterSet.count(key) > 0) {
        m_counterSet[key] = val;
        int prevIndex = m_positionMap.at(key);
        m_orderedKeys.erase(m_orderedKeys.begin() + prevIndex);
        
        return linearInsert(key, val);
    } else {
        if (linearInsert(key, val)) {
            m_counterSet[key] = val;
            m_size ++;
            return true;
        } else {
            return false;
        }
    }
    
    return false;
}

bool
OCSet::linearInsert(string key, int val)
{
    bool inserted = false;
    cout << "beginning linear insertion" << endl;
    for ( int i = 0; i < m_orderedKeys.size(); i ++ ) {
        cout << "insertion iteration starting" << endl;
        string iKey = m_orderedKeys.at(i);
        int iVal = m_counterSet.at(iKey);
        if (!inserted && val > iVal) {
            m_orderedKeys.insert(m_orderedKeys.begin() + i, key);
            m_positionMap[key] = i;
            inserted = true;
        } else {
            m_positionMap.at(iKey) = i;
        }
    }
    if (!inserted) {
        m_orderedKeys.push_back(key);
        m_positionMap[key] = (int)m_orderedKeys.size() - 1;
    }
    return true;
}

bool
OCSet::binaryInsert(string key, int val)
{
    int start = 0;
    int end = (int)m_orderedKeys.size() - 1;
    while (start <= end) {
        int mid = (start + end)/2;
        cout << "Start: " << start << ", end: " << end << ", mid: " << mid << endl;
        int midVal = m_counterSet.at(m_orderedKeys.at(mid));
        cout << "Midval: " << midVal << " val: " << val << endl;
        if (midVal == val || start == end) {
            cout << "Conducting insertion" << endl;
            int insertionIndex = mid;
            cout << "insertion index " << insertionIndex << endl;
            while (insertionIndex < m_orderedKeys.size() - 1 && m_counterSet.at(m_orderedKeys.at(insertionIndex + 1)) >= val) {
                insertionIndex ++;
                cout << "insertion index " << insertionIndex << endl;
            }
            if (insertionIndex >= m_orderedKeys.size() - 1) {
                m_orderedKeys.push_back(key);
                m_positionMap.at(key) = insertionIndex;
            } else {
                m_orderedKeys.insert(m_orderedKeys.begin() + insertionIndex, key);
                m_positionMap.at(key) = insertionIndex;
            }
            return true;
        } else if (val < midVal) {
            start = mid + 1;
        } else if (midVal < val) {
            end = mid;
        }
    }
    cout << "binary insert returned false" << endl;
    return false;
}

int
OCSet::get(string key)
{
    if (m_counterSet.count(key) > 0) {
        return m_counterSet.at(key);
    } else {
        return 0;
    }
}

int
OCSet::size()
{
    return m_size;
}

void
OCSet::write(string filename, int numValues)
{
    // loop through the first numValues orderedKeys and write them each to the counterset alongside their corresponding count
    ofstream outFile(filename, ofstream::app);
    for ( string key: m_orderedKeys ) {
        if ( m_counterSet.count(key) > 0) {
            cout << "Key not found in set" << endl;
        } else {
            int val = m_counterSet.at(key);
            if (outFile.is_open()) {
                outFile << key << " : " << val << endl;
            }
        }
    }
    if (outFile.is_open()) {
        outFile.close();
    }
}

void
OCSet::debug()
{
    for ( string key: m_orderedKeys ) {
        if (m_counterSet.count(key) < 1) {
            cout << "Key not found in set" << endl;
        } else {
            int val = m_counterSet.at(key);
            cout << "Value for key " << key << " : " << val << endl;
        }
    }
}

void
ocSet_runTests()
{
    OCSet* testSet1 = new OCSet();
    OCSet* testSet2 = new OCSet();
    int numAddFailed;
    int numSetFailed;
    if ((numAddFailed = ocSet_testAdd(testSet1)) != 0) {
        cout << numAddFailed << " Adding tests failed" << endl;
    }
    cout << "Debug output for adding tests: " << endl;
    testSet1->debug();
    if ((numSetFailed = ocSet_testSet(testSet2)) != 0) {
        cout << numSetFailed << " Set tests failed" << endl;
    }
    cout << "Debug output for setting tests: " << endl;
    testSet2->debug();
    delete testSet1;
    delete testSet2;
    
    if (numAddFailed == 0 && numSetFailed == 0) {
        cout << "All tests passed!" << endl;
    }
}

int
ocSet_testAdd(OCSet* testSet)
{
    int numFailed = 0;
    testSet->add("string1");
    if (testSet->size() != 1) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    testSet->add("string2");
    if (testSet->size() != 2) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    testSet->add("string1");
    testSet->add("string1");
    if (testSet->get("string1") != 3 || testSet->get("string2") != 1) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    testSet->add("string3");
    testSet->add("string3");
    testSet->add("string3");
    testSet->add("string3");
    testSet->add("string3");
    if (testSet->get("string1") != 3 || testSet->get("string2") != 1 || testSet->get("string3") != 5) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    testSet->add("string1");
    testSet->add("string1");
    testSet->add("string1");
    testSet->add("string1");
    testSet->add("string1");
    testSet->add("string1");
    if (testSet->get("string1") != 9 || testSet->get("string2") != 1 || testSet->get("string3") != 5) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    return numFailed;
}

int
ocSet_testSet(OCSet* testSet)
{
    int numFailed = 0;
    testSet->add("string1");
    testSet->add("string2");
    testSet->add("string2");
    testSet->add("string3");
    testSet->add("string3");
    testSet->add("string3");
    if (!testSet->set("string1", 10) || testSet->get("string1") != 10) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    cout << "test set: " << endl;
    testSet->debug();
    if (!testSet->set("string2", 10) || testSet->get("string2") != 10) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    cout << "test set: " << endl;
    testSet->debug();
    if (!testSet->set("string3", 10) || testSet->get("string3") != 10) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    cout << "test set: " << endl;
    testSet->debug();
    if (!testSet->set("string2", 1) || testSet->get("string2") != 1) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    cout << "test set: " << endl;
    testSet->debug();
    if (!testSet->set("string3", 5) || testSet->get("string3") != 5) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    cout << "test set: " << endl;
    testSet->debug();
    if (testSet->size() != 3) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    
    if (!testSet->set("string4", 15) || testSet->get("string4") != 15) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    if (testSet->size() != 4) {
        cout << "test failed" << endl;
        numFailed ++;
    } else {
        cout << "test passed" << endl;
    }
    testSet->debug();
    
    return numFailed;
}
