#include <curl/curl.h>
#include <iostream>
#include <cstdlib>
using namespace std;

size_t function_pt(char *ptr, size_t size, size_t nmemb, string *stream){
    cout << "Output :" << 10*(double)atof(ptr) << endl;
}

int main(){

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, function_pt);

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://download.finance.yahoo.com/d/quotes.csv?s=csco&f=l1");
        res = curl_easy_perform(curl);
        cout << "foobar" << endl << flush;
        curl_easy_setopt(curl, CURLOPT_URL, "http://download.finance.yahoo.com/d/quotes.csv?s=goog&f=l1");
        res = curl_easy_perform(curl);
        cout << "foobar" << endl << flush;
        curl_easy_setopt(curl, CURLOPT_URL, "http://download.finance.yahoo.com/d/quotes.csv?s=qqq&f=l1");
        res = curl_easy_perform(curl);
        cout << "foobar" << endl << flush;
        curl_easy_cleanup(curl);
    }

    return 0;
}

