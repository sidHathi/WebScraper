//
//  MarketTracker.cpp
//  WebScraper
//
//  Created by Siddharth Hathi on 1/28/22.
//

#include "MarketTracker.hpp"

MarketTracker::MarketTracker(string tickerFileName, double trackingFreq)
{
    m_trackingFrequency = trackingFreq;
    string line;
    ifstream tickerFile(tickerFileName);
    while ( tickerFile.is_open() && getline(tickerFile, line) ) {
        if (line.find("size=") == 0) {
            string sizeStr = line.substr(5, line.length() - 4);
            int size = stoi(sizeStr);
            m_tickers.reserve(size);
            m_stocks.reserve(size);
        } else {
            m_tickers.push_back(line);
            StockTracker* tracker = new StockTracker(line, m_trackingFrequency);
            m_stocks.push_back(tracker);
            
        }
    }
}

MarketTracker::MarketTracker(vector<string> tickers, double trackingFreq)
{
    m_trackingFrequency = trackingFreq;
    m_tickers.resize(tickers.size());
    for ( string ticker: tickers ) {
        m_tickers.push_back(ticker);
        StockTracker* tracker = new StockTracker(ticker, m_trackingFrequency);
        m_stocks.push_back(tracker);
        cout << "Ticker added to tracker" << endl;
    }
}

void
MarketTracker::start()
{
    cout << "MarketTracker began tracking" << endl;
    m_promisedTracks.reserve(m_stocks.size());
    for ( StockTracker* stock: m_stocks ) {
        cout << "Async StockTracker started" << endl;
        m_promisedTracks.push_back(stock->startTracking());
    }
}

void
MarketTracker::stop()
{
    for ( StockTracker* stock: m_stocks ) {
        stock->endTracking();
    }
    
    for ( int i = 0; i < m_promisedTracks.size(); i ++ ) {
        m_promisedTracks.at(i).wait();
    }
}

void
MarketTracker::freeTickers()
{
    for ( StockTracker* stock: m_stocks ) {
        stock->free();
    }
}
