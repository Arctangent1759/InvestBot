#include "NeuralGrid.hpp"

class NeuralClassifier{
    public:
        /**
         *
         * Constructs a neural classfier.
         * @param layerSize the number of neurons in the layer
         * @param numLayers the number of layers
         * @param numFeatures the 
         * @param numOutputs
         *
         */
        NeuralClassifier(int layerSize, int numLayers, int numFeatures, int numOutputs);
    protected:
        NeuralGrid* myGrid;
};
