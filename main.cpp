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

using namespace std;

int
main(int argc, char** argv)
{
//    HelloWorld* hw = new HelloWorld();
//    hw->printToConsole();
    
    string testUrl = "https://finance.yahoo.com/quote/IBM";
    Scraper* scraper = new Scraper(testUrl);
    
    unordered_map<string, string> htmlAttribs;
    htmlAttribs["data-test"] = "qsp-price";
    htmlAttribs["data-field"] = "regularMarketPrice";
    
    string html = scraper->getResponse();
//    ofstream htmlFile("html.txt");
//    if (htmlFile.is_open()) {
//        htmlFile << html;
//        htmlFile.close();
//    }
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
    //printf("%s\n", html.data());
}
