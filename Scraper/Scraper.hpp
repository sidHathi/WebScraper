//
//  WebScraper.hpp
//  WebScraper
//
//  Created by Siddharth Hathi on 1/24/22.
//

#ifndef Scraper_hpp
#define Scraper_hpp

#include <stdio.h>
#include <cpr/cpr.h>
#include <iostream>
#include <gumbo.h>
#include <vector>
#include <unordered_map>

using namespace cpr;
using namespace std;

const int c_initialVectorSize = 1000;

class Scraper {
    
protected:
    Url m_url;
    string m_html;
    GumboOutput* m_response;
    vector<string> m_hrefs;
    unordered_map<string, vector<int>*> m_trackingTraces;
    unordered_map<string, string> m_trackedValues;
    
    void extractLinks(GumboNode* node);
    bool trackElement(string elemName, unordered_map<string, string> attributes, int depth, GumboNode* node, vector<int>* trace);
    GumboNode* followTrace(GumboNode* root, vector<int>* trace);
public:
    Scraper(string url);
    string getResponse();
    void parseResponse();
    vector<string> getLinks();
    void trackNewElement(string elemName, unordered_map<string, string> attributes);
    void updateTrackedValues();
    unordered_map<string, string> getTrackedValues();
    void debug();
    void free();
};

#endif /* Scraper_hpp */
