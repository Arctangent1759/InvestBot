#include <iostream>
#include <sstream>
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

void NeuralGrid::train(vector<Datum> &data){
    stringstream debugStr;
    cout << "Traning Neural Grid..." << endl;
    //cout << "<" << flush;
    cout << "Learning Rate : " << this->learningRate << endl;
    for (int iterNum=0; iterNum < this->maxIterations;){
        int progressIncrement = maxIterations/20;
        //cout << "--- Iteration " << iterNum << " ---" << endl;
        //this->toString();
        //cout << endl;
        for (int i = 0; i <data.size(); i++){
            /*debugStr << */(this->evaluate(data[i].features))[0] /*<< " "*/;
            cout << "=== DONE EVALUATING ===" << endl;
            this->propogateError(data[i].label);
            cout << "=== DONE PROPAGATING ===" << endl;
            this->updateWeights();
            cout << "=== DONE UPDATING ===" << endl;
            iterNum++;
        }
        //cout << endl << debugStr.str() << endl;
        //cout << endl << flush << endl;
    }
    //cout << ">" << endl;
}

void NeuralGrid::toString(){
    for (int i = 0; i < (*(this->inputNodes))[0]->outgoingEdges->size(); i++){
        cout << (*((*(this->inputNodes))[0]->outgoingEdges))[i]->getWeight() << " ";
    }
    cout << endl;
    for (int i = 0; i < (*(this->outputNodes))[0]->incomingEdges->size(); i++){
        cout << (*((*(this->outputNodes))[0]->incomingEdges))[i]->getWeight() << " ";
    }
    cout << endl;
}


