#include <iostream>

using namespace std;

void swap(int &a, int &b){
    int x = a;
    a=b;
    b=x;
}
int main(){
    int a = 1;
    int b = 2;
    cout << "Before: " << a << " " << b << endl;
    swap(a,b);
    cout << "After: " << a << " " << b << endl;
}
