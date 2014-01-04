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

template <class T>
Datum<T>::Datum(T& data, string label){
    this->myData=data;
    this->myLabel=label;
}

template <class T>
T& Datum<T>::getData(){
    return this->myData;
}

template <class T>
string Datum<T>::getLabel(){
    return this->myLabel;
}
#endif
