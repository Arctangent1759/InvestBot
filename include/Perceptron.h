#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <vector>
#include "include/Datum.h"
using namespace std;

template <class T>
class Perceptron{
    public:
        Perceptron();
        Perceptron(vector< Datum<T> > training, vector< Datum<T> > heldOut, vector< Datum<T> > Validation);
    protected:
        vector<float> myWeights;
};
#endif
