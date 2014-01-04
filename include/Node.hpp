/**
 *
 * Implementation of a Node in a Neural Net. A Node handles the 
 * sigmoid transformation and the dot product, but does not encode 
 * the weights themselves.
 *
 * OutputNode extends Node and models a motor neruon; it returns the
 * returned value of the neural grid as an output of the computation.
 *
 * InputNode extend Node extends Node and models a sensory neuron;
 * it takes in the input features and processes them through the rest
 * of the net.
 *
 * BiasNode extends InputNode and adds a bias input to the neural net.
 *
 * @author Alex Chu
 *
 */

#ifndef NODE_H
#define NODE_H

#include <vector>


using namespace std;

class Edge;


class Node{

    public:

        friend class Edge;

        /**
         *
         * Constructs a Node.
         *
         */
        Node();

        /**
         *
         * Computes the dot product of the input vector
         * with the corresponding weights of this node's
         * incoming edges.
         * Then, applies the sigmoid transformation to 
         * the resulting value, and returns the output
         * float.
         *
         * @param a vector of feature float values.
         * @return the evaluation value
         *
         */
        virtual float evaluate(vector<float> &inputVector); 

        /**
         *
         * Gets the error generated by the last evaluation
         * of this node.
         *
         * @param the label value of the correct classification
         * @return the error value
         *
         */
        virtual float getError(vector<float> &label);

        /**
         * 
         * Updates the weights of the edges using the method of
         * gradient descent.
         *
         * @param epsilon the learning rate of the network in [0,1]
         *
         */
        virtual void updateWeights(float learningRate);

        /**
         *
         * Resets the error and output status of this node. Used 
         * between iterations of the backpropogation training 
         * algorithm.
         *
         */
        virtual void clearCache();

    protected:
        float sigmoid(float val);
        bool hasOutput;
        float lastOutput;
        vector<float> *lastInput;
        bool hasError;
        float error;
        vector<Edge*> *incomingEdges;
        vector<Edge*> *outgoingEdges;
};

class OutputNode : public Node{
    public:
        /**
         *
         * Constructs an OutputNode.
         *
         * @param index the index of the Inpt node's respective 
         *        output value.
         *
         */
        OutputNode(int index);

        /**
         *
         * Get error function for an OutputNode.
         *
         * @return the difference between the label corresponding
         *         to the last classified datum and the last output
         *         of this node.
         *
         */
        virtual float getError(vector<float> &label);

        /**
         *
         * Computes the output of this node, and stores it in the 
         * appropriate index of outVec.
         *
         * @param outVec a reference to a vector as least as long
         *        as the number of output nodes of the neural net.
         *
         */
        void getOutput(vector<float>& outVec){
        }
    private:
        int index;
};


class InputNode : public Node{
    public:

        /**
         *
         * Constructs an InputNode.
         *
         * @param index the index of the Input node's respective 
         *        feature value.
         *
         */
        InputNode(int index);

        /**
         *
         * Extracts the value of the input value from the inputVector
         * vector and passes it to the rest of the neural net.
         *
         * @param inputVector a reference to the input vector of 
         *        features
         * @return the value of this InputNode's respective feature
         *
         */
        virtual float evaluate(vector<float> &inputVector);

        /**
         *
         * Gets the error value of the node.
         * Always returns 0, becuase there are no dependencies.
         *
         * @param label the label of the correct classification of
         *        the data element.
         * @return 0.0
         *
         */
        virtual float getError(vector<float> &label);

        /**
         *
         * Updates the weights of the edges using the method of
         * gradient descent.
         *
         * @param epsilon the learning rate of the network in [0,1]
         *
         */
        virtual void updateWeights(float learningRate);

        /**
         *
         * Resets the error and output status of this node. Used 
         * between iterations of the backpropogation training 
         * algorithm.
         *
         */
        virtual void clearCache();

    protected:
        int index;
};

class BiasNode : public InputNode{
    public:
        /**
         *
         * Constructs a BiasNode.
         *
         */
        BiasNode();

        /**
         *
         * Evaluation function for the bias node; always returns
         * one.
         *
         * @param inputVector a reference to te vector of input 
         *        features
         * @return 1.0
         *
         */
        virtual float evaluate(vector<float> &inputVector);
};

#endif