#include <cstdlib>
#include <iostream>
using namespace std;
int main(){
    rand();
    cout << rand() << endl;
    float x = rand();
    cout << x/RAND_MAX << endl;
    cout << (rand()/RAND_MAX)/2-1 << endl;
    return 0;
}
