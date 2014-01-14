#include "NeuralGrid.hpp"
#include <iostream>

int main(){
    NeuralGrid *n = new NeuralGrid(5,5,5,5,.01,10000);
    delete n;
}
