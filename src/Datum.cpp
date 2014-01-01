#include "Datum.h"
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
