#include "PriceGetter.hpp"
#include <cstdlib>
#include <iostream>

CURL *init(){
}

/*
size_t function_pt(char *ptr, size_t size, size_t nmemb, string *stream){
}

PriceGetter::PriceGetter(){
    curl = curl_easy_init();
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, function_pt);
    if (!curl){
        cerr << "Failed to initialize curl" << endl;
        exit(1);
    }
}

double PriceGetter::getCurrPrice(string symbol){
    string s = "http://download.finance.yahoo.com/d/quotes.csv?s="+symbol+"&f=l1";
    curl_easy_setopt(curl, CURLOPT_URL, &s);
    CURLcode res = curl_easy_perform(curl);
}
*/
