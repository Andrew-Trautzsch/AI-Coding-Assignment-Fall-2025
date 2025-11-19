#include "ann.hpp"

std::vector<double> ANN::forward(const std::vector<double>& input)
{
    std::vector<double> holder = input;

    for(int i=0; i<layers_.size(); i++)
    {
        holder = layers_[i].computeOutput(holder);
    }

    return holder;
}

void ANN::backPropagate()
{
    Layer& out = layers_.back();
    out.delta_.resize(out.output_.size());

    // delta for output layer
    for(int i=0; i<out.output_.size(); i++)
    {
        out.delta_[i] = (out.output_[i] - desiredOutput_[i]) * out.sigmoidPrime(out.saved_[i]);
    }

    // delta for other layers
    for(int i=layers_.size()-2; i>=0; i--)
    {
        Layer& current = layers_[i];
        Layer& next = layers_[i+1];

        current.delta_.resize(current.output_.size());

        for(int j=0; j<current.output_.size(); j++)
        {
            double sum = 0;

            for(int k=0; k<next.delta_.size(); k++)
            {
                sum += next.weights_[k][j] * next.delta_[k];
            }

            current.delta_[j] = sum * current.sigmoidPrime(current.saved_[j]);
        }
    }

    // update weights
    layers_[0].updateWeights(input_);

    for(int i=1; i<layers_.size(); i++)
        layers_[i].updateWeights(layers_[i-1].output_);
}