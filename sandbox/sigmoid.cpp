#include <iostream>
#include <math.h>
using namespace std;

float sigmoid(float x){
    return 1/(1+exp(-x));

}

int main(){
    for (float i = -5.0; i < 5.0; i+=.1){
        cout << "sigmoid(" << i << ") = " << sigmoid(i) << endl;
    }
    return 0;
}
