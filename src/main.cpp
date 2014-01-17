#include "NeuralGrid.hpp"
#include <iostream>
#include "math.h"

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
    /**
    NeuralGrid* n = new NeuralGrid(5,2,1,1,0.01,1000000);


    n->save("simple_initial.dat");

    vector<Datum> trainingData(200);
    for (int i = 0.0; i < trainingData.size() ; i++){
        double x = i*45/trainingData.size();
        double y = f(x);
        trainingData[i].features = vector<double>(1,x);
        trainingData[i].label = vector<double>(1,y);
    }

    double rmsError=0.0;
    for (int i = 0.0; i < trainingData.size() ; i++){
        double x = i*45/trainingData.size();
        double actualVal = f(x);
        double netOutput=(n->evaluate(vector<double>(1,x))[0]);
        rmsError+=(actualVal-netOutput)*(actualVal-netOutput);
    }
    rmsError=sqrt(rmsError);

    cout << "Root mean square error before training:" << rmsError << endl;

    n->train(trainingData);

    for (int i = 0.0; i < trainingData.size() ; i++){
        double x = i*45/trainingData.size();
        double actualVal = f(x);
        double netOutput=(n->evaluate(vector<double>(1,x))[0]);
        rmsError+=(actualVal-netOutput)*(actualVal-netOutput);
    }
    rmsError=sqrt(rmsError);

    cout << "Root mean square error after training:" << rmsError << endl;


    n->save("simple_trained.dat");

    cout << "Deleting old grid..." << endl;
    delete n;
    **/

    cout << "Loading..." << endl;
    NeuralGrid* n = new NeuralGrid("simple_initial.dat");
    n->save("restored_trained.dat");

    double userInput;
    while (true){
        cout << ">> ";
        cin >> userInput;
        cout << endl;
        double netOutput=(n->evaluate(vector<double>(1,userInput))[0]);
        double actualVal=f(userInput);
        cout << "Value computed by neural net:\t" << netOutput << endl;
        cout << "Value computed by f:\t" << actualVal << endl;
        cout << "Error : \t\t" << netOutput - actualVal << endl;
    }
    delete n;
}
