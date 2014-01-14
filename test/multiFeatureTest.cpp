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
double g(double x){
    if (x<15){
        return 0.25;
    }else if (x == 15){
        return 0.5;
    }else if (x < 30){
        return 0.75;
    }else if (x==30){
        return 0.5;
    }else{
        return 0.25;
    }
}

int main(){

    NeuralGrid& n = *(new NeuralGrid(40,1,1,2,0.01,1000000));

    vector<Datum> trainingData(200);

    for (int i = 0.0; i < trainingData.size() ; i++){
        double x = i*F_DATA_RANGE/trainingData.size();
        double fx = f(x);
        double gx = g(x);
        trainingData[i].features = vector<double>(1,x);
        trainingData[i].label = vector<double>(2);
        trainingData[i].label[0]=fx;
        trainingData[i].label[1]=gx;
    }

    n.train(trainingData);

    double userInput;

    while (true){
        cout << ">> ";
        cin >> userInput;
        cout << endl;
        vector<double> netOutput=(n.evaluate(vector<double>(1,userInput)));
        double actualF=f(userInput);
        double actualG=g(userInput);
        cout << "Value computed by neural net:\t" << netOutput[0] << " " << netOutput[1] << endl;
        cout << "Value computed by f,g:\t" << actualF << " " << actualG << endl;
        cout << "Error : \t\t" << netOutput[0] - actualF << " " << netOutput[1] - actualG << endl;
    }
}
