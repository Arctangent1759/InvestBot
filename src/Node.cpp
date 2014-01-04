#include "Node.hpp"
#include "Edge.hpp"
#include <math.h>

/////////////////////////
// Node Implementation //
/////////////////////////

Node::Node(){
    this->lastOutput = 0.0;
    this->lastInput = new vector<float>();
    this->incomingEdges = new vector<Edge*>();
    this->outgoingEdges = new vector<Edge*>();
    this->error=0.0;
    this->hasError=false;
    this->hasOutput=false;
}

float Node::evaluate(vector<float> &inputVector){
    if (this->hasOutput){
        return this->lastOutput;
    }

    this->hasOutput=true;
    float dotProd = 0.0;

    for (int i = 0; i < this->incomingEdges->size(); i++){
        float inputVal = (*(this->incomingEdges))[i]->getSource().evaluate(inputVector);
        (*(this->lastInput))[i]=inputVal;
        dotProd += (*(this->incomingEdges))[i]->getWeight() * inputVal;
    }
    return (this->lastOutput=this->sigmoid(dotProd));
}

float Node::getError(vector<float> &label){
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

void Node::updateWeights(float learningRate){
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

float Node::sigmoid(float val){
    return 1/(1+exp(-val));
}

///////////////////////////////
// OutputNode Implementation //
///////////////////////////////

OutputNode::OutputNode(int index) : Node(){
    this->index=index;
}

float OutputNode::getError(vector<float> &label){
    return (this->error=label[this->index]-this->lastOutput);
}

//////////////////////////////
// InputNode Implementation //
//////////////////////////////

InputNode::InputNode(int index) : Node(){
    this->index = index;
}

float InputNode::evaluate(vector<float> &inputVector){
    return (this->lastOutput=inputVector[this->index]);
}

float InputNode::getError(vector<float> &label){
    for (int i = 0; i < this->outgoingEdges->size(); i++){
        (*(this->outgoingEdges))[i]->getTarget().getError(label);
    }
    return 0.0;
}

void InputNode::updateWeights(float learningRate){
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

float BiasNode::evaluate(vector<float> &inputVector){
    return 1.0;
}
