#ifndef DATUM_H
#define DATUM_H

#include <vector>
using namespace std;
typedef struct {
    vector<double> features;
    vector<double> label;
} Datum;

#endif
