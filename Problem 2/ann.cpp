#include "ann.hpp"

std::vector<double> ANN::forward(const std::vector<double>& input)
{
    forwardInputs_.clear();
    forwardOutputs_.clear();

    std::vector<double> holder = input;

    for (int i = 0; i < layers_.size(); i++)
    {
        forwardInputs_.push_back(holder);
        holder = layers_[i].computeOutput(holder);
        forwardOutputs_.push_back(layers_[i].output_);
    }

    return holder;
}

void ANN::backPropagate()
{
    // Output layer delta
    Layer& outLayer = layers_.back();
    outLayer.delta_.resize(outLayer.output_.size());

    for (int i = 0; i < outLayer.output_.size(); i++)
    {
        double error = outLayer.output_[i] - desired_[i];
        outLayer.delta_[i] = error * outLayer.sigmoidPrime(outLayer.saved_[i]);
    }

    // Hidden layers
    for (int L = layers_.size() - 2; L >= 0; L--)
    {
        Layer& curr = layers_[L];
        Layer& next = layers_[L + 1];

        curr.delta_.resize(curr.output_.size());

        for (int i = 0; i < curr.output_.size(); i++)
        {
            double sum = 0.0;
            for (int j = 0; j < next.delta_.size(); j++)
                sum += next.weights_[j][i] * next.delta_[j];

            curr.delta_[i] = sum * curr.sigmoidPrime(curr.saved_[i]);
        }
    }

    // Weight updates
    layers_[0].updateWeights(input_);
    for (int L = 1; L < layers_.size(); L++)
        layers_[L].updateWeights(layers_[L - 1].output_);
}
