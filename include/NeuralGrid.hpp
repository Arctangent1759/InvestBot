/**
 *
 * An implementation of a grid-structured Neural Net. The net has a 
 * set of input nodes equal to the number of features supplied by
 * the feature extractor.
 *
 * Inspired by and translated from the python implementation at 
 * http://jeremykun.com/2012/12/09/neural-networks-and-backpropagation/
 * and extended to support multiple output nodes.
 *
 * @author Alex Chu
 *
 */

#ifndef NEURALGRID_H
#define NEURALGRID_H

#include <vector>
#include <string>
#include "Node.hpp"
#include "Datum.hpp"

using namespace std;

class NeuralGrid{
    public:
        /**
         *
         * Constructs a layerSize by numLayers Neural Grid, along 
         * with input and output nodes.
         *
         * @param layerSize the number of neurons per layer of the 
         *        grid.
         * @param numLayers the number of layers between the input 
         *        and output layers
         * @param numFeatures the number of features supplied to the
         *        net by the feature extractor
         * @param numOutputs the number of outputs supplied by the
         *        neural net
         * @param learningRate the rate at which existing weights are
         *        changed as the network makes mistakes
         * @param maxIterations the number of passes the 
         *        backpropagation training algorithm passes over the
         *        data
         *
         */
        NeuralGrid(int layerSize, int numLayers, int numFeatures, int numOutputs, double learningRate, double maxIterations);

        /**
         *
         * Destructor for Neural Grids. Destroys the neural Grid
         * and its constituent Nodes and Edges.
         *
         */
        ~NeuralGrid();

        /**
         *
         * Evaluates an input vector and returns the corresponding 
         * output values.
         *
         * @param inputVector the vector of features provided by the
         *        feature extractor
         *
         */
        vector<double>& evaluate(vector<double> inputVector);

        /**
         *
         * Trains the Neural Grid based on the vector of data provided.
         *
         * @param data a reference to a vector of training data
         *
         */
        void train(vector<Datum> &data);

    private:
        Node *biasNode;
        void propogateError(vector<double> &label);
        void updateWeights();
        int layerSize;
        int numLayers;
        int numFeatures;
        int numOutputs;
        vector<InputNode*> *inputNodes;
        vector<OutputNode*> *outputNodes;
        double learningRate;
        double maxIterations;
};


#endif
