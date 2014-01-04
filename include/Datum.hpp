#ifndef DATUM_H
#define DATUM_H

#include <vector>
using namespace std;
typedef struct {
    vector<float> features;
    vector<float> label;
} Datum;

#endif
