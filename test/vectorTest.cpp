#include "Counter.h"
#include "Datum.h"
#include "Doge.h"
#include "Doge.cpp"
#include <iostream>

void testPrint(string s);

int main(){
    Counter<string,float> a;
    Counter<string,float> b;

    testPrint("Testing basic map functionality");
    a["a"]=1;
    a["c"]=2.5;
    a["d"]=1;
    cout << a;
    cout << " should be { \"a\":1 \"b\":0 \"c\":2.5 \"d\":1 } " << endl;
    b["a"]=3.5;
    b["b"]=-2.5;
    b["c"]=-5.0;
    b["d"]=-2;
    cout << b;
    cout << " should be { \"a\":3.5 \"b\":-2.5 \"c\":-5.0 \"d\":-2.0 } " << endl;

    testPrint("Testing vector-add functionality");
    Counter<string,float> c = a+b;
    cout << c;
    cout << " should be { \"a\":4.5 \"b\":-2.5 \"c\":-2.5 \"d\":-1.0 } " << endl;

    testPrint("Testing vector-subtraction functionality ...");
    Counter<string,float> d = a-b;
    cout << d;
    cout << " should be { \"a\":-2.5 \"b\":2.5 \"c\":7.5 \"d\":3.0 } " << endl;

    testPrint("Testing vector scaling...");
    cout << a*2;
    cout << " should be { \"a\":2 \"b\":0 \"c\":5.0 \"d\":2 } " << endl;

    testPrint("Testing original vector integrity");
    cout << a;
    cout << " should be { \"a\":1 \"b\":0 \"c\":2.5 \"d\":1 } " << endl;
    cout << b;
    cout << " should be { \"a\":3.5 \"b\":-2.5 \"c\":-5.0 \"d\":-2.0 } " << endl;

    testPrint("Testing Dot Product...");
    int p = a*b;
    cout << p;
    cout << " should be -11 " << endl;
    cout << c*d << " should be -39.25" << endl;

    testPrint("Testing reflexive add...");
    a+=b;
    cout << a;
    cout << " should be " << c << endl;

    testPrint("Testing reflexive subtract...");
    a-=b;
    cout << a;
    cout << " should be { \"a\":1 \"b\":0 \"c\":2.5 \"d\":1 } " << endl;

    testPrint("Testing reflexive scale...");
    a*=2;
    cout << a;
    cout << " should be { \"a\":2 \"b\":0 \"c\":5 \"d\":2 } " << endl;

}

void testPrint(string s){
    cout << endl << s <<  endl;
    for (int i = 0; i < s.length(); i++){
        cout << "=";
    }
    cout << endl << endl;
}
