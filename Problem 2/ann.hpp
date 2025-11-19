#ifndef ANN_HPP
#define ANN_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <string>

struct Layer
{
    std::vector<std::vector<double>> weights_; // neurons * inputs
    std::vector<double> bias_; // neurons
    std::vector<double> saved_; // saved pre-sigmoid actiavation for backprop
    std::vector<double> output_; // activation
    std::vector<double> delta_; // error term

    // forward
    std::vector<double> computeOutput(const std::vector<double>&);

    // backwards
    void updateWeights(const std::vector<double>&);

    // activation
    double sigmoid(double x) const { return 1.0 / (1.0 + std::exp(-x)); }
    double sigmoidPrime(double x) const { double s = sigmoid(x); return s * (1 - s); }

    // logging
    void printLayerInfo(const std::vector<double>&, std::ostream&) const;
    void printBackpropInfo(std::ostream&) const;
};

class ANN
{
public:
    ANN(const std::vector<double>& input, const std::vector<double>& desiredOutput, const std::vector<Layer>& layers)
    : input_(input), desired_(desiredOutput), layers_(layers) {}

    std::vector<double> forward(const std::vector<double>&);
    void backPropagate();

    std::vector<Layer> layers_; // all layers except input, as it is given

    // kept for logging
    std::vector<std::vector<double>> forwardInputs_;
    std::vector<std::vector<double>> forwardOutputs_;

private:
    std::vector<double> input_;
    std::vector<double> desired_;
};

#endif
