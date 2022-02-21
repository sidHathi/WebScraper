//
//  main.cpp
//  WebScraper
//
//  Created by Siddharth Hathi on 1/24/22.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "HelloWorld.hpp"
#include "Scraper.hpp"
#include "StockTracker.hpp"
#include "MarketTracker.hpp"
#include "OCSet/OCSet.hpp"

using namespace std;

void
scraperTests()
{
    
    string testUrl = "https://finance.yahoo.com/quote/IBM";
    Scraper* scraper = new Scraper(testUrl);
    
    unordered_map<string, string> htmlAttribs;
    htmlAttribs["data-test"] = "qsp-price";
    htmlAttribs["data-field"] = "regularMarketPrice";
    
    string html = scraper->getResponse();
    scraper->parseResponse();
    scraper->trackNewElement("price", htmlAttribs);
    unordered_map<string, string> elemMap = scraper->getTrackedValues();
    if (elemMap.size() > 0) {
        cout << "value appended to elemMap\n";
        for ( auto item: elemMap ) {
            string key = item.first;
            string val = item.second;
            cout << "ElemMap value for key " << key << " is " << val << "\n";
        }
    } else {
        cout << "empty elemMap\n";
    }
    
    scraper->updateTrackedValues();
    elemMap = scraper->getTrackedValues();
    if (elemMap.size() > 0) {
        cout << "value appended to elemMap\n";
        for ( auto item: elemMap ) {
            string key = item.first;
            string val = item.second;
            cout << "ElemMap value for key " << key << " is " << val << "\n";
        }
    } else {
        cout << "empty elemMap\n";
    }
    //scraper->debug();
    scraper->free();
    delete scraper;
}

void
startInputLoop(StockTracker* tracker/*, future<void>* trackAsync*/)
{
    bool shouldQuit = false;
    string next;
    while (!shouldQuit) {
        cout << "Checking for input" << endl;
        cin >> next;
        if ( next.length() > 0 && (next[0] == 'q' || next[0] == 'Q')) {
//            cout << "Quit Signal received" << endl;
            shouldQuit = true;
            tracker->endTracking();
            return;
        }
    }
}


void
startInputLoop2(MarketTracker* tracker/*, future<void>* trackAsync*/)
{
    bool shouldQuit = false;
    string next;
    while (!shouldQuit) {
        cout << "Checking for input" << endl;
        cin >> next;
        if ( next.length() > 0 && (next[0] == 'q' || next[0] == 'Q')) {
//            cout << "Quit Signal received" << endl;
            shouldQuit = true;
            tracker->stop();
            return;
        }
    }
}

int
main(int argc, char** argv)
{
    ocSet_runTests();
//
//    StockTracker* appleTracker = new StockTracker("AAPL", 5);
//
//    future<void> inputAsync = async(launch::async, &startInputLoop, appleTracker);
//    future<void> trackAsync = appleTracker->startTracking();
//
//    cout << "startTracking exitted\n";
//    inputAsync.wait();
//    trackAsync.wait();
//
//    appleTracker->free();
//    delete appleTracker;
//
//    vector<string> tickers = {"AAPL", "^GSPC", "DOCU"};
//    MarketTracker* tracker = new MarketTracker(tickers, 1);
//    inputAsync = async(launch::async, &startInputLoop2, tracker);
//    tracker->start();
//    inputAsync.wait();
//    tracker->freeTickers();
}
