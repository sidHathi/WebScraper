//
//  WebScraper.cpp
//  WebScraper
//
//  Created by Siddharth Hathi on 1/24/22.
//

#include "Scraper.hpp"

Scraper::Scraper(string urlStr)
{
    m_url = Url{urlStr};
    m_html = "";
    m_response = NULL;
    m_hrefs = vector<string>(1000, "");
}

string
Scraper::getResponse()
{
    m_html = "";
    printf("Attempting to retrieve html response\n");
    if (m_url != NULL) {
        printf("Non-null URL\n");
        Response res = Get(m_url);
        m_html = res.text;
        long status_code = res.status_code;
        Url resUrl = res.url;
        cout << "URL: " + resUrl.str() + "\n";
        printf("Status code returned: %ld\n", status_code);
        
        m_response = gumbo_parse(m_html.c_str());
    }
    return m_html;
}

void
Scraper::parseResponse()
{
    if (m_response == NULL) {
        return;
    }
    
    extractLinks(m_response->root);
}

void
Scraper::extractLinks(GumboNode* node)
{
    if (node == NULL || node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    
    if (node->v.element.tag == GUMBO_TAG_A) {
        GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
        if (href) {
            m_hrefs.push_back(href->value);
        }
    }
    
    GumboVector* children = &node->v.element.children;
    for ( int i = 0; i < children->length; i ++ ) {
        extractLinks(static_cast<GumboNode*>(children->data[i]));
    }
}

vector<string>
Scraper::getLinks()
{
    if (m_hrefs.size() < 1 && m_response != NULL) {
        extractLinks(m_response->root);
    }
    
    return m_hrefs;
}

void
Scraper::trackNewElement(string elemName, unordered_map<string, string> attributes)
{
    if (m_response != NULL && trackElement(elemName, attributes, 0, m_response->root, new vector<int>())) {
        cout << "values found\n";
    }
}

bool
Scraper::trackElement(string elemName, unordered_map<string, string> attributes, int depth, GumboNode *node, vector<int>* trace)
{
    if (node == NULL || node->type != GUMBO_NODE_ELEMENT) {
        return false;
    }
    
    //cout << "tracking element " << elemName << "\n";
    int matchingKeys = 0;
    GumboVector* attribs = &node->v.element.attributes;
    if (attribs != NULL && attribs->length > attributes.size() && attribs->length < 100) {
        ///cout << "Iterating current node attributes\n";
        for ( int i = 0; i < attribs->length; i ++ ) {
            GumboAttribute* attrib = static_cast<GumboAttribute*>(attribs->data[i]);
            string attribName = attrib->name;
            if (attributes.count(attribName) != 0 && attributes.at(attribName) == attrib->value) {
                cout << "Matched ";
                cout << "Attribute name " << attribName << " Attribute value " << attrib->value << "\n";
                matchingKeys ++;
            } else if (attributes.count(attribName) != 0) {
                cout << "Attribute name " << attribName << " Attribute value " << attrib->value << "\n";
                //break;
            }
        }
    }
    
    if (matchingKeys == attributes.size()) {
        if (depth > trace->size()) {
            cout << "Resizing trace vector to size " << depth << "\n";
            trace->resize(depth);
            trace->at(depth - 1) = (int)node->index_within_parent;
            m_trackedValues[elemName] = gumbo_get_attribute(attribs, "value")->value;
            //trace.at(depth) = (int)node->index_within_parent;
        }
        return true;
    }
     
    GumboVector* children = &node->v.element.children;
    for ( int i = 0; i < children->length; i ++ ) {
        GumboNode* child = static_cast<GumboNode*>(children->data[i]);
        if (trackElement(elemName, attributes, depth + 1, child, trace)) {
            cout << "Inserting into trace vector at index " << depth << "\n";
            if (depth == 0) {
                m_trackingTraces[elemName] = trace;
            } else {
                trace->at(depth - 1) = (int)node->index_within_parent;
            }
            return true;
        }
    }
    return false;
}

void
Scraper::updateTrackedValues()
{
    if (m_trackingTraces.size() < 1) {
        return;
    }
    getResponse();
    for ( auto keyVal: m_trackedValues ) {
        string name = keyVal.first;
        m_trackedValues[name] = gumbo_get_attribute(&followTrace(m_response->root, m_trackingTraces.at(name))->v.element.attributes, "value")->value;
    }
}

GumboNode*
Scraper::followTrace(GumboNode *root, vector<int>* trace)
{
    if (root == NULL) {
        return NULL;
    }
    GumboNode* currentNode = root;
    for ( int nextIndex: *trace ) {
        GumboVector* children = &currentNode->v.element.children;
        if (nextIndex < children->length) {
            currentNode = static_cast<GumboNode*>(children->data[nextIndex]);
        }
    }
    return currentNode;
}

unordered_map<string, string>
Scraper::getTrackedValues()
{
    return m_trackedValues;
}

void
Scraper::debug()
{
    if (m_response == NULL) {
        cout << "No response \n";
        return;
    }
    
    cout << "Url: " << m_url.str();
    cout << "Links:\n";
    
    if (m_hrefs.size() > 0) {
        for ( int i = 0; i < m_hrefs.size(); i ++ ) {
            cout << m_hrefs.at(i) << "\n";
        }
    }
}

void
Scraper::free()
{
    if (m_response != NULL) {
        gumbo_destroy_output(&kGumboDefaultOptions, m_response);
    }
    m_hrefs.clear();
}
