//
//  StockTracker.cpp
//  WebScraper
//
//  Created by Siddharth Hathi on 1/25/22.
//

#include "StockTracker.hpp"

StockTracker::StockTracker(string ticker, string outFileName, double trackingFrequency)
{
    m_fileAddress = ticker + ".txt";
    m_trackingFrequency = trackingFrequency;
    
    string urlStr = "https://finance.yahoo.com/quote/" + ticker;
    m_webScraper = new Scraper(urlStr);
    m_webScraper->trackNewElement("price", c_yfPriceHtmlAttribs);
    m_low = numeric_limits<double>::max();
    m_high = numeric_limits<double>::min();
    m_currentlyTracking = new bool;
    *m_currentlyTracking = false;
}

void
StockTracker::startTracking()
{
    
}

void
StockTracker::track()
{
    
}
