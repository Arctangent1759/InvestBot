/**
 *
 * Gets the quote for a stock symbol via the Yahoo Finance API.
 *
 * @author Alex Chu
 *
 */
#include <string>
#include <curl/curl.h>

using namespace std;

CURL *init();

double getCurrPrice(CURL *curl, string symbol);
double getHistoricalPrice(CURL *curl, string symbol);

void cleanup();
