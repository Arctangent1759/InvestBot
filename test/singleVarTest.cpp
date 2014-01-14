#include "NeuralGrid.hpp"
#include <iostream>
#include <math.h>

#define _USE_MATH_DEFINES

#define F_DATA_RANGE (45)

double f(double x){
    if (x<15){
        return 0.75;
    }else if (x == 15){
        return 0.5;
    }else if (x < 30){
        return 0.25;
    }else if (x==30){
        return 0.5;
    }else{
        return 0.75;
    }
}

int main(){

    NeuralGrid& n = *(new NeuralGrid(40,1,1,1,0.01,1000000));

    vector<Datum> trainingData(200);

    for (int i = 0.0; i < trainingData.size() ; i++){
        double x = i*F_DATA_RANGE/trainingData.size();
        double y = f(x);
        trainingData[i].features = vector<double>(1,x);
        trainingData[i].label = vector<double>(1,y);
    }

    n.train(trainingData);

    double rmsError=0.0;
    for (int i = 0.0; i < trainingData.size() ; i++){
        double x = i*F_DATA_RANGE/trainingData.size();
        double actualVal = f(x);
        double netOutput=(n.evaluate(vector<double>(1,x))[0]);
        rmsError+=(actualVal-netOutput)*(actualVal-netOutput);
    }
    rmsError=sqrt(rmsError);
    cout << "Root-mean-square error: " << rmsError << endl;

    double userInput;

    while (true){
        cout << ">> ";
        cin >> userInput;
        cout << endl;
        double netOutput=(n.evaluate(vector<double>(1,userInput))[0]);
        double actualVal=f(userInput);
        cout << "Value computed by neural net:\t" << netOutput << endl;
        cout << "Value computed by f:\t" << actualVal << endl;
        cout << "Error : \t\t" << netOutput - actualVal << endl;
    }
}
