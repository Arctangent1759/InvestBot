#include <set>
#include <iostream>

using  namespace std;

int main(){
    set<int> s;
    s.insert(0);
    s.insert(0);
    s.insert(1);
    cout <<" "<< s.size() <<" "<< s.count(0) <<" "<< s.count(1) <<" "<< s.count(2) <<" "<< endl;


    return 0;
}
