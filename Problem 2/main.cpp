#include "ann.hpp"

/*
learning rates and threshold are global consts in layer.cpp
lr = 0.03
threshold = 0.0
*/

int main(int argc, char* argv[])
{
    // default parameter
    int cycles = 100;
    if (argc >= 2) cycles = std::atoi(argv[1]);

    std::ifstream in("input.txt");
    if (!in.is_open())
    {
        std::cerr << "Could not open input.txt\n";
        return 1;
    }

    // read input output layer size
    int inputSize, outputSize;
    in >> inputSize >> outputSize;

    // read given input
    std::vector<double> input(inputSize);
    for (int i = 0; i < inputSize; i++)
        in >> input[i];

    // read given expected output
    std::vector<double> expected(outputSize);
    for (int i = 0; i < outputSize; i++)
        in >> expected[i];

    // read num of hidden layers
    int numHiddenLayers;
    in >> numHiddenLayers;

    // read hidden layer sizes
    std::vector<int> hiddenSizes(numHiddenLayers);
    for (int i = 0; i < numHiddenLayers; i++)
        in >> hiddenSizes[i];

    // read each hidden layer
    std::vector<Layer> layers;
    layers.reserve(numHiddenLayers + 1); // +1 for output layer

    int prevSize = inputSize;

    // load each hidden layer
    for (int L = 0; L < numHiddenLayers; L++)
    {
        int currSize = hiddenSizes[L];

        Layer layer;
        layer.weights_.resize(currSize, std::vector<double>(prevSize));
        layer.bias_.resize(currSize);

        // read weights
        for (int i = 0; i < currSize; i++)
            for (int j = 0; j < prevSize; j++)
                in >> layer.weights_[i][j];

        // read biases
        for (int i = 0; i < currSize; i++)
            in >> layer.bias_[i];

        layers.push_back(layer);

        prevSize = currSize;
    }

    // read output layer
    Layer outputLayer;
    outputLayer.weights_.resize(outputSize, std::vector<double>(prevSize));
    outputLayer.bias_.resize(outputSize);

    // read output layer weights
    for (int i = 0; i < outputSize; i++)
        for (int j = 0; j < prevSize; j++)
            in >> outputLayer.weights_[i][j];

    // read output layer bias
    for (int i = 0; i < outputSize; i++)
        in >> outputLayer.bias_[i];

    layers.push_back(outputLayer);

    in.close();



    ANN ann(input, expected, layers);

    std::filesystem::create_directory("output");

    // training cycles
    for (int c = 1; c <= cycles; c++)
    {
        std::vector<double> result = ann.forward(input);

        std::ofstream out("output/output" + std::to_string(c) + ".txt");

        out << "===== FORWARD PASS =====\n\n";
        for (int L = 0; L < ann.layers_.size(); L++)
        {
            out << "Layer " << L << ":\n";
            ann.layers_[L].printLayerInfo(ann.forwardInputs_[L], out);
            out << "\n";
        }

        out << "Network Output:\n  ";
        for (double v : result) out << v << " ";
        out << "\n\n";

        out << "===== BACKPROPAGATION =====\n\n";

        ann.backPropagate();

        for (int L = ann.layers_.size() - 1; L >= 0; L--)
        {
            out << "Layer " << L << " Error:\n";
            ann.layers_[L].printBackpropInfo(out);
            out << "\n";
        }

        out.close();
    }

    std::cout << "Training complete. See /output folder.\n";
    return 0;
}
