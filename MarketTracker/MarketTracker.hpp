//
//  MarketTracker.hpp
//  WebScraper
//
//  Created by Siddharth Hathi on 1/28/22.
//

#ifndef MarketTracker_hpp
#define MarketTracker_hpp

#include <stdio.h>
#include <vector>

#include "StockTracker.hpp"

class MarketTracker
{
protected:
    vector<StockTracker*> m_stocks;
    vector<string> m_tickers;
    vector<future<void>> m_promisedTracks;
    double m_trackingFrequency;
public:
    MarketTracker(string tickerFileName, double trackingFreq);
    MarketTracker(vector<string> tickers, double trackingFreq);
    void start();
    void stop();
    void freeTickers();
    void debug();
};

#endif /* MarketTracker_hpp */
