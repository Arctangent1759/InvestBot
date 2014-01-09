#include "Edge.hpp"
#include "Node.hpp"
#include <cstdlib>
#include <time.h>
#include <iostream>

bool random_seeded=false;

float getRandomWeight(){
    if (!random_seeded){
        srand(time(NULL));
        random_seeded=true;
    }
    float randVal = 0.0; //rand();
    return randVal/RAND_MAX;
}

Edge::Edge(Node& source, Node& target){
    this->source=&source;
    this->target=&target;
    this->weight=getRandomWeight();
    source.outgoingEdges->push_back(this);
    target.incomingEdges->push_back(this);
    target.lastInput->push_back(0.0);
}

double Edge::getWeight(){
    return this->weight;
}

Node& Edge::getSource(){
    return *(this->source);
}

Node& Edge::getTarget(){
    return *(this->target);
}


