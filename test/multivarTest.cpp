#include "NeuralGrid.hpp"
#include <iostream>
#include <math.h>

#define _USE_MATH_DEFINES

#define F_DATA_RANGE (45)

#define DATA_DIMENSION (20)

double f(double x, double y){
    return x>y?0.8:0.2;
}
double g(double x, double y){
    return x>y?0.2:0.8;
}

int main(){

    NeuralGrid& n = *(new NeuralGrid(200,3,2,2,0.01,50000));

    vector<Datum> trainingData(DATA_DIMENSION*DATA_DIMENSION);

    for (int i = 0.0; i < DATA_DIMENSION ; i++){
        for (int j = 0.0; j < DATA_DIMENSION ; j++){
            double x = i*F_DATA_RANGE/DATA_DIMENSION;
            double y = j*F_DATA_RANGE/DATA_DIMENSION;
            double fx = f(x,y);
            double gx = g(x,y);
            trainingData[i+DATA_DIMENSION*j].features = vector<double>(2);
            trainingData[i+DATA_DIMENSION*j].features[0] = x;
            trainingData[i+DATA_DIMENSION*j].features[1] = y;
            trainingData[i+DATA_DIMENSION*j].label = vector<double>(2);
            trainingData[i+DATA_DIMENSION*j].label[0]=fx;
            trainingData[i+DATA_DIMENSION*j].label[1]=gx;
        }
    }

    n.train(trainingData);

    double fError = 0.0;
    double gError = 0.0;

    //Testing
    for (int i = 0.0; i < DATA_DIMENSION ; i++){
        for (int j = 0.0; j < DATA_DIMENSION ; j++){
            double x = i*F_DATA_RANGE/DATA_DIMENSION;
            double y = j*F_DATA_RANGE/DATA_DIMENSION;
            double fx = f(x,y);
            double gx = g(x,y);
            vector<double> input(2);
            input[0]=x;
            input[1]=y;
            vector<double> netOutput=n.evaluate(input);
            fError+=(netOutput[0]-fx)*(netOutput[0]-fx);
            gError+=(netOutput[0]-gx)*(netOutput[0]-gx);
        }
    }
    cout << "Root-mean-square error : " << sqrt(fError)+sqrt(gError) << endl;

    double userInputX;
    double userInputY;

    while (true){
        cout << ">> ";
        cin >> userInputX >> userInputY;
        cout << endl;
        vector<double> userInput(2);
        userInput[0]=userInputX;
        userInput[1]=userInputY;
        vector<double> netOutput=n.evaluate(userInput);
        double actualF=f(userInputX,userInputY);
        double actualG=g(userInputX,userInputY);
        cout << "Value computed by neural net:\t" << netOutput[0] << " " << netOutput[1] << endl;
        cout << "Value computed by f,g:\t" << actualF << " " << actualG << endl;
        cout << "Error : \t\t" << netOutput[0] - actualF << " " << netOutput[1] - actualG << endl;
    }
}
