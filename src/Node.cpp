#include "Node.hpp"
#include "Edge.hpp"
#include <math.h>
#include <iostream>
#include <sstream>

/////////////////////////
// Node Implementation //
/////////////////////////

Node::Node(){
    this->lastOutput = 0.0;
    this->lastInput = new vector<double>();
    this->incomingEdges = new vector<Edge*>();
    this->outgoingEdges = new vector<Edge*>();
    this->error=0.0;
    this->hasError=false;
    this->hasOutput=false;
}

double Node::evaluate(vector<double> &inputVector){
    stringstream debugStr;
    if (this->hasOutput){
        return this->lastOutput;
    }

    this->hasOutput=true;
    double dotProd = 0.0;

    for (int i = 0; i < this->incomingEdges->size(); i++){
        double inputVal = (*(this->incomingEdges))[i]->getSource().evaluate(inputVector);
        (*(this->lastInput))[i]=inputVal;
        dotProd += (*(this->incomingEdges))[i]->getWeight() * inputVal;
        debugStr << (*(this->incomingEdges))[i]->getWeight() << " ";
    }
    this->lastOutput=this->sigmoid(dotProd);
    return this->lastOutput;
}

double Node::getError(vector<double> &label){
    if (this->hasError){
        return this->error;
    }

    this->hasError=true;
    this->error=0.0;

    for (int i = 0; i < this->outgoingEdges->size(); i++){
        this->error+=(*(this->outgoingEdges))[i]->getWeight() 
            * (*(this->outgoingEdges))[i]->getTarget().getError(label);
    }
    return this->error;
}

void Node::updateWeights(double learningRate){
    if (this->hasError && this->hasOutput){
        for (int i = 0; i < this->incomingEdges->size(); i++){
            (*(this->incomingEdges))[i]->weight += (learningRate 
                    * this->lastOutput * (1 - this->lastOutput) 
                    * this->error * (*(this->lastInput))[i]);
        }
        for (int i = 0; i < this->outgoingEdges->size(); i++){
            (*(this->outgoingEdges))[i]->getTarget().updateWeights(learningRate);
        }
        this->hasError=false;
        this->hasOutput=false;
    }
}

void Node::clearCache(){
    if (this->hasOutput){
        this->hasOutput=false;
        this->hasError=false;
        for (int i = 0; i < this->incomingEdges->size(); i++){
            (*(this->incomingEdges))[i]->getSource().clearCache();
        }
    }
}

double Node::sigmoid(double val){
    return 1/(1+exp(-val));
}

///////////////////////////////
// OutputNode Implementation //
///////////////////////////////

OutputNode::OutputNode(int index) : Node(){
    this->index=index;
}

double OutputNode::getError(vector<double> &label){
    if (this->hasError){
        return this->error;
    }
    this->hasError=true;
    this->error=label[this->index]-this->lastOutput;
    return this->error;
}

//////////////////////////////
// InputNode Implementation //
//////////////////////////////

InputNode::InputNode(int index) : Node(){
    this->index = index;
}

double InputNode::evaluate(vector<double> &inputVector){
    this->lastOutput=inputVector[this->index];
    return this->lastOutput;
}

double InputNode::getError(vector<double> &label){
    for (int i = 0; i < this->outgoingEdges->size(); i++){
        (*(this->outgoingEdges))[i]->getTarget().getError(label);
    }
    return 0.0;
}

void InputNode::updateWeights(double learningRate){
    for (int i = 0; i < this->outgoingEdges->size(); i++){
        (*(this->outgoingEdges))[i]->getTarget().updateWeights(learningRate);
    }
}

void InputNode::clearCache(){
    this->hasOutput=false;
    this->hasError=false;
}


/////////////////////////////
// BiasNode Implementation //
/////////////////////////////

BiasNode::BiasNode() : InputNode(-1){}

double BiasNode::evaluate(vector<double> &inputVector){
    return 1.0;
}
