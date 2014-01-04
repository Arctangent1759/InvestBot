#ifndef COUNTER_H
#define COUNTER_H
#include <map>
#include <iostream>
using namespace std;
template <class K, class V>
class Counter : public map<K,V>{
    public:
        Counter();
        Counter(const Counter<K,V>& other);
        Counter<K,V>& operator+(Counter<K,V>& other);
        Counter<K,V>& operator+=(Counter<K,V>& other);
        Counter<K,V>& operator-(Counter<K,V>& other);
        Counter<K,V>& operator-=(Counter<K,V>& other);
        Counter<K,V>& operator*(float other);
        Counter<K,V>& operator*=(float other);
        float operator*(Counter<K,V>& other);
        template <class T, class U>
        friend ostream& operator<<(ostream &strm, const Counter<T,U>& rhs);
};

template <class K, class V>
Counter<K,V>::Counter(){}

template <class K, class V>
Counter<K,V>::Counter(const Counter<K,V>& other){
    for (typename map<K,V>::const_iterator i = other.begin();i!=other.end();++i){
        (*this)[i->first]=i->second;
    }
}

template <class K, class V>
Counter<K,V>& Counter<K,V>::operator+(Counter<K,V>& other){
    Counter& out = *(new Counter(*this)); //copy this
    for (typename map<K,V>::const_iterator i = other.begin();i!=other.end();++i){
        out[i->first]+=other[i->first];
    }
    return out;
}

template <class K, class V>
Counter<K,V>& Counter<K,V>::operator+=(Counter<K,V>& other){
    Counter& out = *this + other;
    *this = out;
    return out;
}

template <class K, class V>
Counter<K,V>& Counter<K,V>::operator-(Counter<K,V>& other){
    Counter& out = *(new Counter(*this)); //copy this
    for (typename map<K,V>::const_iterator i = other.begin();i!=other.end();++i){
        out[i->first]-=other[i->first];
    }
    return out;
}

template <class K, class V>
Counter<K,V>& Counter<K,V>::operator-=(Counter<K,V>& other){
    Counter& out = *this - other;
    *this = out;
    return out;
}

template <class K, class V>
Counter<K,V>& Counter<K,V>::operator*(float rhs){
    Counter& out = *(new Counter(*this)); //copy this
    for (typename map<K,V>::const_iterator i = this->begin();i!=this->end();++i){
        out[i->first]*=rhs;
    }
    return out;
}

template <class K, class V>
Counter<K,V>& Counter<K,V>::operator*=(float rhs){
    Counter& out = *this * rhs;
    *this = out;
    return out;
}

template <class K, class V>
float Counter<K,V>::operator*(Counter<K,V>& other){
    float out = 0.0; 
    for (typename map<K,V>::const_iterator i = this->begin();i!=this->end();++i){
        out+=(*this)[i->first]*other[i->first];
    }
    return out;
}

template <class K, class V>
std::ostream& operator<<(std::ostream &strm, const Counter<K,V>& rhs){
    strm << "{ ";
    for (typename map<K,V>::const_iterator i = rhs.begin();i!=rhs.end();++i){
        strm << i->first << ":" << i->second << " ";
    }
    strm << "}";
    return strm;
}
#endif
