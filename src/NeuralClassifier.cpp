#include "NeuralClassifier.hpp"
#include <iostream>
#include "math.h"

NeuralClassifier::NeuralClassifier(int layerSize, int minLayers, 
        int maxLayers, double learningRate, int iterations,
        vector<Datum> &trainingData){
    this->init(layerSize, minLayers, maxLayers, learningRate, 
            iterations, trainingData);
}

NeuralClassifier::NeuralClassifier(int layerSize, int maxLayers, 
        double learningRate, int iterations, vector<Datum> &trainingData){
    this->init(layerSize, 1, maxLayers, learningRate, iterations, 
            trainingData);
}

NeuralClassifier::NeuralClassifier(string filename){
    this->myGrid = new NeuralGrid(filename);
}

void swapDatum(Datum &a, Datum &b){
    Datum tmp = a;
    a=b;
    b=tmp;
}

void NeuralClassifier::init(int layerSize, int minLayers, 
        int maxLayers, double learningRate, int iterations,
        vector<Datum> &trainingData){

    //Prepare training Data
    vector<Datum> training;
    vector<Datum> heldOut;
    vector<Datum> validation;
    
    //cout << "Preparing data..." << endl;

    randomizeTrainingDataArray(trainingData);
    for (int i = 0; i < trainingData.size(); i++){
        if (i%10<6){
            //60% of data in training
            training.push_back(trainingData[i]); 
        }else{
            //40% of data held out
            heldOut.push_back(trainingData[i]); 
        }
    }
    //cout << "Training Neural Classifier..." << endl;

    NeuralGrid* bestGrid = NULL;
    double bestScore=-1.0;;

    for (int numLayers = minLayers; numLayers <= maxLayers; numLayers++){
        //cout << "Training grid with " << numLayers << " layers..." << endl;
        
        NeuralGrid* curr = new NeuralGrid(layerSize, numLayers, training[0].features.size(), training[0].label.size(), learningRate, iterations);
        curr->train(training);
        double score = this->getAccuracy(curr,heldOut);
        //cout << "\tGrid score : " << score << endl;
        if (score > bestScore){
            //Invariant: Always trips on first iteration
            if (bestGrid){
                //cout << "Deleting best grid..." << endl;
                delete bestGrid;
                //cout << "Done deleting best grid..." << endl;
            }
            bestGrid = curr;
            bestScore = score;
        }else{
            delete curr;
            break;
        }
    }

    //cout << "Output grid score with held-out data: " << this->getAccuracy(bestGrid,heldOut) << endl;

    this->myGrid = bestGrid;
}

void NeuralClassifier::save(string filename){
    this->myGrid->save(filename);
}

void NeuralClassifier::load(string filename){
    delete this->myGrid;
    this->myGrid = new NeuralGrid(filename);
}

NeuralClassifier::~NeuralClassifier(){
    delete this->myGrid;
}

vector<double>& NeuralClassifier::evaluate(vector<double> &features){
    return this->myGrid->evaluate(features);
}

double NeuralClassifier::getAccuracy(NeuralGrid *grid, 
        vector<Datum> &heldOutData){
    double out = 0.0;
    for (vector<Datum>::iterator i = heldOutData.begin();
            i!=heldOutData.end();i++){
        vector<double> gridResult = grid->evaluate(i->features);
        for (int j = 0; j < gridResult.size(); j++){
            out+=(gridResult[j]-i->label[j])*(gridResult[j]-i->label[j]);
        }
    }
    return 1.0/sqrt(out);
}
