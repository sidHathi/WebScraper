//
//  StockTracker.hpp
//  WebScraper
//
//  Created by Siddharth Hathi on 1/25/22.
//

#ifndef StockTracker_hpp
#define StockTracker_hpp

#include <stdio.h>
#include <iostream>
#include <unordered_map>

#include "Scraper.hpp"

const unordered_map<string, string> c_yfPriceHtmlAttribs = {
    { "data-test", "qsp-price" },
    { "data-field", "regularMarketPrice" }
};

class StockTracker
{
protected:
    string m_fileAddress;
    Scraper* m_webScraper;
    bool* m_currentlyTracking;
    double m_trackingFrequency;
    double m_high;
    double m_low;
    
    void track();
public:
    StockTracker(string ticker, string outFileName, double trackingFrequency);
    void startTracking();
    void endTracking();
    void free();
};

#endif /* StockTracker_hpp */
