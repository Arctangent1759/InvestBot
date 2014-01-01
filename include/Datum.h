#ifndef DATUM_H
#define DATUM_H
#include <string>
using namespace std;

template <class T> 
class Datum{
    public:
        Datum<T>(T& data,string label);
        T& getData();
        string getLabel();
    protected:
        T myData;
        string myLabel;
};
#endif
