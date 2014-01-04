#include "Edge.hpp"
#include "Node.hpp"
#include "cstdlib"

Edge::Edge(Node& source, Node& target){
    this->source=&source;
    this->target=&target;
    this->weight=(rand()/RAND_MAX)*2-1;
    source.outgoingEdges->push_back(this);
    target.incomingEdges->push_back(this);
    target.lastInput->push_back(0.0);
}

float Edge::getWeight(){
    return this->weight;
}

Node& Edge::getSource(){
    return *(this->source);
}

Node& Edge::getTarget(){
    return *(this->target);
}

