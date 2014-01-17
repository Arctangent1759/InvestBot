#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream f("test.txt");
    f<<"asdfg"<<endl;
    f<<"foobar"<<endl;
    f.close();
}
