#ifndef ANN_HPP
#define ANN_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

class Layer;

class ANN
{
public:
    ANN(const std::vector<double>&, const std::vector<double>&, const std::vector<Layer>&);

    std::vector<double> forward(const std::vector<double>&);
    void backPropagate();

private:
    float learningRate;
    std::vector<Layer> layers_;
    std::vector<double> input_;
    std::vector<double> desiredOutput_;
};

struct Layer
{
    std::vector<std::vector<double>> weights_;  // [n_curr][n_prev]
    std::vector<double> bias_;                  // [n_curr]
    std::vector<double> saved_;                 // pre-activation [n_curr]
    std::vector<double> output_;                // activation [n_curr]
    std::vector<double> delta_;                 // backprop error [n_curr]

    // forward pass for this layer
    std::vector<double> computeOutput(const std::vector<double>&);

    // derivative of activation
    double sigmoid(double input) {return 1.0 / (1.0 + std::exp(-input));}
    double sigmoidPrime(double input) {return (sigmoid(input) * (1-sigmoid(input)));}

    // weight update
    void updateWeights(const std::vector<double>&, double);
};

#endif // ANN_HPP