#include "Counter.h"
#include <iostream>

int main(){
    Counter<string,int> a;
    Counter<string,int> b;
    a["a"]=1;
    a["b"]=0;
    a["c"]=2.5;
    a["d"]=1;

    cout << a << endl;

    b["a"]=3.5;
    b["b"]=-2.5;
    b["c"]=-5.0;
    b["d"]=-2;

    cout << b << endl;
}
