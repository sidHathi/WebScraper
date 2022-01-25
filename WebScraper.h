#ifndef _WEBSCRAPER_H
#define _WEBSCRAPER_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cpr/cpr.h>
#include "gumbo.h"

using namespace cpr;
using namespace std;

class WebScraper {
    protected:
        Url* m_url;
    public:
        WebScraper(string url);
};

#endif // _WEBSCRAPER_H