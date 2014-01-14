#include <iostream>
#include <set>
#include <queue>
#include <sstream>
#include <cstdlib>
#include "NeuralGrid.hpp"
#include "Edge.hpp"
#include "math.h"
NeuralGrid::NeuralGrid(int layerSize, int numLayers, int numFeatures, int numOutputs, double learningRate, double maxIterations){
    //Init params
    this->layerSize=layerSize;
    this->numLayers=numLayers;
    this->numFeatures=numFeatures;
    this->numOutputs=numOutputs;
    this->learningRate=learningRate;
    this->maxIterations=maxIterations;

    //lol
    this->thisAlgorithmBecomingSkynetCost=999999999;

    //Init bias node.
    this->biasNode = new BiasNode();

    //Init input and output layers
    this->inputNodes = new vector<InputNode*>(numFeatures);
    this->outputNodes = new vector<OutputNode*>(numOutputs);

    //Build numLayers by layerSize Neural Grid
    for (int i = 0; i < this->inputNodes->size(); i++){
        (*(this->inputNodes))[i] = new InputNode(i);
    }
    for (int i = 0; i < this->outputNodes->size(); i++){
        (*(this->outputNodes))[i] = new OutputNode(i);
    }

    vector<Node*> lastLayer(layerSize);
    vector<Node*> currLayer(layerSize);
    for (int i = 0; i < numLayers; i++){
        for (int j = 0; j < layerSize; j++){
            currLayer[j] = new Node();
            if (i == 0){
                //First layer; link to inputnodes.
                for (int k = 0; k < this->inputNodes->size(); k++){
                    new Edge(*((*(this->inputNodes))[k]),*(currLayer[j]));
                }
            }else{
                //Link to last layer of nodes.
                for (int k = 0; k < lastLayer.size(); k++){
                    new Edge(*(lastLayer[k]),*(currLayer[j]));
                }
            }
            //Link to bias node.
            new Edge(*(this->biasNode),*(currLayer[j]));

        }
        lastLayer = currLayer;
    }
    //Link last layer of nodes to outputNodes
    for (int i = 0; i < this->outputNodes->size(); i++){
        for (int j = 0; j < layerSize; j++){
            new Edge(*(currLayer[j]),*((*(this->outputNodes))[i]));
        }
        new Edge(*(this->biasNode),*((*(this->outputNodes))[i]));
    }
}

NeuralGrid::~NeuralGrid(){
    delete(this->biasNode);

    queue<Node*> q;
    set<Node*> s;
    for (vector<OutputNode*>::iterator i = this->outputNodes->begin(); i != this->outputNodes->end(); i++){
        q.push(*i);
    }
    while (!q.empty()){
        Node* curr = q.front();
        q.pop();
        for (vector<Edge*>::iterator i = curr->incomingEdges->begin(); i != curr->incomingEdges->end(); i++){
            if (s.count(&((*i)->getSource()))==0){
                q.push(&((*i)->getSource()));
                s.insert(&((*i)->getSource()));
            }
        }
        delete(curr);
    }
}

vector<double>& NeuralGrid::evaluate(vector<double> inputVector){
    for (int i = 0; i < this->outputNodes->size(); i++){
        (*(this->outputNodes))[i]->clearCache();
    }

    vector<double>& out = *(new vector<double>(this->numOutputs));

    for (int i = 0; i < out.size(); i++){
        out[i]=(*(this->outputNodes))[i]->evaluate(inputVector);
    }

    return out;
}

void NeuralGrid::propogateError(vector<double> &label){
    for (int i = 0; i < this->inputNodes->size(); i++){
        (*(this->inputNodes))[i]->getError(label);
    }
}

void NeuralGrid::updateWeights(){
    for (int i = 0; i < this->inputNodes->size(); i++){
        (*(this->inputNodes))[i]->updateWeights(this->learningRate);
    }
}


void swapDatum(Datum &a, Datum &b){
    Datum tmp = a;
    a=b;
    b=tmp;
}
void randomizeTrainingDataArray(vector<Datum> &data){
    for (int i = data.size()-1; i >= 0; i--){
        int j = rand()%(i+1);
        swap(data[i],data[j]);
    }
}

void NeuralGrid::train(vector<Datum> &data){
    randomizeTrainingDataArray(data);
    for (int iterNum=0; iterNum < this->maxIterations;){
        int progressIncrement = maxIterations/20;
        for (int i = 0; i <data.size(); i++){
            (this->evaluate(data[i].features))[0];
            this->propogateError(data[i].label);
            this->updateWeights();
            iterNum++;
        }
        //pointless comment
    }
}
