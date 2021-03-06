/**
 *
 * Wrapper class for Neural Grids. Abstracts away training and
 * hyperparameter tuning.
 *
 * @author Alex Chu
 *
 */

#ifndef NEURALCLASSIFIER_H
#define NEURALCLASSIFIER_H

#include "NeuralGrid.hpp"

class NeuralClassifier{
    public:
        /**
         *
         * Constructs and trains a neural classfier.
         *
         * @param layerSize the number of neurons in the layer
         * @param minLayers the minimum number of layers
         * @param maxLayers the maximum number of layers
         * @param learningRate the learning rate of the internal grid
         * @param iteratioons the number of iterations used to train the net
         * @param trainingData a vector of training data 
         *
         */
        NeuralClassifier(int layerSize, int minLayers, int maxLayers, 
                double llearningRate, int iterations, 
                vector<Datum> &trainingData);

        /**
         *
         * Constructs and trains a neural classfier.
         *
         * @param layerSize the number of neurons in the layer
         * @param maxLayers the maximum number of layers
         * @param learningRate the learning rate of the internal grid
         * @param iteratioons the number of iterations used to train the net
         * @param trainingData a vector of training data 
         *
         */
        NeuralClassifier(int layerSize, int maxLayers, 
                double learningRate, int iterations, 
                vector<Datum> &trainingData);

        /**
         *
         * Constructs a neural classifier from a saved neural grid 
         * file.
         *
         * @param filename the location of the neural grid save file.
         *
         */
        NeuralClassifier(string filename);

        /**
         *
         * Saves the data in the neural grid to the file located at
         * filename.
         *
         * @param filename the location of the file to save the 
         *        neural grid
         *
         */
        void save(string filename);

        /**
         *
         * Loads the data in the save file located at filename. 
         * Replaces the current grid with the loaded grid.
         *
         * @param filename the location of the neural grid save file.
         *
         */
        void load(string filename);

        /**
         *
         * Destroys a neural classifier
         *
         */
        ~NeuralClassifier();

        /**
         *
         * Returns the evaluation of a dataset.
         *
         * @param data the features of the input data
         *
         */
        vector<double>& evaluate(vector<double> &features);
        

    protected:
        NeuralGrid* myGrid;
    private:
        void init(int layerSize, int minLayers, 
                int maxLayers, double learningRate, int iterations,
                vector<Datum> &trainingData);
        double getAccuracy(NeuralGrid *grid, vector<Datum> &heldOutData);
};

#endif
