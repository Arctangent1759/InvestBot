#include "NeuralGrid.hpp"
#include <iostream>
#include <math.h>

#define samplingRate (2)
#define numPeriods (2)
#define _USE_MATH_DEFINES

int main(){

    NeuralGrid& n = *(new NeuralGrid(20,1,1,1,0.25,100000));

    vector<Datum> trainingData(floor(numPeriods*2*M_PI*samplingRate));
    for (int i = 0; i < trainingData.size(); i++){
        float x = (i*numPeriods*2*M_PI)/trainingData.size();
        float y = sin(x);
        trainingData[i].features = vector<float>(1,x);
        trainingData[i].label = vector<float>(1,y);
    }

    n.train(trainingData);

    float userInput;

    while (true){
        cout << ">> ";
        cin >> userInput;
        cout << endl;
        float netOutput=(n.evaluate(vector<float>(1,userInput))[0]);
        float actualVal=sin(userInput);
        cout << "Value computed by neural net:\t" << netOutput << endl;
        cout << "Value computed by std::sin :\t" << actualVal << endl;
        cout << "Error : \t\t" << netOutput - actualVal << endl;
    }
}
