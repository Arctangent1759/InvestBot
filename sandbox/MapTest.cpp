#include <map>
#include <string>
#include <iostream>

using namespace std;

int main(){
    map<string, int> m;
    m["a"]=1;
    m["b"]=2;
    m["c"]-=1;
    cout << m["a"] << m["b"] << m["c"] << endl;
}

